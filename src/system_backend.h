#ifndef SYSTEM_BACKEND_H
#define SYSTEM_BACKEND_H

// Abstract system backend interface
// This allows the engine to be independent of the system/timing library

typedef void (*TimerCallback)();
typedef void (*CloseCallback)();

class SystemBackend {
public:
    virtual ~SystemBackend() {}
    
    // Initialization
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    
    // Timing
    virtual void install_timer(TimerCallback callback, int fps) = 0;
    virtual void rest(int milliseconds) = 0;
    
    // File operations
    virtual bool file_exists(const char* filename) = 0;
    virtual void set_config_file(const char* filename) = 0;
    virtual const char* get_config_string(const char* section, const char* key, const char* default_value) = 0;
    virtual int get_config_int(const char* section, const char* key, int default_value) = 0;
    virtual void set_config_string(const char* section, const char* key, const char* value) = 0;
    virtual void set_config_int(const char* section, const char* key, int value) = 0;
    
    // Dialogs/Messages
    virtual void show_message(const char* message) = 0;
    
    // Close button
    virtual void set_close_button_callback(CloseCallback callback) = 0;
    
    // UTF-8 support
    virtual void set_utf8_format() = 0;
};

#endif // SYSTEM_BACKEND_H
