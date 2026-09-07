#ifndef GLES_BRIDGE_H
#define GLES_BRIDGE_H

class GLESBridge {
public:
    static GLESBridge& getInstance();
    void initGL();
    void resize(int width, int height);
    void renderFrame();
private:
    GLESBridge() = default;
    ~GLESBridge() = default;
};

extern "C" {
    bool fake_EAGLContext_setCurrentContext(void* context);
}

#endif // GLES_BRIDGE_H
