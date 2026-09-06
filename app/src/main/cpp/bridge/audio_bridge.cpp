#include "audio_bridge.h"
#include <android/log.h>

#define LOG_TAG "Audio_Bridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

AudioBridge& AudioBridge::getInstance() {
    static AudioBridge instance;
    return instance;
}

bool AudioBridge::initAudio() {
    LOGI("Inicializando OpenSL ES para áudio nativo no Android...");

    SLresult result;

    result = slCreateEngine(&engineObject, 0, nullptr, 0, nullptr, nullptr);
    if (result != SL_RESULT_SUCCESS) return false;

    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) return false;

    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineInterface);
    if (result != SL_RESULT_SUCCESS) return false;

    result = (*engineInterface)->CreateOutputMix(engineInterface, &outputMixObject, 0, nullptr, nullptr);
    if (result != SL_RESULT_SUCCESS) return false;

    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS) return false;

    initialized = true;
    LOGI("Engine de áudio OpenSL ES pronta.");
    return true;
}

void AudioBridge::playSound(const char* soundPath) {
    if (!initialized) return;
    LOGI("Reproduzindo efeito/trilha: %s", soundPath);
}

void AudioBridge::stopAllSounds() {
    if (!initialized) return;
    LOGI("Parando reprodução de áudio.");
}

void AudioBridge::destroyAudio() {
    if (outputMixObject != nullptr) {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = nullptr;
    }
    if (engineObject != nullptr) {
        (*engineObject)->Destroy(engineObject);
        engineObject = nullptr;
        engineInterface = nullptr;
    }
    initialized = false;
    LOGI("Engine de áudio liberada.");
}

extern "C" {
    void fake_AudioServicesPlaySystemSound(uint32_t soundID) {
        LOGI("AudioServicesPlaySystemSound chamado com id: %d", soundID);
    }

    void fake_alSourcePlay(uint32_t source) {
        LOGI("alSourcePlay (OpenAL) executado para fonte id: %d", source);
    }
}
