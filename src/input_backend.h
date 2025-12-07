#ifndef INPUT_BACKEND_H
#define INPUT_BACKEND_H

// Abstract input backend interface
// This allows the engine to be independent of the input library

// Key code constants - these will be mapped to backend-specific values
enum KeyCode {
    KEY_UNKNOWN = 0,
    KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H,
    KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
    KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X,
    KEY_Y, KEY_Z,
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
    KEY_8, KEY_9,
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,
    KEY_SPACE, KEY_ENTER, KEY_ESC,
    KEY_LSHIFT, KEY_RSHIFT, KEY_LCONTROL, KEY_RCONTROL,
    KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6,
    KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,
    KEY_MAX
};

class InputBackend {
public:
    virtual ~InputBackend() {}
    
    // Initialization
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    
    // Keyboard
    virtual bool is_key_pressed(KeyCode key) = 0;
    virtual int get_scancode(int key_constant) = 0;
    
    // Mouse
    virtual void poll_mouse() = 0;
    virtual int mouse_x() = 0;
    virtual int mouse_y() = 0;
    virtual bool mouse_button_left() = 0;
    virtual bool mouse_button_right() = 0;
    virtual bool mouse_button_middle() = 0;
    virtual void show_mouse(void* bitmap) = 0;
    
    // Joystick (optional, for future expansion)
    virtual bool init_joystick() = 0;
    virtual int num_joysticks() = 0;
};

#endif // INPUT_BACKEND_H
