static qboolean GLW_CreateWindow( const char *drivername, int width, int height, int colorbits, qboolean cdsFullscreen )
{
	RECT			r;
	cvar_t			*vid_xpos, *vid_ypos;
	int				stylebits;
	int				x, y, w, h;
	int				exstyle;

	// fullscreen DEVMODE for use with win_allowAltTab 
	memset( &glw_fs_dm, 0, sizeof( glw_fs_dm ) );

	//
	// register the window class if necessary
	//
	if ( !s_classRegistered )
	{
		WNDCLASS wc;

		memset( &wc, 0, sizeof( wc ) );

		wc.style         = 0;
		wc.lpfnWndProc   = (WNDPROC) glw_state.wndproc;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = g_wv.hInstance;
		wc.hIcon         = LoadIcon( g_wv.hInstance, MAKEINTRESOURCE(IDI_ICON1));
		wc.hCursor       = LoadCursor (NULL,IDC_ARROW);
		wc.hbrBackground = (void *)COLOR_GRAYTEXT;
		wc.lpszMenuName  = 0;
		wc.lpszClassName = CLIENT_WINDOW_TITLE;

		if ( !RegisterClass( &wc ) )
		{
			ri.Error( ERR_FATAL, "GLW_CreateWindow: could not register window class" );
		}
		s_classRegistered = qtrue;
		ri.Printf( PRINT_ALL, "...registered window class\n" );
	}

	//
	// create the HWND if one does not already exist
	//
	if ( !g_wv.hWnd )
	{
		//
		// compute width and height
		//
		r.left = 0;
		r.top = 0;
		r.right  = width;
		r.bottom = height;

		if ( cdsFullscreen || !Q_stricmp( _3DFX_DRIVER_NAME, drivername ) )
		{
			exstyle = WS_EX_TOPMOST;
			stylebits = WS_POPUP|WS_VISIBLE|WS_SYSMENU;
		}
		else
		{
			exstyle = 0;
			stylebits = WINDOW_STYLE|WS_SYSMENU|WS_MINIMIZEBOX;
			AdjustWindowRect (&r, stylebits, FALSE);
		}

		w = r.right - r.left;
		h = r.bottom - r.top;

		if ( cdsFullscreen || !Q_stricmp( _3DFX_DRIVER_NAME, drivername ) )
		{
			x = 0;
			y = 0;
		}
		else
		{
			vid_xpos = ri.Cvar_Get ("vid_xpos", "", 0);
			vid_ypos = ri.Cvar_Get ("vid_ypos", "", 0);
			x = vid_xpos->integer;
			y = vid_ypos->integer;

			// adjust window coordinates if necessary 
			// so that the window is completely on screen
			if ( x < 0 )
				x = 0;
			if ( y < 0 )
				y = 0;

			if ( w < glw_state.desktopWidth &&
				 h < glw_state.desktopHeight )
			{
				if ( x + w > glw_state.desktopWidth )
					x = ( glw_state.desktopWidth - w );
				if ( y + h > glw_state.desktopHeight )
					y = ( glw_state.desktopHeight - h );
			}
		}

		g_wv.hWnd = CreateWindowEx (
			 exstyle, 
			 CLIENT_WINDOW_TITLE,
			 CLIENT_WINDOW_TITLE,
			 stylebits,
			 x, y, w, h,
			 NULL,
			 NULL,
			 g_wv.hInstance,
			 NULL);

		if ( !g_wv.hWnd )
		{
			ri.Error (ERR_FATAL, "GLW_CreateWindow() - Couldn't create window");
		}
	
		ShowWindow( g_wv.hWnd, SW_SHOW );
		UpdateWindow( g_wv.hWnd );
		ri.Printf( PRINT_ALL, "...created window@%d,%d (%dx%d)\n", x, y, w, h );
	}
	else
	{
		ri.Printf( PRINT_ALL, "...window already present, CreateWindowEx skipped\n" );
	}

	if ( !GLW_InitDriver( drivername, colorbits ) )
	{
		ShowWindow( g_wv.hWnd, SW_HIDE );
		DestroyWindow( g_wv.hWnd );
		g_wv.hWnd = NULL;

		return qfalse;
	}

	SetForegroundWindow( g_wv.hWnd );
	SetFocus( g_wv.hWnd );

	return qtrue;
}