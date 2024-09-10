int Run(LPTSTR lpstrCmdLine = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainDlg dlgMain;

	if(dlgMain.Create(NULL) == NULL)
	{
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}

	if(dlgMain.openPreview() == NULL)
	{
		ATLTRACE(_T("Preview Window creation failed!\n"));
		return 0;
	}

	dlgMain.ShowWindow(nCmdShow);

	if(lpstrCmdLine){
		char buf[256];
		wcstombs(buf, lpstrCmdLine, sizeof buf);
		dlgMain.OpenModel(buf);
	}

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}