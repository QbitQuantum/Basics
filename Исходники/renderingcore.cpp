bool RenderingCore::SetupCoreProfile()
{
	HWND dummy = CreateWindow("TestClass", "Dummy", WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
		0, 0, 100, 100, 0, 0, GetModuleHandle(0), 0);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32, // color
		0, 0, 0, 0, 0, 0,
		0, // alpha
		0, 0, 0, 0, 0, 0,
		24, 8, 0, // depth, stencil, aux
		PFD_MAIN_PLANE,
		0, 0, 0, 0
	};

	HDC hdc = GetDC(dummy);
	V_RETURN(false, "InitGL(): Could not get device context", hdc);
	
	int pixelformat = ChoosePixelFormat(hdc, &pfd);
	V_RETURN(false, "InitGL(): Could not find suitable pixel format", pixelformat);

	BOOL success = SetPixelFormat(hdc, pixelformat, &pfd);
	V_RETURN(false, "InitGL(): Could not setup pixel format", success);

	HGLRC hrc = wglCreateContext(hdc);
	V_RETURN(false, "InitGL(): Context creation failed", hrc);

	success = wglMakeCurrent(hdc, hrc);
	V_RETURN(false, "InitGL(): Could not acquire context", success);

	const char* str = (const char*)glGetString(GL_VENDOR);
	std::cout << "Vendor: " << str << "\n";

	str = (const char*)glGetString(GL_RENDERER);
	std::cout << "Renderer: " << str << "\n";

	str = (const char*)glGetString(GL_VERSION);
	std::cout << "OpenGL version: " << str << "\n\n";

	sscanf_s(str, "%1d.%2d %*s", &GLMajorVersion, &GLMinorVersion);

	if( GLMajorVersion < 3 || (GLMajorVersion == 3 && GLMinorVersion < 2) )
	{
		std::cout << "Device does not support OpenGL 3.2\n";
		return false;
	}

	if( Quadron::wIsSupported("WGL_ARB_pixel_format", hdc) )
	{
		std::cout << "WGL_ARB_pixel_format present, querying pixel formats...\n";

		wglGetPixelFormatAttribivARB = (WGLGETPIXELFORMATATTRIBIVARBPROC)wglGetProcAddress("wglGetPixelFormatAttribivARB");
		wglGetPixelFormatAttribfvARB = (WGLGETPIXELFORMATATTRIBFVARBPROC)wglGetProcAddress("wglGetPixelFormatAttribfvARB");
		wglChoosePixelFormatARB = (WGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
		
		if( Quadron::wIsSupported("WGL_ARB_create_context", hdc) &&
			Quadron::wIsSupported("WGL_ARB_create_context_profile", hdc) )
		{
			wglCreateContextAttribsARB = (WGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		}
	}

	success = wglMakeCurrent(hdc, NULL);
	V_RETURN(false, "InitGL(): Could not release dummy context", success);

	success = wglDeleteContext(hrc);
	V_RETURN(false, "InitGL(): Could not delete dummy context", success);

	ReleaseDC(dummy, hdc);
	DestroyWindow(dummy);

	return true;
}