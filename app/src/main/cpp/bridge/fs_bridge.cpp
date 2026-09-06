#include "fs_bridge.h"
#include <android/log.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdarg>

#define LOG_TAG "FS_Bridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)

FSBridge& FSBridge::getInstance() {
    static FSBridge instance;
    return instance;
}

void FSBridge::setBaseDataPath(const std::string& path) {
    baseDataPath = path;
    LOGI("Caminho base de dados configurado para: %s", baseDataPath.c_str());
}

std::string FSBridge::resolvePath(const char* originalPath) {
    if (!originalPath) return "";

    std::string pathStr(originalPath);

    if (pathStr.find("/var/mobile/") != std::string::npos ||
        pathStr.find(".app/") != std::string::npos) {
        
        size_t lastSlash = pathStr.find_last_of('/');
        if (lastSlash != std::string::npos) {
            std::string fileName = pathStr.substr(lastSlash + 1);
            return baseDataPath + "/" + fileName;
        }
    }

    if (originalPath[0] != '/') {
        return baseDataPath + "/" + pathStr;
    }

    return pathStr;
}

FILE* FSBridge::customFopen(const char* path, const char* mode) {
    std::string resolved = resolvePath(path);
    LOGI("fopen interceptado: %s -> %s", path, resolved.c_str());
    return fopen(resolved.c_str(), mode);
}

int FSBridge::customOpen(const char* path, int flags, mode_t mode) {
    std::string resolved = resolvePath(path);
    LOGI("open interceptado: %s -> %s", path, resolved.c_str());
    return open(resolved.c_str(), flags, mode);
}

extern "C" {
    FILE* fake_fopen(const char* path, const char* mode) {
        return FSBridge::getInstance().customFopen(path, mode);
    }

    int fake_open(const char* path, int flags, ...) {
        mode_t mode = 0;
        if (flags & O_CREAT) {
            va_list args;
            va_start(args, flags);
            mode = static_cast<mode_t>(va_arg(args, int));
            va_end(args);
        }
        return FSBridge::getInstance().customOpen(path, flags, mode);
    }
}
