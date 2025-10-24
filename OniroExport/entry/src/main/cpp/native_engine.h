#include "UnityHarmonyBridge.h"
#include <arkgraphics/ark_graphics_vulkan.h>
#include <graphic/graphic_2d_gl.h>
#include <hilog/log.h>

static UnityHarmonyGraphicsContext g_GraphicsContext;

void UnityHarmony_InitializeGraphics(int width, int height, OHNativeWindow* nativeWindow) {
    g_GraphicsContext.nativeWindow = nativeWindow;
    
    // Initialize EGL context
    g_GraphicsContext.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (g_GraphicsContext.display == EGL_NO_DISPLAY) {
        OH_LOG_ERROR(LOG_APP, "Failed to get EGL display");
        return;
    }
    
    // Initialize EGL
    EGLint major, minor;
    if (!eglInitialize(g_GraphicsContext.display, &major, &minor)) {
        OH_LOG_ERROR(LOG_APP, "Failed to initialize EGL");
        return;
    }
    
    OH_LOG_INFO(LOG_APP, "EGL initialized: %d.%d", major, minor);
    
    // Choose EGL config
    const EGLint configAttribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };
    
    EGLConfig config;
    EGLint numConfigs;
    if (!eglChooseConfig(g_GraphicsContext.display, configAttribs, &config, 1, &numConfigs)) {
        OH_LOG_ERROR(LOG_APP, "Failed to choose EGL config");
        return;
    }
    
    // Create EGL surface from OHNativeWindow
    EGLint surfaceAttribs[] = { EGL_NONE };
    g_GraphicsContext.surface = eglCreateWindowSurface(
        g_GraphicsContext.display, config, 
        g_GraphicsContext.nativeWindow, surfaceAttribs);
        
    if (g_GraphicsContext.surface == EGL_NO_SURFACE) {
        OH_LOG_ERROR(LOG_APP, "Failed to create EGL surface");
        return;
    }
    
    // Create EGL context
    const EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 3,
        EGL_NONE
    };
    
    g_GraphicsContext.context = eglCreateContext(
        g_GraphicsContext.display, config, EGL_NO_CONTEXT, contextAttribs);
        
    if (g_GraphicsContext.context == EGL_NO_CONTEXT) {
        OH_LOG_ERROR(LOG_APP, "Failed to create EGL context");
        return;
    }
    
    // Make current
    if (!eglMakeCurrent(g_GraphicsContext.display, g_GraphicsContext.surface, 
                       g_GraphicsContext.surface, g_GraphicsContext.context)) {
        OH_LOG_ERROR(LOG_APP, "Failed to make EGL context current");
        return;
    }
    
    OH_LOG_INFO(LOG_APP, "Graphics initialized: %dx%d", width, height);
}

void UnityHarmony_CreateVulkanSurface(VkInstance vkInstance, VkSurfaceKHR* vkSurface) {
    if (!g_GraphicsContext.nativeWindow) {
        OH_LOG_ERROR(LOG_APP, "No native window available for Vulkan surface");
        return;
    }
    
    // Use ArkGraphics to create Vulkan surface from OHNativeWindow
    Ark_Graphics_Vulkan_Surface_CreateInfo surfaceInfo = {};
    surfaceInfo.instance = vkInstance;
    surfaceInfo.window = g_GraphicsContext.nativeWindow;
    
    Ark_Graphics_Result result = Ark_Graphics_Vulkan_Surface_Create(
        g_GraphicsContext.arkDevice, &surfaceInfo, vkSurface);
    
    if (result == ARK_GRAPHICS_RESULT_SUCCESS) {
        OH_LOG_INFO(LOG_APP, "Vulkan surface created successfully");
    } else {
        OH_LOG_ERROR(LOG_APP, "Failed to create Vulkan surface: %d", result);
    }
}

void UnityHarmony_RenderFrame() {
    if (g_GraphicsContext.display && g_GraphicsContext.surface) {
        eglSwapBuffers(g_GraphicsContext.display, g_GraphicsContext.surface);
    }
}