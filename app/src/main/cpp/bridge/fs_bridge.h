#ifndef FS_BRIDGE_H
#define FS_BRIDGE_H

#include <cstdio>
#include <string>
#include <sys/stat.h> // Necessario para mode_t no Android NDK

class FSBridge {
public:
    static FSBridge& getInstance();

    void setBaseDataPath(const std::string& path);
    std::string resolvePath(const char* originalPath);

    FILE* customFopen(const char* path, const char* mode);
    int customOpen(const char* path, int flags, mode_t mode = 0);

private:
    FSBridge() = default;
    ~FSBridge() = default;

    std::string baseDataPath;
};

extern "C" {
    FILE* fake_fopen(const char* path, const char* mode);
    int fake_open(const char* path, int flags, ...);
}

#endif // FS_BRIDGE_H
