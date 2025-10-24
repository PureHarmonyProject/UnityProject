#include "UnityHarmonyBridge.h"
#include <napi/native_api.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <hilog/log.h>

// HarmonyOS Native API for ArkTS integration
static napi_value InitializeBridge(napi_env env, napi_callback_info info) {
    UnityHarmony_Initialize();
    OH_LOG_INFO(LOG_APP, "Unity-Harmony bridge initialized");
    return nullptr;
}

static napi_value ShutdownBridge(napi_env env, napi_callback_info info) {
    UnityHarmony_Shutdown();
    OH_LOG_INFO(LOG_APP, "Unity-Harmony bridge shutdown");
    return nullptr;
}

static napi_value RenderFrame(napi_env env, napi_callback_info info) {
    UnityHarmony_RenderFrame();
    return nullptr;
}

static napi_value SetNativeWindow(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    
    // Get OHNativeWindow from XComponent
    OH_NativeXComponent *nativeXComponent = nullptr;
    napi_unwrap(env, args[0], (void**)&nativeXComponent);
    
    if (nativeXComponent) {
        OHNativeWindow* nativeWindow = nullptr;
        OH_NativeXComponent_GetNativeWindow(nativeXComponent, &nativeWindow);
        if (nativeWindow) {
            UnityHarmony_InitializeGraphics(1080, 2400, nativeWindow);
        }
    }
    
    return nullptr;
}

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc[] = {
        {"initialize", nullptr, InitializeBridge, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"shutdown", nullptr, ShutdownBridge, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"renderFrame", nullptr, RenderFrame, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"setNativeWindow", nullptr, SetNativeWindow, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"handleTouch", nullptr, nullptr, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"handleKeyEvent", nullptr, nullptr, nullptr, nullptr, nullptr, napi_default, nullptr}
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module unity_bridge_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "unity.bridge",
    .nm_priv = ((void*)0),
};

extern "C" __attribute__((constructor)) void RegisterUnityBridgeModule() {
    napi_module_register(&unity_bridge_module);
}