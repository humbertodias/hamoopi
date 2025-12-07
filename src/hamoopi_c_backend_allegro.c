/* Pure C Backend Implementation using Allegro 4
 * This file implements the hamoopi_c_backend.h interface
 */

#include "hamoopi_c_backend.h"
#include <allegro.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/* ============================================================================
 * TYPE IMPLEMENTATIONS
 * ============================================================================ */

/* HamoopiImage wraps Allegro BITMAP with compatible layout */
struct HamoopiImage {
    BITMAP* allegro_bitmap;  /* Actual Allegro bitmap */
};

struct HamoopiFont {
    FONT* allegro_font;
};

struct HamoopiSample {
    SAMPLE* allegro_sample;
};

struct HamoopiMidi {
    MIDI* allegro_midi;
};

/* ============================================================================
 * GLOBAL VARIABLES
 * ============================================================================ */

BITMAP* hamoopi_screen = NULL;
volatile char hamoopi_key[128];

/* ============================================================================
 * STDLIB REPLACEMENTS
 * ============================================================================ */

int hamoopi_sprintf(char* str, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = vsprintf(str, format, args);
    va_end(args);
    return result;
}

int hamoopi_snprintf(char* str, int size, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int result = vsnprintf(str, size, format, args);
    va_end(args);
    return result;
}

int hamoopi_abs(int x) {
    return abs(x);
}

double hamoopi_floor(double x) {
    return floor(x);
}

double hamoopi_ceil(double x) {
    return ceil(x);
}

double hamoopi_sqrt(double x) {
    return sqrt(x);
}

double hamoopi_sin(double x) {
    return sin(x);
}

double hamoopi_cos(double x) {
    return cos(x);
}

void* hamoopi_memset(void* ptr, int value, unsigned int num) {
    return memset(ptr, value, num);
}

void* hamoopi_memcpy(void* dest, const void* src, unsigned int num) {
    return memcpy(dest, src, num);
}

/* ============================================================================
 * GRAPHICS BACKEND
 * ============================================================================ */

int hamoopi_init(void) {
    if (allegro_init() != 0) {
        return -1;
    }
    return 0;
}

void hamoopi_shutdown(void) {
    allegro_exit();
}

int hamoopi_set_gfx_mode(int mode, int width, int height, int v_width, int v_height) {
    int result = set_gfx_mode(mode, width, height, v_width, v_height);
    if (result == 0) {
        hamoopi_screen = screen;
    }
    return result;
}

void hamoopi_set_color_depth(int depth) {
    set_color_depth(depth);
}

void hamoopi_set_window_title(const char* title) {
    set_window_title(title);
}

BITMAP* hamoopi_create_bitmap(int width, int height) {
    BITMAP* bmp = create_bitmap(width, height);
    return (BITMAP*)bmp;  /* Direct cast since we're using Allegro bitmaps */
}

BITMAP* hamoopi_load_bitmap(const char* filename, void* palette) {
    BITMAP* bmp = load_bitmap(filename, (RGB*)palette);
    return (BITMAP*)bmp;
}

void hamoopi_destroy_bitmap(BITMAP* bitmap) {
    if (bitmap) {
        destroy_bitmap((BITMAP*)bitmap);
    }
}

void hamoopi_clear_bitmap(BITMAP* bitmap) {
    if (bitmap) {
        clear_bitmap((BITMAP*)bitmap);
    }
}

void hamoopi_clear_to_color(BITMAP* bitmap, Color color) {
    if (bitmap) {
        clear_to_color((BITMAP*)bitmap, color);
    }
}

int hamoopi_bitmap_width(BITMAP* bitmap) {
    return bitmap ? ((BITMAP*)bitmap)->w : 0;
}

int hamoopi_bitmap_height(BITMAP* bitmap) {
    return bitmap ? ((BITMAP*)bitmap)->h : 0;
}

void hamoopi_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height) {
    blit((BITMAP*)source, (BITMAP*)dest, source_x, source_y, dest_x, dest_y, width, height);
}

void hamoopi_masked_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height) {
    masked_blit((BITMAP*)source, (BITMAP*)dest, source_x, source_y, dest_x, dest_y, width, height);
}

void hamoopi_stretch_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int source_w, int source_h, int dest_x, int dest_y, int dest_w, int dest_h) {
    stretch_blit((BITMAP*)source, (BITMAP*)dest, source_x, source_y, source_w, source_h, dest_x, dest_y, dest_w, dest_h);
}

void hamoopi_draw_sprite(BITMAP* dest, BITMAP* sprite, int x, int y) {
    draw_sprite((BITMAP*)dest, (BITMAP*)sprite, x, y);
}

void hamoopi_draw_sprite_h_flip(BITMAP* dest, BITMAP* sprite, int x, int y) {
    draw_sprite_h_flip((BITMAP*)dest, (BITMAP*)sprite, x, y);
}

void hamoopi_draw_sprite_v_flip(BITMAP* dest, BITMAP* sprite, int x, int y) {
    draw_sprite_v_flip((BITMAP*)dest, (BITMAP*)sprite, x, y);
}

void hamoopi_rectfill(BITMAP* bitmap, int x1, int y1, int x2, int y2, Color color) {
    rectfill((BITMAP*)bitmap, x1, y1, x2, y2, color);
}

void hamoopi_rect(BITMAP* bitmap, int x1, int y1, int x2, int y2, Color color) {
    rect((BITMAP*)bitmap, x1, y1, x2, y2, color);
}

void hamoopi_line(BITMAP* bitmap, int x1, int y1, int x2, int y2, Color color) {
    line((BITMAP*)bitmap, x1, y1, x2, y2, color);
}

void hamoopi_hline(BITMAP* bitmap, int x1, int y, int x2, Color color) {
    hline((BITMAP*)bitmap, x1, y, x2, color);
}

void hamoopi_vline(BITMAP* bitmap, int x, int y1, int y2, Color color) {
    vline((BITMAP*)bitmap, x, y1, y2, color);
}

void hamoopi_circle(BITMAP* bitmap, int x, int y, int radius, Color color) {
    circle((BITMAP*)bitmap, x, y, radius, color);
}

void hamoopi_circlefill(BITMAP* bitmap, int x, int y, int radius, Color color) {
    circlefill((BITMAP*)bitmap, x, y, radius, color);
}

void hamoopi_putpixel(BITMAP* bitmap, int x, int y, Color color) {
    putpixel((BITMAP*)bitmap, x, y, color);
}

Color hamoopi_getpixel(BITMAP* bitmap, int x, int y) {
    return getpixel((BITMAP*)bitmap, x, y);
}

Color hamoopi_makecol(int r, int g, int b) {
    return makecol(r, g, b);
}

int hamoopi_getr(Color c) {
    return getr(c);
}

int hamoopi_getg(Color c) {
    return getg(c);
}

int hamoopi_getb(Color c) {
    return getb(c);
}

void hamoopi_set_palette_range(const void* palette, int from, int to, int vsync) {
    set_palette_range((const RGB*)palette, from, to, vsync);
}

FONT* hamoopi_load_font(const char* filename, void* palette, void* param) {
    FONT* f = load_font(filename, (RGB*)palette, param);
    return (FONT*)f;
}

void hamoopi_destroy_font(FONT* font) {
    if (font) {
        destroy_font((FONT*)font);
    }
}

void hamoopi_textout_ex(BITMAP* bmp, FONT* f, const char* s, int x, int y, Color color, Color bg) {
    textout_ex((BITMAP*)bmp, (FONT*)f, s, x, y, color, bg);
}

void hamoopi_textout_centre_ex(BITMAP* bmp, FONT* f, const char* s, int x, int y, Color color, Color bg) {
    textout_centre_ex((BITMAP*)bmp, (FONT*)f, s, x, y, color, bg);
}

void hamoopi_textprintf_ex(BITMAP* bmp, FONT* f, int x, int y, Color color, Color bg, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    textout_ex((BITMAP*)bmp, (FONT*)f, buffer, x, y, color, bg);
}

int hamoopi_text_length(FONT* f, const char* str) {
    return text_length((FONT*)f, str);
}

int hamoopi_text_height(FONT* f) {
    return text_height((FONT*)f);
}

/* ============================================================================
 * INPUT BACKEND
 * ============================================================================ */

int hamoopi_install_keyboard(void) {
    int result = install_keyboard();
    /* Copy Allegro key array to our array */
    return result;
}

int hamoopi_keypressed(void) {
    return keypressed();
}

int hamoopi_readkey(void) {
    return readkey();
}

void hamoopi_clear_keybuf(void) {
    clear_keybuf();
}

int hamoopi_install_mouse(void) {
    return install_mouse();
}

void hamoopi_show_mouse(BITMAP* bmp) {
    show_mouse((BITMAP*)bmp);
}

void hamoopi_hide_mouse(BITMAP* bmp) {
    scare_mouse_area(0, 0, SCREEN_W, SCREEN_H);
}

int hamoopi_mouse_x(void) {
    return mouse_x;
}

int hamoopi_mouse_y(void) {
    return mouse_y;
}

int hamoopi_mouse_b(void) {
    return mouse_b;
}

int hamoopi_install_joystick(int type) {
    return install_joystick(type);
}

int hamoopi_poll_joystick(void) {
    return poll_joystick();
}

int hamoopi_num_joysticks(void) {
    return num_joysticks;
}

/* ============================================================================
 * AUDIO BACKEND
 * ============================================================================ */

int hamoopi_install_sound(int digi, int midi, const char* cfg_path) {
    return install_sound(digi, midi, cfg_path);
}

void hamoopi_remove_sound(void) {
    remove_sound();
}

SAMPLE* hamoopi_load_sample(const char* filename) {
    SAMPLE* s = load_sample(filename);
    return (SAMPLE*)s;
}

void hamoopi_destroy_sample(SAMPLE* spl) {
    if (spl) {
        destroy_sample((SAMPLE*)spl);
    }
}

int hamoopi_play_sample(SAMPLE* spl, int vol, int pan, int freq, int loop) {
    return play_sample((SAMPLE*)spl, vol, pan, freq, loop);
}

void hamoopi_stop_sample(SAMPLE* spl) {
    stop_sample((SAMPLE*)spl);
}

void hamoopi_adjust_sample(SAMPLE* spl, int vol, int pan, int freq, int loop) {
    adjust_sample((SAMPLE*)spl, vol, pan, freq, loop);
}

MIDI* hamoopi_load_midi(const char* filename) {
    MIDI* m = load_midi(filename);
    return (MIDI*)m;
}

void hamoopi_destroy_midi(MIDI* midi) {
    if (midi) {
        destroy_midi((MIDI*)midi);
    }
}

int hamoopi_play_midi(MIDI* midi, int loop) {
    return play_midi((MIDI*)midi, loop);
}

void hamoopi_stop_midi(void) {
    stop_midi();
}

int hamoopi_midi_pos(void) {
    return midi_pos;
}

/* ============================================================================
 * SYSTEM BACKEND
 * ============================================================================ */

void hamoopi_install_timer(void) {
    install_timer();
}

void hamoopi_install_int_ex(void (*proc)(void), int speed) {
    install_int_ex(proc, BPS_TO_TIMER(speed));
}

void hamoopi_set_utf8_format(void) {
    set_uformat(U_UTF8);
}

void hamoopi_set_close_button_callback(void (*callback)(void)) {
    set_close_button_callback(callback);
}

void hamoopi_rest(int msec) {
    rest(msec);
}

int hamoopi_retrace_count(void) {
    return retrace_count;
}

void hamoopi_set_config_file(const char* filename) {
    set_config_file(filename);
}

const char* hamoopi_get_config_string(const char* section, const char* name, const char* def) {
    return get_config_string(section, name, def);
}

int hamoopi_get_config_int(const char* section, const char* name, int def) {
    return get_config_int(section, name, def);
}

void hamoopi_set_config_string(const char* section, const char* name, const char* val) {
    set_config_string(section, name, val);
}

void hamoopi_set_config_int(const char* section, const char* name, int val) {
    set_config_int(section, name, val);
}

int hamoopi_alert(const char* s1, const char* s2, const char* s3, const char* b1, const char* b2, int c1, int c2) {
    return alert(s1, s2, s3, b1, b2, c1, c2);
}

void hamoopi_allegro_message(const char* msg) {
    allegro_message("%s", msg);
}

int hamoopi_exists(const char* filename) {
    return exists(filename);
}

int hamoopi_rand(void) {
    return rand();
}

void hamoopi_allegro_exit(void) {
    allegro_exit();
}
