#include "input_bridge.h"
#include <android/log.h>

#define LOG_TAG "Input_Bridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

InputBridge& InputBridge::getInstance() {
    static InputBridge instance;
    return instance;
}

void InputBridge::sendTouchEvent(int id, float x, float y, int phase) {
    LOGI("Evento de Toque Android -> ID: %d | X: %.2f | Y: %.2f | Fase: %d", id, x, y, phase);
}

void InputBridge::sendButtonState(uint32_t buttonMask, bool isPressed) {
    if (isPressed) {
        currentButtonState |= buttonMask;
    } else {
        currentButtonState &= ~buttonMask;
    }
    LOGI("Estado do Gamepad Atualizado: 0x%X", currentButtonState);
}

extern "C" {
    void fake_registerTouchEvent(int id, float x, float y, int phase) {
        InputBridge::getInstance().sendTouchEvent(id, x, y, phase);
    }
}
