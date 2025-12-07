/* Backend-agnostic Type Definitions
 * 
 * This header provides type definitions that work with both Allegro and STB backends.
 * Include this instead of <allegro.h> when using STB backend.
 */

#ifndef BACKEND_TYPES_H
#define BACKEND_TYPES_H

#ifdef USE_STB_BACKEND
    /* STB Backend - Define types that match Allegro API */
    
    /* Forward declare structures */
    typedef struct HamoopiImage BITMAP;
    typedef struct HamoopiFont FONT;
    typedef struct HamoopiSample SAMPLE;
    typedef struct HamoopiMidi MIDI;
    
    /* Color depth modes */
    #define GFX_AUTODETECT 0
    #define GFX_AUTODETECT_WINDOWED 1
    #define GFX_AUTODETECT_FULLSCREEN 2
    
    /* Keyboard constants - These map to scancode values */
    #define KEY_ESC     1
    #define KEY_SPACE   57
    #define KEY_ENTER   28
    #define KEY_UP      72
    #define KEY_DOWN    80
    #define KEY_LEFT    75
    #define KEY_RIGHT   77
    #define KEY_A       30
    #define KEY_S       31
    #define KEY_D       32
    #define KEY_W       17
    #define KEY_Z       44
    #define KEY_X       45
    #define KEY_C       46
    
    /* Mouse buttons */
    #define MOUSE_LEFT  1
    #define MOUSE_RIGHT 2
    #define MOUSE_MIDDLE 4
    
    /* Drawing modes */
    #define DRAW_MODE_SOLID 0
    #define DRAW_MODE_XOR 1
    #define DRAW_MODE_COPY_PATTERN 2
    #define DRAW_MODE_MASKED_PATTERN 3
    #define DRAW_MODE_TRANS 4
    
    /* Global variables that Allegro provides */
    extern int SCREEN_W;
    extern int SCREEN_H;
    extern BITMAP* screen;
    extern volatile int mouse_x;
    extern volatile int mouse_y;
    extern volatile int mouse_b;
    extern volatile int key[];
    
    /* Color maker function */
    int makecol(int r, int g, int b);
    int makeacol(int r, int g, int b, int a);
    int getr(int color);
    int getg(int color);
    int getb(int color);
    int geta(int color);
    
#else
    /* Allegro Backend - Use standard Allegro types */
    #include <allegro.h>
#endif

#endif /* BACKEND_TYPES_H */
