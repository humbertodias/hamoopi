// platform_allegro.c - Allegro 4 implementation of platform abstraction layer

#include "platform.h"
#include <allegro.h>
#include <stdarg.h>
#include <string.h>

// Map our opaque types to Allegro types
struct PlatformBitmap {
    BITMAP *allegro_bitmap;
};

struct PlatformFont {
    FONT *allegro_font;
};

struct PlatformSample {
    SAMPLE *allegro_sample;
};

struct PlatformMidi {
    MIDI *allegro_midi;
};

// ============================================================================
// INITIALIZATION & SYSTEM
// ============================================================================

int platform_init(void) {
    return allegro_init();
}

void platform_set_uformat(int format) {
    set_uformat(U_UTF8);
}

int platform_install_timer(void) {
    return install_timer();
}

int platform_install_keyboard(void) {
    return install_keyboard();
}

int platform_install_mouse(void) {
    return install_mouse();
}

void platform_set_color_depth(int depth) {
    set_color_depth(depth);
}

int platform_set_gfx_mode(int mode, int width, int height, int v_width, int v_height) {
    int allegro_mode;
    if (mode == PGFX_AUTODETECT_FULLSCREEN) {
        allegro_mode = GFX_AUTODETECT_FULLSCREEN;
    } else {
        allegro_mode = GFX_AUTODETECT_WINDOWED;
    }
    return set_gfx_mode(allegro_mode, width, height, v_width, v_height);
}

void platform_set_window_title(const char *title) {
    set_window_title(title);
}

void platform_set_close_button_callback(void (*callback)(void)) {
    set_close_button_callback(callback);
}

void platform_install_int_ex(void (*callback)(void), int bps) {
    install_int_ex(callback, BPS_TO_TIMER(bps));
}

volatile char* platform_get_key_state(void) {
    return key;
}

PlatformBitmap* platform_get_screen(void) {
    PlatformBitmap *pb = (PlatformBitmap*)malloc(sizeof(PlatformBitmap));
    if (pb) {
        pb->allegro_bitmap = screen;
    }
    return pb;
}

// ============================================================================
// GRAPHICS - BITMAP OPERATIONS
// ============================================================================

PlatformBitmap* platform_create_bitmap(int width, int height) {
    PlatformBitmap *pb = (PlatformBitmap*)malloc(sizeof(PlatformBitmap));
    if (pb) {
        pb->allegro_bitmap = create_bitmap(width, height);
        if (!pb->allegro_bitmap) {
            free(pb);
            return NULL;
        }
    }
    return pb;
}

void platform_destroy_bitmap(PlatformBitmap *bitmap) {
    if (bitmap) {
        if (bitmap->allegro_bitmap) {
            destroy_bitmap(bitmap->allegro_bitmap);
        }
        free(bitmap);
    }
}

PlatformBitmap* platform_load_bitmap(const char *filename, void *palette) {
    PlatformBitmap *pb = (PlatformBitmap*)malloc(sizeof(PlatformBitmap));
    if (pb) {
        pb->allegro_bitmap = load_bitmap(filename, palette);
        if (!pb->allegro_bitmap) {
            free(pb);
            return NULL;
        }
    }
    return pb;
}

void platform_clear_bitmap(PlatformBitmap *bitmap) {
    if (bitmap && bitmap->allegro_bitmap) {
        clear_bitmap(bitmap->allegro_bitmap);
    }
}

void platform_clear_to_color(PlatformBitmap *bitmap, PlatformColor color) {
    if (bitmap && bitmap->allegro_bitmap) {
        clear_to_color(bitmap->allegro_bitmap, color);
    }
}

void platform_draw_sprite(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && dest->allegro_bitmap && src && src->allegro_bitmap) {
        draw_sprite(dest->allegro_bitmap, src->allegro_bitmap, x, y);
    }
}

void platform_stretch_blit(PlatformBitmap *src, PlatformBitmap *dest,
                          int src_x, int src_y, int src_w, int src_h,
                          int dest_x, int dest_y, int dest_w, int dest_h) {
    if (src && src->allegro_bitmap && dest && dest->allegro_bitmap) {
        stretch_blit(src->allegro_bitmap, dest->allegro_bitmap,
                    src_x, src_y, src_w, src_h,
                    dest_x, dest_y, dest_w, dest_h);
    }
}

void platform_blit(PlatformBitmap *src, PlatformBitmap *dest,
                  int src_x, int src_y, int dest_x, int dest_y, int w, int h) {
    if (src && src->allegro_bitmap && dest && dest->allegro_bitmap) {
        blit(src->allegro_bitmap, dest->allegro_bitmap,
            src_x, src_y, dest_x, dest_y, w, h);
    }
}

void platform_masked_blit(PlatformBitmap *src, PlatformBitmap *dest,
                         int src_x, int src_y, int dest_x, int dest_y, int w, int h) {
    if (src && src->allegro_bitmap && dest && dest->allegro_bitmap) {
        masked_blit(src->allegro_bitmap, dest->allegro_bitmap,
                   src_x, src_y, dest_x, dest_y, w, h);
    }
}

void platform_draw_sprite_h_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && dest->allegro_bitmap && src && src->allegro_bitmap) {
        draw_sprite_h_flip(dest->allegro_bitmap, src->allegro_bitmap, x, y);
    }
}

void platform_draw_sprite_v_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && dest->allegro_bitmap && src && src->allegro_bitmap) {
        draw_sprite_v_flip(dest->allegro_bitmap, src->allegro_bitmap, x, y);
    }
}

void platform_draw_sprite_vh_flip(PlatformBitmap *dest, PlatformBitmap *src, int x, int y) {
    if (dest && dest->allegro_bitmap && src && src->allegro_bitmap) {
        draw_sprite_vh_flip(dest->allegro_bitmap, src->allegro_bitmap, x, y);
    }
}

void platform_rotate_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                           int x, int y, int angle) {
    if (dest && dest->allegro_bitmap && src && src->allegro_bitmap) {
        rotate_sprite(dest->allegro_bitmap, src->allegro_bitmap, x, y, itofix(angle));
    }
}

void platform_pivot_sprite(PlatformBitmap *dest, PlatformBitmap *src,
                          int x, int y, int cx, int cy, int angle) {
    if (dest && dest->allegro_bitmap && src && src->allegro_bitmap) {
        pivot_sprite(dest->allegro_bitmap, src->allegro_bitmap, x, y, cx, cy, itofix(angle));
    }
}

PlatformColor platform_getpixel(PlatformBitmap *bitmap, int x, int y) {
    if (bitmap && bitmap->allegro_bitmap) {
        return getpixel(bitmap->allegro_bitmap, x, y);
    }
    return 0;
}

void platform_putpixel(PlatformBitmap *bitmap, int x, int y, PlatformColor color) {
    if (bitmap && bitmap->allegro_bitmap) {
        putpixel(bitmap->allegro_bitmap, x, y, color);
    }
}

// ============================================================================
// GRAPHICS - PRIMITIVES
// ============================================================================

void platform_line(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color) {
    if (bitmap && bitmap->allegro_bitmap) {
        line(bitmap->allegro_bitmap, x1, y1, x2, y2, color);
    }
}

void platform_rect(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color) {
    if (bitmap && bitmap->allegro_bitmap) {
        rect(bitmap->allegro_bitmap, x1, y1, x2, y2, color);
    }
}

void platform_rectfill(PlatformBitmap *bitmap, int x1, int y1, int x2, int y2, PlatformColor color) {
    if (bitmap && bitmap->allegro_bitmap) {
        rectfill(bitmap->allegro_bitmap, x1, y1, x2, y2, color);
    }
}

void platform_circle(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color) {
    if (bitmap && bitmap->allegro_bitmap) {
        circle(bitmap->allegro_bitmap, x, y, radius, color);
    }
}

void platform_circlefill(PlatformBitmap *bitmap, int x, int y, int radius, PlatformColor color) {
    if (bitmap && bitmap->allegro_bitmap) {
        circlefill(bitmap->allegro_bitmap, x, y, radius, color);
    }
}

PlatformColor platform_makecol(int r, int g, int b) {
    return makecol(r, g, b);
}

// ============================================================================
// GRAPHICS - TEXT
// ============================================================================

PlatformFont* platform_load_font(const char *filename, void *palette, void *param) {
    PlatformFont *pf = (PlatformFont*)malloc(sizeof(PlatformFont));
    if (pf) {
        pf->allegro_font = load_font(filename, palette, param);
        if (!pf->allegro_font) {
            free(pf);
            return NULL;
        }
    }
    return pf;
}

void platform_destroy_font(PlatformFont *font) {
    if (font) {
        if (font->allegro_font) {
            destroy_font(font->allegro_font);
        }
        free(font);
    }
}

void platform_textout_ex(PlatformBitmap *bitmap, PlatformFont *font,
                        const char *text, int x, int y,
                        PlatformColor color, PlatformColor bg) {
    if (bitmap && bitmap->allegro_bitmap && font && font->allegro_font) {
        textout_ex(bitmap->allegro_bitmap, font->allegro_font, text, x, y, color, bg);
    }
}

void platform_textout_centre_ex(PlatformBitmap *bitmap, PlatformFont *font,
                               const char *text, int x, int y,
                               PlatformColor color, PlatformColor bg) {
    if (bitmap && bitmap->allegro_bitmap && font && font->allegro_font) {
        textout_centre_ex(bitmap->allegro_bitmap, font->allegro_font, text, x, y, color, bg);
    }
}

void platform_textprintf_ex(PlatformBitmap *bitmap, PlatformFont *font,
                           int x, int y, PlatformColor color, PlatformColor bg,
                           const char *format, ...) {
    if (bitmap && bitmap->allegro_bitmap && font && font->allegro_font) {
        va_list args;
        va_start(args, format);
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        textout_ex(bitmap->allegro_bitmap, font->allegro_font, buffer, x, y, color, bg);
    }
}

void platform_textprintf_centre_ex(PlatformBitmap *bitmap, PlatformFont *font,
                                  int x, int y, PlatformColor color, PlatformColor bg,
                                  const char *format, ...) {
    if (bitmap && bitmap->allegro_bitmap && font && font->allegro_font) {
        va_list args;
        va_start(args, format);
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        textout_centre_ex(bitmap->allegro_bitmap, font->allegro_font, buffer, x, y, color, bg);
    }
}

// ============================================================================
// AUDIO
// ============================================================================

int platform_install_sound(int digi, int midi, const char *cfg) {
    return install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
}

PlatformSample* platform_load_sample(const char *filename) {
    PlatformSample *ps = (PlatformSample*)malloc(sizeof(PlatformSample));
    if (ps) {
        ps->allegro_sample = load_sample(filename);
        if (!ps->allegro_sample) {
            free(ps);
            return NULL;
        }
    }
    return ps;
}

PlatformMidi* platform_load_midi(const char *filename) {
    PlatformMidi *pm = (PlatformMidi*)malloc(sizeof(PlatformMidi));
    if (pm) {
        pm->allegro_midi = load_midi(filename);
        if (!pm->allegro_midi) {
            free(pm);
            return NULL;
        }
    }
    return pm;
}

void platform_destroy_sample(PlatformSample *sample) {
    if (sample) {
        if (sample->allegro_sample) {
            destroy_sample(sample->allegro_sample);
        }
        free(sample);
    }
}

void platform_destroy_midi(PlatformMidi *midi) {
    if (midi) {
        if (midi->allegro_midi) {
            destroy_midi(midi->allegro_midi);
        }
        free(midi);
    }
}

int platform_play_sample(PlatformSample *sample, int vol, int pan, int freq, int loop) {
    if (sample && sample->allegro_sample) {
        return play_sample(sample->allegro_sample, vol, pan, freq, loop);
    }
    return -1;
}

int platform_play_midi(PlatformMidi *midi, int loop) {
    if (midi && midi->allegro_midi) {
        return play_midi(midi->allegro_midi, loop);
    }
    return -1;
}

void platform_stop_midi(void) {
    stop_midi();
}

void platform_set_volume(int digi, int midi) {
    set_volume(digi, midi);
}

void platform_adjust_sample(PlatformSample *sample, int vol, int pan, int freq, int loop) {
    if (sample && sample->allegro_sample) {
        adjust_sample(sample->allegro_sample, vol, pan, freq, loop);
    }
}

// ============================================================================
// CONFIG FILE
// ============================================================================

void platform_set_config_file(const char *filename) {
    set_config_file(filename);
}

int platform_get_config_int(const char *section, const char *key, int default_value) {
    return get_config_int(section, key, default_value);
}

const char* platform_get_config_string(const char *section, const char *key, const char *default_value) {
    return get_config_string(section, key, default_value);
}

void platform_set_config_int(const char *section, const char *key, int value) {
    set_config_int(section, key, value);
}

void platform_set_config_string(const char *section, const char *key, const char *value) {
    set_config_string(section, key, value);
}
