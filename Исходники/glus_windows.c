GLUSboolean GLUSAPIENTRY glusCreateWindow(const char* title, GLUSuint width, GLUSuint height, GLUSboolean fullscreen)
{
	GLUSint attribList[] =
	{
	  WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      WGL_CONTEXT_MINOR_VERSION_ARB, 0,
      WGL_CONTEXT_FLAGS_ARB, 0,
      0
	};

	static PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	GLUSuint	PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	g_fullscreen=fullscreen;			// Set The Global Fullscreen Flag

	g_hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= g_hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "GLUS";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		return GLUS_FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= 32;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			glusDestroyWindow();
			return GLUS_FALSE;
		}
	}

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;							// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(g_hWnd = CreateWindowEx(dwExStyle,						// Extended Style For The Window
								"GLUS",								// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								g_hInstance,						// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		glusDestroyWindow();
		return GLUS_FALSE;
	}
	
	if (!(g_hDC = GetDC(g_hWnd)))					// Did We Get A Device Context?
	{
		glusDestroyWindow();
		return GLUS_FALSE;							// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(g_hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		glusDestroyWindow();
		return GLUS_FALSE;							// Return FALSE
	}

	if(!SetPixelFormat(g_hDC, PixelFormat, &pfd))	// Are We Able To Set The Pixel Format?
	{
		glusDestroyWindow();
		return GLUS_FALSE;							// Return FALSE
	}

	if (!(g_hRC=wglCreateContext(g_hDC)))			// Are We Able To Get A Rendering Context?
	{
		glusDestroyWindow();
		return GLUS_FALSE;							// Return FALSE
	}

	if(!wglMakeCurrent(g_hDC, g_hRC))				// Try To Activate The Rendering Context
	{
		glusDestroyWindow();
		return GLUS_FALSE;							// Return FALSE
	}

	if (g_major >= 3)
	{
		PFNWGLCREATECONTEXTATTRIBSARBPROCTEMP wglCreateContextAttribsARBTemp = NULL;
		HGLRC hRCTemp = NULL;

		GLUSint attribList[] =
		{
		  WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
		  WGL_CONTEXT_MINOR_VERSION_ARB, 0,
      WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB,        
      0, 0,
      0
		};

		attribList[1] = g_major;
		attribList[3] = g_minor;
		//attribList[5] = g_flags;

		if (!(wglCreateContextAttribsARBTemp = (PFNWGLCREATECONTEXTATTRIBSARBPROCTEMP)wglGetProcAddress("wglCreateContextAttribsARB")))
		{
			glusDestroyWindow();
			return GLUS_FALSE;							// Return FALSE
		}

		if (!(hRCTemp = wglCreateContextAttribsARBTemp(g_hDC, 0, attribList)))
		{
			glusDestroyWindow();
			return GLUS_FALSE;							// Return FALSE
		}

		if(!wglMakeCurrent(NULL, NULL))
		{
			wglDeleteContext(hRCTemp);

			glusDestroyWindow();
			return GLUS_FALSE;							// Return FALSE
		}

		if (!wglDeleteContext(g_hRC))
		{
			wglDeleteContext(hRCTemp);

			glusDestroyWindow();
			return GLUS_FALSE;							// Return FALSE
		}

		g_hRC = hRCTemp;

		if(!wglMakeCurrent(g_hDC, g_hRC))
		{
			glusDestroyWindow();
			return GLUS_FALSE;							// Return FALSE
		}
	}

	ShowWindow(g_hWnd, SW_SHOW);					// Show The Window
	SetForegroundWindow(g_hWnd);					// Slightly Higher Priority
	SetFocus(g_hWnd);								// Sets Keyboard Focus To The Window

	g_width = width;
	g_height = height;

	return GLUS_TRUE;								// Success
}