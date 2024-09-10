BOOL CMyWinApp::InitInstance(){
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	m_pMainWnd = pFrame;
	pFrame->Create(NULL,"MFCSplit");
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return true;
}