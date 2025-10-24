#include <native_engine.h>
#include <arkui/xcomponent.h>
#include <arkgraphics/ark_graphics.h>
#include <vulkan/vulkan.h>
#include <EGL/egl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    OH_NativeWindow* nativeWindow;
    Ark_Graphics_Device* arkDevice;
    VkDevice vkDevice;
} UnityHarmonyGraphicsContext;

// Core API
void UnityHarmony_Initialize();
void UnityHarmony_Shutdown();
void UnityHarmony_SendMessage(const char* obj, const char* method, const char* message);
const char* UnityHarmony_ReceiveMessage();

// Graphics API  
void UnityHarmony_InitializeGraphics(int width, int height, void* nativeWindow);
void UnityHarmony_CreateVulkanSurface(void* vkInstance, void* vkSurface);
void UnityHarmony_RenderFrame();

// Input API
void UnityHarmony_HandleTouch(int fingerId, float x, float y, int phase);
void UnityHarmony_HandleKeyEvent(int keyCode, int action);

// XEngine API
void UnityHarmony_EnableXEngineOptimizations();

#ifdef __cplusplus
}
#endif