BOOL CEdFrame::InitInstance()
{
	if (!CHECKVALIDATE)
		return FALSE;
	
	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetRegistryKey(_T("Edson"));
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	if (m_pDocManager)
		RegisterShellFileTypes(TRUE);

	return TRUE;
}