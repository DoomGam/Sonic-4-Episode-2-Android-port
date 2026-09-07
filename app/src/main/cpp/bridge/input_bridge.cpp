#include "input_bridge.h"
#include <android/log.h>

#define LOG_TAG "InputBridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

InputBridge& InputBridge::getInstance() {
    static InputBridge instance;
    return instance;
}

void InputBridge::sendTouchEvent(int id, float x, float y, int phase) {
    (void)id; (void)x; (void)y; (void)phase;
}

extern "C" void fake_registerTouchEvent(int id, float x, float y, int phase) {
    InputBridge::getInstance().sendTouchEvent(id, x, y, phase);
}
