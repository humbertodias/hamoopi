# HAMOOPI Backend Abstraction Layer

## Overview

This document describes the backend abstraction layer that decouples HAMOOPI from the Allegro library, making the engine agnostic to the underlying graphics/input/audio library.

## Architecture

The abstraction layer consists of the following components:

### 1. Backend Interfaces (Abstract Classes)

- **`graphics_backend.h`**: Defines the interface for graphics operations (rendering, bitmap operations, text, etc.)
- **`input_backend.h`**: Defines the interface for input handling (keyboard, mouse, joystick)
- **`audio_backend.h`**: Defines the interface for audio operations (samples, MIDI music)
- **`system_backend.h`**: Defines the interface for system operations (timing, file I/O, configuration)

### 2. Allegro Implementation

- **`allegro_graphics_backend.h`**: Implements GraphicsBackend using Allegro 4
- **`allegro_input_backend.h`**: Implements InputBackend using Allegro 4
- **`allegro_audio_backend.h`**: Implements AudioBackend using Allegro 4
- **`allegro_system_backend.h`**: Implements SystemBackend using Allegro 4

### 3. Backend Manager

- **`backend_manager.h`**: Singleton class that manages all backend instances and provides a unified access point

### 4. Compatibility Layer

- **`hamoopi_wrapper.h`**: Provides wrapper functions that maintain compatibility with existing code while using the backend abstraction
- **`backend_init.cpp`**: Initializes the backend system with Allegro implementations

## Benefits

1. **Library Independence**: The game engine is no longer tightly coupled to Allegro
2. **Portability**: Easy to port to other libraries (SDL2, Raylib, etc.) by implementing the backend interfaces
3. **Testability**: Can create mock backends for unit testing
4. **Maintainability**: Clear separation between engine logic and platform-specific code
5. **Flexibility**: Can switch backends at runtime if needed

## Migration Strategy

The migration from direct Allegro calls to the abstraction layer can be done gradually:

### Phase 1: Initial Setup (Current)
- Create backend interfaces
- Implement Allegro backends
- Add compatibility wrappers

### Phase 2: Gradual Migration (Future)
Replace direct Allegro calls with wrapper functions:

```cpp
// Before (direct Allegro call):
BITMAP* bmp = create_bitmap(640, 480);

// After (using wrapper):
BITMAP* bmp = wrapper_create_bitmap(640, 480);

// Or eventually (using backend directly):
GraphicsBitmap bmp = g_backend->getGraphics()->create_bitmap(640, 480);
```

### Phase 3: Complete Decoupling (Future)
- Remove all direct Allegro includes from game logic
- Move all Allegro-specific code to backend implementations
- Game engine becomes completely library-agnostic

## Usage Example

### Initializing the Backends

```cpp
#include "backend_init.cpp"

int main() {
    // Initialize backends
    init_backends();
    
    // Use backends through wrapper or directly
    GraphicsBackend* gfx = g_backend->getGraphics();
    gfx->set_graphics_mode(false, 640, 480);
    
    // ... game code ...
    
    // Cleanup
    shutdown_backends();
    return 0;
}
```

### Creating an Alternative Backend

To support a different library (e.g., SDL2), implement the backend interfaces:

```cpp
#include "graphics_backend.h"
#include <SDL2/SDL.h>

class SDLGraphicsBackend : public GraphicsBackend {
public:
    bool init() override {
        return SDL_Init(SDL_INIT_VIDEO) == 0;
    }
    
    GraphicsBitmap create_bitmap(int width, int height) override {
        SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
        return surface;
    }
    
    // ... implement other methods ...
};
```

Then register it:

```cpp
g_backend->setGraphicsBackend(new SDLGraphicsBackend());
```

## File Structure

```
src/
├── graphics_backend.h          # Graphics interface
├── input_backend.h             # Input interface
├── audio_backend.h             # Audio interface
├── system_backend.h            # System interface
├── backend_manager.h           # Backend manager
├── allegro_graphics_backend.h  # Allegro graphics implementation
├── allegro_input_backend.h     # Allegro input implementation
├── allegro_audio_backend.h     # Allegro audio implementation
├── allegro_system_backend.h    # Allegro system implementation
├── hamoopi_wrapper.h           # Compatibility wrappers
├── backend_init.cpp            # Backend initialization
└── HAMOOPI.cpp                 # Main game code
```

## Future Enhancements

1. **Shader Support**: Add shader abstraction to graphics backend
2. **Network Backend**: Add networking abstraction for multiplayer
3. **Controller Support**: Enhanced gamepad/controller abstraction
4. **Asset Loading**: Abstract asset loading pipeline
5. **Rendering Pipeline**: Create a high-level rendering pipeline abstraction

## Notes

- The current implementation maintains full backward compatibility with existing Allegro code
- No changes to game logic are required to use the abstraction layer
- The abstraction can be adopted gradually without breaking existing functionality
- Performance overhead is minimal (mostly inline function calls)

## Contributing

When adding new features:
1. Define the interface in the appropriate backend header
2. Implement it in the Allegro backend
3. Add a wrapper function if needed for compatibility
4. Document any new abstractions

## License

This abstraction layer follows the same GPL v2 license as the main HAMOOPI project.
