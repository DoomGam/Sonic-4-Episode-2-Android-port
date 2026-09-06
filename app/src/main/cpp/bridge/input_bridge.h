#ifndef INPUT_BRIDGE_H
#define INPUT_BRIDGE_H

#include <cstdint>

enum TouchPhase {
    TOUCH_BEGAN = 0,
    TOUCH_MOVED = 1,
    TOUCH_ENDED = 2,
    TOUCH_CANCELLED = 3
};

struct TouchEventData {
    int id;
    float x;
    float y;
    TouchPhase phase;
};

class InputBridge {
public:
    static InputBridge& getInstance();

    void sendTouchEvent(int id, float x, float y, int phase);
    void sendButtonState(uint32_t buttonMask, bool isPressed);

private:
    InputBridge() = default;
    ~InputBridge() = default;

    uint32_t currentButtonState = 0;
};

extern "C" {
    void fake_registerTouchEvent(int id, float x, float y, int phase);
}

#endif // INPUT_BRIDGE_H
