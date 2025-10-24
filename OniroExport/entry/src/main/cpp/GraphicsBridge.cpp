#include "UnityHarmonyBridge.h"
#include <arkgraphics/ark_graphics_vulkan.h>
#include <hilog/log.h>

static UnityHarmonyGraphicsContext g_GraphicsContext;

void UnityHarmony_InitializeGraphics(int width, int height, void* nativeWindow) {
    g_GraphicsContext.nativeWindow = static_cast<OH_NativeWindow*>(nativeWindow);
    
    // Initialize EGL
    g_GraphicsContext.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(g_GraphicsContext.display, nullptr, nullptr);
    
    // Create EGL surface from XComponent
    EGLConfig config;
    EGLint numConfigs;
    const EGLint configAttribs[] = { EGL_SURFACE_TYPE, EGL_WINDOW_BIT, EGL_NONE };
    eglChooseConfig(g_GraphicsContext.display, configAttribs, &config, 1, &numConfigs);
    
    g_GraphicsContext.surface = eglCreateWindowSurface(
        g_GraphicsContext.display, config, g_GraphicsContext.nativeWindow, nullptr);
    
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "UnityHarmony", 
                 "Graphics initialized: %dx%d", width, height);
}