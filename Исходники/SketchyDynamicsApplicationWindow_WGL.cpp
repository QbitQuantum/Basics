	bool ApplicationWindow_WGL::createWindow( std::string title, Vector2 position, Vector2 size, bool fullscreen, const ParameterMap *parameters)
	{
		_renderer = Renderer::getSingletonPtr();

		HWND		parentWnd = nullptr;
		int			bpp = 32;
		int			PixelFormat;			// Holds The Results After Searching For A Match
		WNDCLASS	wc;						// Windows Class Structure
		DWORD		dwExStyle;				// Window Extended Style
		DWORD		dwStyle;				// Window Style

		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;

		if(parameters != nullptr)
		{
			ParameterMap::const_iterator it;
			ParameterMap::const_iterator itEnd = parameters->end();
			if ( (it = parameters->find("parent_window")) != itEnd )
			{
				parentWnd = (HWND) atoi(it->second.c_str());
				dwStyle = WS_CHILD;
			}
		}

		Vector2 sceneSize = _renderer->_sceneViewMax - _renderer->_sceneViewMin;
		_aspectRatio = sceneSize.x / sceneSize.y;

		_fullscreen = fullscreen;			

		_hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window

		wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
		wc.lpfnWndProc		= &ApplicationWindow_WGL::initialWndProc;// WndProc Handles Messages
		wc.cbClsExtra		= 0;									// No Extra Window Data
		wc.cbWndExtra		= 0;									// No Extra Window Data
		wc.hInstance		= _hInstance;							// Set The Instance
		wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
		wc.hbrBackground	= NULL;									// No Background Required For GL
		wc.lpszMenuName		= NULL;									// We Don't Want A Menu
		wc.lpszClassName	= SKETCHYDYNAMICS_WINDOW_CLASS_NAME;			// Set The Class Name

		if (!RegisterClass(&wc))									// Attempt To Register The Window Class
		{
			Logger::getSingletonPtr()->writeError("{ApplicationWindow_WGL}Failed To Register The Window Class");
			return FALSE;											// Return FALSE
		}

		if (fullscreen)												// Attempt Fullscreen Mode?
		{
			DEVMODE dmScreenSettings;								// Device Mode
			memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
			dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
			dmScreenSettings.dmPelsWidth	= (long)size.x;			// Selected Screen Width
			dmScreenSettings.dmPelsHeight	= (long)size.y;			// Selected Screen Height
			dmScreenSettings.dmBitsPerPel	= bpp;					// Selected Bits Per Pixel
			dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

			// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
			if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
			{
				// If The Mode Fails, Use Windowed Mode.			
				fullscreen=FALSE;
				Logger::getSingletonPtr()->writeWarning("Fullscreen mode not supported");			
			}
		}

		if (fullscreen)												// Are We Still In Fullscreen Mode?
		{
			dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
			dwStyle=WS_POPUP;										// Windows Style
			//ShowCursor(FALSE);										// Hide Mouse Pointer
		}		

		RECT		WindowRect;				
		WindowRect.left	= (long)position.x;
		WindowRect.right = (long)(position.x + size.x);
		WindowRect.top = (long)position.y;
		WindowRect.bottom = (long)(position.y + size.y);

		AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

		// Create The Window
		if (!(_hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
			SKETCHYDYNAMICS_WINDOW_CLASS_NAME,		// Class Name
			title.c_str(),						// Window Title
			dwStyle |							// Defined Window Style
			WS_CLIPSIBLINGS |					// Required Window Style
			WS_CLIPCHILDREN,					// Required Window Style
			(int)position.x, (int)position.y,	// Window Position
			WindowRect.right-WindowRect.left,	// Calculate Window Width
			WindowRect.bottom-WindowRect.top,	// Calculate Window Height
			parentWnd,							// Parent Window
			NULL,								// No Menu
			_hInstance,							// Instance
			this)))								// Pass To WM_CREATE
		{
			destroyWindow();								// Reset The Display
			Logger::getSingletonPtr()->writeError("{ApplicationWindow_WGL}Window Creation Error");
			return FALSE;								// Return FALSE
		}

		static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
		{
			sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
			1,											// Version Number
			PFD_DRAW_TO_WINDOW |						// Format Must Support Window
			PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,							// Must Support Double Buffering
			PFD_TYPE_RGBA,								// Request An RGBA Format
			bpp,										// Select Our Color Depth
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

		if (!(_hDC=GetDC(_hWnd)))							// Did We Get A Device Context?
		{
			destroyWindow();								// Reset The Display
			Logger::getSingletonPtr()->writeError("{ApplicationWindow_WGL}Can't Create A GL Device Context");
			return FALSE;								// Return FALSE
		}

		if (!(PixelFormat=ChoosePixelFormat(_hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
		{
			destroyWindow();								// Reset The Display
			Logger::getSingletonPtr()->writeError("{ApplicationWindow_WGL}Can't Find A Suitable PixelFormat");
			return FALSE;								// Return FALSE
		}

		if(!SetPixelFormat(_hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
		{
			destroyWindow();								// Reset The Display
			Logger::getSingletonPtr()->writeError("{ApplicationWindow_WGL}Can't Set The PixelFormat");
			return FALSE;								// Return FALSE
		}

		if (!(_hRC=wglCreateContext(_hDC)))				// Are We Able To Get A Rendering Context?
		{
			destroyWindow();								// Reset The Display
			Logger::getSingletonPtr()->writeError("{ApplicationWindow_WGL}Can't Create A GL Rendering Context");
			return FALSE;								// Return FALSE
		}

		if(!wglMakeCurrent(_hDC,_hRC))					// Try To Activate The Rendering Context
		{
			destroyWindow();								// Reset The Display
			Logger::getSingletonPtr()->writeError("{ApplicationWindow_WGL}Can't Activate The GL Rendering Context");
			return FALSE;								// Return FALSE
		}
				
		ShowWindow(_hWnd, SW_SHOW);						// Show The Window
		SetForegroundWindow(_hWnd);						// Slightly Higher Priority
		SetFocus(_hWnd);								// Sets Keyboard Focus To The Window
		resizeGLScene((int)size.x, (int)size.y);					// Set Up Our Perspective GL Screen

		if(!_renderer->initGL())
		{
			SKETCHYDYNAMICS_LOG_ERROR("OpenGL init failed");
			destroyWindow();
			return FALSE;
		}

		setVSync(false);

		return TRUE;									// Success
	}