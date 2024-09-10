/*
** Sys_CreateConsole
*/
void Sys_CreateConsole( void )
{
	HDC hDC;
	WNDCLASS wc;
	RECT rect;
	const char *DEDCLASS = "JAMP WinConsole";
	int nHeight;
	int swidth, sheight;
	int DEDSTYLE = WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX;

	memset( &wc, 0, sizeof( wc ) );

	wc.style         = 0;
	wc.lpfnWndProc   = (WNDPROC) ConWndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = g_wv.hInstance;
	wc.hIcon         = LoadIcon( g_wv.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor       = LoadCursor (NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH__ *)COLOR_INACTIVEBORDER;
	wc.lpszMenuName  = 0;
	wc.lpszClassName = DEDCLASS;

	if ( !RegisterClass (&wc) )	{
		return;
	}

	rect.left = 0;
	rect.right = 600;
	rect.top = 0;
	rect.bottom = 450;
	AdjustWindowRect( &rect, DEDSTYLE, FALSE );

	hDC = GetDC( GetDesktopWindow() );
	swidth = GetDeviceCaps( hDC, HORZRES );
	sheight = GetDeviceCaps( hDC, VERTRES );
	ReleaseDC( GetDesktopWindow(), hDC );

	s_wcd.windowWidth = rect.right - rect.left + 1;
	s_wcd.windowHeight = rect.bottom - rect.top + 1;

	s_wcd.hWnd = CreateWindowEx( 0,
							   DEDCLASS,
							   CLIENT_CONSOLE_TITLE,
							   DEDSTYLE,
							   ( swidth - 600 ) / 2, ( sheight - 450 ) / 2 , rect.right - rect.left + 1, rect.bottom - rect.top + 1,
							   NULL,
							   NULL,
							   g_wv.hInstance,
							   NULL );

	if ( s_wcd.hWnd == NULL )
	{
		return;
	}

	//
	// create fonts
	//
	hDC = GetDC( s_wcd.hWnd );
	nHeight = -MulDiv( 8, GetDeviceCaps( hDC, LOGPIXELSY), 72);

	s_wcd.hfBufferFont = CreateFont( nHeight,
									  0,
									  0,
									  0,
									  FW_LIGHT,
									  0,
									  0,
									  0,
									  DEFAULT_CHARSET,
									  OUT_DEFAULT_PRECIS,
									  CLIP_DEFAULT_PRECIS,
									  DEFAULT_QUALITY,
									  FF_MODERN | FIXED_PITCH,
									  "Courier New" );

	ReleaseDC( s_wcd.hWnd, hDC );

	//
	// create the input line
	//
	s_wcd.hwndInputLine = CreateWindow( "edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | 
												ES_LEFT | ES_AUTOHSCROLL | WS_TABSTOP,
												6, 400, s_wcd.windowWidth-20, 20,
												s_wcd.hWnd, 
												( HMENU ) INPUT_ID,	// child window ID
												g_wv.hInstance, NULL );

	//
	// create the buttons
	//
	s_wcd.hwndButtonCopy = CreateWindow( "button", NULL, BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP,
												5, 425, 72, 24,
												s_wcd.hWnd, 
												( HMENU ) COPY_ID,	// child window ID
												g_wv.hInstance, NULL );
	SendMessage( s_wcd.hwndButtonCopy, WM_SETTEXT, 0, ( LPARAM ) "Copy" );

	s_wcd.hwndButtonClear = CreateWindow( "button", NULL, BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP,
												82, 425, 72, 24,
												s_wcd.hWnd, 
												( HMENU ) CLEAR_ID,	// child window ID
												g_wv.hInstance, NULL );
	SendMessage( s_wcd.hwndButtonClear, WM_SETTEXT, 0, ( LPARAM ) "Clear" );

	s_wcd.hwndButtonQuit = CreateWindow( "button", NULL, BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_TABSTOP,
												s_wcd.windowWidth-92, 425, 72, 24,
												s_wcd.hWnd, 
												( HMENU ) QUIT_ID,	// child window ID
												g_wv.hInstance, NULL );
	SendMessage( s_wcd.hwndButtonQuit, WM_SETTEXT, 0, ( LPARAM ) "Quit" );


	//
	// create the scrollbuffer
	//
	s_wcd.hwndBuffer = CreateWindow( "edit", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_BORDER | 
												ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY | WS_TABSTOP,
												6, 40, s_wcd.windowWidth-20, 354,
												s_wcd.hWnd, 
												( HMENU ) EDIT_ID,	// child window ID
												g_wv.hInstance, NULL );
	SendMessage( s_wcd.hwndBuffer, WM_SETFONT, ( WPARAM ) s_wcd.hfBufferFont, 0 );

	s_wcd.SysInputLineWndProc = ( WNDPROC ) SetWindowLongPtr( s_wcd.hwndInputLine, GWLP_WNDPROC, ( long ) InputLineWndProc );
	SendMessage( s_wcd.hwndInputLine, WM_SETFONT, ( WPARAM ) s_wcd.hfBufferFont, 0 );
	SendMessage( s_wcd.hwndBuffer, EM_LIMITTEXT, ( WPARAM ) 0x7fff, 0 );

	ShowWindow( s_wcd.hWnd, SW_SHOWDEFAULT);
	UpdateWindow( s_wcd.hWnd );
	SetForegroundWindow( s_wcd.hWnd );
	SetFocus( s_wcd.hwndInputLine );

	Field_Clear( &s_wcd.g_consoleField );
	s_wcd.g_consoleField.widthInChars = g_console_field_width;
	for ( int i = 0 ; i < COMMAND_HISTORY ; i++ ) {
		Field_Clear( &s_wcd.historyEditLines[i] );
		s_wcd.historyEditLines[i].widthInChars = g_console_field_width;
	}

	s_wcd.visLevel = 1;
}