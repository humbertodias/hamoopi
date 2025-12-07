/* STB Backend Initialization
 * 
 * This module initializes the STB backend and provides Allegro-compatible global variables.
 */

#ifdef USE_STB_BACKEND

#include "backend_types.h"
#include "hamoopi_image.h"
#include "hamoopi_font.h"
#include <stdlib.h>
#include <string.h>

/* Forward declare STB backend functions */
extern ImageBackend* get_stb_image_backend(void);
extern FontBackend* get_stb_font_backend(void);

/* Global variables (Allegro compatibility) */
int SCREEN_W = 0;
int SCREEN_H = 0;
BITMAP* screen = NULL;
volatile int mouse_x = 0;
volatile int mouse_y = 0;
volatile int mouse_b = 0;
volatile int key[128] = {0};

/* Backend pointers */
static ImageBackend* img_backend = NULL;
static FontBackend* font_backend = NULL;

/* Color functions */
int makecol(int r, int g, int b) {
    if (!img_backend) img_backend = get_stb_image_backend();
    return img_backend->make_color(r, g, b, 255);
}

int makeacol(int r, int g, int b, int a) {
    if (!img_backend) img_backend = get_stb_image_backend();
    return img_backend->make_color(r, g, b, a);
}

int getr(int color) {
    return (color >> 16) & 0xFF;
}

int getg(int color) {
    return (color >> 8) & 0xFF;
}

int getb(int color) {
    return color & 0xFF;
}

int geta(int color) {
    return (color >> 24) & 0xFF;
}

/* Graphics mode setup */
int set_gfx_mode(int card, int w, int h, int v_w, int v_h) {
    if (!img_backend) img_backend = get_stb_image_backend();
    
    /* Create screen buffer */
    if (screen) {
        img_backend->destroy_image((HamoopiImage*)screen);
    }
    
    screen = (BITMAP*)img_backend->create_image(w, h, 4);
    if (!screen) return -1;
    
    SCREEN_W = w;
    SCREEN_H = h;
    
    return 0;
}

/* Allegro initialization (no-op for STB) */
int allegro_init(void) {
    img_backend = get_stb_image_backend();
    font_backend = get_stb_font_backend();
    return 0;
}

int install_timer(void) { return 0; }
int install_keyboard(void) { return 0; }
int install_mouse(void) { return 0; }
int install_sound(int digi, int midi, const char* cfg) { return 0; }

void set_color_depth(int depth) {}
void set_palette(const void* p) {}
void clear_bitmap(BITMAP* bitmap) {
    if (!img_backend) img_backend = get_stb_image_backend();
    if (bitmap) {
        img_backend->fill_rect((HamoopiImage*)bitmap, 0, 0, 
                              bitmap->w - 1, bitmap->h - 1, 
                              img_backend->make_color(0, 0, 0, 255));
    }
}

void clear_to_color(BITMAP* bitmap, int color) {
    if (!img_backend) img_backend = get_stb_image_backend();
    if (bitmap) {
        img_backend->fill_rect((HamoopiImage*)bitmap, 0, 0,
                              bitmap->w - 1, bitmap->h - 1, color);
    }
}

/* Bitmap functions */
BITMAP* create_bitmap(int w, int h) {
    if (!img_backend) img_backend = get_stb_image_backend();
    return (BITMAP*)img_backend->create_image(w, h, 4);
}

BITMAP* load_bitmap(const char* filename, void* pal) {
    if (!img_backend) img_backend = get_stb_image_backend();
    return (BITMAP*)img_backend->load_image(filename);
}

void destroy_bitmap(BITMAP* bitmap) {
    if (!img_backend) img_backend = get_stb_image_backend();
    if (bitmap) {
        img_backend->destroy_image((HamoopiImage*)bitmap);
    }
}

int save_bitmap(const char* filename, BITMAP* bitmap, const void* pal) {
    if (!img_backend) img_backend = get_stb_image_backend();
    return img_backend->save_image((HamoopiImage*)bitmap, filename);
}

/* Drawing functions */
void putpixel(BITMAP* bitmap, int x, int y, int color) {
    if (!img_backend) img_backend = get_stb_image_backend();
    img_backend->draw_pixel((HamoopiImage*)bitmap, x, y, color);
}

int getpixel(BITMAP* bitmap, int x, int y) {
    if (!img_backend) img_backend = get_stb_image_backend();
    return img_backend->get_pixel((HamoopiImage*)bitmap, x, y);
}

void line(BITMAP* bitmap, int x1, int y1, int x2, int y2, int color) {
    if (!img_backend) img_backend = get_stb_image_backend();
    img_backend->draw_line((HamoopiImage*)bitmap, x1, y1, x2, y2, color);
}

void rect(BITMAP* bitmap, int x1, int y1, int x2, int y2, int color) {
    if (!img_backend) img_backend = get_stb_image_backend();
    img_backend->draw_rect((HamoopiImage*)bitmap, x1, y1, x2, y2, color);
}

void rectfill(BITMAP* bitmap, int x1, int y1, int x2, int y2, int color) {
    if (!img_backend) img_backend = get_stb_image_backend();
    img_backend->fill_rect((HamoopiImage*)bitmap, x1, y1, x2, y2, color);
}

void circle(BITMAP* bitmap, int x, int y, int radius, int color) {
    if (!img_backend) img_backend = get_stb_image_backend();
    img_backend->draw_circle((HamoopiImage*)bitmap, x, y, radius, color);
}

void circlefill(BITMAP* bitmap, int x, int y, int radius, int color) {
    if (!img_backend) img_backend = get_stb_image_backend();
    img_backend->fill_circle((HamoopiImage*)bitmap, x, y, radius, color);
}

void blit(BITMAP* src, BITMAP* dest, int src_x, int src_y, int dest_x, int dest_y, int w, int h) {
    if (!img_backend) img_backend = get_stb_image_backend();
    img_backend->blit_image((HamoopiImage*)src, (HamoopiImage*)dest,
                           src_x, src_y, dest_x, dest_y, w, h);
}

void masked_blit(BITMAP* src, BITMAP* dest, int src_x, int src_y, int dest_x, int dest_y, int w, int h) {
    /* For now, same as blit - would need alpha handling */
    blit(src, dest, src_x, src_y, dest_x, dest_y, w, h);
}

void stretch_blit(BITMAP* src, BITMAP* dest, int src_x, int src_y, int src_w, int src_h, 
                  int dest_x, int dest_y, int dest_w, int dest_h) {
    /* Simple nearest-neighbor stretch */
    if (!img_backend) img_backend = get_stb_image_backend();
    
    float x_ratio = (float)src_w / dest_w;
    float y_ratio = (float)src_h / dest_h;
    
    for (int y = 0; y < dest_h; y++) {
        for (int x = 0; x < dest_w; x++) {
            int src_px = src_x + (int)(x * x_ratio);
            int src_py = src_y + (int)(y * y_ratio);
            int color = img_backend->get_pixel((HamoopiImage*)src, src_px, src_py);
            img_backend->draw_pixel((HamoopiImage*)dest, dest_x + x, dest_y + y, color);
        }
    }
}

/* Font functions */
FONT* load_font(const char* filename, void* pal, void* param) {
    if (!font_backend) font_backend = get_stb_font_backend();
    return (FONT*)font_backend->load_font(filename, 12); /* Default size */
}

void destroy_font(FONT* f) {
    if (!font_backend) font_backend = get_stb_font_backend();
    if (f) {
        font_backend->destroy_font((struct HamoopiFont*)f);
    }
}

void textout_ex(BITMAP* bitmap, FONT* f, const char* text, int x, int y, int color, int bg) {
    if (!font_backend) font_backend = get_stb_font_backend();
    font_backend->draw_text((HamoopiImage*)bitmap, (struct HamoopiFont*)f, text, x, y, color);
}

void textout_centre_ex(BITMAP* bitmap, FONT* f, const char* text, int x, int y, int color, int bg) {
    if (!font_backend) font_backend = get_stb_font_backend();
    font_backend->draw_text_centered((HamoopiImage*)bitmap, (struct HamoopiFont*)f, text, x, y, color);
}

int text_length(FONT* f, const char* text) {
    if (!font_backend) font_backend = get_stb_font_backend();
    return font_backend->get_text_width((struct HamoopiFont*)f, text);
}

int text_height(FONT* f) {
    if (!font_backend) font_backend = get_stb_font_backend();
    return font_backend->get_text_height((struct HamoopiFont*)f);
}

/* Timing */
volatile int retrace_count = 0;
void rest(unsigned int time) {
    /* Simple sleep - would need platform-specific implementation */
}

/* Config */
void set_config_file(const char* filename) {}
const char* get_config_string(const char* section, const char* name, const char* def) { return def; }
int get_config_int(const char* section, const char* name, int def) { return def; }
void set_config_string(const char* section, const char* name, const char* val) {}
void set_config_int(const char* section, const char* name, int val) {}

/* Misc */
int allegro_message(const char* fmt, ...) {
    /* Would need proper implementation with vsprintf */
    return 0;
}

void allegro_exit(void) {
    if (screen) {
        destroy_bitmap(screen);
        screen = NULL;
    }
}

#endif /* USE_STB_BACKEND */
