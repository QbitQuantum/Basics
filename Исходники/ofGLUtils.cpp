//---------------------------------
int ofGetGlInternalFormat(const ofPixels& pix) {
	return ofGetGLInternalFormatFromPixelFormat(pix.getPixelFormat());
}