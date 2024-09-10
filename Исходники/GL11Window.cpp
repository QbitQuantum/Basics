BOOL GL11Window::Create(CONST WindowSettings& settings /*= {}*/)
{
	m_settings = settings;

	CONST auto hInstance{GetModuleHandle(NULL)};
	if (!hInstance)
	{
		DisplayError(TEXT("Failed to retrieve the application handle."), GetLastError());
		return FALSE;
	}

	WNDCLASSEX wndClassEx{};
	ZeroMemory(&wndClassEx, sizeof(WNDCLASSEX));
	wndClassEx.cbSize        = sizeof(WNDCLASSEX);
	wndClassEx.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wndClassEx.lpfnWndProc   = WndProc;
	wndClassEx.cbClsExtra    = 0;
	wndClassEx.cbWndExtra    = sizeof(VOID*) + sizeof(INT);
	wndClassEx.hInstance     = hInstance;
	wndClassEx.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hbrBackground = NULL;
	wndClassEx.lpszMenuName  = NULL;
	wndClassEx.lpszClassName = TEXT("GL11WindowClass");
	wndClassEx.hIconSm       = NULL;

	if (FAILED(RegisterClassEx(&wndClassEx)))
	{
		DisplayError(TEXT("Failed to register the window class."), GetLastError());
		return FALSE;
	}

	DWORD windowStyle{WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS};
	DWORD windowStyleEx{WS_EX_ACCEPTFILES};

	RECT windowRect{0, 0, m_settings.width, m_settings.height};
	if (FAILED(AdjustWindowRectEx(&windowRect, windowStyle, FALSE, windowStyleEx)))
	{
		DisplayError(TEXT("Failed to adjust the window rect."), GetLastError());
		return FALSE;
	}

	m_settings.x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (m_settings.width / 2);
	m_settings.y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (m_settings.height / 2);

	CONST auto FULL_TITLE{m_settings.title + m_settings.titleEx};
	m_handle = CreateWindowEx(windowStyleEx,
	                          wndClassEx.lpszClassName,
	                          FULL_TITLE.c_str(),
	                          windowStyle,
	                          m_settings.x,
	                          m_settings.y,
	                          windowRect.right - windowRect.left,
	                          windowRect.bottom - windowRect.top,
	                          NULL,
	                          NULL,
	                          hInstance,
	                          this);
	if (!m_handle)
	{
		DisplayError(TEXT("Failed to create the window handle."), GetLastError());
		return FALSE;
	}

	m_deviceContext = GetDC(m_handle);

	// Query a pixel format:
	PIXELFORMATDESCRIPTOR desiredPixelFormat{};
	ZeroMemory(&desiredPixelFormat, sizeof(PIXELFORMATDESCRIPTOR));
	desiredPixelFormat.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
	desiredPixelFormat.nVersion     = 1;
	desiredPixelFormat.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
	desiredPixelFormat.iPixelType   = PFD_TYPE_RGBA;
	desiredPixelFormat.cColorBits   = 32;
	desiredPixelFormat.cDepthBits   = 24;
	desiredPixelFormat.cStencilBits = 8;
	desiredPixelFormat.iLayerType   = PFD_MAIN_PLANE;

	auto chosenPixelFormat{ChoosePixelFormat(m_deviceContext, &desiredPixelFormat)};
	if (!chosenPixelFormat)
	{
		DisplayError(TEXT("Failed to choose a dummy pixel format."), GetLastError());
		return FALSE;
	}

	if (FAILED(DescribePixelFormat(m_deviceContext,
	                               chosenPixelFormat,
	                               sizeof(PIXELFORMATDESCRIPTOR),
	                               &desiredPixelFormat)))
	{
		DisplayError(TEXT("Failed to fill the pixel format."), GetLastError());
		return FALSE;
	}

	if (FAILED(SetPixelFormat(m_deviceContext, chosenPixelFormat, &desiredPixelFormat)))
	{
		DisplayError(TEXT("Failed to set the pixel format."), GetLastError());
		return FALSE;
	}

	// Create the OpenGL context:
	m_renderingContext = wglCreateContext(m_deviceContext);
	if (!m_renderingContext)
	{
		DisplayError(TEXT("Failed to create the OpenGL context."), GetLastError());
		return FALSE;
	}

	if (FAILED(wglMakeCurrent(m_deviceContext, m_renderingContext)))
	{
		DisplayError(TEXT("Failed to make the OpenGL context current."), GetLastError());
		return FALSE;
	}

	ShowWindow(m_handle, SW_SHOWNORMAL);
	UpdateWindow(m_handle);

	if (!s_firstWindowInitialized)
	{
		s_firstWindowInitialized = TRUE;
		m_isFirstWindow          = TRUE;
	}

	return TRUE;
}