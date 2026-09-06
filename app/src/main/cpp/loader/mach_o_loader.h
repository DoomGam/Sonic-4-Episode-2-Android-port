#ifndef MACH_O_LOADER_H
#define MACH_O_LOADER_H

#include <string>
#include <cstdint>

class MachOLoader {
public:
    MachOLoader();
    ~MachOLoader();

    bool loadBinary(const std::string& binaryPath);
    void* getSymbolAddress(const std::string& symbolName);
    bool executeEntryPoint();

private:
    uintptr_t baseAddress;
    size_t imageSize;
    bool isLoaded;
};

#endif // MACH_O_LOADER_H
