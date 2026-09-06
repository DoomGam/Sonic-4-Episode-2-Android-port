#include "mach_o_loader.h"
#include <android/log.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <mach-o/loader.h>
#include <mach-o/fat.h>

#define LOG_TAG "MachOLoader"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

MachOLoader::MachOLoader() : baseAddress(0), imageSize(0), isLoaded(false) {}

MachOLoader::~MachOLoader() {
    if (isLoaded && baseAddress != 0) {
        munmap(reinterpret_cast<void*>(baseAddress), imageSize);
    }
}

bool MachOLoader::loadBinary(const std::string& binaryPath) {
    int fd = open(binaryPath.c_str(), O_RDONLY);
    if (fd < 0) {
        LOGE("Não foi possível abrir o binário no caminho: %s", binaryPath.c_str());
        return false;
    }

    struct stat st;
    if (fstat(fd, &st) < 0) {
        LOGE("Erro ao obter o tamanho do arquivo.");
        close(fd);
        return false;
    }

    size_t fileSize = st.st_size;
    uint8_t* fileData = static_cast<uint8_t*>(mmap(NULL, fileSize, PROT_READ, MAP_PRIVATE, fd, 0));
    close(fd);

    if (fileData == MAP_FAILED) {
        LOGE("Falha ao mapear o arquivo binário na memória inicial.");
        return false;
    }

    uint32_t magic = *reinterpret_cast<uint32_t*>(fileData);
    uint8_t* targetBinary = fileData;

    if (magic == FAT_MAGIC || magic == FAT_CIGAM) {
        LOGI("Binário FAT detectado. Procurando arquitetura compatível...");
        struct fat_header* fatHeader = reinterpret_cast<struct fat_header*>(fileData);
        uint32_t nfat_arch = __builtin_bswap32(fatHeader->nfat_arch);
        struct fat_arch* archs = reinterpret_cast<struct fat_arch*>(fileData + sizeof(struct fat_header));

        for (uint32_t i = 0; i < nfat_arch; i++) {
            cpu_type_t cputype = __builtin_bswap32(archs[i].cputype);
            uint32_t offset = __builtin_bswap32(archs[i].offset);

            if (cputype == 12 || cputype == (12 | 0x01000000)) {
                targetBinary = fileData + offset;
                magic = *reinterpret_cast<uint32_t*>(targetBinary);
                LOGI("Arquitetura ARM correspondente encontrada no offset 0x%x", offset);
                break;
            }
        }
    }

    if (magic == MH_MAGIC || magic == MH_CIGAM) {
        LOGI("Processando cabeçalho Mach-O 32-bit...");
        struct mach_header* header = reinterpret_cast<struct mach_header*>(targetBinary);
        uint8_t* cmdPtr = targetBinary + sizeof(struct mach_header);

        for (uint32_t i = 0; i < header->ncmds; i++) {
            struct load_command* lc = reinterpret_cast<struct load_command*>(cmdPtr);
            if (lc->cmd == LC_SEGMENT) {
                struct segment_command* seg = reinterpret_cast<struct segment_command*>(lc);
                LOGI("Segmento 32-bit encontrado: %s | VAddr: 0x%08x | VSize: 0x%08x",
                     seg->segname, seg->vmaddr, seg->vmsize);
            }
            cmdPtr += lc->cmdsize;
        }
    } else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64) {
        LOGI("Processando cabeçalho Mach-O 64-bit...");
        struct mach_header_64* header = reinterpret_cast<struct mach_header_64*>(targetBinary);
        uint8_t* cmdPtr = targetBinary + sizeof(struct mach_header_64);

        for (uint32_t i = 0; i < header->ncmds; i++) {
            struct load_command* lc = reinterpret_cast<struct load_command*>(cmdPtr);
            if (lc->cmd == LC_SEGMENT_64) {
                struct segment_command_64* seg = reinterpret_cast<struct segment_command_64*>(lc);
                LOGI("Segmento 64-bit encontrado: %s | VAddr: 0x%016llx | VSize: 0x%016llx",
                     seg->segname, seg->vmaddr, seg->vmsize);
            }
            cmdPtr += lc->cmdsize;
        }
    } else {
        LOGE("Magic number inválido (0x%x). O arquivo não é um executável Mach-O válido.", magic);
        munmap(fileData, fileSize);
        return false;
    }

    munmap(fileData, fileSize);
    isLoaded = true;
    return true;
}

void* MachOLoader::getSymbolAddress(const std::string& symbolName) {
    return nullptr;
}

bool MachOLoader::executeEntryPoint() {
    return isLoaded;
}
