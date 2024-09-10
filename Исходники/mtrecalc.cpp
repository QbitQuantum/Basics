BOOL CRecalcApp::InitInstance()
{
	// WIN32 multi-threading APIs are not available on non-NT versions
	// of Windows less than Windows version 4.0.
	if ((::GetVersion() & 0x80000000) && (BYTE(::GetVersion()) < 4))
	{
		AfxMessageBox(IDS_CANNOT_RUN_ON_16BIT_WINDOWS_LT_4);
		return FALSE;
	}

	// Standard initialization

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register document templates

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_RECALCTYPE,
		RUNTIME_CLASS(CRecalcDoc),
		RUNTIME_CLASS(CMDIChildWnd),          // standard MDI child frame
		RUNTIME_CLASS(CRecalcView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME)) {
		delete pMainFrame;	
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}