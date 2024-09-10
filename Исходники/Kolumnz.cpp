int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	if (wndMain.m_wp.showCmd == SW_MAXIMIZE)
		nCmdShow = SW_MAXIMIZE;
	if (wndMain.m_wp.rcNormalPosition.right > 0 &&
		wndMain.m_wp.rcNormalPosition.bottom > 0 &&
		wndMain.m_wp.rcNormalPosition.top < wndMain.m_wp.rcNormalPosition.bottom && 
		wndMain.m_wp.rcNormalPosition.left < wndMain.m_wp.rcNormalPosition.right)
		wndMain.MoveWindow(	
			wndMain.m_wp.rcNormalPosition.left, 
			wndMain.m_wp.rcNormalPosition.top, 
			wndMain.m_wp.rcNormalPosition.right-wndMain.m_wp.rcNormalPosition.left, 
			wndMain.m_wp.rcNormalPosition.bottom-wndMain.m_wp.rcNormalPosition.top, FALSE); 
	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}