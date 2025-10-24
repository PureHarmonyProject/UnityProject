using UnityEngine;
using System;
using System.Runtime.InteropServices;

public static class HarmonyNativePlugin
{
    #if UNITY_EDITOR || UNITY_STANDALONE_WIN
        private const string NativeLib = "UnityHarmonyBridge";
    #else
        private const string NativeLib = "unity.bridge";
    #endif

    [DllImport(NativeLib)] public static extern void UnityHarmony_Initialize();
    [DllImport(NativeLib)] public static extern void UnityHarmony_Shutdown();
    [DllImport(NativeLib)] public static extern void UnityHarmony_SendMessage(string obj, string method, string message);
    [DllImport(NativeLib)] public static extern IntPtr UnityHarmony_ReceiveMessage();
    [DllImport(NativeLib)] public static extern void UnityHarmony_InitializeGraphics(int w, int h, IntPtr nativeWindow);
    [DllImport(NativeLib)] public static extern void UnityHarmony_CreateVulkanSurface(IntPtr vkInstance, IntPtr vkSurface);
    [DllImport(NativeLib)] public static extern void UnityHarmony_EnableXEngineOptimizations();
    [DllImport(NativeLib)] public static extern void UnityHarmony_HandleTouch(int id, float x, float y, int phase);
    [DllImport(NativeLib)] public static extern void UnityHarmony_HandleKeyEvent(int key, int action);
}