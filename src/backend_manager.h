#ifndef BACKEND_MANAGER_H
#define BACKEND_MANAGER_H

#include "graphics_backend.h"
#include "input_backend.h"
#include "audio_backend.h"
#include "system_backend.h"

// Singleton class to manage all backends
class BackendManager {
private:
    static BackendManager* instance;
    
    GraphicsBackend* graphics;
    InputBackend* input;
    AudioBackend* audio;
    SystemBackend* system;
    
    BackendManager() : graphics(nullptr), input(nullptr), audio(nullptr), system(nullptr) {}
    
public:
    static BackendManager* getInstance() {
        if (!instance) {
            instance = new BackendManager();
        }
        return instance;
    }
    
    void setGraphicsBackend(GraphicsBackend* backend) { graphics = backend; }
    void setInputBackend(InputBackend* backend) { input = backend; }
    void setAudioBackend(AudioBackend* backend) { audio = backend; }
    void setSystemBackend(SystemBackend* backend) { system = backend; }
    
    GraphicsBackend* getGraphics() { return graphics; }
    InputBackend* getInput() { return input; }
    AudioBackend* getAudio() { return audio; }
    SystemBackend* getSystem() { return system; }
    
    bool initAll() {
        bool success = true;
        if (system) success &= system->init();
        if (graphics) success &= graphics->init();
        if (input) success &= input->init();
        if (audio) success &= audio->init();
        return success;
    }
    
    void shutdownAll() {
        if (audio) audio->shutdown();
        if (input) input->shutdown();
        if (graphics) graphics->shutdown();
        if (system) system->shutdown();
    }
    
    ~BackendManager() {
        shutdownAll();
    }
};

// Initialize static instance
BackendManager* BackendManager::instance = nullptr;

#endif // BACKEND_MANAGER_H
