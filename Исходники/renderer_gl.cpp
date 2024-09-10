//----------------------------------------------------------------------------
bool Renderer_GL::Init(HWND hWnd, HDC hdc)
{
	logger->Write("[OpenGL] Initializing OpenGL\n");
	this->hdc = hdc;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	
    int pFormat = ChoosePixelFormat(hdc, &pfd); 
	if (pFormat == 0)
	{
		// Windows could not find a format for our needs.
		logger->Write("[OpenGL] Error choosing pixel Format\n");
		return false;
	}
    if (!SetPixelFormat(hdc, pFormat, &pfd))
	{
		// Our format was not valid
		logger->Write("[OpenGL] Error setting pixel Format\n");
		return false;
	}

	// Temporary OpenGL 2.1 Context used to springboard our 3.0+ Context
	HGLRC temp = wglCreateContext(hdc);
	wglMakeCurrent (hdc, temp);

	// Enable GLEW
	GLenum error =  glewInit();
	if (error != GLEW_OK)
	{
		
		// Can not init GLEW
		return false;
	}

	int attr[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		0
	};

	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		// Success, create new context and switch to it
		hglrc = wglCreateContextAttribsARB(hdc, NULL, attr);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(temp);
		wglMakeCurrent(hdc, hglrc);
	}
	else
	{
		// Our level not supported, Use temp 2.1 OpenGL
		hglrc = temp;
	}
#ifdef DEBUG
	glEnable(GL_DEBUG_OUTPUT);
#endif
	// Dump our GL Versions to verify
	int glVersion[2] = {-1, -1};
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
	
	char buffer [50];
	int bufferLen = sprintf (buffer, "[OpenGL] Successfully intialized OpenGL %d.%d\n",glVersion[0], glVersion[1]);
	//std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl;
	logger->Write(buffer);
	renderable = new Renderable();	
	
	m_logger = *(this->logger);

	const GLvoid *userParam​;
	glDebugMessageCallback(glDebug, (const GLvoid *) userParam​);

	log_gl_params();
	// Success
	return true;
}