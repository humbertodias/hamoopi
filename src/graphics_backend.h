#ifndef GRAPHICS_BACKEND_H
#define GRAPHICS_BACKEND_H

// Abstract graphics backend interface
// This allows the engine to be independent of the graphics library

typedef void* GraphicsBitmap;
typedef void* GraphicsFont;

class GraphicsBackend {
public:
    virtual ~GraphicsBackend() {}
    
    // Initialization
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual bool set_graphics_mode(bool fullscreen, int width, int height) = 0;
    virtual void set_window_title(const char* title) = 0;
    virtual void set_color_depth(int depth) = 0;
    
    // Bitmap operations
    virtual GraphicsBitmap create_bitmap(int width, int height) = 0;
    virtual GraphicsBitmap load_bitmap(const char* filename) = 0;
    virtual void destroy_bitmap(GraphicsBitmap bitmap) = 0;
    virtual void clear_bitmap(GraphicsBitmap bitmap) = 0;
    virtual void blit(GraphicsBitmap source, GraphicsBitmap dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height) = 0;
    virtual void stretch_blit(GraphicsBitmap source, GraphicsBitmap dest, int source_x, int source_y, int source_w, int source_h, int dest_x, int dest_y, int dest_w, int dest_h) = 0;
    virtual void draw_sprite(GraphicsBitmap dest, GraphicsBitmap sprite, int x, int y) = 0;
    virtual void masked_blit(GraphicsBitmap source, GraphicsBitmap dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height) = 0;
    virtual void draw_sprite_h_flip(GraphicsBitmap dest, GraphicsBitmap sprite, int x, int y) = 0;
    virtual void draw_sprite_v_flip(GraphicsBitmap dest, GraphicsBitmap sprite, int x, int y) = 0;
    
    // Drawing primitives
    virtual void rectfill(GraphicsBitmap bitmap, int x1, int y1, int x2, int y2, int color) = 0;
    virtual void rect(GraphicsBitmap bitmap, int x1, int y1, int x2, int y2, int color) = 0;
    virtual void line(GraphicsBitmap bitmap, int x1, int y1, int x2, int y2, int color) = 0;
    virtual void circle(GraphicsBitmap bitmap, int x, int y, int radius, int color) = 0;
    virtual void circlefill(GraphicsBitmap bitmap, int x, int y, int radius, int color) = 0;
    
    // Text operations
    virtual GraphicsFont load_font(const char* filename) = 0;
    virtual void destroy_font(GraphicsFont font) = 0;
    virtual void textout(GraphicsBitmap bitmap, GraphicsFont font, const char* text, int x, int y, int color) = 0;
    virtual void textout_centre(GraphicsBitmap bitmap, GraphicsFont font, const char* text, int x, int y, int color) = 0;
    virtual void textprintf(GraphicsBitmap bitmap, GraphicsFont font, int x, int y, int color, const char* format, ...) = 0;
    
    // Color operations
    virtual int makecol(int r, int g, int b) = 0;
    virtual void set_palette_range(const void* palette, int from, int to, int vsync) = 0;
    
    // Screen operations
    virtual GraphicsBitmap get_screen() = 0;
    virtual void clear_to_color(GraphicsBitmap bitmap, int color) = 0;
    virtual void vsync() = 0;
    virtual void rest(int milliseconds) = 0;
    
    // Bitmap properties
    virtual int bitmap_width(GraphicsBitmap bitmap) = 0;
    virtual int bitmap_height(GraphicsBitmap bitmap) = 0;
};

#endif // GRAPHICS_BACKEND_H
