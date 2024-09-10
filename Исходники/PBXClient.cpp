BOOL CPBXClientApp::InitInstance()
{
	
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(REG_KEY_APP);

	CString lang = GetProfileString("Settings", "Language", "");
	SetLanguage(lang);
	   
	CString cmdLine = this->m_lpCmdLine;

	HWND hwnd = FindWindow(NULL, _T("BSOC Main Application Window"));

	m_bShellOpenFile = FALSE;	
	m_bAllowCmdLineOriginate = 1;	
	m_bDeveloperVersion = TRUE;

	if (cmdLine.Left(9).MakeLower()=="originate") {
		Semaphore s(ORIGINATE_FILE_MUTEX);
		CStdioFile debugFile(::theApp.GetInstallDir()+"\\originate.tmp", CFile::modeCreate | CFile::modeWrite);
		debugFile.SeekToEnd();
		debugFile.WriteString(cmdLine);
		debugFile.Close();		
		return TRUE;
	}	

	if (hwnd!=NULL) { //only one instance of OutCALL can be run		
		CString str;
		str.Format(_("%s is already running."), APP_NAME);
		MessageBox(NULL, str, APP_NAME, MB_ICONINFORMATION | MB_OK);
		return FALSE;
	}

	WSADATA		WSAData = { 0 };
	if ( 0 != WSAStartup( WSA_VERSION, &WSAData ) )
	{
		// Tell the user that we could not find a usable
		// WinSock DLL.
		if ( LOBYTE( WSAData.wVersion ) != LOBYTE(WSA_VERSION) ||
			 HIBYTE( WSAData.wVersion ) != HIBYTE(WSA_VERSION) )
			 ::MessageBox(NULL, _("Incorrect version of WS2_32.dll found."), APP_NAME, MB_OK | MB_ICONERROR);

		WSACleanup( );
		return FALSE;
	}	
	

	if (_tcscmp(this->m_lpCmdLine, _T("background"))==0) {
		Sleep(10000);
	} else if (cmdLine!="") {
		m_bShellOpenFile = TRUE;
		ReadConfigFile(cmdLine);		
	}

	AfxOleInit();
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

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	pFrame->CreateDatabaseTable("RecivedCalls", "CREATE TABLE RecivedCalls(Date TEXT, Time TEXT, Callee TEXT, CallerID TEXT, Sec NUMERIC)");
	pFrame->CreateDatabaseTable("PlacedCalls", "CREATE TABLE PlacedCalls(Date TEXT, Time TEXT, Callee TEXT, CallerID TEXT, Sec NUMERIC)");
	pFrame->CreateDatabaseTable("MissedCalls", "CREATE TABLE MissedCalls(NewCall NUMERIC, Date TEXT, Time TEXT, Callee TEXT, CallerID TEXT, Sec NUMERIC)");
	pFrame->CreateDatabaseTable("Contacts", "CREATE TABLE Contacts(Title TEXT, FirstName TEXT, MiddleName TEXT, LastName TEXT, Suffix TEXT, CompanyName TEXT, Assistant TEXT, Business TEXT, Business2 TEXT, BusinessFax TEXT, Callback TEXT, Car TEXT, Company TEXT, Home TEXT, Home2 TEXT, HomeFax TEXT, ISDN TEXT, Mobile TEXT, Other TEXT, OtherFax TEXT, Pager TEXT, PrimaryTel TEXT, Radio TEXT, Telex TEXT, TTYTDD TEXT)");

	// create and load the frame with its resources
	int left = (GetSystemMetrics(SM_CXSCREEN)-500)/2;	
	int top = (GetSystemMetrics(SM_CYSCREEN)-500)/2;
	

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | WS_MINIMIZE | FWS_ADDTOTITLE, NULL,
		NULL);
	pFrame->MoveWindow(left, top, left+500, top+500);


	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_HIDE);
	pFrame->UpdateWindow();

	//pFrame->SetWindowPos(&pFrame->wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	this->m_pMainWnd = pFrame;	
		
	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	IntegrateIntoOutlook();
		
	BOOL showSettingsDlg = (GetProfileInt("Settings", "ShowSettingsOnStartup", 0)==1?TRUE:FALSE);
	CSettingsDlg settingsDlg;
	
	if (showSettingsDlg || (pFrame->IsOutCALLConfigured()==false)) {
		settingsDlg.DoModal();		
	}

	if (GetProfileInt("Settings", "ContactsLoaded", 0)==0 && GetProfileInt("Settings", "OutlookFeatures", 1)==1) {
		pFrame->LoadOutlookContacts(NULL);		
	}

	return TRUE;
}