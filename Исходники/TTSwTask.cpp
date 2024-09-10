int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	
	if(_tcsstr(lpCmdLine, _T("/glass")))
	{
		g_Aero = TRUE;
	}
	
	GetIniPath();
	g_WndList  = new CWndList();
	g_Launcher = new CLauncher();
	g_EditIni = new CEditIniFile();
	g_Launcher->ReadFromFile(g_IniPath);

	BOOL enable = FALSE;
	DwmIsCompositionEnabled( &enable );
	if(!enable) g_Aero = FALSE;

	MyRegisterClass(hInstance);
	if (!InitInstance (hInstance, nCmdShow)) return FALSE;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	delete [] g_IniPath;
	delete g_EditIni;
	delete g_WndList;
	delete g_Launcher;
	return (int) msg.wParam;
}