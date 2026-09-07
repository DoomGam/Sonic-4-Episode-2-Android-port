#ifndef AUDIO_BRIDGE_H
#define AUDIO_BRIDGE_H

class AudioBridge {
public:
    static AudioBridge& getInstance();
    void initAudio();
private:
    AudioBridge() = default;
    ~AudioBridge() = default;
};

extern "C" {
    void fake_AudioServicesPlaySystemSound(unsigned int soundID);
    void fake_alSourcePlay(unsigned int source);
}

#endif // AUDIO_BRIDGE_H
