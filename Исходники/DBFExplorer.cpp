BOOL CDBFExplorerApp::InitInstance()
{
   _tsetlocale(LC_ALL, _T(""));
   // Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

   InitCommonControls();
#ifndef _WIN64
   AfxDaoInit();
#endif
	// Change the registry key under which our settings are stored.
   SetRegistryKey(_T("Pablo Software Solutions"));

	LoadStdProfileSettings(max(_AFX_MRU_COUNT, 9));  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

   AddDocTemplates();

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE | FWS_PREFIXTITLE))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
#ifdef _DEBUG
   RegisterShellFileTypes(TRUE);
#endif

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;

	// prevent application from opening a new (empty) document
	//cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew) 
      cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_nCmdShow = SW_SHOWMAXIMIZED;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	return TRUE;
}