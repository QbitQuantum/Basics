/* Set the final window size, set the window text and icon, and then unhide the
 * window. */
void GraphicsWindow::CreateGraphicsWindow( const VideoModeParams &p, bool bForceRecreateWindow )
{
	g_CurrentParams = p;

	// Adjust g_CurrentParams to reflect the actual display settings.
	AdjustVideoModeParams( g_CurrentParams );

	if( g_hWndMain == NULL || bForceRecreateWindow )
	{
		int iWindowStyle = GetWindowStyle( p.windowed );

		AppInstance inst;
		HWND hWnd = CreateWindow( g_sClassName, "app", iWindowStyle,
						0, 0, 0, 0, NULL, NULL, inst, NULL );
		if( hWnd == NULL )
			RageException::Throw( "%s", werr_ssprintf( GetLastError(), "CreateWindow" ).c_str() );

		/* If an old window exists, transfer focus to the new window before
		 * deleting it, or some other window may temporarily get focus, which
		 * can cause it to be resized. */
		if( g_hWndMain != NULL )
		{
			// While we change to the new window, don't do ChangeDisplaySettings in WM_ACTIVATE.
			g_bRecreatingVideoMode = true;
			SetForegroundWindow( hWnd );
			g_bRecreatingVideoMode = false;

			GraphicsWindow::DestroyGraphicsWindow();
		}

		g_hWndMain = hWnd;
		CrashHandler::SetForegroundWindow( g_hWndMain );
		g_HDC = GetDC( g_hWndMain );
	}

	// Update the window title.
	do
	{
		if( m_bWideWindowClass )
		{
			if( SetWindowText( g_hWndMain, ConvertUTF8ToACP(p.sWindowTitle).c_str() ) )
				break;
		}

		SetWindowTextA( g_hWndMain, ConvertUTF8ToACP(p.sWindowTitle) );
	} while(0);

	// Update the window icon.
	if( g_hIcon != NULL )
	{
		SetClassLong( g_hWndMain, GCL_HICON, (LONG) LoadIcon(NULL,IDI_APPLICATION) );
		DestroyIcon( g_hIcon );
		g_hIcon = NULL;
	}
	g_hIcon = IconFromFile( p.sIconFile );
	if( g_hIcon != NULL )
		SetClassLong( g_hWndMain, GCL_HICON, (LONG) g_hIcon );

	/* The window style may change as a result of switching to or from fullscreen;
	 * apply it. Don't change the WS_VISIBLE bit. */
	int iWindowStyle = GetWindowStyle( p.windowed );
	if( GetWindowLong( g_hWndMain, GWL_STYLE ) & WS_VISIBLE )
		iWindowStyle |= WS_VISIBLE;
	SetWindowLong( g_hWndMain, GWL_STYLE, iWindowStyle );

	RECT WindowRect;
	SetRect( &WindowRect, 0, 0, p.width, p.height );
	AdjustWindowRect( &WindowRect, iWindowStyle, FALSE );

	//LOG->Warn( "w = %d, h = %d", p.width, p.height );

	const int iWidth = WindowRect.right - WindowRect.left;
	const int iHeight = WindowRect.bottom - WindowRect.top;

	// If windowed, center the window.
	int x = 0, y = 0;
	if( p.windowed )
	{
		x = GetSystemMetrics(SM_CXSCREEN)/2-iWidth/2;
		y = GetSystemMetrics(SM_CYSCREEN)/2-iHeight/2;
	}

	/* Move and resize the window. SWP_FRAMECHANGED causes the above
	 * SetWindowLong to take effect. */
	if( !SetWindowPos( g_hWndMain, HWND_NOTOPMOST, x, y, iWidth, iHeight, SWP_FRAMECHANGED|SWP_SHOWWINDOW ) )
		LOG->Warn( "%s", werr_ssprintf( GetLastError(), "SetWindowPos" ).c_str() );

	SetForegroundWindow( g_hWndMain );

	/* Pump messages quickly, to make sure the window is completely set up.
	 * If we don't do this, then starting up in a D3D fullscreen window may
	 * cause all other windows on the system to be resized. */
	MSG msg;
	while( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
	{
		GetMessage( &msg, NULL, 0, 0 );
		DispatchMessage( &msg );
	}
}