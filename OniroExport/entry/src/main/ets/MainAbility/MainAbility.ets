import UIAbility from '@ohos.app.ability.UIAbility';
import window from '@ohos.window';
import unityBridge from '../cpp/libunity.bridge';

export default class MainAbility extends UIAbility {
    private unityWindow: window.Window | null = null;
    
    async onCreate(want, launchParam) {
        console.log('[UnityHarmony] MainAbility onCreate');
        try {
            unityBridge.initialize();
        } catch (error) {
            console.error('[UnityHarmony] Native bridge init failed: ' + error);
        }
    }

    async onWindowStageCreate(windowStage: window.WindowStage) {
        console.log('[UnityHarmony] onWindowStageCreate');
        this.unityWindow = await windowStage.getMainWindow();
        
        windowStage.loadContent('pages/Index', (err) => {
            if (err) {
                console.error('[UnityHarmony] Load content failed: ' + JSON.stringify(err));
                return;
            }
            this.startUnityRuntime();
        });
    }

    private startUnityRuntime() {
        // Unity main loop at 60fps
        setInterval(() => {
            try {
                unityBridge.renderFrame();
            } catch (error) {
                console.error('[UnityHarmony] Render error: ' + error);
            }
        }, 16);
    }

    onWindowStageDestroy() {
        unityBridge.shutdown();
    }
}