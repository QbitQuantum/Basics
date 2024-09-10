void PhotoBoothApp::touchesBegan( TouchEvent event ){

    TouchEvent::Touch touch = event.getTouches().front();
    Vec2f cameraButtonTargetPos = Vec2f(mCameraButtonPos.value());
    
    float touchX = touch.getX() / DISPLAY_SCALE;
    float touchY = touch.getY() / DISPLAY_SCALE;
    
    switch(mCurrentState) {
        case STATE_PREVIEW:
        
            // see if the camera icon has been tapped (touch coordinates are reversed for landscape mode)
            
            cameraButtonTargetPos.x += mCameraButtonTexture.getWidth() / 2.0f;
            cameraButtonTargetPos.y += mCameraButtonTexture.getHeight() / 2.0f;
            
            if( cameraButtonTargetPos.distance( Vec2f(touchX, touchY) ) < (mCameraButtonTexture.getWidth() * 2) ) {
               mCountDownStartTime = getElapsedSeconds();
               mCurrentState = STATE_COUNT_DOWN;
            }
        
        break;

        case STATE_COUNT_DOWN:
            // stub..
        break;
        
        case STATE_ACCEPT:
            
            if(touchY > 1280) { // only look for touches near the bottom of the screen.
                
                // just split the screen in half, no need to do precise hit detection for save/cancel buttons..
                if(touchX > width / 2){
                    
                    ip::flipVertical( &mCameraSurface );
                    cinder::cocoa::SafeUiImage img = cocoa::createUiImage( mCameraSurface );
                    
                    
                    // Call into objective C to do upload via cocoa
                    FileSender::sendFile(img);

                    
                    timeline().apply( &mPreviewTexturePos, Vec2f(0, -height ), 1.0f, EaseInCubic() );
                    
                }else{
                    timeline().apply( &mPreviewTexturePos, Vec2f(0, height ), 1.0f, EaseInBack() );
                }
                
                mCurrentState = STATE_PREVIEW;
                
                timeline().apply( &mDarkBgAlpha, 0.0f, 1.0f, EaseInCubic() );
                
                // Hide buttons
                timeline().apply( &mDiscardPos, Vec2f(100, height + 100 ), 1.0f, EaseInCubic() );
                timeline().apply( &mSavePos, Vec2f(width-700, height + 100 ), 1.0f, EaseInCubic() );
            }
        break;
    }
}