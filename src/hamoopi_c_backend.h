#ifndef HAMOOPI_C_BACKEND_H
#define HAMOOPI_C_BACKEND_H

/* Pure C Backend Interface for HAMOOPI
 * This is the ONLY header that HAMOOPI.c should include
 * All types, functions, and dependencies are provided through this interface
 */

/* ============================================================================
 * OPAQUE TYPES - Implementation details hidden from HAMOOPI.c
 * ============================================================================ */

/* Graphics types */
typedef struct HamoopiImage HamoopiImage;
typedef struct HamoopiFont HamoopiFont;

/* Use BITMAP/FONT as aliases for compatibility */
typedef HamoopiImage BITMAP;
typedef HamoopiFont FONT;

/* Audio types */
typedef struct HamoopiSample SAMPLE;
typedef struct HamoopiMidi MIDI;

/* Configuration type */
typedef struct HamoopiConfig CONFIG;

/* ============================================================================
 * COLOR TYPE
 * ============================================================================ */
typedef unsigned int Color;

/* ============================================================================
 * STDLIB REPLACEMENTS - No direct stdlib dependencies in HAMOOPI.c
 * ============================================================================ */

/* String formatting */
int hamoopi_sprintf(char* str, const char* format, ...);
int hamoopi_snprintf(char* str, int size, const char* format, ...);

/* Math functions */
int hamoopi_abs(int x);
double hamoopi_floor(double x);
double hamoopi_ceil(double x);
double hamoopi_sqrt(double x);
double hamoopi_sin(double x);
double hamoopi_cos(double x);

/* Memory operations (if needed) */
void* hamoopi_memset(void* ptr, int value, unsigned int num);
void* hamoopi_memcpy(void* dest, const void* src, unsigned int num);

/* ============================================================================
 * GRAPHICS BACKEND FUNCTIONS
 * ============================================================================ */

/* Initialization */
int hamoopi_init(void);
void hamoopi_shutdown(void);
int hamoopi_set_gfx_mode(int mode, int width, int height, int v_width, int v_height);
void hamoopi_set_color_depth(int depth);
void hamoopi_set_window_title(const char* title);

/* Bitmap operations */
BITMAP* hamoopi_create_bitmap(int width, int height);
BITMAP* hamoopi_load_bitmap(const char* filename, void* palette);
void hamoopi_destroy_bitmap(BITMAP* bitmap);
void hamoopi_clear_bitmap(BITMAP* bitmap);
void hamoopi_clear_to_color(BITMAP* bitmap, Color color);

/* Bitmap properties - direct field access replacement */
int hamoopi_bitmap_width(BITMAP* bitmap);
int hamoopi_bitmap_height(BITMAP* bitmap);

/* Blitting operations */
void hamoopi_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void hamoopi_masked_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void hamoopi_stretch_blit(BITMAP* source, BITMAP* dest, int source_x, int source_y, int source_w, int source_h, int dest_x, int dest_y, int dest_w, int dest_h);
void hamoopi_draw_sprite(BITMAP* dest, BITMAP* sprite, int x, int y);
void hamoopi_draw_sprite_h_flip(BITMAP* dest, BITMAP* sprite, int x, int y);
void hamoopi_draw_sprite_v_flip(BITMAP* dest, BITMAP* sprite, int x, int y);

/* Drawing primitives */
void hamoopi_rectfill(BITMAP* bitmap, int x1, int y1, int x2, int y2, Color color);
void hamoopi_rect(BITMAP* bitmap, int x1, int y1, int x2, int y2, Color color);
void hamoopi_line(BITMAP* bitmap, int x1, int y1, int x2, int y2, Color color);
void hamoopi_hline(BITMAP* bitmap, int x1, int y, int x2, Color color);
void hamoopi_vline(BITMAP* bitmap, int x, int y1, int y2, Color color);
void hamoopi_circle(BITMAP* bitmap, int x, int y, int radius, Color color);
void hamoopi_circlefill(BITMAP* bitmap, int x, int y, int radius, Color color);
void hamoopi_putpixel(BITMAP* bitmap, int x, int y, Color color);
Color hamoopi_getpixel(BITMAP* bitmap, int x, int y);

/* Color operations */
Color hamoopi_makecol(int r, int g, int b);
int hamoopi_getr(Color c);
int hamoopi_getg(Color c);
int hamoopi_getb(Color c);

/* Palette operations */
void hamoopi_set_palette_range(const void* palette, int from, int to, int vsync);

/* Screen operations */
extern BITMAP* hamoopi_screen;  /* Global screen bitmap */
#define screen hamoopi_screen

/* Font operations */
FONT* hamoopi_load_font(const char* filename, void* palette, void* param);
void hamoopi_destroy_font(FONT* font);
void hamoopi_textout_ex(BITMAP* bmp, FONT* f, const char* s, int x, int y, Color color, Color bg);
void hamoopi_textout_centre_ex(BITMAP* bmp, FONT* f, const char* s, int x, int y, Color color, Color bg);
void hamoopi_textprintf_ex(BITMAP* bmp, FONT* f, int x, int y, Color color, Color bg, const char* fmt, ...);
int hamoopi_text_length(FONT* f, const char* str);
int hamoopi_text_height(FONT* f);

/* ============================================================================
 * INPUT BACKEND FUNCTIONS
 * ============================================================================ */

/* Keyboard */
int hamoopi_install_keyboard(void);
int hamoopi_keypressed(void);
int hamoopi_readkey(void);
void hamoopi_clear_keybuf(void);

/* Key state array */
extern volatile char hamoopi_key[];
#define key hamoopi_key

/* Key codes - must match Allegro for compatibility */
#define KEY_A            1
#define KEY_B            2
#define KEY_C            3
#define KEY_D            4
#define KEY_E            5
#define KEY_F            6
#define KEY_G            7
#define KEY_H            8
#define KEY_I            9
#define KEY_J            10
#define KEY_K            11
#define KEY_L            12
#define KEY_M            13
#define KEY_N            14
#define KEY_O            15
#define KEY_P            16
#define KEY_Q            17
#define KEY_R            18
#define KEY_S            19
#define KEY_T            20
#define KEY_U            21
#define KEY_V            22
#define KEY_W            23
#define KEY_X            24
#define KEY_Y            25
#define KEY_Z            26
#define KEY_0            27
#define KEY_1            28
#define KEY_2            29
#define KEY_3            30
#define KEY_4            31
#define KEY_5            32
#define KEY_6            33
#define KEY_7            34
#define KEY_8            35
#define KEY_9            36
#define KEY_ESC          1
#define KEY_SPACE        57
#define KEY_ENTER        28
#define KEY_UP           72
#define KEY_DOWN         80
#define KEY_LEFT         75
#define KEY_RIGHT        77

/* Mouse */
int hamoopi_install_mouse(void);
void hamoopi_show_mouse(BITMAP* bmp);
void hamoopi_hide_mouse(BITMAP* bmp);
int hamoopi_mouse_x(void);
int hamoopi_mouse_y(void);
int hamoopi_mouse_b(void);

/* Mouse position globals - for direct access compatibility */
#define mouse_x (hamoopi_mouse_x())
#define mouse_y (hamoopi_mouse_y())
#define mouse_b (hamoopi_mouse_b())

/* Joystick */
int hamoopi_install_joystick(int type);
int hamoopi_poll_joystick(void);
int hamoopi_num_joysticks(void);

/* Joystick globals - for compatibility */
#define num_joysticks (hamoopi_num_joysticks())

/* ============================================================================
 * AUDIO BACKEND FUNCTIONS
 * ============================================================================ */

int hamoopi_install_sound(int digi, int midi, const char* cfg_path);
void hamoopi_remove_sound(void);

/* Sample operations */
SAMPLE* hamoopi_load_sample(const char* filename);
void hamoopi_destroy_sample(SAMPLE* spl);
int hamoopi_play_sample(SAMPLE* spl, int vol, int pan, int freq, int loop);
void hamoopi_stop_sample(SAMPLE* spl);
void hamoopi_adjust_sample(SAMPLE* spl, int vol, int pan, int freq, int loop);

/* MIDI operations */
MIDI* hamoopi_load_midi(const char* filename);
void hamoopi_destroy_midi(MIDI* midi);
int hamoopi_play_midi(MIDI* midi, int loop);
void hamoopi_stop_midi(void);
int hamoopi_midi_pos(void);

/* ============================================================================
 * SYSTEM BACKEND FUNCTIONS
 * ============================================================================ */

/* Timing */
void hamoopi_install_timer(void);
void hamoopi_install_int_ex(void (*proc)(void), int speed);  /* For custom timers */
void hamoopi_rest(int msec);
int hamoopi_retrace_count(void);

/* Special system functions */
void hamoopi_set_utf8_format(void);
void hamoopi_set_close_button_callback(void (*callback)(void));

/* Timer globals - for compatibility */
#define retrace_count (hamoopi_retrace_count())
#define SCREEN_W 640  /* These should be queried from actual screen */
#define SCREEN_H 480

/* Configuration */
void hamoopi_set_config_file(const char* filename);
const char* hamoopi_get_config_string(const char* section, const char* name, const char* def);
int hamoopi_get_config_int(const char* section, const char* name, int def);
void hamoopi_set_config_string(const char* section, const char* name, const char* val);
void hamoopi_set_config_int(const char* section, const char* name, int val);

/* Messages */
int hamoopi_alert(const char* s1, const char* s2, const char* s3, const char* b1, const char* b2, int c1, int c2);
void hamoopi_allegro_message(const char* msg);

/* File operations */
int hamoopi_exists(const char* filename);

/* Random */
int hamoopi_rand(void);

/* MIDI position global */
int hamoopi_midi_pos(void);
#define midi_pos (hamoopi_midi_pos())

/* Exit */
void hamoopi_allegro_exit(void);

/* ============================================================================
 * CONSTANTS
 * ============================================================================ */

/* Graphics modes */
#define GFX_AUTODETECT           0
#define GFX_AUTODETECT_WINDOWED  1
#define GFX_AUTODETECT_FULLSCREEN 2

/* Boolean values */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* NULL */
#ifndef NULL
#define NULL ((void*)0)
#endif

/* ============================================================================
 * COMPATIBILITY LAYER - Maps old function names to hamoopi_ versions
 * This allows existing code to work without modification
 * ============================================================================ */

/* Allegro initialization */
#define allegro_init hamoopi_init
#define allegro_exit hamoopi_allegro_exit
#define install_timer hamoopi_install_timer
#define install_keyboard hamoopi_install_keyboard
#define install_mouse hamoopi_install_mouse
#define install_joystick hamoopi_install_joystick
#define install_sound hamoopi_install_sound
#define remove_sound hamoopi_remove_sound

/* Graphics */
#define set_gfx_mode hamoopi_set_gfx_mode
#define set_color_depth hamoopi_set_color_depth
#define set_window_title hamoopi_set_window_title
#define create_bitmap hamoopi_create_bitmap
#define load_bitmap hamoopi_load_bitmap
#define destroy_bitmap hamoopi_destroy_bitmap
#define clear_bitmap hamoopi_clear_bitmap
#define clear_to_color hamoopi_clear_to_color
#define blit hamoopi_blit
#define masked_blit hamoopi_masked_blit
#define stretch_blit hamoopi_stretch_blit
#define draw_sprite hamoopi_draw_sprite
#define draw_sprite_h_flip hamoopi_draw_sprite_h_flip
#define draw_sprite_v_flip hamoopi_draw_sprite_v_flip
#define rectfill hamoopi_rectfill
#define rect hamoopi_rect
#define line hamoopi_line
#define hline hamoopi_hline
#define vline hamoopi_vline
#define circle hamoopi_circle
#define circlefill hamoopi_circlefill
#define putpixel hamoopi_putpixel
#define getpixel hamoopi_getpixel
#define makecol hamoopi_makecol
#define getr hamoopi_getr
#define getg hamoopi_getg
#define getb hamoopi_getb
#define set_palette_range hamoopi_set_palette_range

/* Fonts */
#define load_font hamoopi_load_font
#define destroy_font hamoopi_destroy_font
#define textout_ex hamoopi_textout_ex
#define textout_centre_ex hamoopi_textout_centre_ex
#define textprintf_ex hamoopi_textprintf_ex
#define text_length hamoopi_text_length
#define text_height hamoopi_text_height

/* Input */
#define keypressed hamoopi_keypressed
#define readkey hamoopi_readkey
#define clear_keybuf hamoopi_clear_keybuf
#define show_mouse hamoopi_show_mouse
#define poll_joystick hamoopi_poll_joystick

/* Audio */
#define load_sample hamoopi_load_sample
#define destroy_sample hamoopi_destroy_sample
#define play_sample hamoopi_play_sample
#define stop_sample hamoopi_stop_sample
#define adjust_sample hamoopi_adjust_sample
#define load_midi hamoopi_load_midi
#define destroy_midi hamoopi_destroy_midi
#define play_midi hamoopi_play_midi
#define stop_midi hamoopi_stop_midi

/* System */
#define rest hamoopi_rest
#define set_config_file hamoopi_set_config_file
#define get_config_string hamoopi_get_config_string
#define get_config_int hamoopi_get_config_int
#define set_config_string hamoopi_set_config_string
#define set_config_int hamoopi_set_config_int
#define alert hamoopi_alert
#define allegro_message hamoopi_allegro_message
#define exists hamoopi_exists

/* Stdlib replacements */
#define sprintf hamoopi_sprintf
#define snprintf hamoopi_snprintf
#define abs hamoopi_abs
#define floor hamoopi_floor
#define ceil hamoopi_ceil
#define sqrt hamoopi_sqrt
#define sin hamoopi_sin
#define cos hamoopi_cos

/* Additional compatibility macros */
#define SCREEN_W 640
#define SCREEN_H 480
#define END_OF_MAIN()

#endif /* HAMOOPI_C_BACKEND_H */
