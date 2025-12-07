# Building HAMOOPI with STB Backend

## Overview

HAMOOPI now supports two graphics backends:
1. **Allegro 4** (default) - Original backend
2. **STB Libraries** (optional) - Modern, dependency-free backend

## Prerequisites

### For Allegro Backend (Default)
```bash
sudo apt-get install liballegro4-dev
```

### For STB Backend
No external dependencies required! STB libraries are included as single-header files.

## Building with Allegro Backend (Default)

```bash
mkdir build
cd build
cmake ..
make
```

## Building with STB Backend

```bash
mkdir build-stb
cd build-stb
cmake -DUSE_STB_BACKEND=ON ..
make
```

## Comparison

| Feature | Allegro Backend | STB Backend |
|---------|----------------|-------------|
| **Dependencies** | liballegro4-dev | None |
| **Binary Size** | ~564KB | ~565KB |
| **Image Formats** | PCX, BMP | PNG, JPG, BMP, TGA |
| **Font Support** | Bitmap fonts (.pcx) | TrueType (.ttf) |
| **Portability** | Linux, Windows | Universal |
| **Performance** | Hardware accelerated | Software rendering |

## Testing STB Backend

### Test Program
```bash
cd src
make -f Makefile.stb test
# View output.png and output_with_text.png
```

### Full Game
```bash
mkdir build-stb
cd build-stb
cmake -DUSE_STB_BACKEND=ON ..
make
./HAMOOPI
```

## Known Differences

### Image Loading
- **Allegro**: Loads .pcx files
- **STB**: Loads .png, .jpg, .bmp, .tga

**Migration**: Convert game assets to PNG format:
```bash
for f in *.pcx; do convert "$f" "${f%.pcx}.png"; done
```

### Font Rendering
- **Allegro**: Uses bitmap fonts (.pcx format)
- **STB**: Uses TrueType fonts (.ttf format)

**Migration**: Use TrueType fonts instead of bitmap fonts:
```c
// Old (Allegro):
FONT* font = load_font("font.pcx", NULL, NULL);

// New (STB):
FONT* font = load_font("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", NULL, NULL);
```

### Timing and Input
STB backend provides basic timing and input stubs. For full game functionality, additional implementation may be needed for:
- Keyboard input handling
- Mouse input handling
- Timer/vsync handling
- Audio playback

## Architecture

### Type Compatibility
The STB backend provides full binary compatibility with Allegro BITMAP types:

```c
// Both backends support:
BITMAP* img = create_bitmap(640, 480);
int width = img->w;   // Direct field access works!
int height = img->h;  // Direct field access works!
```

### Backend Selection
Selection happens at compile time via CMake option. The same source code compiles with either backend thanks to:
- `backend_types.h` - Provides type definitions
- `stb_backend_init.c` - Implements Allegro-compatible functions
- `stb_backend_full.c` - Core STB implementation

## Advantages of STB Backend

1. **Zero Dependencies**: No external libraries required
2. **Modern Formats**: PNG and JPG support out of the box
3. **TrueType Fonts**: Better text rendering quality
4. **Public Domain**: No licensing concerns
5. **Portable**: Works on any platform with C compiler
6. **Single Header**: Easy to integrate and maintain

## Current Status

- ✅ Core graphics operations working
- ✅ Image loading/saving (PNG, JPG, BMP, TGA)
- ✅ Drawing primitives (lines, rectangles, circles)
- ✅ TrueType font rendering
- ✅ BITMAP field compatibility (->w, ->h access)
- ⚠️ Input handling (basic stubs, needs implementation)
- ⚠️ Audio (basic stubs, needs implementation)
- ⚠️ Timing (basic stubs, needs implementation)

## Future Work

For production use with STB backend, implement:
1. Platform-specific window creation (SDL2, GLFW, or native)
2. Event loop and input handling
3. Audio playback (OpenAL, SDL_mixer, or platform native)
4. VSync/timing mechanisms

Alternatively, use STB backend for:
- Offline rendering/processing
- Headless testing
- Asset conversion tools
- Screenshot generation

## Example: Building and Running

```bash
# Build with Allegro (default)
mkdir build && cd build
cmake .. && make
./HAMOOPI

# Build with STB
mkdir build-stb && cd build-stb
cmake -DUSE_STB_BACKEND=ON .. && make
./HAMOOPI

# Test STB backend independently
cd src
make -f Makefile.stb test
ls -lh output*.png
```

## Troubleshooting

### "undefined reference to stb functions"
Make sure stb_backend_full.c is being compiled and linked.

### "BITMAP has no member named 'w'"
Make sure you're including `backend_types.h` or that USE_STB_BACKEND is defined.

### Segfault on startup
Check that image/font backends are initialized before use. Call `allegro_init()` first.

### Black screen or no output
STB backend does software rendering. Make sure to call `set_gfx_mode()` to create screen buffer.

## Support

For issues or questions:
1. Check `PHASE2_COMPLETE.md` for implementation details
2. Review `docs/PHASE2_INTEGRATION.md` for integration guide
3. Examine `src/stb_backend_test.c` for usage examples
