void	Win32OpenGLWindow::init(int width,int height, bool fullscreen,int colorBitsPerPixel, void* windowHandle)
{
	// get handle to exe file
	HINSTANCE hInstance = GetModuleHandle(0);

	// create the window if we need to and we do not use the null device
	if (!windowHandle)
	{
		const char* ClassName = "DeviceWin32";

		// Register Class
		WNDCLASSEX wcex;
		wcex.cbSize		= sizeof(WNDCLASSEX);
		wcex.style		= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= hInstance;
		wcex.hIcon		= LoadIcon( NULL, IDI_APPLICATION ); //(HICON)LoadImage(hInstance, "bullet_ico.ico", IMAGE_ICON, 0,0, LR_LOADTRANSPARENT);//LR_LOADFROMFILE);
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= 0;
		wcex.lpszClassName	= ClassName;
		wcex.hIconSm		= 0;

		// if there is an icon, load it
		wcex.hIcon = (HICON)LoadImage(hInstance, "irrlicht.ico", IMAGE_ICON, 0,0, LR_LOADFROMFILE);

		RegisterClassEx(&wcex);

		// calculate client size

		RECT clientSize;
		clientSize.top = 0;
		clientSize.left = 0;
		clientSize.right = width;
		clientSize.bottom = height;

		DWORD style = WS_POPUP;

		if (!fullscreen)
			style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;

		AdjustWindowRect(&clientSize, style, FALSE);

		m_data->m_width = clientSize.right - clientSize.left;
		m_data->m_height = clientSize.bottom - clientSize.top;

		int windowLeft = (GetSystemMetrics(SM_CXSCREEN) - m_data->m_width) / 2;
		int windowTop = (GetSystemMetrics(SM_CYSCREEN) - m_data->m_height) / 2;

		if (fullscreen)
		{
			windowLeft = 0;
			windowTop = 0;
		}

		// create window

		m_data->m_hWnd = CreateWindow( ClassName, "", style, windowLeft, windowTop,
					m_data->m_width, m_data->m_height, NULL, NULL, hInstance, NULL);

		ShowWindow(m_data->m_hWnd, SW_SHOW);
		UpdateWindow(m_data->m_hWnd);

		MoveWindow(m_data->m_hWnd, windowLeft, windowTop, m_data->m_width, m_data->m_height, TRUE);
	}
	else if (windowHandle)
	{
		// attach external window
		m_data->m_hWnd = static_cast<HWND>(windowHandle);
		RECT r;
		GetWindowRect(m_data->m_hWnd, &r);
		m_data->m_width = r.right - r.left;
		m_data->m_height = r.bottom - r.top;
		//sFullScreen = false;
		//sExternalWindow = true;
	}


	if (fullscreen)
	{
		DEVMODE dm;
		memset(&dm, 0, sizeof(dm));
		dm.dmSize = sizeof(dm);
		// use default values from current setting
		EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
		m_data->m_oldScreenWidth = dm.dmPelsWidth;
		m_data->m_oldHeight = dm.dmPelsHeight;
		m_data->m_oldBitsPerPel = dm.dmBitsPerPel;

		dm.dmPelsWidth = width;
		dm.dmPelsHeight = height;
		if (colorBitsPerPixel)
		{
			dm.dmBitsPerPel = colorBitsPerPixel;
		}
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

		LONG res = ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
		if (res != DISP_CHANGE_SUCCESSFUL)
		{ // try again without forcing display frequency
			dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
			res = ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
		}

	}

	//VideoDriver = video::createOpenGLDriver(CreationParams, FileSystem, this);
	enableOpenGL();


	const wchar_t* text= L"OpenCL rigid body demo";

	DWORD dwResult;

#ifdef _WIN64
		SetWindowTextW(m_data->m_hWnd, text);
#else
		SendMessageTimeoutW(m_data->m_hWnd, WM_SETTEXT, 0,
				reinterpret_cast<LPARAM>(text),
				SMTO_ABORTIFHUNG, 2000, &dwResult);
#endif
	

}