BOOL CMcEvtQueryApp::InitInstance()
{
	//get app path
    char lpFilename[_MAX_PATH];
    memset(lpFilename,0,_MAX_PATH);
    GetModuleFileName( NULL,lpFilename,_MAX_PATH);
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    _splitpath( lpFilename, drive, dir, fname, ext );
    CString sAppDrive=drive;
    CString sAppPath=dir;
    m_path=sAppDrive+sAppPath;

	GetPrivateProfileString("evtlq", "folder", (LPCSTR)m_path, lpFilename, _MAX_PATH, get_config_file());
	m_folder=lpFilename;

    AfxEnableControlContainer();

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
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources

	//pFrame->LoadFrame(IDR_MAINFRAME,
	//	WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
	//	NULL);
	pFrame->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW,NULL,NULL);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

    CMCCommand cmdInfo;
	ParseCommandLine(cmdInfo);
    if(cmdInfo.bShowAtTop){
        pFrame->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
    }

	return TRUE;
}