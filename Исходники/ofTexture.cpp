//----------------------------------------------------------
void ofTexture::allocate(const ofPixels& pix, bool bUseARBExtention){
	allocate(pix.getWidth(), pix.getHeight(), ofGetGlInternalFormat(pix), bUseARBExtention, ofGetGlFormat(pix), ofGetGlType(pix));
	if((pix.getPixelFormat()==OF_PIXELS_GRAY || pix.getPixelFormat()==OF_PIXELS_GRAY_ALPHA) && ofIsGLProgrammableRenderer()){
		setRGToRGBASwizzles(true);
	}
	loadData(pix);
}