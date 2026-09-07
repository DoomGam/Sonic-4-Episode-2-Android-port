#include "fs_bridge.h"
#include <android/log.h>
#include <fcntl.h>
#include <cstdarg>

#define LOG_TAG "FSBridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

FSBridge& FSBridge::getInstance() {
    static FSBridge instance;
    return instance;
}

void FSBridge::setBaseDataPath(const std::string& path) {
    baseDataPath = path;
}

std::string FSBridge::resolvePath(const char* originalPath) {
    if (!originalPath) return "";
    return baseDataPath + "/" + originalPath;
}

FILE* FSBridge::customFopen(const char* path, const char* mode) {
    std::string resolved = resolvePath(path);
    return fopen(resolved.c_str(), mode);
}

int FSBridge::customOpen(const char* path, int flags, mode_t mode) {
    std::string resolved = resolvePath(path);
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
