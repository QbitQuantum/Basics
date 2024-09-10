/**
 * Initializes the OpenGL context using EGL.
 */
bool EGLPlatform::initContext()
{
	// if there is already a current context, destroy it first
	destroyContext();

	// choose the default config for now
	int numConfigs = 1;
	
	EGLint attribute_list[] = {
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
		EGL_NONE
	};
	if(!eglChooseConfig(this->display, attribute_list, &this->config, 1, &numConfigs))
	{
		printf("Choosing EGL config failed (error code: 0x%x)\n", eglGetError());
		return false;
	}
	else if(numConfigs == 0)
	{
		printf("No matching EGL configs\n");
		return false;
	}
	
	this->context = eglCreateContext(this->display, this->config, EGL_NO_CONTEXT, NULL);
	if(this->context == EGL_NO_CONTEXT)
	{
		printf("Error: creating OpenGL context failed (error code: 0x%x)\n", eglGetError());
		return false;
	}

#if USE_PBUFFER
	if(this->surface == EGL_NO_SURFACE)
	{
		if(!initSurface()) return false;
	}
#endif
	
	return true;
}