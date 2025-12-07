#ifndef ALLEGRO_GRAPHICS_BACKEND_H
#define ALLEGRO_GRAPHICS_BACKEND_H

#include "graphics_backend.h"
#include <allegro.h>
#include <cstdarg>

class AllegroGraphicsBackend : public GraphicsBackend {
public:
    bool init() override {
        return true; // Allegro is initialized elsewhere
    }
    
    void shutdown() override {
        // Cleanup handled by allegro_exit
    }
    
    bool set_graphics_mode(bool fullscreen, int width, int height) override {
        int mode = fullscreen ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED;
        return set_gfx_mode(mode, width, height, 0, 0) == 0;
    }
    
    void set_window_title(const char* title) override {
        ::set_window_title(title);
    }
    
    void set_color_depth(int depth) override {
        ::set_color_depth(depth);
    }
    
    GraphicsBitmap create_bitmap(int width, int height) override {
        return ::create_bitmap(width, height);
    }
    
    GraphicsBitmap load_bitmap(const char* filename) override {
        return ::load_bitmap(filename, NULL);
    }
    
    void destroy_bitmap(GraphicsBitmap bitmap) override {
        if (bitmap) {
            ::destroy_bitmap((BITMAP*)bitmap);
        }
    }
    
    void clear_bitmap(GraphicsBitmap bitmap) override {
        ::clear_bitmap((BITMAP*)bitmap);
    }
    
    void blit(GraphicsBitmap source, GraphicsBitmap dest, int source_x, int source_y, 
              int dest_x, int dest_y, int width, int height) override {
        ::blit((BITMAP*)source, (BITMAP*)dest, source_x, source_y, dest_x, dest_y, width, height);
    }
    
    void stretch_blit(GraphicsBitmap source, GraphicsBitmap dest, 
                     int source_x, int source_y, int source_w, int source_h,
                     int dest_x, int dest_y, int dest_w, int dest_h) override {
        ::stretch_blit((BITMAP*)source, (BITMAP*)dest, 
                      source_x, source_y, source_w, source_h,
                      dest_x, dest_y, dest_w, dest_h);
    }
    
    void draw_sprite(GraphicsBitmap dest, GraphicsBitmap sprite, int x, int y) override {
        ::draw_sprite((BITMAP*)dest, (BITMAP*)sprite, x, y);
    }
    
    void masked_blit(GraphicsBitmap source, GraphicsBitmap dest, 
                    int source_x, int source_y, int dest_x, int dest_y, 
                    int width, int height) override {
        ::masked_blit((BITMAP*)source, (BITMAP*)dest, source_x, source_y, dest_x, dest_y, width, height);
    }
    
    void draw_sprite_h_flip(GraphicsBitmap dest, GraphicsBitmap sprite, int x, int y) override {
        ::draw_sprite_h_flip((BITMAP*)dest, (BITMAP*)sprite, x, y);
    }
    
    void draw_sprite_v_flip(GraphicsBitmap dest, GraphicsBitmap sprite, int x, int y) override {
        ::draw_sprite_v_flip((BITMAP*)dest, (BITMAP*)sprite, x, y);
    }
    
    void rectfill(GraphicsBitmap bitmap, int x1, int y1, int x2, int y2, int color) override {
        ::rectfill((BITMAP*)bitmap, x1, y1, x2, y2, color);
    }
    
    void rect(GraphicsBitmap bitmap, int x1, int y1, int x2, int y2, int color) override {
        ::rect((BITMAP*)bitmap, x1, y1, x2, y2, color);
    }
    
    void line(GraphicsBitmap bitmap, int x1, int y1, int x2, int y2, int color) override {
        ::line((BITMAP*)bitmap, x1, y1, x2, y2, color);
    }
    
    void circle(GraphicsBitmap bitmap, int x, int y, int radius, int color) override {
        ::circle((BITMAP*)bitmap, x, y, radius, color);
    }
    
    void circlefill(GraphicsBitmap bitmap, int x, int y, int radius, int color) override {
        ::circlefill((BITMAP*)bitmap, x, y, radius, color);
    }
    
    GraphicsFont load_font(const char* filename) override {
        return ::load_font(filename, NULL, NULL);
    }
    
    void destroy_font(GraphicsFont font) override {
        if (font) {
            ::destroy_font((FONT*)font);
        }
    }
    
    void textout(GraphicsBitmap bitmap, GraphicsFont font, const char* text, 
                int x, int y, int color) override {
        ::textout_ex((BITMAP*)bitmap, (FONT*)font, text, x, y, color, -1);
    }
    
    void textout_centre(GraphicsBitmap bitmap, GraphicsFont font, const char* text, 
                       int x, int y, int color) override {
        ::textout_centre_ex((BITMAP*)bitmap, (FONT*)font, text, x, y, color, -1);
    }
    
    void textprintf(GraphicsBitmap bitmap, GraphicsFont font, int x, int y, 
                   int color, const char* format, ...) override {
        va_list args;
        va_start(args, format);
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        ::textout_ex((BITMAP*)bitmap, (FONT*)font, buffer, x, y, color, -1);
    }
    
    int makecol(int r, int g, int b) override {
        return ::makecol(r, g, b);
    }
    
    void set_palette_range(const void* palette, int from, int to, int vsync) override {
        ::set_palette_range((const RGB*)palette, from, to, vsync);
    }
    
    GraphicsBitmap get_screen() override {
        return screen;
    }
    
    void clear_to_color(GraphicsBitmap bitmap, int color) override {
        ::clear_to_color((BITMAP*)bitmap, color);
    }
    
    void vsync() override {
        ::vsync();
    }
    
    void rest(int milliseconds) override {
        ::rest(milliseconds);
    }
    
    int bitmap_width(GraphicsBitmap bitmap) override {
        return ((BITMAP*)bitmap)->w;
    }
    
    int bitmap_height(GraphicsBitmap bitmap) override {
        return ((BITMAP*)bitmap)->h;
    }
};

#endif // ALLEGRO_GRAPHICS_BACKEND_H
