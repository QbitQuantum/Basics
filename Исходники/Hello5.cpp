	virtual BOOL InitInstance()
	{
		CFrameWnd* pFrame = new CFrameWnd;
		
		CString str = AfxRegisterWndClass( 0, LoadStandardCursor(IDC_IBEAM),
							(HBRUSH)GetStockObject(BLACK_BRUSH), 
							LoadStandardIcon(IDI_WINLOGO));

		pFrame->Create( str,  // 윈도우 클래스..
						"Hello, MFC", 
						WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
						CRect(100,100,200,200), 0, 0,
						WS_EX_TOPMOST); // 확장 윈도우 style

		pFrame->ShowWindow( SW_SHOW );
		pFrame->UpdateWindow( );
		
		m_pMainWnd = pFrame;

		return TRUE;
	}