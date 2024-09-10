int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = 
#ifndef _WIN32_WCE
		SW_SHOWDEFAULT
#else // _WIN32_WCE
		SW_SHOWNORMAL
#endif // _WIN32_WCE
		)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}