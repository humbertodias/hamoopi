# HAMOOPI Libretro Core

This directory contains the libretro port of HAMOOPI, allowing it to run on RetroArch and other libretro frontends.

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

## Controls

The libretro core maps standard RetroArch controller buttons to HAMOOPI controls:

### Player 1
- D-Pad: Movement
- A: Button 1
- B: Button 2
- Y: Button 3
- X: Button 4
- L: Button 5
- R: Button 6
- Select: Select
- Start: Start

### Player 2
- Same layout as Player 1

## Files

- `libretro.cpp` - Main libretro API implementation
- `hamoopi_core.cpp` - Bridge between libretro and HAMOOPI game logic
- `hamoopi_core.h` - Header file for core functions
- `libretro.h` - Official libretro API header
- `Makefile.libretro` - Build system for the libretro core
- `link.T` - Version script for symbol visibility (Linux)
- `hamoopi_libretro.info` - Core metadata file

## Current Status

This is an initial libretro port with basic functionality:
- ✅ Core builds successfully
- ✅ Video output working
- ✅ Input handling implemented
- ✅ Frame-based execution
- ⚠️ Game logic integration in progress
- ⚠️ Audio output not yet implemented
- ❌ Save states not implemented

## Development

The core currently displays a test pattern. To integrate the full HAMOOPI game:

1. Refactor HAMOOPI.cpp to separate initialization and frame logic
2. Implement proper state management for libretro
3. Add audio callback integration
4. Implement save state support (optional)

## License

The libretro core follows the same GPL v2 license as HAMOOPI.

## Contributing

Contributions are welcome! Please see the main HAMOOPI repository for contribution guidelines.
