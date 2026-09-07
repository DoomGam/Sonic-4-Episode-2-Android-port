#ifndef INPUT_BRIDGE_H
#define INPUT_BRIDGE_H

class InputBridge {
public:
    static InputBridge& getInstance();
    void sendTouchEvent(int id, float x, float y, int phase);
private:
    InputBridge() = default;
    ~InputBridge() = default;
};

extern "C" {
    void fake_registerTouchEvent(int id, float x, float y, int phase);
}

#endif // INPUT_BRIDGE_H
