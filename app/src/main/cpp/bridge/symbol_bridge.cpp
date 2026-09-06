#include <unordered_map>
#include <string>
#include <cstring>
#include <cstdlib>
#include <android/log.h>
#include <time.h>

#define LOG_TAG "Sonic4_SymbolBridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)

static double fake_mach_absolute_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<double>(ts.tv_sec) * 1e9 + static_cast<double>(ts.tv_nsec);
}

static void fake_NSLog(const char* format, ...) {
    LOGI("[iOS NSLog]: %s", format);
}

static const std::unordered_map<std::string, void*> g_symbol_table = {
    {"_malloc", (void*)&malloc},
    {"_free", (void*)&free},
    {"_realloc", (void*)&realloc},
    {"_memcpy", (void*)&memcpy},
    {"_memset", (void*)&memset},
    {"_strlen", (void*)&strlen},
    {"_strcmp", (void*)&strcmp},
    
    {"_mach_absolute_time", (void*)&fake_mach_absolute_time},
    {"_NSLog", (void*)&fake_NSLog}
};

extern "C" void* resolve_ios_symbol(const char* name) {
    if (name == nullptr) return nullptr;

    auto it = g_symbol_table.find(name);
    if (it != g_symbol_table.end()) {
        return it->second;
    }

    LOGW("Símbolo não resolvido tentado pelo executável do jogo: %s", name);
    return nullptr;
}
