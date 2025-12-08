# HAMOOPI Libretro Core

This directory contains the libretro core implementation for HAMOOPI, allowing it to run in RetroArch and other libretro-compatible frontends.

## Building

### Using Makefile (Recommended)

```bash
make -f Makefile.libretro
```

This will create `hamoopi_libretro.so` (or `.dylib` on macOS, `.dll` on Windows).

### Using CMake

```bash
mkdir build
cd build
cmake -DUSE_LIBRETRO=ON ..
make
```

### Platform-specific builds

For Linux:
```bash
make -f Makefile.libretro platform=unix
```

For Windows (MinGW):
```bash
make -f Makefile.libretro platform=mingw
```

For macOS:
```bash
make -f Makefile.libretro platform=osx
```

For Android:
```bash
make -f Makefile.libretro platform=android
```

## Installation

### Manual Installation

1. Copy `hamoopi_libretro.so` to your RetroArch cores directory:
   - Linux: `~/.config/retroarch/cores/`
   - Windows: `RetroArch/cores/`
   - macOS: `~/Library/Application Support/RetroArch/cores/`

2. Copy `hamoopi_libretro.info` to your RetroArch info directory:
   - Linux: `~/.config/retroarch/cores/`
   - Windows: `RetroArch/info/`
   - macOS: `~/Library/Application Support/RetroArch/info/`

3. Copy the `data/` folder to the same directory where you'll run RetroArch, or place it in the system directory.

### Quick Install (Linux only)

```bash
make -f Makefile.libretro install
```

## Running

1. Open RetroArch
2. Go to "Load Core" and select "HAMOOPI"
3. Select "Start Core" (no content needed - the game runs standalone)
4. Enjoy!

## Controls

The libretro core maps controls as follows:

### Joypad
- D-Pad: Movement (Up/Down/Left/Right)
- Button A: Kick (C)
- Button B: Punch (Z)
- Button X: Punch (A)
- Button Y: Punch (X)
- L Button: Kick (S)
- R Button: Kick (D)
- Start: Player 1 Start
- Select: Coin

### Keyboard
- Arrow Keys: Movement
- Z, X, C: Punches
- A, S, D: Kicks
- Enter: Confirm/Start
- Escape: Back/Exit
- F1, F2, F3: Debug functions

## Technical Details

The libretro implementation provides:
- Video output: 640x480 @ 60 FPS, XRGB8888 format
- Audio output: 44100 Hz stereo
- Input: Keyboard and joypad support
- No save state support (currently)
- No content loading required (standalone game)

## Implementation Notes

The libretro core uses the platform abstraction layer in `platform_libretro.c`, which implements:
- Graphics rendering to a framebuffer
- Input polling from libretro frontend
- Timer callbacks for game logic
- Stub implementations for audio (TODO)
- Config file handling (TODO)

## TODO

- [ ] Implement audio playback
- [ ] Add save state support
- [ ] Implement config file persistence
- [ ] Add content loading for custom characters/stages
- [ ] Implement text rendering
- [ ] Add sprite flipping and rotation
- [ ] Improve image loading (currently stubs)

## License

HAMOOPI is licensed under GPL v2. See the LICENSE file in the root directory.

## Credits

- Original Engine: Daniel Moura (dev@hamoopi.com)
- Libretro Core: Implemented as part of platform abstraction layer
