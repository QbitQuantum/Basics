int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	BkString::Load(IDR_STRING_DEF); // ╪стьвж╥Ш╢╝
	BkSkin::LoadSkins(IDR_SKIN_DEF); // ╪стьф╓╥Т
	BkStyle::LoadStyles(IDR_STYLE_DEF); // ╪сть╥Г╦Я

	CMainDlg dlgMain;

	if(dlgMain.Create(NULL) == NULL)
	{
		DWORD dwErr = GetLastError();
		ATLTRACE(_T("Main dialog creation failed!\n"));
		return 0;
	}
 
	dlgMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}