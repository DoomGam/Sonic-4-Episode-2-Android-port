#include "gles_bridge.h"
#include <android/log.h>

#define LOG_TAG "GLES_Bridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

GLESBridge& GLESBridge::getInstance() {
    static GLESBridge instance;
    return instance;
}

bool GLESBridge::initGL() {
    LOGI("Inicializando contexto OpenGL ES 2.0 no Android...");
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    initialized = true;
    return true;
}

void GLESBridge::resize(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
    LOGI("Resolução da tela atualizada no OpenGL: %dx%d", width, height);
}

void GLESBridge::renderFrame() {
    if (!initialized) return;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GLESBridge::destroyGL() {
    initialized = false;
    LOGI("Contexto OpenGL ES destruído.");
}

extern "C" {
    void* fake_EAGLContext_setCurrentContext(void* context) {
        return context;
    }

    void fake_glSwapBuffers() {
    }
}
