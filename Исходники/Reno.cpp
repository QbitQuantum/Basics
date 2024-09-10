BOOL CRenoApp::InitInstance()
{
	// Set common controls standard classes
	INITCOMMONCONTROLSEX commonControls;
	commonControls.dwSize = sizeof(commonControls);
	commonControls.dwICC = ICC_WIN95_CLASSES;

	// Initialize common controls
	if(!InitCommonControlsEx(&commonControls))
	{
		AfxMessageBox(IDP_CONTROLS_INIT_FAILED);
		return FALSE;
	}

	// Initialize winsock
	if(!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Set settings registry key, if not set the ini file will be used
	//SetRegistryKey(TEXT("Miha Software"));

	// Get the current directory and add it to the ini path so the ini does not get stored into win.ini
	TCHAR directory[MAX_PATH];
	GetModuleFileName(NULL,directory,sizeof(directory)/sizeof(TCHAR));
	PathRemoveFileSpec(directory);
	PathAppend(directory,m_pszProfileName);
 
	// Store the ini file path
	free((LPVOID)m_pszProfileName);
	m_pszProfileName = _tcsdup(directory);	// String gets free'd by mfc on app exit

	// Initialize super
	if(!CRenoSocketApp::InitInstance())
		return FALSE;

	// Initialize fonts
	if(!InitFonts())
		return FALSE;

	// Create the main window
	CMDIFrameWnd* pFrame = new CRenoMainFrame;
	if(!pFrame)
		return FALSE;

	// Set our local member pointer to the frame instance
	m_pMainWnd = pFrame;

	// Create main MDI frame window
	if(!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	// Try to load shared MDI menus and accelerator table
	// TODO Add additional member variables and load calls for additional menu types your application may need

	m_hCommandMenu = ::LoadMenu(AfxGetResourceHandle(),MAKEINTRESOURCE(IDR_COMMANDFRAME));
	m_hCommandAccelerator = ::LoadAccelerators(AfxGetResourceHandle(),MAKEINTRESOURCE(IDR_COMMANDFRAME));

	m_hChatMenu = ::LoadMenu(AfxGetResourceHandle(),MAKEINTRESOURCE(IDR_CHATFRAME));
	m_hChatAccelerator = ::LoadAccelerators(AfxGetResourceHandle(),MAKEINTRESOURCE(IDR_CHATFRAME));

	// Load the settings
	LoadSettings();

	// TODO Load the previous window placement

	// The main window has been initialized, so show and update it
	pFrame->ShowWindow(m_nCmdShow);
	pFrame->UpdateWindow();

	// Create a inital command window
	// TODO Make it an option
	OnFileNew();

	return TRUE;
}