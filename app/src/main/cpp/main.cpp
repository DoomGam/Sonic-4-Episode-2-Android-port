#include <jni.h>
#include <android/log.h>
#include "loader/mach_o_loader.h"
#include "bridge/gles_bridge.h"
#include "bridge/input_bridge.h"

#define LOG_TAG "Sonic4Ep2_Loader"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static MachOLoader g_loader;

extern "C" JNIEXPORT jboolean JNICALL
Java_com_doomgam_sonic4ep2_MainActivity_initNativeEngine(
        JNIEnv* env,
        jobject instance,
        jstring dataDirPath,
        jstring binaryPath) {

    const char* nativeBinaryPath = env->GetStringUTFChars(binaryPath, nullptr);
    LOGI("Iniciando o carregador do Sonic 4 Ep 2 com o binário: %s", nativeBinaryPath);

    if (!g_loader.loadBinary(nativeBinaryPath)) {
        LOGE("Falha ao carregar o binário Mach-O do Sonic 4 Episode 2!");
        env->ReleaseStringUTFChars(binaryPath, nativeBinaryPath);
        return JNI_FALSE;
    }

    env->ReleaseStringUTFChars(binaryPath, nativeBinaryPath);
    return JNI_TRUE;
}

extern "C" JNIEXPORT void JNICALL
Java_com_doomgam_sonic4ep2_MainActivity_sendTouchEvent(
        JNIEnv* env,
        jobject instance,
        jint id,
        jfloat x,
        jfloat y,
        jint phase) {
    InputBridge::getInstance().sendTouchEvent(id, x, y, phase);
}

extern "C" JNIEXPORT void JNICALL
Java_com_doomgam_sonic4ep2_GameRenderer_nativeInitGL(
        JNIEnv* env,
        jobject instance) {
    GLESBridge::getInstance().initGL();
}

extern "C" JNIEXPORT void JNICALL
Java_com_doomgam_sonic4ep2_GameRenderer_nativeResize(
        JNIEnv* env,
        jobject instance,
        jint width,
        jint height) {
    GLESBridge::getInstance().resize(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_doomgam_sonic4ep2_GameRenderer_nativeRenderFrame(
        JNIEnv* env,
        jobject instance) {
    GLESBridge::getInstance().renderFrame();
}
