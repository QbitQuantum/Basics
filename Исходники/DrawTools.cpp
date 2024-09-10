int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	int nRet = 0;
	FUNCTION_BLOCK_INIT();
	{
		FUNCTION_BLOCK_TRACE(0);

		CMessageLoop theLoop;
		_Module.AddMessageLoop(&theLoop);

		CMainFrame wndMain;

		if(wndMain.CreateEx() == NULL)
		{
			ATLTRACE(_T("Main window creation failed!\n"));
			return 0;
		}

		wndMain.ShowWindow(nCmdShow);

		nRet = theLoop.Run();

		_Module.RemoveMessageLoop();
	}
	FUNCTION_BLOCK_UNINIT();
	return nRet;
}