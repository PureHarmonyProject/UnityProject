cmake_minimum_required(VERSION 3.4.1)
project(UnityBridge)

set(NATIVE_LIB_SOURCE
    src/main/cpp/UnityHarmonyBridge.cpp
    src/main/cpp/libunity_bridge.cpp
    src/main/cpp/GraphicsBridge.cpp
)

add_library(unity.bridge SHARED ${NATIVE_LIB_SOURCE})

# CORRECT HarmonyOS NDK libraries
target_link_libraries(
    unity.bridge
    
    # Core system
    PUBLIC libace_engine.so
    PUBLIC libace_ndk.z.so
    PUBLIC libnative_window.so
    PUBLIC libnative_vulkan.so
    
    # Graphics stack
    PUBLIC libegl.so
    PUBLIC libglapi.so
    PUBLIC libvulkan.so
    PUBLIC libgraphic_2d_gl.so
    PUBLIC libarkgraphics.so
    PUBLIC libarkgraphics_vulkan.so
    
    # UI & Windowing
    PUBLIC libxcomponent.so
    PUBLIC libxcomponent_ndk.so
    
    # Utilities
    PUBLIC libhilog.so
    PUBLIC librawfile.z.so
)

target_include_directories(
    unity.bridge
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp
    PRIVATE ${OHOS_NDK_HOME}/sysroot/usr/include
    PRIVATE ${OHOS_NDK_HOME}/include
    PRIVATE ${OHOS_NDK_HOME}/napi/include
)

target_compile_definitions(unity.bridge PRIVATE _UNITY_HARMONY_BUILD_)