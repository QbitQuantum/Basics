//--------------------------------------------------------------
ofxThreadedVideo::ofxThreadedVideo(){

    instanceID = ofxThreadedVideoGlobalInstanceID;
    ofxThreadedVideoGlobalInstanceID++;
    

#ifdef OF_VIDEO_PLAYER_GSTREAMER
    setPlayer<ofGstVideoPlayer>();
#else
    initializeQuicktime();
    setPlayer<ofQuickTimePlayer>();
#endif
    
    // setup video instances
    video[0].setUseTexture(false);
    video[1].setUseTexture(false);
    
    setPixelFormat(OF_PIXELS_RGB);
    
    drawTexture.allocate(1, 1, GL_RGB);
    ofPixels p;
    p.allocate(1, 1, OF_IMAGE_COLOR);
    p.set(0);
    drawTexture.loadData(p.getPixels(), 1, 1, GL_RGB);
    pixels = &video[0].getPixelsRef();
    
    // set vars to default values
    currentVideoID = VIDEO_FLIP;
    bCriticalSection = false;
    bLoaded = false;
    
    bUseTexture = true;
    bIsFrameNew = false;
    bIsPlaying = false;
    bIsLoading = false;
    bIsMovieDone = false;
    
    width = 0.0f;
    height = 0.0f;
    
    speed = 0.0f;
    position = 0.0f;
    duration = 0.0f;
    
    volume = 0.0f;
    pan = 0.0f;
    
    loopState = OF_LOOP_NORMAL;
    
    frameCurrent = 0;
    frameTotal = 0;
    
    movieName = "";
    moviePath = "";
    
    fade = 1.0f;
    fades.clear();
    
    prevMillis = ofGetElapsedTimeMillis();
    lastFrameTime = timeNow = timeThen = fps = frameRate = 0;
    
    ofxThreadedVideoNullCommand.setCommand("NULL_COMMAND", -1);
    
    bVerbose = false;
    
    // let's go!
    startThread();
}