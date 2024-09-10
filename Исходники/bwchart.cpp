BOOL CBwchartApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.


	SetRegistryKey("bwchart");

	// Enable drag/drop open
	//m_pMainWnd->DragAcceptFiles();

	
	if(strstr(AfxGetApp()->m_lpCmdLine,"-korean")!=0)
		SetThreadLocale(MAKELCID(MAKELANGID(LANG_KOREAN,SUBLANG_KOREAN),SORT_DEFAULT ));
	else if(strstr(AfxGetApp()->m_lpCmdLine,"-english")!=0)
		SetThreadLocale(MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US),SORT_DEFAULT ));
	else if(strstr(AfxGetApp()->m_lpCmdLine,"-chinese")!=0)
		SetThreadLocale(MAKELCID(MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED),SORT_DEFAULT ));
	else
		DlgOptions::SetLanguage();
	
	// corrupted file
	CString corrupted = AfxGetApp()->GetProfileString("LOG","LASTREP","");
	if(!corrupted.IsEmpty()) 
	{
		CString msg;
		msg.Format(IDS_CORRUPTED3,(const char*)corrupted);
		AfxMessageBox(msg,MB_OK|MB_ICONEXCLAMATION);
		AfxGetApp()->WriteProfileString("LOG","LASTREP","");
		AfxGetApp()->WriteProfileString("MAIN","LASTREPLAY","");
	}

	// command line mode?
	if(strstr(m_lpCmdLine,"/rep")!=0)
	{
		m_exitCode = /*m_msgCur.wParam =*/ _CommandLineMode();
	}
	else
	{
		// windowed mode
		DlgBWChart dlg(m_lpCmdLine);
		m_pMainWnd = &dlg;
		dlg.DoModal();
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}