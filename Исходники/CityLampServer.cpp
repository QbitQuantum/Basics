int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	if(dlgMain.Create(NULL) == NULL)
	{
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}
	
	dlgMain.ShowWindow(nCmdShow);

	StartServer();

	int nRet = theLoop.Run();
	_Module.RemoveMessageLoop();
	return nRet;
}