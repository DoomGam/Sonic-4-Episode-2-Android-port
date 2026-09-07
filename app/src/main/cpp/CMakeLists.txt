cmake_minimum_required(VERSION 3.22.1)

project("sonic4ep2_loader")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/loader
    ${CMAKE_CURRENT_SOURCE_DIR}/bridge
)

add_library(
    sonic4ep2_loader
    SHARED
    main.cpp
    loader/mach_o_loader.cpp
    bridge/symbol_bridge.cpp
    bridge/gles_bridge.cpp
    bridge/audio_bridge.cpp
    bridge/input_bridge.cpp
    bridge/fs_bridge.cpp
)

find_library(log-lib log)
find_library(gles-lib GLESv2)
find_library(egl-lib EGL)
find_library(opensles-lib OpenSLES)

target_link_libraries(
    sonic4ep2_loader
    ${log-lib}
    ${gles-lib}
    ${egl-lib}
    ${opensles-lib}
)
