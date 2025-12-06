#include "hamoopi_core.h"
#include "libretro.h"
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global state variables
static BITMAP* screen_buffer = NULL;
static bool initialized = false;
static bool running = false;

// Input state for two players
hamoopi_input_t hamoopi_input[2] = {0};

// Key mapping (for now, we'll use a simple approach)
// Player 1 keys
static int p1_up_key = KEY_W;
static int p1_down_key = KEY_S;
static int p1_left_key = KEY_A;
static int p1_right_key = KEY_D;
static int p1_bt1_key = KEY_J;
static int p1_bt2_key = KEY_K;
static int p1_bt3_key = KEY_L;
static int p1_bt4_key = KEY_U;
static int p1_bt5_key = KEY_I;
static int p1_bt6_key = KEY_O;
static int p1_select_key = KEY_1;
static int p1_start_key = KEY_ENTER;

// Player 2 keys
static int p2_up_key = KEY_UP;
static int p2_down_key = KEY_DOWN;
static int p2_left_key = KEY_LEFT;
static int p2_right_key = KEY_RIGHT;
static int p2_bt1_key = KEY_1_PAD;
static int p2_bt2_key = KEY_2_PAD;
static int p2_bt3_key = KEY_3_PAD;
static int p2_bt4_key = KEY_4_PAD;
static int p2_bt5_key = KEY_5_PAD;
static int p2_bt6_key = KEY_6_PAD;
static int p2_select_key = KEY_7_PAD;
static int p2_start_key = KEY_8_PAD;

void hamoopi_init(void)
{
   if (initialized)
      return;
   
   // Create a screen buffer for rendering
   screen_buffer = create_bitmap(640, 480);
   if (!screen_buffer)
   {
      fprintf(stderr, "Failed to create screen buffer\n");
      return;
   }
   
   clear_to_color(screen_buffer, makecol(0, 0, 0));
   
   // Override the global Allegro 'screen' variable
   screen = screen_buffer;
   
   // Initialize keyboard state
   install_keyboard();
   
   initialized = true;
   running = false;
}

void hamoopi_deinit(void)
{
   if (!initialized)
      return;
   
   if (screen_buffer)
   {
      destroy_bitmap(screen_buffer);
      screen_buffer = NULL;
   }
   
   screen = NULL;
   initialized = false;
   running = false;
}

void hamoopi_reset(void)
{
   // Reset game state (to be implemented based on HAMOOPI's reset logic)
   // For now, just clear the screen
   if (screen_buffer)
      clear_to_color(screen_buffer, makecol(0, 0, 0));
}

void hamoopi_run_frame(void)
{
   if (!initialized || !screen_buffer)
      return;
   
   // Update the Allegro key array based on hamoopi_input state
   key[p1_up_key] = hamoopi_input[0].up;
   key[p1_down_key] = hamoopi_input[0].down;
   key[p1_left_key] = hamoopi_input[0].left;
   key[p1_right_key] = hamoopi_input[0].right;
   key[p1_bt1_key] = hamoopi_input[0].a;
   key[p1_bt2_key] = hamoopi_input[0].b;
   key[p1_bt3_key] = hamoopi_input[0].y;
   key[p1_bt4_key] = hamoopi_input[0].x;
   key[p1_bt5_key] = hamoopi_input[0].l;
   key[p1_bt6_key] = hamoopi_input[0].r;
   key[p1_select_key] = hamoopi_input[0].select;
   key[p1_start_key] = hamoopi_input[0].start;
   
   key[p2_up_key] = hamoopi_input[1].up;
   key[p2_down_key] = hamoopi_input[1].down;
   key[p2_left_key] = hamoopi_input[1].left;
   key[p2_right_key] = hamoopi_input[1].right;
   key[p2_bt1_key] = hamoopi_input[1].a;
   key[p2_bt2_key] = hamoopi_input[1].b;
   key[p2_bt3_key] = hamoopi_input[1].y;
   key[p2_bt4_key] = hamoopi_input[1].x;
   key[p2_bt5_key] = hamoopi_input[1].l;
   key[p2_bt6_key] = hamoopi_input[1].r;
   key[p2_select_key] = hamoopi_input[1].select;
   key[p2_start_key] = hamoopi_input[1].start;
   
   // Here we would call the main game loop iteration
   // For now, just draw a test pattern
   if (!running)
   {
      running = true;
      // First frame - draw something visible
      clear_to_color(screen_buffer, makecol(32, 32, 64));
      
      // Draw a test pattern
      for (int i = 0; i < 480; i += 20)
      {
         hline(screen_buffer, 0, i, 640, makecol(64, 64, 128));
      }
      for (int i = 0; i < 640; i += 20)
      {
         vline(screen_buffer, i, 0, 480, makecol(64, 64, 128));
      }
      
      // Draw "HAMOOPI" text
      textout_centre_ex(screen_buffer, font, "HAMOOPI", 320, 220, makecol(255, 255, 255), -1);
      textout_centre_ex(screen_buffer, font, "Libretro Core", 320, 240, makecol(200, 200, 200), -1);
      textout_centre_ex(screen_buffer, font, "Press START to begin", 320, 260, makecol(150, 150, 150), -1);
   }
   
   // Simulate game logic updates here
   // TODO: This is where the main HAMOOPI game loop would be called
}

BITMAP* hamoopi_get_screen_buffer(void)
{
   return screen_buffer;
}

void hamoopi_set_input_state(unsigned port, unsigned device, unsigned index, unsigned id, int16_t state)
{
   if (port > 1)
      return;
   
   switch (id)
   {
      case RETRO_DEVICE_ID_JOYPAD_UP:
         hamoopi_input[port].up = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_DOWN:
         hamoopi_input[port].down = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_LEFT:
         hamoopi_input[port].left = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_RIGHT:
         hamoopi_input[port].right = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_A:
         hamoopi_input[port].a = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_B:
         hamoopi_input[port].b = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_X:
         hamoopi_input[port].x = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_Y:
         hamoopi_input[port].y = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_L:
         hamoopi_input[port].l = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_R:
         hamoopi_input[port].r = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_SELECT:
         hamoopi_input[port].select = state;
         break;
      case RETRO_DEVICE_ID_JOYPAD_START:
         hamoopi_input[port].start = state;
         break;
   }
}
