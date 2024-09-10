LRESULT CALLBACK Main_WindowProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )       //主窗口窗口过程
{
	static HDC				Main_WindowHdc;
	static HINSTANCE		hInstance;
	static PAINTSTRUCT		ps;
	
	static HWND				Button_Handle[NUM];
	static int				cxChar, cyChar;

	switch( message )
	{
	case WM_CREATE:
		cxChar = LOWORD( GetDialogBaseUnits() );
		cyChar = HIWORD( GetDialogBaseUnits() );

		for( int i = 0; i < NUM; i++ )
		{
			Button_Handle[i] = CreateWindow ( TEXT( "Button" ),
											  button[i].szText,
											  WS_CHILD | WS_VISIBLE | button[i].iStyle,				//窗口风格
											  cxChar,												//窗口初始水平位置
											  cyChar * ( 1 + 2 * i ),								//窗口初始垂直位置
											  20 * cxChar,											//窗口宽
											  cyChar * 7 / 4,										//窗口高
											  hwnd,													//父窗口句柄
											  ( HMENU ) i,											//菜单句柄
											  hInstance,											//实例句柄
											  NULL );
		}
		return 0;

	case WM_PAINT:
		Main_WindowHdc = BeginPaint( hwnd, &ps );

		EndPaint( hwnd, &ps );
		return 0;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hwnd, message, wParam, lParam );
}