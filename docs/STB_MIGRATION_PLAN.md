# Migration to STB Libraries - Phase 2 Plan

## Current State
- HAMOOPI.c: 11,733 lines using BITMAP*, FONT*, SAMPLE*, MIDI* types directly
- Backend abstraction in pure C with function pointers
- Types come from Allegro library

## Requested Change
Replace Allegro types (BITMAP, FONT) with STB library equivalents:
- stb_image for image loading
- stb_image_write for image saving
- stb_truetype for font rendering

## Challenge
This requires changing every single reference to BITMAP* and FONT* throughout HAMOOPI.c:
- ~500+ BITMAP* declarations and usages
- ~50+ FONT* declarations and usages
- ~2000+ function calls using these types
- All struct members that store these pointers

## Proposed Approach

### Phase 2a: Define Abstract Types
Create abstract types that can wrap either Allegro or STB implementations:

```c
// hamoopi_image.h
typedef struct HamoopiImage HamoopiImage;
typedef struct HamoopiFont HamoopiFont;

typedef struct {
    int width;
    int height;
    int channels;
    unsigned char* pixels;
} ImageData;

// Backend can implement with either Allegro BITMAP or STB
```

### Phase 2b: Create STB Backend
Implement graphics backend using STB libraries:

```c
// stb_graphics_backend.c
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

HamoopiImage* stb_load_image(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 4);
    // ... create HamoopiImage wrapper
}
```

### Phase 2c: Gradual Migration
Replace BITMAP* with HamoopiImage* throughout HAMOOPI.c:
- This would require changing ~11,000 lines
- Need to update every function signature
- Update every struct definition
- Update every function call

## Estimated Effort
- Phase 2a (Abstract types): 2-3 hours
- Phase 2b (STB backend): 8-10 hours  
- Phase 2c (Migrate HAMOOPI.c): 20-30 hours
- **Total: 30-43 hours of development work**

## Recommendation
The current pure C backend with Allegro types is a solid foundation. Migration to STB should be a separate, dedicated effort given the scope.

**Alternative Incremental Approach:**
1. Keep current Allegro-based backend as default
2. Create parallel STB-based backend
3. Add compile-time flag to choose backend
4. Gradually migrate code sections to use abstract types
5. Eventually deprecate Allegro backend

This allows:
- Working code at every stage
- Ability to test both backends
- Incremental migration
- Less risk of breaking everything

## Files Needed for STB Migration

### STB Headers (single-file public domain libraries)
- `stb_image.h` - Image loading (PNG, JPG, BMP, TGA, etc.)
- `stb_image_write.h` - Image saving
- `stb_truetype.h` - TrueType font rendering
- `stb_rect_pack.h` - Rectangle packing for font atlases

### New Backend Files
- `hamoopi_image.h` - Abstract image type
- `hamoopi_font.h` - Abstract font type  
- `stb_graphics_backend.c` - STB implementation
- `stb_graphics_backend.h` - STB backend header

### Modified Files
- Every file that uses BITMAP* or FONT*
- All function signatures
- All struct definitions
- CMakeLists.txt

## Conclusion
This is Phase 2 work that requires significant refactoring. Current state (pure C with Allegro types) is complete and functional.
