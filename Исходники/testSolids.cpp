/****************************************************************************
 SetupWindow()

 Creates a window and the device and rendering contexts for it.
*****************************************************************************/
BOOL SetupWindow(char *title, int width, int height, int bits, bool isFullscreen)
{
  // set the global flag
  g_isFullScreen = isFullscreen;

  // get our instance handle
  g_hInstance	= GetModuleHandle(NULL);

  WNDCLASSEX  wc;    // window class

  // fill out the window class structure
  wc.cbSize         = sizeof(WNDCLASSEX);
  wc.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc    = WndProc;
  wc.cbClsExtra     = 0;
  wc.cbWndExtra     = 0;
  wc.hInstance      = g_hInstance;
  wc.hIcon          = LoadIcon(NULL, IDI_APPLICATION);	// default icon
  wc.hIconSm        = LoadIcon(NULL, IDI_WINLOGO);		  // windows logo small icon
  wc.hCursor        = LoadCursor(NULL, IDC_ARROW);		  // default arrow
  wc.hbrBackground  = NULL; //(HBRUSH) GetStockObject(BLACK_BRUSH);   // black background
  wc.lpszMenuName   = NULL;     // no menu
  wc.lpszClassName  = WND_CLASS_NAME;
  
  // register the windows class
  if (!RegisterClassEx(&wc))
  {
    MessageBox(NULL,"Unable to register the window class", "Error", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;							// Exit And Return FALSE
  }

  // if we're in fullscreen mode, set the display up for it
  if (g_isFullScreen)
  {
    // set up the device mode structure
    DEVMODE screenSettings;
    memset(&screenSettings,0,sizeof(screenSettings));

    screenSettings.dmSize       = sizeof(screenSettings);	
    screenSettings.dmPelsWidth  = width;			// screen width
    screenSettings.dmPelsHeight = height;			// screen height
    screenSettings.dmBitsPerPel = bits;				// bits per pixel
    screenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    // attempt to switch to the resolution and bit depth we've selected
    if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    { 
        g_isFullScreen = FALSE;	
    }
  }

  DWORD dwExStyle;
  DWORD dwStyle;

  // if we're still in fullscreen mode, set the window style appropriately
  if (g_isFullScreen)
  {
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;			  // simple window with no borders or title bar
		ShowCursor(FALSE);            // hide the cursor for now
  }
  else
  {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
  }

  // set up the window we're rendering to so that the top left corner is at (0,0)
  // and the bottom right corner is (height,width)
  RECT  windowRect;
  windowRect.left = 0;
  windowRect.right = (LONG) width;
  windowRect.top = 0;
  windowRect.bottom = (LONG) height;

  // change the size of the rect to account for borders, etc. set by the style
  AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

  // class registered, so now create our window
  g_hwnd = CreateWindowEx(dwExStyle,          // extended style
                          WND_CLASS_NAME,     // class name
                          title,              // app name
                          dwStyle |           // window style
                          WS_CLIPCHILDREN |   // required for
                          WS_CLIPSIBLINGS,    // using OpenGL
                          0, 0,               // x,y coordinate
                          windowRect.right - windowRect.left, // width
                          windowRect.bottom - windowRect.top, // height
                          NULL,               // handle to parent
                          NULL,               // handle to menu
                          g_hInstance,        // application instance
                          NULL);              // no extra params

  // see if our window handle is valid
  if (!g_hwnd)
	{
    // reset the display
		KillWindow();
		MessageBox(NULL, "Unable to create window", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

  // get a device context
	if (!(g_HDC = GetDC(g_hwnd)))
	{
    // reset the display
		KillWindow();
		MessageBox(NULL,"Unable to create device context", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

  // set the pixel format we want (p55)
  PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),	// size of structure
    1,                              // default version
    PFD_DRAW_TO_WINDOW |            // window drawing support
    PFD_SUPPORT_OPENGL |            // OpenGL support
    PFD_DOUBLEBUFFER,               // double buffering support
    PFD_TYPE_RGBA,                  // RGBA color mode
    bits,                           // 32 bit color mode
    0, 0, 0, 0, 0, 0,               // ignore color bits, non-palettized mode
    0,                              // no alpha buffer
    0,                              // ignore shift bit
    0,                              // no accumulation buffer
    0, 0, 0, 0,                     // ignore accumulation bits
    16,                             // 16 bit z-buffer size
    0,                              // no stencil buffer
    0,                              // no auxiliary buffer
    PFD_MAIN_PLANE,                 // main drawing plane
    0,                              // reserved
    0, 0, 0 };                      // layer masks ignored
      
	GLuint  pixelFormat;

	// choose best matching pixel format
	if (!(pixelFormat = ChoosePixelFormat(g_HDC, &pfd)))
	{
    // reset the display
		KillWindow();
		MessageBox(NULL, "Can't find an appropriate pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	// set pixel format to device context
  if(!SetPixelFormat(g_HDC, pixelFormat,&pfd))
	{
    // reset the display
		KillWindow();
		MessageBox(NULL, "Unable to set pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
  }

  // create the OpenGL rendering context
  if (!(g_HRC = wglCreateContext(g_HDC)))
	{
    // reset the display
		KillWindow();
		MessageBox(NULL, "Unable to create OpenGL rendering context", "Error",MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

  // now make the rendering context the active one
  if(!wglMakeCurrent(g_HDC, g_HRC))
	{
    // reset the display
		KillWindow();
		MessageBox(NULL,"Unable to activate OpenGL rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

  // show the window in the forground, and set the keyboard focus to it
  ShowWindow(g_hwnd, SW_SHOW);
  SetForegroundWindow(g_hwnd);
  SetFocus(g_hwnd);

  // set up the perspective for the current screen size
  ResizeScene(width, height);

  // do one-time initialization
  
  if (!InitializeScene())
  {
    // reset the display
	  KillWindow();
	  MessageBox(NULL, "Initialization failed", "Error", MB_OK | MB_ICONEXCLAMATION);
	  return FALSE;
  }
  
  return TRUE;
} // end SetupWindow()