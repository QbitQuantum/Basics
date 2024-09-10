BOOL CXsvrApp::InitInstance()
{
	OleInitialize(NULL);
	AfxEnableControlContainer();

	InitializeCriticalSection(& g_cs);

	CFileFind fFind;
	CStdioFile file;
	char buf[MAX_PATH];
	GetProgramDirectory(buf);
	CString fileName;
	fileName.Format("%s%s", buf, "sys.log");
	if (! fFind.FindFile(fileName))
	{
	//	AfxMessageBox("File don't existed.");
		file.Open(fileName, CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone, NULL);
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

	CXsvrDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}