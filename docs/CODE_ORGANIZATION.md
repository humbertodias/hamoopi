# HAMOOPI Code Organization

## Overview

The HAMOOPI codebase has been organized into a modular structure to improve maintainability and code clarity. The main game logic in `HAMOOPI.c` (11,439 lines) is being gradually extracted into separate module files.

## Module Structure

### Core Files

- **`HAMOOPI.c`** - Main game file (11,439 lines) - contains game loop, initialization, and most function implementations
- **`hamoopi_core.h`** - Central header that includes all modular components

### Implementation Modules

#### 1. `hamoopi_input.c` / `hamoopi_input.h`
**Status: Partially implemented (141 lines extracted)**

Extracted functions:
- `MovSlots_P1()` - Manage Player 1 input buffer (IMPLEMENTED)
- `MovSlots_P2()` - Manage Player 2 input buffer (IMPLEMENTED)
- `zeraListaDeInputs()` - Clear input list (IMPLEMENTED)

Remaining in HAMOOPI.c:
- `check_keys_P1()` - Process Player 1 input (286 lines)
- `check_keys_P2()` - Process Player 2 input (188 lines)

#### 2. `hamoopi_collision.c` / `hamoopi_collision.h`
**Status: Stub created, implementations remain in HAMOOPI.c**

Functions to be extracted:
- `Checar_Colisao()` - Check for collisions (~1357 lines)
- `Aplicar_HIT()` - Apply hit effects (~426 lines)
- `Draw_CHBoxes_P1()` - Draw P1 collision boxes (~101 lines)
- `Draw_CHBoxes_P2()` - Draw P2 collision boxes (~101 lines)
- `Draw_CHBoxes_ED()` - Draw Editor collision boxes (~107 lines)

#### 3. `hamoopi_player.c` / `hamoopi_player.h`
**Status: Stub created, implementations remain in HAMOOPI.c**

Functions to be extracted:
- `LOAD_PLAYERS()` - Load player data (~164 lines)
- `PLAYER_STATE()` - Change animation state (~463 lines)
- `AddTableAtlas()` - Add animation frame (~155 lines)
- `New_Fireball()` - Create projectile (~176 lines)
- `New_HitBox()` - Create hit boxes (~43 lines)

#### 4. `hamoopi_editor.c` / `hamoopi_editor.h`
**Status: Stub created, implementations remain in HAMOOPI.c**

Functions to be extracted:
- `ED_inicializar()` - Initialize editor (~135 lines)
- `ED_save_charini()` - Save configuration (~160 lines)
- `ED_load_charini()` - Load configuration (~282 lines)
- `ED_load_inputs()` - Load special inputs (~106 lines)

### Type Definition Files (No .c needed)

#### `hamoopi_types.h`
Defines all game structures:
- `struct HitSparkDEF` - Hit spark effect data
- `struct FireballsDEF` - Projectile data
- `struct PlayerDEF` - Complete player state and animation data

#### `hamoopi_globals.h`
Extern declarations for shared global variables
- `ED_load_inputs()` - Load special move inputs

## File Organization in HAMOOPI.c

The main file is organized into these sections (marked with `[**NN]` tags):

1. **[**01]** Initial Declarations - Constants, globals, and structure definitions
2. **[**02]** Allegro Initialization - Graphics and sound system setup
3. **[**03]** Game Loop - Main game logic and state management
4. **[**04]** Collision System - (integrated into game loop)
5. **[**05]** FSM (Finite State Machine) - Character state management
6. **[**06]** Difs - Parameter changes and modifications
7. **[**07]** Drawing Functions - Rendering logic
8. **[**08]** Debug - Debug visualization
9. **[**09]** Edit Mode - Character editor
10. **[**10]** Finalization - Cleanup and resource deallocation
11. **[**11]** Check Keys - Input processing functions (lines 7359-7943)
12. **[**12]** States (Chg) - State change functions (lines 7945+)

## Benefits of This Organization

1. **Improved Navigation** - Developers can quickly find function declarations by module
2. **Clear Responsibilities** - Each header file represents a logical subsystem
3. **Better Documentation** - Headers serve as API documentation
4. **Future Refactoring** - Provides a foundation for further code splitting if needed
5. **Minimal Changes** - All existing code continues to work without modification

## Usage

To include the modular structure in new files:

```c
#include "hamoopi_core.h"  // Includes all modules
```

Or include specific modules:

```c
#include "hamoopi_types.h"
#include "hamoopi_input.h"
// etc.
```

## Future Improvements

While the current organization improves code clarity through headers, future refactoring could:

1. Extract functions into separate `.c` files with proper extern declarations
2. Reduce global state by passing structures as parameters
3. Create a proper game engine API with initialization/update/render functions
4. Split the 11,748-line file into multiple implementation files

## Compilation

The modular structure doesn't affect compilation. The project continues to use:

- **CMake** for build configuration (see `CMakeLists.txt`)
- **Make** for simplified building (see `Makefile`)
- Supports both SDL2 and Allegro 4 backends

Build with:
```bash
make build
```

Or using CMake directly:
```bash
cmake -B build
cmake --build build
```
