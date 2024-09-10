int APIENTRY _tWinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPTSTR    lpCmdLine,
					 int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);

	SetDllDirectory(L"");
	SetTaskIDPerUUID();
	MSG msg;
	HACCEL hAccelTable;

	CCmdLineParser parser(lpCmdLine);

	if (parser.HasKey(_T("?")) || parser.HasKey(_T("help")))
	{
		TCHAR buf[1024];
		LoadString(hInstance, IDS_COMMANDLINEHELP, buf, sizeof(buf)/sizeof(TCHAR));
		MessageBox(NULL, buf, _T("TortoiseGitUDiff"), MB_ICONINFORMATION);
		return 0;
	}

	INITCOMMONCONTROLSEX used = {
		sizeof(INITCOMMONCONTROLSEX),
		ICC_STANDARD_CLASSES | ICC_BAR_CLASSES
	};
	InitCommonControlsEx(&used);


	HMODULE hSciLexerDll = ::LoadLibrary(_T("SciLexer.DLL"));
	if (hSciLexerDll == NULL)
		return FALSE;

	CMainWindow mainWindow(hInstance);
	mainWindow.SetRegistryPath(_T("Software\\TortoiseGit\\UDiffViewerWindowPos"));
	if (parser.HasVal(_T("title")))
		mainWindow.SetTitle(parser.GetVal(_T("title")));
	else if (parser.HasVal(_T("patchfile")))
		mainWindow.SetTitle(parser.GetVal(_T("patchfile")));
	else
		mainWindow.SetTitle(_T("diff from pipe"));

	if (!mainWindow.RegisterAndCreateWindow())
	{
		FreeLibrary(hSciLexerDll);
		return 0;
	}

	bool bLoadedSuccessfully = false;
	if ( (lpCmdLine[0] == 0) ||
		(parser.HasKey(_T("p"))) )
	{
		// input from console pipe
		// set console to raw mode
		DWORD oldMode;
		GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &oldMode);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), oldMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

		bLoadedSuccessfully = mainWindow.LoadFile(GetStdHandle(STD_INPUT_HANDLE));
	}
	else if (parser.HasVal(_T("patchfile")))
		bLoadedSuccessfully = mainWindow.LoadFile(parser.GetVal(_T("patchfile")));
	else if (lpCmdLine[0] != 0)
		bLoadedSuccessfully = mainWindow.LoadFile(lpCmdLine);


	if (!bLoadedSuccessfully)
	{
		FreeLibrary(hSciLexerDll);
		return 0;
	}

	::ShowWindow(mainWindow.GetHWNDEdit(), SW_SHOW);
	::SetFocus(mainWindow.GetHWNDEdit());

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TORTOISEUDIFF));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(mainWindow, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	FreeLibrary(hSciLexerDll);
	return (int) msg.wParam;
}