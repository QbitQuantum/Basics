bool GLWindow::DisplayWindow(int _width, int _height)
{
	GLuint	  PixelFormat;			// Holds The Results After Searching For A Match
	DWORD	   dwExStyle;			  // Window Extended Style
	DWORD	   dwStyle;				// Window Style

	RECT rcdesktop;
	GetWindowRect(GetDesktopWindow(), &rcdesktop);

	if (conf.fullscreen())
	{
		nBackbufferWidth = rcdesktop.right - rcdesktop.left;
		nBackbufferHeight = rcdesktop.bottom - rcdesktop.top;

		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(false);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	RECT rc;

	rc.left = 0;
	rc.top = 0;
	rc.right = nBackbufferWidth;
	rc.bottom = nBackbufferHeight;
	AdjustWindowRectEx(&rc, dwStyle, false, dwExStyle);
	int X = (rcdesktop.right - rcdesktop.left) / 2 - (rc.right - rc.left) / 2;
	int Y = (rcdesktop.bottom - rcdesktop.top) / 2 - (rc.bottom - rc.top) / 2;

	SetWindowLong(GShwnd, GWL_STYLE, dwStyle);
	SetWindowLong(GShwnd, GWL_EXSTYLE, dwExStyle);

	SetWindowPos(GShwnd, HWND_TOP, X, Y, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW);

	if (conf.fullscreen())
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= nBackbufferWidth;
		dmScreenSettings.dmPelsHeight   = nBackbufferHeight;
		dmScreenSettings.dmBitsPerPel   = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
				conf.setFullscreen(false);
			else
				return false;
		}
	}
	else
	{
		// change to default resolution
		ChangeDisplaySettings(NULL, 0);
	}

	PIXELFORMATDESCRIPTOR pfd =			 // pfd Tells Windows How We Want Things To Be

	{
		sizeof(PIXELFORMATDESCRIPTOR),			  // Size Of This Pixel Format Descriptor
		1,										  // Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,						   // Must Support Double Buffering
		PFD_TYPE_RGBA,							  // Request An RGBA Format
		32,										 // Select Our Color Depth
		0, 0, 0, 0, 0, 0,						   // Color Bits Ignored
		0,										  // 8bit Alpha Buffer
		0,										  // Shift Bit Ignored
		0,										  // No Accumulation Buffer
		0, 0, 0, 0,								 // Accumulation Bits Ignored
		24,										 // 24Bit Z-Buffer (Depth Buffer)
		8,										  // 8bit Stencil Buffer
		0,										  // No Auxiliary Buffer
		PFD_MAIN_PLANE,							 // Main Drawing Layer
		0,										  // Reserved
		0, 0, 0									 // Layer Masks Ignored
	};

	if (!(hDC = GetDC(GShwnd)))
	{
		MessageBox(NULL, "(1) Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		MessageBox(NULL, "(2) Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		MessageBox(NULL, "(3) Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (!(hRC = wglCreateContext(hDC)))
	{
		MessageBox(NULL, "(4) Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (!wglMakeCurrent(hDC, hRC))
	{
		MessageBox(NULL, "(5) Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	UpdateWindow(GShwnd);

	return true;
}