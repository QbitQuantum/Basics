void GLContext::Create( void* hwnd, const GLContextParam& param )
{
	this->hwnd = hwnd;
	hdc = (void*)GetDC((HWND)hwnd);

	// ------------------------------------------------------------

	// Create a dummy window

	WNDCLASSEX wc;
	const TCHAR* className = _T("DummyWindow");

	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = 0;
	wc.lpfnWndProc   = FakeWindowProcedure;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = GetModuleHandle(NULL);
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = className;
	wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError, "RegisterClassEx");
	}

	HWND dummyHwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		className,
		_T("Dummy"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, GetModuleHandle(NULL), NULL);

	if (dummyHwnd == NULL)
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError, "CreateWindowEx");
	}

	HDC dummyHdc = GetDC(dummyHwnd);

	// ------------------------------------------------------------

	// Setup pixel format for dummy context

	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelformat = ChoosePixelFormat(dummyHdc, &pfd);

	if (pixelformat == 0)
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError, "ChoosePixelFormat");
	}

	if (!SetPixelFormat(dummyHdc, pixelformat, &pfd))
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError, "SetPixelFormat");
	}

	// ------------------------------------------------------------

	// Create a dummy context
	HGLRC dummyContext = wglCreateContext(dummyHdc);

	if (dummyContext == NULL)
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError,
			(boost::format("Failed to create context: wglCreateContext: %s") % GetLastError()).str());		
	}

	wglMakeCurrent(dummyHdc, dummyContext); 

	// Load extensions
	GLUtil::InitializeGlew(false);

	// Destroy the dummy window
	if (!DestroyWindow((HWND)dummyHwnd))
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError, "DestroyWindow");
	}

	if (!UnregisterClass(className, GetModuleHandle(NULL)))
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError, "UnregisterClass");
	}

	// ------------------------------------------------------------

	// Get version

	int major;
	int minor;

	if (param.MajorVersion == 0)
	{
		// Get version
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
	}
	else
	{
		major = param.MajorVersion;
		minor = param.MinorVersion;
	}

	// ------------------------------------------------------------

	// Setup pixel format for main context

	int pixelFormatAttr[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, param.ColorBits,
		WGL_DEPTH_BITS_ARB, param.DepthBits,
		WGL_STENCIL_BITS_ARB, param.StencilBits,
		WGL_SAMPLE_BUFFERS_ARB, param.Multisample > 0 ? GL_TRUE : GL_FALSE,
		WGL_SAMPLES_ARB, param.Multisample,
		0
	};

	unsigned int numformats;

	if (!wglChoosePixelFormatARB((HDC)hdc, pixelFormatAttr, NULL, 1, &pixelformat, &numformats))
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError, "wglChoosePixelFormatARB");
	}

	if (!SetPixelFormat((HDC)hdc, pixelformat, NULL))
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError, "SetPixelFormat");
	}

	// ------------------------------------------------------------

	// Create GL context

	int flags = 0;

	flags |= param.ForwardCompatible ? WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB : 0;
	flags |= param.DebugMode ? WGL_CONTEXT_DEBUG_BIT_ARB : 0;

	int contextAttr[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, major,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor,
		WGL_CONTEXT_FLAGS_ARB, flags,
		WGL_CONTEXT_PROFILE_MASK_ARB, (param.UseCoreProfile ? WGL_CONTEXT_CORE_PROFILE_BIT_ARB : WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB),
		0
	};

	hglrc = (void*)wglCreateContextAttribsARB((HDC)hdc, 0, contextAttr);

	if (hglrc == NULL)
	{
		THROW_GL_EXCEPTION(GLException::RunTimeError, "wglCreateContextAttribsARB");
	}

	// ------------------------------------------------------------

	// Delete the dummy resources
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(dummyContext);

	// Enable current GL context
	wglMakeCurrent((HDC)hdc, (HGLRC)hglrc);

	// Initialize GLEW
	GLUtil::InitializeGlew(true);
}