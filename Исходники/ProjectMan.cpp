BOOL CApp::InitInstance()
{
	if(!CDCGFApp::InitInstance()) return FALSE;
	
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

/*
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
*/
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("DEAD:CODE"));

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	CDCGFStringTable::Init();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_PROJECTYPE,
		RUNTIME_CLASS(CProjectDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CProjectView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	//m_pMainWnd->DragAcceptFiles();

	// This code replaces the MFC created menus with 
	// the Ownerdrawn versions 
	static UINT toolbars[]={
		IDR_MAINFRAME, IDR_TOOLBAR_2
	};	
	pDocTemplate->m_hMenuShared=pMainFrame->NewMenu(IDR_PROJECTYPE, toolbars, 2);
	pMainFrame->m_hMenuDefault=pMainFrame->NewDefaultMenu(IDR_MAINFRAME, toolbars, 2);
/*
	CDCGFStringTable::LocMenu(CMenu::FromHandle(pMainFrame->m_hMenuDefault));
	CDCGFStringTable::LocMenu(CMenu::FromHandle(pDocTemplate->m_hMenuShared));
*/
	// This simulates a window being opened if you don't have
	// a default window displayed at startup
	pMainFrame->OnUpdateFrameMenu(pMainFrame->m_hMenuDefault);


	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(FALSE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if(cmdInfo.m_nShellCommand==CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;


	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNothing)
	{
		DoSomeNagging();

		if(GetRegInt(HKEY_CURRENT_USER, DCGF_TOOLS_REG_PATH, "AutoCheckUpdates", 1))
		{
			pMainFrame->CheckForUpdates(true);
		}
	}

	pMainFrame->UpdateMenuURL(pMainFrame->GetMenu());


	return TRUE;
}