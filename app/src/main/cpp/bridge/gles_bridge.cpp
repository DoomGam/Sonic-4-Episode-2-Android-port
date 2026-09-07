#include "gles_bridge.h"
#include <android/log.h>
#include <GLES2/gl2.h>

#define LOG_TAG "GLESBridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

GLESBridge& GLESBridge::getInstance() {
    static GLESBridge instance;
    return instance;
}

void GLESBridge::initGL() {
    LOGI("OpenGL ES 2.0 inicializado.");
}

void GLESBridge::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void GLESBridge::renderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

extern "C" bool fake_EAGLContext_setCurrentContext(void* context) {
    (void)context;
    return true;
}
