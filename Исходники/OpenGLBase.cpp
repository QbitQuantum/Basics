bool GL_Init(HWND window, std::string *error_message) {
	*error_message = "ok";
	hWnd = window;
	GLuint PixelFormat;

	static const PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),							// Size Of This Pixel Format Descriptor
			1,														// Version Number
			PFD_DRAW_TO_WINDOW |									// Format Must Support Window
			PFD_SUPPORT_OPENGL |									// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,										// Must Support Double Buffering
			PFD_TYPE_RGBA,											// Request An RGBA Format
			32,														// Select Our Color Depth
			0, 0, 0, 0, 0, 0,										// Color Bits Ignored
			0,														// No Alpha Buffer
			0,														// Shift Bit Ignored
			0,														// No Accumulation Buffer
			0, 0, 0, 0,										// Accumulation Bits Ignored
			16,														// 16Bit Z-Buffer (Depth Buffer)  
			0,														// No Stencil Buffer
			0,														// No Auxiliary Buffer
			PFD_MAIN_PLANE,								// Main Drawing Layer
			0,														// Reserved
			0, 0, 0												// Layer Masks Ignored
	};

	hDC = GetDC(hWnd);

	if (!hDC) {
		*error_message = "Failed to get a device context.";
		return false;											// Return FALSE
	}

	// Did Windows Find A Matching Pixel Format?
	if (!(PixelFormat = ChoosePixelFormat(hDC,&pfd)))
	{
		*error_message = "Can't Find A Suitable PixelFormat.";
		return false;
	}

	// Are We Able To Set The Pixel Format?
	if (!SetPixelFormat(hDC,PixelFormat,&pfd)) {
		*error_message = "Can't Set The PixelFormat.";
		return false;
	}

	// Are We Able To Get A Rendering Context?
	if (!(hRC = wglCreateContext(hDC)))	{
		*error_message = "Can't Create A GL Rendering Context.";
		return false;
	}	

	// Try To Activate The Rendering Context
	if (!wglMakeCurrent(hDC,hRC)) {
		*error_message = "Can't activate the GL Rendering Context.";
		return false;
	}

	if (GLEW_OK != glewInit()) {
		*error_message = "Failed to initialize GLEW.";
		return false;
	}

	// Alright, now for the modernity.
	static const int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 1,
		WGL_CONTEXT_FLAGS_ARB, enableGLDebug ? WGL_CONTEXT_DEBUG_BIT_ARB : 0,
		0
	};

	HGLRC	m_hrc;
	if(wglewIsSupported("WGL_ARB_create_context") == 1) {
		m_hrc = wglCreateContextAttribsARB(hDC, 0, attribs);
		if (!m_hrc) {
			// Fall back
			m_hrc = hRC;
		} else {
			// Switch to the new ARB context.
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hRC);
			wglMakeCurrent(hDC, m_hrc);
		}
	} else {
		// We can't make a GL 3.x context. Use an old style context (GL 2.1 and before)
		m_hrc = hRC;
	}

	if (!m_hrc) {
		*error_message = "No m_hrc";
		return false;
	}

	hRC = m_hrc;

	//Checking GL version
	const char *GLVersionString = (const char *)glGetString(GL_VERSION);

	//Or better yet, use the GL3 way to get the version number
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);

	glstate.Initialize();
	CheckGLExtensions();
	GL_SetVSyncInterval(0);
	if (enableGLDebug && glewIsSupported("GL_ARB_debug_output")) {
		glDebugMessageCallbackARB((GLDEBUGPROCARB)&DebugCallbackARB, 0); // print debug output to stderr
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
	}

	GL_Resized();								// Set Up Our Perspective GL Screen
	return true;												// Success
}