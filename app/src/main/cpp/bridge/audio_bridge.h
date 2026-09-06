#ifndef AUDIO_BRIDGE_H
#define AUDIO_BRIDGE_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class AudioBridge {
public:
    static AudioBridge& getInstance();

    bool initAudio();
    void playSound(const char* soundPath);
    void stopAllSounds();
    void destroyAudio();

private:
    AudioBridge() = default;
    ~AudioBridge() = default;

    SLObjectItf engineObject = nullptr;
    SLEngineItf engineInterface = nullptr;
    SLObjectItf outputMixObject = nullptr;

    bool initialized = false;
};

extern "C" {
    void fake_AudioServicesPlaySystemSound(uint32_t soundID);
    void fake_alSourcePlay(uint32_t source);
}

#endif // AUDIO_BRIDGE_H
