static void VID_SetWindowSize( bool fullscreen )
{
	RECT r;
	int stylebits;
	int exstyle;
	int x = glw_state.win_x, y = glw_state.win_y;
	int width = glConfig.width, height = glConfig.height;
	HWND parentHWND = glw_state.parenthWnd;

	if( fullscreen )
	{
		exstyle = WS_EX_TOPMOST;
		stylebits = ( WS_POPUP|WS_VISIBLE );
		parentHWND = NULL;
	}
	else if( parentHWND )
	{
		exstyle = 0;
		stylebits = WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_VISIBLE;
	}
	else
	{
		exstyle = 0;
		stylebits = WINDOW_STYLE;
	}

	r.left = 0;
	r.top = 0;
	r.right  = width;
	r.bottom = height;

	AdjustWindowRect( &r, stylebits, FALSE );

	width = r.right - r.left;
	height = r.bottom - r.top;

	if( fullscreen )
	{
		x = 0;
		y = 0;
	}
	else if( parentHWND )
	{
		RECT parentWindowRect;

		GetWindowRect( parentHWND, &parentWindowRect );

		// share centre with the parent window
		x = (parentWindowRect.right - parentWindowRect.left - width) / 2;
		y = (parentWindowRect.bottom - parentWindowRect.top - height) / 2;
	}

	SetActiveWindow( glw_state.hWnd );

	SetWindowLong( glw_state.hWnd, GWL_EXSTYLE, exstyle );
	SetWindowLong( glw_state.hWnd, GWL_STYLE, stylebits );

	SetWindowPos( glw_state.hWnd, HWND_TOP, x, y, width, height, SWP_FRAMECHANGED );

	ShowWindow( glw_state.hWnd, SW_SHOW );
	UpdateWindow( glw_state.hWnd );

	SetForegroundWindow( glw_state.hWnd );
	SetFocus( glw_state.hWnd );
}