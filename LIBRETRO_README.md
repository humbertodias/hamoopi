# HAMOOPI Libretro Core

This directory contains the libretro port of HAMOOPI, allowing it to run on RetroArch and other libretro frontends.

## Features

The libretro core includes:
- ✅ Full 2-player fighting game implementation
- ✅ Physics-based movement (walking, jumping)
- ✅ Combat system with health tracking
- ✅ Real-time gameplay at 60 FPS
- ✅ Title screen and winner announcement
- ✅ Controller/keyboard support for both players

## Building the Libretro Core

### Prerequisites

- GCC/G++ compiler
- Allegro 4 development libraries (`liballegro4-dev` on Debian/Ubuntu)
- Make

### Build Instructions

```bash
make -f Makefile.libretro
```

This will produce `hamoopi_libretro.so` (on Linux), `hamoopi_libretro.dylib` (on macOS), or `hamoopi_libretro.dll` (on Windows).

### Platform-Specific Builds

**Linux:**
```bash
make -f Makefile.libretro platform=unix
```

**macOS:**
```bash
make -f Makefile.libretro platform=osx
```

**Windows (MinGW):**
```bash
make -f Makefile.libretro platform=win
```

## Installing the Core

1. Build the core as described above
2. Copy `hamoopi_libretro.so` to your RetroArch cores directory:
   - Linux: `~/.config/retroarch/cores/`
   - Windows: `retroarch/cores/`
   - macOS: `~/Library/Application Support/RetroArch/cores/`
3. Copy `hamoopi_libretro.info` to your RetroArch info directory:
   - Linux: `~/.config/retroarch/info/`
   - Windows: `retroarch/info/`
   - macOS: `~/Library/Application Support/RetroArch/info/`

## Using the Core

1. Launch RetroArch
2. Go to "Load Core" and select "HAMOOPI"
3. Since HAMOOPI doesn't require content files, you can start it directly from "Start Core"
4. Press START to begin fighting!

## Controls

The libretro core maps standard RetroArch controller buttons to HAMOOPI controls:

### Player 1
- **D-Pad**: Movement (Left/Right = Walk, Up = Jump)
- **A Button**: Punch attack
- **B Button**: (Reserved)
- **Y Button**: (Reserved)
- **X Button**: (Reserved)
- **L Button**: (Reserved)
- **R Button**: (Reserved)
- **Start**: Begin game / Rematch

### Player 2
- Same layout as Player 1

## Gameplay

- **Title Screen**: Press START to begin
- **Fight**: Move with D-pad, jump with UP, attack with A button
- **Objective**: Reduce opponent's health to zero
- **Winner Screen**: Press START for rematch

Each player starts with 100 HP. Land attacks to damage your opponent!

## Files

- `libretro.cpp` - Main libretro API implementation
- `hamoopi_core.cpp` - Fighting game logic and bridge between libretro and game engine
- `hamoopi_core.h` - Header file for core functions
- `libretro.h` - Official libretro API header
- `Makefile.libretro` - Build system for the libretro core
- `link.T` - Version script for symbol visibility (Linux)
- `hamoopi_libretro.info` - Core metadata file

## Current Status

This is a fully functional libretro fighting game:
- ✅ Core builds successfully (27KB)
- ✅ Video output working (640x480 @ 60fps)
- ✅ Input handling implemented (2 players)
- ✅ Frame-based execution
- ✅ **Game logic fully integrated**
- ✅ **Physics engine (gravity, movement, collision)**
- ✅ **Combat system with health management**
- ✅ **Game states (title, fight, winner)**
- ⚠️ Audio output not yet implemented
- ❌ Save states not implemented
- ⚠️ Full HAMOOPI character system pending (using simple sprites for now)

## Technical Details

The core implements a complete fighting game with:
- **Physics System**: Gravity-based movement, ground collision detection
- **Combat Mechanics**: Attack range detection, health tracking
- **Game Flow**: Title screen → Fight → Winner → Rematch
- **Real-time Rendering**: Direct Allegro rendering at 60 FPS
- **Input Processing**: Frame-accurate controller input via libretro API

## Development Notes

The current implementation uses simplified sprite rendering (rectangles and circles) to demonstrate the fighting game mechanics. The architecture supports extending to full HAMOOPI character sprites and animations by integrating the original game's asset loading and rendering systems.

## License

The libretro core follows the same GPL v2 license as HAMOOPI.

## Contributing

Contributions are welcome! Please see the main HAMOOPI repository for contribution guidelines.
