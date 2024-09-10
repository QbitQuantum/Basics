LRESULT CExtWSGripper::WindowProc(
	UINT message,
	WPARAM wParam,
	LPARAM lParam
	) 
{
	if( message == WM_NCHITTEST )
	{
		CWnd * pWnd = GetParent();
		ASSERT( pWnd != NULL );
		ASSERT_VALID( pWnd );
		if( pWnd->IsZoomed() )
			return HTNOWHERE;

		__EXT_MFC_LONG_PTR dwExStyle = ::__EXT_MFC_GetWindowLong( pWnd->GetSafeHwnd(), GWL_EXSTYLE );
		bool bRTL = ( (dwExStyle & WS_EX_LAYOUTRTL) != 0 ) ? true : false;
		return bRTL 
			? HTBOTTOMLEFT 
			: HTBOTTOMRIGHT;
	}

 	if( message == WM_CREATE )
	{
		LRESULT lResult = CWnd::WindowProc( message, wParam, lParam );

		CRect rcClient;
		GetClientRect( &rcClient );
 	
		POINT ptCorners[] =
		{
			{
				rcClient.left,
				rcClient.bottom
			},
			{
				rcClient.right,
				rcClient.bottom
			},
			{
				rcClient.right,
				rcClient.top
			},
		};

		HRGN hRgn = ::CreatePolygonRgn( ptCorners, sizeof(ptCorners)/sizeof(ptCorners[0]), ALTERNATE );
		SetWindowRgn( hRgn, TRUE );
		
		return lResult;
	}

	if( message == WM_MOUSEACTIVATE )
		return MA_NOACTIVATEANDEAT;

	if( message == WM_ERASEBKGND )
		return 0L;

	if( message == WM_PRINTCLIENT )
	{
		CDC * pDC = CDC::FromHandle( (HDC)wParam );
		DoPaint( pDC );
		return (!0);
	}

	if( message == WM_PAINT )
	{
		ASSERT_VALID( this );
		CPaintDC dcPaint( this );
		CRect rcClient;
		GetClientRect( &rcClient );
		CExtMemoryDC dc(
			&dcPaint,
			&rcClient
			);
		DoPaint( &dc );
		return 0L;
	}

	return CWnd::WindowProc( message, wParam, lParam );
}