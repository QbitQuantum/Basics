/// Called per frame after iterating over all streams
///
/// @return false if failed
bool 
stageConsumer::endFrame() {
	glViewport(0,0, window::getInstance().width(), window::getInstance().height());
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);	
    if(!wglSwapLayerBuffers(_rc->hDC(), WGL_SWAP_MAIN_PLANE))
    {
        window::getInstance().messageBoxWithLastError("wglSwapLayerBuffers");
        return false;
    }
	return true;
}