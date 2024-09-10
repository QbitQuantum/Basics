	virtual BOOL InitInstance()
	{
		CMainFrame* pFrame = new CMainFrame;

		pFrame->Create(0, "Message");
		pFrame->ShowWindow( SW_SHOW );
		pFrame->UpdateWindow( );

		m_pMainWnd = pFrame;

		return TRUE;
	}