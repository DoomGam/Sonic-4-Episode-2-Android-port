#ifndef GLES_BRIDGE_H
#define GLES_BRIDGE_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>

class GLESBridge {
public:
    static GLESBridge& getInstance();

    bool initGL();
    void resize(int width, int height);
    void renderFrame();
    void destroyGL();

private:
    GLESBridge() = default;
    ~GLESBridge() = default;

    int screenWidth = 0;
    int screenHeight = 0;
    bool initialized = false;
};

extern "C" {
    void* fake_EAGLContext_setCurrentContext(void* context);
    void fake_glSwapBuffers();
}

#endif // GLES_BRIDGE_H
