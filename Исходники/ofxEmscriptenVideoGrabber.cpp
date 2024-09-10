bool ofxEmscriptenVideoGrabber::initGrabber(int w, int h){
	if(id!=-1){
		html5video_grabber_init(id,w,h,desiredFramerate);
		switch(getPixelFormat()){
		case OF_PIXELS_RGBA:
			pixels.allocate(w,h,4);
			break;
		case OF_PIXELS_RGB:
			pixels.allocate(w,h,3);
			break;
		case OF_PIXELS_MONO:
			pixels.allocate(w,h,1);
			break;
		default:
			ofLogError() << "unknown pixel format, can't allocating texture";
			break;
		}
		pixels.set(0);
		return true;
	}else{
		return false;
	}
}