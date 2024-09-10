void OnPaint( HWND hWnd )
{
	PAINTSTRUCT ps = { 0 };
	HDC hdc = BeginPaint( hWnd, &ps );
	HICON hIcon = LoadIcon( g_hInstance, 
						MAKEINTRESOURCE(IDI_ICON1) );
	DrawIcon( hdc, 100, 100, hIcon );
	EndPaint( hWnd, &ps );
}