INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	MSG msg;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CEyepatch *wnd = new CEyepatch();
	wnd->m_hInstance = hInstance;

	wnd->Create(NULL, CRect(0,0,WINDOW_X,WINDOW_Y), APP_CLASS,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE);
	while( GetMessage( &msg, NULL, 0, 0 ) ){
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	delete wnd;

	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}