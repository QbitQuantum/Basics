static void W32_WindowLayoutSetSize(HWND hWnd, RECT *pRect, int dwWidth, int dwHeight, bool bFullScrn, bool bResizable) // Must be in called at D3Dx window creation
{
	DWORD dwStyle = GetWindowStyle(hWnd);
	DWORD dwExStyle = GetWindowExStyle( hWnd);
	RECT  rc;
	// If we are still a WS_POPUP window we should convert to a normal app
	// window so we look like a windows app.
	if (!bFullScrn)
	{
#if _WIN32_WCE
		dwExStyle|= bResizable ? WS_EX_WINDOWEDGE : 0;						// Window Extended Style
		dwStyle|= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
#else
		dwExStyle|=WS_EX_APPWINDOW | (bResizable ? WS_EX_WINDOWEDGE : 0);						// Window Extended Style
		dwStyle|= WS_OVERLAPPED| WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;	// Windows Style
		if (bResizable)
			dwStyle|= WS_THICKFRAME | WS_MAXIMIZEBOX;

#endif
	}
	else
	{
		dwStyle|= WS_POPUP;
	}
	SetWindowLong(hWnd, GWL_STYLE, dwStyle);
	SetWindowLong(hWnd, GWL_EXSTYLE, dwExStyle);

	if (!bFullScrn)
	{
		RECT  rcWork;

		// Center Window
		SetRect( &rc, 0, 0, dwWidth, dwHeight );
		SystemParametersInfo( SPI_GETWORKAREA, 0, &rcWork, 0 );

		int cx = (rcWork.right - rcWork.left - (rc.right - rc.left)) >>1;
		int cy = (rcWork.bottom - rcWork.top - (rc.bottom - rc.top)) >>1;

		rc.left+=cx;
		rc.right+=cx;
		rc.top+=cy;
		rc.bottom+=cy;

		//  Make sure our window does not hang outside of the work area
		if( rc.left < rcWork.left ) rc.left = rcWork.left;
		if( rc.top  < rcWork.top )  rc.top  = rcWork.top;

		AdjustWindowRectEx( &rc,
							GetWindowStyle(hWnd),
#if _WIN32_WCE
							0,
#else
							GetMenu(hWnd) != NULL,
#endif
							GetWindowExStyle(hWnd) );




		SetWindowPos( hWnd, NULL,
					  rc.left, rc.top,
					  rc.right - rc.left,
					  rc.bottom - rc.top,
					  SWP_NOZORDER | SWP_NOACTIVATE );


	}