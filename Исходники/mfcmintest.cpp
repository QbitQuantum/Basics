	BOOL InitInstance()
	{
		CFrameWnd* pFrame = new CFrameWnd;
		pFrame->Create(NULL, L"Hello MFC");
		pFrame->ShowWindow(m_nCmdShow);
		pFrame->UpdateWindow();
		m_pMainWnd = pFrame;
		return TRUE;
	}