#ifndef ALLEGRO_AUDIO_BACKEND_H
#define ALLEGRO_AUDIO_BACKEND_H

#include "audio_backend.h"
#include <allegro.h>

class AllegroAudioBackend : public AudioBackend {
public:
    bool init() override {
        return install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) == 0;
    }
    
    void shutdown() override {
        remove_sound();
    }
    
    AudioSample load_sample(const char* filename) override {
        return ::load_sample(filename);
    }
    
    void destroy_sample(AudioSample sample) override {
        if (sample) {
            ::destroy_sample((SAMPLE*)sample);
        }
    }
    
    void play_sample(AudioSample sample, int volume, int pan, int frequency, bool loop) override {
        ::play_sample((SAMPLE*)sample, volume, pan, frequency, loop ? 1 : 0);
    }
    
    void stop_sample(AudioSample sample) override {
        ::stop_sample((SAMPLE*)sample);
    }
    
    void set_volume(int volume) override {
        ::set_volume(volume, volume);
    }
    
    MidiMusic load_midi(const char* filename) override {
        return ::load_midi(filename);
    }
    
    void destroy_midi(MidiMusic midi) override {
        if (midi) {
            ::destroy_midi((MIDI*)midi);
        }
    }
    
    void play_midi(MidiMusic midi, bool loop) override {
        ::play_midi((MIDI*)midi, loop ? 1 : 0);
    }
    
    void stop_midi() override {
        ::stop_midi();
    }
};

#endif // ALLEGRO_AUDIO_BACKEND_H
