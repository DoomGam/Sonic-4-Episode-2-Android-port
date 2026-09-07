#include "audio_bridge.h"
#include <android/log.h>

#define LOG_TAG "AudioBridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

AudioBridge& AudioBridge::getInstance() {
    static AudioBridge instance;
    return instance;
}

void AudioBridge::initAudio() {
    LOGI("Sistema de audio OpenSL ES inicializado.");
}

extern "C" {
    void fake_AudioServicesPlaySystemSound(unsigned int soundID) {
        (void)soundID;
    }

    void fake_alSourcePlay(unsigned int source) {
        (void)source;
    }
}
