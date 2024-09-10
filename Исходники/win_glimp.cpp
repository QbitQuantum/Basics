/*
=======================
GLW_CreateWindow

Responsible for creating the Win32 window.
If fullscreen, it won't have a border
=======================
*/
static bool GLW_CreateWindow( glimpParms_t parms ) {
	int				x, y, w, h;
	if ( !GLW_GetWindowDimensions( parms, x, y, w, h ) ) {
		return false;
	}

	int				stylebits;
	int				exstyle;
	if ( parms.fullScreen != 0 ) {
		exstyle = WS_EX_TOPMOST;
		stylebits = WS_POPUP|WS_VISIBLE|WS_SYSMENU;
	} else {
		exstyle = 0;
		stylebits = WINDOW_STYLE|WS_SYSMENU;
	}

	win32.hWnd = CreateWindowEx (
		 exstyle, 
		 WIN32_WINDOW_CLASS_NAME,
		 GAME_NAME,
		 stylebits,
		 x, y, w, h,
		 NULL,
		 NULL,
		 win32.hInstance,
		 NULL);

	if ( !win32.hWnd ) {
		common->Printf( "^3GLW_CreateWindow() - Couldn't create window^0\n" );
		return false;
	}

	::SetTimer( win32.hWnd, 0, 100, NULL );

	ShowWindow( win32.hWnd, SW_SHOW );
	UpdateWindow( win32.hWnd );
	common->Printf( "...created window @ %d,%d (%dx%d)\n", x, y, w, h );

	// makeCurrent NULL frees the DC, so get another
	win32.hDC = GetDC( win32.hWnd );
	if ( !win32.hDC ) {
		common->Printf( "^3GLW_CreateWindow() - GetDC()failed^0\n" );
		return false;
	}

	// Check to see if we can get a stereo pixel format, even if we aren't going to use it,
	// so the menu option can be 
	if ( GLW_ChoosePixelFormat( win32.hDC, parms.multiSamples, true ) != -1 ) {
		glConfig.stereoPixelFormatAvailable = true;
	} else {
		glConfig.stereoPixelFormatAvailable = false;
	}

	if ( !GLW_InitDriver( parms ) ) {
		ShowWindow( win32.hWnd, SW_HIDE );
		DestroyWindow( win32.hWnd );
		win32.hWnd = NULL;
		return false;
	}

	SetForegroundWindow( win32.hWnd );
	SetFocus( win32.hWnd );

	glConfig.isFullscreen = parms.fullScreen;

	return true;
}