@Entry
@Component
struct Index {
  private xComponentController: XComponentController = new XComponentController();
  
  aboutToAppear() {
    this.xComponentController.setXComponentSurfaceInitCallback((xComponent) => {
      console.log('[UnityHarmony] XComponent surface created');
      
      // Get native window from XComponent
      let nativeWindow = xComponent.getNativeWindow();
      if (nativeWindow) {
        unityBridge.setNativeWindow(nativeWindow);
      }
    });
  }

  build() {
    Row() {
      Column() {
        XComponent({
          id: 'unity_surface',
          type: 'surface',
          controller: this.xComponentController
        })
          .width('100%')
          .height('100%')
          .onTouch((event: TouchEvent) => {
            event.touches.forEach(touch => {
              unityBridge.handleTouch(
                touch.id,
                touch.x,
                touch.y,
                touch.type === TouchType.Down ? 0 :
                touch.type === TouchType.Move ? 1 : 2
              );
            });
          })
      }
      .width('100%')
      .height('100%')
    }
    .height('100%')
    .width('100%')
  }
}