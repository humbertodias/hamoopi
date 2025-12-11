#ifndef HAMOOPI_INITIALIZATION_H
#define HAMOOPI_INITIALIZATION_H

#include "types.h"
#include "../backend/platform_compat.h"

/**
 * Initialize Allegro/SDL subsystems
 * Returns 0 on success, non-zero on failure
 */
int initialize_allegro_subsystems(void);

/**
 * Load all font resources
 * Returns 0 on success, non-zero on failure
 */
int load_fonts(void);

/**
 * Load configuration from SETUP.ini
 * Returns 0 on success, non-zero on failure
 */
int load_configuration(void);

/**
 * Load all system bitmaps (UI elements, sprites, etc.)
 * Returns 0 on success, non-zero on failure
 */
int load_system_bitmaps(void);

/**
 * Load all sound and music resources
 * Returns 0 on success, non-zero on failure
 */
int load_audio_resources(void);

/**
 * Initialize character and background data
 * Returns 0 on success, non-zero on failure
 */
int initialize_character_data(void);

/**
 * Create dynamic bitmaps for rendering
 * Returns 0 on success, non-zero on failure
 */
int create_render_buffers(void);

/**
 * Set window mode (fullscreen or windowed) based on configuration
 * Returns 0 on success, non-zero on failure
 */
int set_window_mode(int fullscreen, int res_x, int res_y);

/**
 * Display error message based on language setting
 */
void display_error_message(const char *idioma, int error_code);

#endif // HAMOOPI_INITIALIZATION_H
