bool CGLDevice::Create30Context( const tInitStruct& initData )
{
	// store some variables
	m_hWnd = initData.hwnd;
	m_hDC = GetDC(m_hWnd);

	// choose PixelFormat
	PIXELFORMATDESCRIPTOR pfd; // Create a new PIXELFORMATDESCRIPTOR (PFD)
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR)); // Clear our  PFD
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); // Set the size of the PFD to the size of the class
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW; // Enable double buffering, opengl support and drawing to a window
	pfd.iPixelType = PFD_TYPE_RGBA; // Set our application to use RGBA pixels
	pfd.cColorBits = 32; // Give us 32 bits of color information (the higher, the more colors)
	pfd.cDepthBits = 32; // Give us 32 bits of depth information (the higher, the more depth levels)
	pfd.iLayerType = PFD_MAIN_PLANE; // Set the layer of the PFD

	int nPixelFormat = ChoosePixelFormat(m_hDC, &pfd); // Check if our PFD is valid and get a pixel format back
	if (nPixelFormat == 0) // If it fails
		return false;

	BOOL bResult = SetPixelFormat(m_hDC, nPixelFormat, &pfd); // Try and set the pixel format based on our PFD
	if (bResult == 0) // If it fails
		return false;

	HGLRC tempOpenGLContext = wglCreateContext(m_hDC); // Create an OpenGL 2.1 context for our device context
	wglMakeCurrent(m_hDC, tempOpenGLContext); // Make the OpenGL 2.1 context current and active

	// init GLEW (Have to be done after create a default Context)
	GLenum error = glewInit(); // Enable GLEW
	if (error != GLEW_OK) // If GLEW fails
		return false;

	// get OpenGL version
	int32_t major, minor;
	GetGLVersion(major, minor);

	// *note* highly suggested to use CORE_PROFILE instead of COMPATIBLE_PROFILE
	uint32_t context_flags = WGL_CONTEXT_DEBUG_BIT_ARB
		//| WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB // Set our OpenGL context to be forward compatible
		;

	int attributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major, // Set the MAJOR version of OpenGL to 4
		WGL_CONTEXT_MINOR_VERSION_ARB, minor, // Set the MINOR version of OpenGL to 2
		// *note* highly suggested to use CORE_PROFILE instead of COMPATIBLE_PROFILE
		WGL_CONTEXT_FLAGS_ARB, context_flags,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1) { // If the OpenGL 3.x context creation extension is available
		m_hRC = wglCreateContextAttribsARB(m_hDC, NULL, attributes); // Create and OpenGL 3.x context based on the given attributes
		wglMakeCurrent(NULL, NULL); // Remove the temporary context from being active
		wglDeleteContext(tempOpenGLContext); // Delete the temporary OpenGL 2.1 context
		wglMakeCurrent(m_hDC, m_hRC); // Make our OpenGL 3.0 context current
	}
	else {
		m_hRC = tempOpenGLContext; // If we didn't have support for OpenGL 3.x and up, use the OpenGL 2.1 context
	}

	int glVersion[2] = {-1, -1}; // Set some default values for the version
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]); // Get back the OpenGL MAJOR version we are using
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]); // Get back the OpenGL MAJOR version we are using

	Debug::Print((boost::wformat(TEXT("Using OpenGL: %1%.%2%")) % glVersion[0] % glVersion[1])); // Output which version of OpenGL we are using

	// setup debug context
	if (context_flags & WGL_CONTEXT_DEBUG_BIT_ARB)
	{
		if (glDebugMessageCallback)
		{
			auto func = &CGLDevice::GLDebugCallback;
			glDebugMessageCallback(func, nullptr);
		}
	}

	// get window info
	glm::vec2 vp_size = BackBufferSize();
	glViewport(0,0,(int32_t)vp_size.x, (int32_t)vp_size.y);

	// setup v-sync
	// http://www.3dbuzz.com/forum/threads/188320-Enable-or-Disable-VSync-in-OpenGL
	if(wglSwapIntervalEXT)
	{
		if(initData.bWaitForVSync)
		{
			wglSwapIntervalEXT(1);
		}
		else
		{
			wglSwapIntervalEXT(0);
		}
	}

	return true;
}