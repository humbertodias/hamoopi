#ifndef ALLEGRO_COMPAT_H
#define ALLEGRO_COMPAT_H

// Allegro 4 to SDL2 Compatibility Layer
// This header provides a compatibility layer to allow Allegro 4 code to work with SDL2

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <map>
#include <string>
#include <vector>

// Allegro 4 Key Code Definitions
#define KEY_A SDL_SCANCODE_A
#define KEY_B SDL_SCANCODE_B
#define KEY_C SDL_SCANCODE_C
#define KEY_D SDL_SCANCODE_D
#define KEY_E SDL_SCANCODE_E
#define KEY_F SDL_SCANCODE_F
#define KEY_G SDL_SCANCODE_G
#define KEY_H SDL_SCANCODE_H
#define KEY_I SDL_SCANCODE_I
#define KEY_J SDL_SCANCODE_J
#define KEY_K SDL_SCANCODE_K
#define KEY_L SDL_SCANCODE_L
#define KEY_M SDL_SCANCODE_M
#define KEY_N SDL_SCANCODE_N
#define KEY_O SDL_SCANCODE_O
#define KEY_P SDL_SCANCODE_P
#define KEY_Q SDL_SCANCODE_Q
#define KEY_R SDL_SCANCODE_R
#define KEY_S SDL_SCANCODE_S
#define KEY_T SDL_SCANCODE_T
#define KEY_U SDL_SCANCODE_U
#define KEY_V SDL_SCANCODE_V
#define KEY_W SDL_SCANCODE_W
#define KEY_X SDL_SCANCODE_X
#define KEY_Y SDL_SCANCODE_Y
#define KEY_Z SDL_SCANCODE_Z
#define KEY_0 SDL_SCANCODE_0
#define KEY_1 SDL_SCANCODE_1
#define KEY_2 SDL_SCANCODE_2
#define KEY_3 SDL_SCANCODE_3
#define KEY_4 SDL_SCANCODE_4
#define KEY_5 SDL_SCANCODE_5
#define KEY_6 SDL_SCANCODE_6
#define KEY_7 SDL_SCANCODE_7
#define KEY_8 SDL_SCANCODE_8
#define KEY_9 SDL_SCANCODE_9
#define KEY_0_PAD SDL_SCANCODE_KP_0
#define KEY_1_PAD SDL_SCANCODE_KP_1
#define KEY_2_PAD SDL_SCANCODE_KP_2
#define KEY_3_PAD SDL_SCANCODE_KP_3
#define KEY_4_PAD SDL_SCANCODE_KP_4
#define KEY_5_PAD SDL_SCANCODE_KP_5
#define KEY_6_PAD SDL_SCANCODE_KP_6
#define KEY_7_PAD SDL_SCANCODE_KP_7
#define KEY_8_PAD SDL_SCANCODE_KP_8
#define KEY_9_PAD SDL_SCANCODE_KP_9
#define KEY_F1 SDL_SCANCODE_F1
#define KEY_F2 SDL_SCANCODE_F2
#define KEY_F3 SDL_SCANCODE_F3
#define KEY_F4 SDL_SCANCODE_F4
#define KEY_F5 SDL_SCANCODE_F5
#define KEY_F6 SDL_SCANCODE_F6
#define KEY_F7 SDL_SCANCODE_F7
#define KEY_F8 SDL_SCANCODE_F8
#define KEY_F9 SDL_SCANCODE_F9
#define KEY_F10 SDL_SCANCODE_F10
#define KEY_F11 SDL_SCANCODE_F11
#define KEY_F12 SDL_SCANCODE_F12
#define KEY_ESC SDL_SCANCODE_ESCAPE
#define KEY_TILDE SDL_SCANCODE_GRAVE
#define KEY_MINUS SDL_SCANCODE_MINUS
#define KEY_EQUALS SDL_SCANCODE_EQUALS
#define KEY_BACKSPACE SDL_SCANCODE_BACKSPACE
#define KEY_TAB SDL_SCANCODE_TAB
#define KEY_OPENBRACE SDL_SCANCODE_LEFTBRACKET
#define KEY_CLOSEBRACE SDL_SCANCODE_RIGHTBRACKET
#define KEY_ENTER SDL_SCANCODE_RETURN
#define KEY_COLON SDL_SCANCODE_SEMICOLON
#define KEY_QUOTE SDL_SCANCODE_APOSTROPHE
#define KEY_BACKSLASH SDL_SCANCODE_BACKSLASH
#define KEY_COMMA SDL_SCANCODE_COMMA
#define KEY_STOP SDL_SCANCODE_PERIOD
#define KEY_SLASH SDL_SCANCODE_SLASH
#define KEY_SPACE SDL_SCANCODE_SPACE
#define KEY_INSERT SDL_SCANCODE_INSERT
#define KEY_DEL SDL_SCANCODE_DELETE
#define KEY_HOME SDL_SCANCODE_HOME
#define KEY_END SDL_SCANCODE_END
#define KEY_PGUP SDL_SCANCODE_PAGEUP
#define KEY_PGDN SDL_SCANCODE_PAGEDOWN
#define KEY_LEFT SDL_SCANCODE_LEFT
#define KEY_RIGHT SDL_SCANCODE_RIGHT
#define KEY_UP SDL_SCANCODE_UP
#define KEY_DOWN SDL_SCANCODE_DOWN
#define KEY_SLASH_PAD SDL_SCANCODE_KP_DIVIDE
#define KEY_ASTERISK SDL_SCANCODE_KP_MULTIPLY
#define KEY_MINUS_PAD SDL_SCANCODE_KP_MINUS
#define KEY_PLUS_PAD SDL_SCANCODE_KP_PLUS
#define KEY_ENTER_PAD SDL_SCANCODE_KP_ENTER
#define KEY_PRTSCR SDL_SCANCODE_PRINTSCREEN
#define KEY_PAUSE SDL_SCANCODE_PAUSE
#define KEY_LSHIFT SDL_SCANCODE_LSHIFT
#define KEY_RSHIFT SDL_SCANCODE_RSHIFT
#define KEY_LCONTROL SDL_SCANCODE_LCTRL
#define KEY_RCONTROL SDL_SCANCODE_RCTRL
#define KEY_ALT SDL_SCANCODE_LALT
#define KEY_ALTGR SDL_SCANCODE_RALT
#define KEY_LWIN SDL_SCANCODE_LGUI
#define KEY_RWIN SDL_SCANCODE_RGUI
#define KEY_MENU SDL_SCANCODE_MENU
#define KEY_SCRLOCK SDL_SCANCODE_SCROLLLOCK
#define KEY_NUMLOCK SDL_SCANCODE_NUMLOCKCLEAR
#define KEY_CAPSLOCK SDL_SCANCODE_CAPSLOCK
#define KEY_MAX SDL_NUM_SCANCODES

// GFX mode constants
#define GFX_AUTODETECT 0
#define GFX_AUTODETECT_FULLSCREEN 1
#define GFX_AUTODETECT_WINDOWED 2

// Audio constants
#define DIGI_AUTODETECT 0
#define MIDI_AUTODETECT 0

// UTF-8 constants
#define U_UTF8 0

// Forward declarations
struct BITMAP;
struct FONT;
struct SAMPLE;
struct MIDI;

// BITMAP structure
struct BITMAP {
    SDL_Texture* texture;
    SDL_Surface* surface;
    int w;
    int h;
    Uint32* line; // For compatibility
};

// FONT structure  
struct FONT {
    TTF_Font* ttf_font;
    SDL_Texture* bitmap_font;
    int char_height;
    int char_width;
};

// SAMPLE structure
struct SAMPLE {
    Mix_Chunk* chunk;
};

// MIDI structure
struct MIDI {
    Mix_Music* music;
};

// Global variables
extern SDL_Window* _sdl_window;
extern SDL_Renderer* _sdl_renderer;
extern BITMAP* screen;
extern const Uint8* key;
extern int mouse_x;
extern int mouse_y;
extern int mouse_b;

// Timer callback function pointer type
typedef void (*timer_callback_t)(void);

// Configuration file management
extern std::map<std::string, std::map<std::string, std::string>> _config_data;
extern std::string _current_config_file;

// Initialization functions
int allegro_init();
void install_timer();
void install_keyboard();
void install_mouse();
int install_sound(int digi, int midi, const char* cfg_path);
void set_color_depth(int depth);
int set_gfx_mode(int card, int w, int h, int v_w, int v_h);
void set_window_title(const char* title);
void set_close_button_callback(void (*callback)(void));
void install_int_ex(timer_callback_t callback, int speed);
void set_uformat(int format);

// BPS to timer conversion
#define BPS_TO_TIMER(x) (1000000 / (x))

// Bitmap functions
BITMAP* create_bitmap(int width, int height);
BITMAP* load_bitmap(const char* filename, void* pal);
void destroy_bitmap(BITMAP* bmp);
void clear(BITMAP* bmp);
void clear_to_color(BITMAP* bmp, int color);
void clear_keybuf();

// Drawing functions
void blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void masked_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void stretch_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int source_w, int source_h, int dest_x, int dest_y, int dest_w, int dest_h);
void masked_stretch_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int source_w, int source_h, int dest_x, int dest_y, int dest_w, int dest_h);
void draw_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y);
void draw_trans_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y);
void draw_sprite_h_flip(BITMAP* bmp, BITMAP* sprite, int x, int y);
void draw_sprite_v_flip(BITMAP* bmp, BITMAP* sprite, int x, int y);
void draw_sprite_vh_flip(BITMAP* bmp, BITMAP* sprite, int x, int y);
void stretch_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y, int w, int h);
void rotate_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y, int angle);
void pivot_sprite(BITMAP* bmp, BITMAP* sprite, int x, int y, int cx, int cy, int angle);

// Drawing mode constants
#define DRAW_MODE_SOLID 0
#define DRAW_MODE_TRANS 1

// Drawing mode functions
void drawing_mode(int mode, BITMAP* pattern, int x_anchor, int y_anchor);
void solid_mode();
void set_trans_blender(int r, int g, int b, int a);

// Primitive drawing
void rectfill(BITMAP* bmp, int x1, int y1, int x2, int y2, int color);
void rect(BITMAP* bmp, int x1, int y1, int x2, int y2, int color);
void line(BITMAP* bmp, int x1, int y1, int x2, int y2, int color);
void hline(BITMAP* bmp, int x1, int y, int x2, int color);
void vline(BITMAP* bmp, int x, int y1, int y2, int color);
void circle(BITMAP* bmp, int x, int y, int radius, int color);
void circlefill(BITMAP* bmp, int x, int y, int radius, int color);
void putpixel(BITMAP* bmp, int x, int y, int color);
int getpixel(BITMAP* bmp, int x, int y);

// Color functions
int makecol(int r, int g, int b);
int getr(int color);
int getg(int color);
int getb(int color);

// Text rendering
FONT* load_font(const char* filename, void* pal, void* param);
void destroy_font(FONT* f);
void textout_ex(BITMAP* bmp, FONT* f, const char* str, int x, int y, int color, int bg);
void textout_centre_ex(BITMAP* bmp, FONT* f, const char* str, int x, int y, int color, int bg);
void textprintf_ex(BITMAP* bmp, FONT* f, int x, int y, int color, int bg, const char* fmt, ...);
void textprintf_centre_ex(BITMAP* bmp, FONT* f, int x, int y, int color, int bg, const char* fmt, ...);
void textprintf_right_ex(BITMAP* bmp, FONT* f, int x, int y, int color, int bg, const char* fmt, ...);
int text_length(FONT* f, const char* str);
int text_height(FONT* f);

// Audio functions
SAMPLE* load_sample(const char* filename);
void destroy_sample(SAMPLE* spl);
int play_sample(SAMPLE* spl, int vol, int pan, int freq, int loop);
void stop_sample(SAMPLE* spl);
void adjust_sample(SAMPLE* spl, int vol, int pan, int freq, int loop);
MIDI* load_midi(const char* filename);
void destroy_midi(MIDI* midi);
int play_midi(MIDI* midi, int loop);
void stop_midi();
void set_volume(int digi_volume, int midi_volume);

// Configuration file functions
void set_config_file(const char* filename);
const char* get_config_string(const char* section, const char* key, const char* def);
int get_config_int(const char* section, const char* key, int def);
float get_config_float(const char* section, const char* key, float def);
void set_config_string(const char* section, const char* key, const char* val);
void set_config_int(const char* section, const char* key, int val);

// Utility functions
void allegro_message(const char* msg, ...);
void rest(int ms);
int exists(const char* filename);

// Allegro main macro
#define END_OF_MAIN()

// Helper functions for SDL2 event processing
void _process_sdl_events();
void _update_keyboard_state();

// Internal helper functions
SDL_Surface* _load_pcx(const char* filename);
FONT* _load_pcx_font(const char* filename);

#endif // ALLEGRO_COMPAT_H
