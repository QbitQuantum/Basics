void WinSetExceptionWnd( HWND wnd ) {
	if ( wnd ) {
		_set_se_translator( WinExceptionHandler );
	} else {
		_set_se_translator( NULL );
	}

	g_hWnd = wnd;
}