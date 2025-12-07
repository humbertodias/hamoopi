#ifndef AUDIO_BACKEND_H
#define AUDIO_BACKEND_H

// Abstract audio backend interface
// This allows the engine to be independent of the audio library

typedef void* AudioSample;
typedef void* MidiMusic;

class AudioBackend {
public:
    virtual ~AudioBackend() {}
    
    // Initialization
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    
    // Sample operations
    virtual AudioSample load_sample(const char* filename) = 0;
    virtual void destroy_sample(AudioSample sample) = 0;
    virtual void play_sample(AudioSample sample, int volume, int pan, int frequency, bool loop) = 0;
    virtual void stop_sample(AudioSample sample) = 0;
    virtual void set_volume(int volume) = 0;
    
    // MIDI operations (optional)
    virtual MidiMusic load_midi(const char* filename) = 0;
    virtual void destroy_midi(MidiMusic midi) = 0;
    virtual void play_midi(MidiMusic midi, bool loop) = 0;
    virtual void stop_midi() = 0;
};

#endif // AUDIO_BACKEND_H
