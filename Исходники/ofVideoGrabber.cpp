//--------------------------------------------------------------------
bool ofVideoGrabber::initGrabber(int w, int h, bool setUseTexture){

#ifndef OF_VID_GRABBER_TYPE
#error OF_VID_GRABBER_TYPE is not #defined! 
#endif
    
	if( grabber == NULL ){
		setGrabber( ofPtr<OF_VID_GRABBER_TYPE>(new OF_VID_GRABBER_TYPE) );
	}

	bInitialized = true;
	bUseTexture = setUseTexture;

	if( RequestedDeviceID >= 0 ){
		grabber->setDeviceID(RequestedDeviceID);
	}

	setPixelFormat(internalPixelFormat); //this safely handles checks for supported format

	if( desiredFramerate!=-1 ){
		grabber->setDesiredFrameRate(desiredFramerate);
	}

	grabberRunning	= grabber->initGrabber(w, h);
	width			= (int)grabber->getWidth();
	height			= (int)grabber->getHeight();

	if( grabberRunning && bUseTexture ){
		if(!grabber->getTexture()) tex.allocate(width, height, ofGetGLInternalFormatFromPixelFormat(internalPixelFormat));
		if(ofGetGLProgrammableRenderer() && internalPixelFormat == OF_PIXELS_MONO){
			tex.setRGToRGBASwizzles(true);
		}
	}

	return grabberRunning;
}