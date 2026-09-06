#include <jni.h>
#include <android/log.h>
#include "loader/mach_o_loader.h"

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
