	void* XdevLOpenGLWGL::getProcAddress(const xdl_char* func) {
		return (void*)wglGetProcAddress(func);
	}