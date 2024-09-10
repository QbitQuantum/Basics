BOOL CMyWinApp::InitInstance(){
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCToolBar",WS_OVERLAPPEDWINDOW,
		CFrameWnd::rectDefault,NULL/*,MAKEINTRESOURCE(IDR_MENU1)*/);
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return true;
}