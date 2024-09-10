BOOL CMyWinApp::InitInstance(){
	//此函数的this为theApp
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCBase");
	m_pMainWnd = pFrame;
	//theApp.m_pMainWnd
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return true;
}