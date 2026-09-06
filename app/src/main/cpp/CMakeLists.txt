cmake_minimum_required(VERSION 3.18.1)
project("sonic4ep2_loader")

set(CMAKE_CXX_STANDARD 17)

add_library(
    sonic4ep2_loader
    SHARED
    main.cpp
    loader/mach_o_loader.cpp
    bridge/gles_bridge.cpp
    bridge/audio_bridge.cpp
    bridge/input_bridge.cpp
)

find_library(log-lib log)
find_library(android-lib android)

target_link_libraries(
    sonic4ep2_loader
    ${log-lib}
    ${android-lib}
    EGL
    GLESv2
    OpenSLES
    dl
)
