BOOL CScintillaDemoApp::InitInstance()
{
  //Load the scintilla dll
  m_hSciDLL = LoadLibrary(_T("SciLexer.dll"));
  if (m_hSciDLL == NULL)
  { 
    AfxMessageBox(_T("Scintilla DLL is not installed, Please download the SciTE editor and copy the SciLexer.dll into this application's directory"));
    return FALSE;
  }

	SetRegistryKey(_T("PJ Naughter"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	//Register the application's document templates.  Document templates
	//serve as the connection between documents, frame windows and views.
	CMultiDocTemplate* pDocTemplate = new CMultiDocTemplate(IDR_SCINTITYPE,
		RUNTIME_CLASS(CScintillaDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CScintillaDemoView));
	AddDocTemplate(pDocTemplate);

	//create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	//Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	//Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}