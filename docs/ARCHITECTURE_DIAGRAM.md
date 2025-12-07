# HAMOOPI Backend Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────────┐
│                          HAMOOPI Game Engine                         │
│                         (Game Logic Layer)                           │
│                                                                       │
│  ┌───────────┐  ┌──────────┐  ┌────────┐  ┌──────────────┐        │
│  │ Player    │  │ Collision│  │ FSM    │  │ Editor       │        │
│  │ System    │  │ Detection│  │ Logic  │  │ Mode         │        │
│  └───────────┘  └──────────┘  └────────┘  └──────────────┘        │
│         │              │            │              │                 │
└─────────┼──────────────┼────────────┼──────────────┼─────────────────┘
          │              │            │              │
          └──────────────┴────────────┴──────────────┘
                         │
┌────────────────────────▼────────────────────────────────────────────┐
│                   Backend Manager (Singleton)                        │
│                                                                       │
│  ┌────────────┐  ┌───────────┐  ┌────────────┐  ┌──────────────┐  │
│  │ Graphics   │  │   Input   │  │   Audio    │  │   System     │  │
│  │  Backend   │  │  Backend  │  │  Backend   │  │   Backend    │  │
│  │ Interface  │  │ Interface │  │ Interface  │  │  Interface   │  │
│  └─────┬──────┘  └─────┬─────┘  └─────┬──────┘  └──────┬───────┘  │
└────────┼───────────────┼───────────────┼─────────────────┼──────────┘
         │               │               │                 │
         │ (implements)  │ (implements)  │ (implements)    │ (implements)
         │               │               │                 │
┌────────▼───────┬───────▼───────┬───────▼──────┬──────────▼──────────┐
│                │               │              │                      │
│  ┌──────────┐  │  ┌─────────┐  │  ┌────────┐  │  ┌──────────────┐  │
│  │ Allegro  │  │  │ Allegro │  │  │Allegro │  │  │   Allegro    │  │
│  │ Graphics │  │  │  Input  │  │  │ Audio  │  │  │   System     │  │
│  │ Backend  │  │  │ Backend │  │  │Backend │  │  │   Backend    │  │
│  └─────┬────┘  │  └────┬────┘  │  └───┬────┘  │  └──────┬───────┘  │
│        │       │       │       │      │       │         │          │
│  ┌─────▼────┐  │  ┌────▼────┐  │  ┌───▼────┐  │  ┌──────▼───────┐  │
│  │ Allegro  │  │  │ Allegro │  │  │Allegro │  │  │   Allegro    │  │
│  │ Library  │  │  │ Library │  │  │Library │  │  │   Library    │  │
│  │   4.x    │  │  │   4.x   │  │  │  4.x   │  │  │     4.x      │  │
│  └──────────┘  │  └─────────┘  │  └────────┘  │  └──────────────┘  │
│                │               │              │                      │
└────────────────┴───────────────┴──────────────┴──────────────────────┘
     Graphics          Input          Audio           System
     Backend          Backend        Backend          Backend
  (Alternative implementations possible: SDL2, Raylib, etc.)


Key Components:
═══════════════

┌──────────────────────────────────────────────────────────────┐
│ Compatibility Layer (Optional)                                │
│ ┌──────────────────────────────────────────────────────────┐ │
│ │ hamoopi_wrapper.h - Provides wrapper functions           │ │
│ │ Allows gradual migration from direct Allegro calls       │ │
│ └──────────────────────────────────────────────────────────┘ │
└──────────────────────────────────────────────────────────────┘


Data Flow Example:
══════════════════

Game wants to draw a sprite:
  1. Game calls: draw_sprite(dest, sprite, x, y)
  2. Routed to: BackendManager::getGraphics()
  3. Calls: AllegroGraphicsBackend::draw_sprite()
  4. Executes: Allegro's ::draw_sprite() function
  5. Result: Sprite drawn to screen

Alternative backend (e.g., SDL2):
  1. Game calls: draw_sprite(dest, sprite, x, y)  [SAME]
  2. Routed to: BackendManager::getGraphics()     [SAME]
  3. Calls: SDLGraphicsBackend::draw_sprite()     [DIFFERENT]
  4. Executes: SDL_RenderCopy() function          [DIFFERENT]
  5. Result: Sprite drawn to screen               [SAME]


Benefits of This Architecture:
═══════════════════════════════

✓ Separation of Concerns
  - Game logic independent of rendering library
  - Easy to understand and maintain

✓ Flexibility
  - Swap backends at initialization
  - Can have multiple backends (e.g., for different platforms)

✓ Testability
  - Create mock backends for unit tests
  - Test game logic without graphics

✓ Portability
  - Port to new libraries without changing game code
  - Target different platforms easily

✓ Extensibility
  - Add new features to backends without affecting game logic
  - Gradual migration path


Future Possible Backends:
═════════════════════════

┌──────────────┐  ┌──────────────┐  ┌──────────────┐
│     SDL2     │  │   Raylib     │  │     SFML     │
│   Backend    │  │   Backend    │  │   Backend    │
└──────────────┘  └──────────────┘  └──────────────┘

┌──────────────┐  ┌──────────────┐  ┌──────────────┐
│   OpenGL     │  │    Vulkan    │  │    WebGL     │
│   Backend    │  │   Backend    │  │   Backend    │
└──────────────┘  └──────────────┘  └──────────────┘
```

## Interface Contracts

Each backend interface defines a contract that implementations must fulfill:

### GraphicsBackend
- Bitmap management (create, load, destroy)
- Drawing operations (sprite, rect, circle, line)
- Text rendering
- Color operations
- Screen management

### InputBackend
- Keyboard state checking
- Mouse position and buttons
- Joystick support

### AudioBackend
- Sample loading and playback
- MIDI music support
- Volume control

### SystemBackend
- Timing and delays
- File I/O and configuration
- Message dialogs
- UTF-8 support

This architecture ensures that HAMOOPI can evolve and adapt to new technologies while maintaining its core functionality.
