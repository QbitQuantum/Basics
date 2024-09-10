int main()
{
	OnStart( "." );

	const char WinName[] = "MyWin";

	WNDCLASS wcl;
	memset( &wcl, 0, sizeof( WNDCLASS ) );
	wcl.lpszClassName = WinName;
	wcl.lpfnWndProc = MyFunc;
	wcl.hCursor = LoadCursor( NULL, IDC_ARROW );

	if ( !RegisterClass( &wcl ) ) { return 0; }

	RECT Rect;

	Rect.left = 0;
	Rect.top = 0;
	Rect.right  = ImageWidth;
	Rect.bottom = ImageHeight;

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	AdjustWindowRect( &Rect, dwStyle, false );

	int WinWidth  = Rect.right  - Rect.left;
	int WinHeight = Rect.bottom - Rect.top;

	HWND hWnd = CreateWindowA( WinName, "App8", dwStyle, 100, 100, WinWidth, WinHeight, 0, NULL, NULL, NULL );

	ShowWindow( hWnd, SW_SHOW );

	HDC dc = GetDC( hWnd );

	// Create the offscreen device context and buffer
	hMemDC = CreateCompatibleDC( dc );
	hTmpBmp = CreateCompatibleBitmap( dc, ImageWidth, ImageHeight );

	// filling the RGB555 bitmap header
	memset( &BitmapInfo.bmiHeader, 0, sizeof( BITMAPINFOHEADER ) );
	BitmapInfo.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
	BitmapInfo.bmiHeader.biWidth = ImageWidth;
	BitmapInfo.bmiHeader.biHeight = ImageHeight;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32;
	BitmapInfo.bmiHeader.biSizeImage = ImageWidth * ImageHeight * 4;

	UpdateWindow( hWnd );

	MSG msg;

	SetTimer( hWnd, 1, 10, NULL );

	while ( GetMessage( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	DeleteDC( hMemDC );
	DeleteObject( hTmpBmp );
	free( g_FrameBuffer );

	return msg.wParam;
}