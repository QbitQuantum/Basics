BOOL CCrtdApp::InitInstance()
	{
	// CG: The following block was added by the Splash Screen component.
\
	{
\
		CCommandLineInfo cmdInfo;
\
		ParseCommandLine(cmdInfo);
\

\
//		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
\
	}
	// CG: The following block was inserted by 'Status Bar' component.
	{
		//Set up date and time defaults so they're the same as system defaults
		setlocale(LC_ALL, "");
	}

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

//	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	LoadGlobalParamFromIni();


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

/*	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCrtdDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CCrtdView));
	AddDocTemplate(pDocTemplate);*/

	// Parse command line for standard shell commands, DDE, file open
//	CCommandLineInfo cmdInfo;
//	ParseCommandLine(cmdInfo);

	HBRUSH hBrush=(HBRUSH)GetStockObject(WHITE_BRUSH);
	HCURSOR hCur=(HCURSOR)::LoadCursor(NULL,IDC_ARROW);
	HICON hIco=LoadIcon(MAKEINTRESOURCE(IDR_MAINFRAME));
	LPCTSTR lpClass=AfxRegisterWndClass(CS_DBLCLKS|CS_VREDRAW,hCur,hBrush,hIco);

	MainFrame *pMainFrame = new MainFrame;
	RECT rcM = { 0,0,100,100 };
	::GetWindowRect(::GetDesktopWindow(),&rcM);
	if (!pMainFrame->Create(lpClass,"Continuous Real-Time Display", WS_VISIBLE | WS_OVERLAPPEDWINDOW,rcM,NULL,NULL))	return FALSE;

	m_pMainWnd = pMainFrame;
	pMainFrame->ShowWindow(m_nCmdShow|SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();


	return TRUE;
	}