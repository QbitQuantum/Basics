COffscreenGLContext::COffscreenGLContext()
{
	//! this creates a 2nd OpenGL context on the >onscreen< window/HDC
	//! so don't render to the the default framebuffer (always bind FBOs,DLs,...) !!!

	//! get the main (onscreen) GL context
	HGLRC mainRC = wglGetCurrentContext();
	hdc = wglGetCurrentDC();
	if (!hdc || !mainRC) {
		throw opengl_error("Couldn't create an offscreen GL context: wglGetCurrentDC failed!");
	}


	//! create a 2nd GL context
	offscreenRC = wglCreateContext(hdc);
	if (!offscreenRC) {
		throw opengl_error("Couldn't create an offscreen GL context: wglCreateContext failed!");
	}


	//! share the GL resources (textures,DLists,shaders,...)
	if(!wglMakeCurrent(NULL, NULL))
		throw opengl_error("Could not deactivate rendering context");
	int status = wglShareLists(mainRC, offscreenRC);
	if(!wglMakeCurrent(hdc, mainRC))
		throw opengl_error("Could not activate rendering context");

	if (!status) {
		DWORD err = GetLastError();
		char msg[256];
		SNPRINTF(msg, 255, "Couldn't create an offscreen GL context: wglShareLists failed (error: %i)!", (int)err);
		throw opengl_error(msg);
	}
}