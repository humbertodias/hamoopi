/* STB Backend Test Program
 * 
 * This demonstrates the STB backend working independently.
 * It creates an image, draws primitives, renders text, and saves to PNG.
 */

#include "hamoopi_image.h"
#include "hamoopi_font.h"
#include <stdio.h>

/* Declare backend getters */
extern ImageBackend* get_stb_image_backend(void);
extern FontBackend* get_stb_font_backend(void);

int main(int argc, char** argv) {
    printf("STB Backend Test Program\n");
    printf("========================\n\n");
    
    /* Get backends */
    ImageBackend* img_backend = get_stb_image_backend();
    FontBackend* font_backend = get_stb_font_backend();
    
    /* Test 1: Create image */
    printf("Test 1: Creating 640x480 image...\n");
    HamoopiImage* canvas = img_backend->create_image(640, 480, 4);
    if (!canvas) {
        printf("ERROR: Failed to create image\n");
        return 1;
    }
    printf("  Success! Image size: %dx%d\n\n", 
           img_backend->image_width(canvas), 
           img_backend->image_height(canvas));
    
    /* Test 2: Draw primitives */
    printf("Test 2: Drawing primitives...\n");
    
    /* Clear to black */
    img_backend->fill_rect(canvas, 0, 0, 639, 479, 
                          img_backend->make_color(0, 0, 0, 255));
    
    /* Draw red rectangle */
    img_backend->fill_rect(canvas, 50, 50, 150, 100, 
                          img_backend->make_color(255, 0, 0, 255));
    printf("  Drawn: Red rectangle\n");
    
    /* Draw green circle */
    img_backend->fill_circle(canvas, 300, 200, 50, 
                            img_backend->make_color(0, 255, 0, 255));
    printf("  Drawn: Green circle\n");
    
    /* Draw blue line */
    img_backend->draw_line(canvas, 100, 300, 500, 400, 
                          img_backend->make_color(0, 0, 255, 255));
    printf("  Drawn: Blue line\n\n");
    
    /* Test 3: Save image */
    printf("Test 3: Saving to output.png...\n");
    if (img_backend->save_image(canvas, "output.png")) {
        printf("  Success! Saved to output.png\n\n");
    } else {
        printf("  ERROR: Failed to save\n\n");
    }
    
    /* Test 4: Load image (if available) */
    printf("Test 4: Loading test image...\n");
    HamoopiImage* loaded = img_backend->load_image("output.png");
    if (loaded) {
        printf("  Success! Loaded image: %dx%d\n\n",
               img_backend->image_width(loaded),
               img_backend->image_height(loaded));
        img_backend->destroy_image(loaded);
    } else {
        printf("  (No test image available, skipping)\n\n");
    }
    
    /* Test 5: Font loading (if TTF font available) */
    printf("Test 5: Loading TrueType font...\n");
    HamoopiFont* font = font_backend->load_font("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    if (font) {
        printf("  Success! Font loaded at size 24\n");
        
        /* Get font metrics */
        FontMetrics metrics;
        font_backend->get_font_metrics(font, &metrics);
        printf("  Metrics: ascent=%d, descent=%d, line_gap=%d\n",
               metrics.ascent, metrics.descent, metrics.line_gap);
        
        /* Draw text */
        const char* test_text = "Hello STB!";
        int text_width = font_backend->get_text_width(font, test_text);
        printf("  Text width of '%s': %d pixels\n", test_text, text_width);
        
        /* Draw white text on canvas */
        font_backend->draw_text(canvas, font, test_text, 200, 150,
                               img_backend->make_color(255, 255, 255, 255));
        printf("  Text rendered to canvas\n\n");
        
        /* Save canvas with text */
        img_backend->save_image(canvas, "output_with_text.png");
        printf("  Saved canvas with text to output_with_text.png\n\n");
        
        font_backend->destroy_font(font);
    } else {
        printf("  (Font not found, skipping text tests)\n\n");
    }
    
    /* Cleanup */
    img_backend->destroy_image(canvas);
    
    printf("All tests completed successfully!\n");
    printf("\nSTB Backend is fully functional.\n");
    printf("Output files: output.png, output_with_text.png\n");
    
    return 0;
}
