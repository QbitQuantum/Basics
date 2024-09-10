int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	if( !RunTimeHelper::IsVista() )
	{
		AtlMessageBox(NULL, L"Windows Vista or greater is required to run this program.");
		return 0;
	}

	CDwm dwm;
	cIsComposited = dwm.DwmIsCompositionEnabled()!=FALSE;

	
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	int basex = 314;//320
	int basey = 290;//285

	CMainFrame frame;
	if( frame.CreateEx(0, CRect(0, 0, basex, basey))==NULL )
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	_wndMain = frame;
	_wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}