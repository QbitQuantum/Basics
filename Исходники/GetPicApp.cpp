int WINAPI WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd )
{
	wchar_t appName[] = _T( "Capture your window!" );
	capInstance = hInstance;

	width = GetSystemMetrics( SM_CXVIRTUALSCREEN );
	height = GetSystemMetrics( SM_CYVIRTUALSCREEN );

	WNDCLASSEX wncx;
	ZeroMemory( &wncx, sizeof( wncx ) );
	
	wncx.cbSize = sizeof( WNDCLASSEX );
	wncx.cbClsExtra	= 0;
	wncx.cbWndExtra	= 0;
	wncx.hbrBackground	= (HBRUSH) GetStockObject( TRANSPARENT );
	wncx.hCursor	= LoadCursor( NULL, IDC_ARROW );
	wncx.hIcon		= LoadIcon( NULL, IDI_APPLICATION );
	wncx.hIconSm	= NULL;
	wncx.hInstance	= hInstance;
	wncx.style		= CS_VREDRAW | CS_HREDRAW;
	wncx.lpszClassName	= appName;
	wncx.lpszMenuName	= _T( "Menu" );
	wncx.lpfnWndProc	= (WNDPROC) WndProc;

	if( !RegisterClassEx( &wncx ) )
	{
		MessageBox( NULL, _T( "Register window class failed!" ), _T( "Failed" ), MB_OK );
		return -1;
	}

	hwnd = CreateWindow( appName, _T( "Capture your window" ), WS_POPUP | WS_SYSMENU | WS_SIZEBOX, 0, 0, width, height,
		NULL, NULL, hInstance, NULL );

	if( NULL == hwnd )
	{
		MessageBox( NULL, _T( "Create window failed!" ), _T( "Failed" ), MB_OK );
		return -1;
	}

	ShowWindow( hwnd, nShowCmd );
	UpdateWindow( hwnd );

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}			
		else
		{
			WaitMessage();
		}
	}

	return (int) msg.wParam;
}