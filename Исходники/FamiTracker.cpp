BOOL CFamiTrackerApp::InitInstance()
{
	// InitCommonControls() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	InitCommonControls();
#ifdef SUPPORT_TRANSLATIONS
	LoadLocalization();
#endif
	CWinApp::InitInstance();

	TRACE("App: InitInstance\n");

	if (!AfxOleInit()) {
		TRACE("OLE initialization failed\n");
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T(""));
	LoadStdProfileSettings(MAX_RECENT_FILES);  // Load standard INI file options (including MRU)

	// Load program settings
	m_pSettings = CSettings::GetObject();
	m_pSettings->LoadSettings();

	// Parse command line for standard shell commands, DDE, file open + some custom ones
	CFTCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (CheckSingleInstance(cmdInfo))
		return FALSE;

	//who: added by Derek Andrews <*****@*****.**>
	//why: Load all custom exporter plugins on startup.
	
	TCHAR pathToPlugins[MAX_PATH];
	GetModuleFileName(NULL, pathToPlugins, MAX_PATH);
	PathRemoveFileSpec(pathToPlugins);
	PathAppend(pathToPlugins, _T("\\Plugins"));
	m_customExporters = new CCustomExporters( pathToPlugins );

	// Load custom accelerator
	m_pAccel = new CAccelerator();
	m_pAccel->LoadShortcuts(m_pSettings);
	m_pAccel->Setup();

	// Create the MIDI interface
	m_pMIDI = new CMIDI();

	// Create sound generator
	m_pSoundGenerator = new CSoundGen();

	// Create channel map
	m_pChannelMap = new CChannelMap();

	// Start sound generator thread, initially suspended
	if (!m_pSoundGenerator->CreateThread(CREATE_SUSPENDED)) {
		// If failed, restore and save default settings
		m_pSettings->DefaultSettings();
		m_pSettings->SaveSettings();
		// Show message and quit
		AfxMessageBox(IDS_START_ERROR, MB_ICONERROR);
		return FALSE;
	}

	// Check if the application is themed
	CheckAppThemed();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CDocTemplate0CC* pDocTemplate = new CDocTemplate0CC(		// // //
		IDR_MAINFRAME, 
		RUNTIME_CLASS(CFamiTrackerDoc), 
		RUNTIME_CLASS(CMainFrame), 
		RUNTIME_CLASS(CFamiTrackerView));

	if (!pDocTemplate)
		return FALSE;
	
	if (m_pDocManager == NULL)		// // //
		m_pDocManager = new CDocManager0CC { };
	m_pDocManager->AddDocTemplate(pDocTemplate);

	// Work-around to enable file type registration in windows vista/7
	if (IsWindowsVistaOrGreater()) {		// // //
		HKEY HKCU;
		long res_reg = ::RegOpenKey(HKEY_CURRENT_USER, _T("Software\\Classes"), &HKCU);
		if(res_reg == ERROR_SUCCESS)
			RegOverridePredefKey(HKEY_CLASSES_ROOT, HKCU);
	}

	// Enable DDE Execute open
	EnableShellOpen();

	// Skip this if in wip/beta mode
#if !defined(WIP) && !defined(_DEBUG)
	// Add shell options
	RegisterShellFileTypes();		// // //
	static const LPCTSTR FILE_ASSOC_NAME = _T("0CC-FamiTracker Module");
	AfxRegSetValue(HKEY_CLASSES_ROOT, "0CCFamiTracker.Document", REG_SZ, FILE_ASSOC_NAME, lstrlen(FILE_ASSOC_NAME) * sizeof(TCHAR));
	// Add an option to play files
	CString strPathName, strTemp, strFileTypeId;
	AfxGetModuleShortFileName(AfxGetInstanceHandle(), strPathName);
	CString strOpenCommandLine = strPathName;
	strOpenCommandLine += _T(" /play \"%1\"");
	if (pDocTemplate->GetDocString(strFileTypeId, CDocTemplate::regFileTypeId) && !strFileTypeId.IsEmpty()) {
		strTemp.Format(_T("%s\\shell\\play\\%s"), (LPCTSTR)strFileTypeId, _T("command"));
		AfxRegSetValue(HKEY_CLASSES_ROOT, strTemp, REG_SZ, strOpenCommandLine, lstrlen(strOpenCommandLine) * sizeof(TCHAR));
	}
#endif

	// Handle command line export
	if (cmdInfo.m_bExport) {
		CCommandLineExport exporter;
		exporter.CommandLineExport(cmdInfo.m_strFileName, cmdInfo.m_strExportFile, cmdInfo.m_strExportLogFile, cmdInfo.m_strExportDPCMFile);
		ExitProcess(0);
	}

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo)) {
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister) {
			// Also clear settings from registry when unregistering
			m_pSettings->DeleteSettings();
		}
		return FALSE;
	}

	// Move root key back to default
	if (IsWindowsVistaOrGreater()) {		// // //
		::RegOverridePredefKey(HKEY_CLASSES_ROOT, NULL);
	}

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
	
	// Initialize the sound interface, also resumes the thread
	if (!m_pSoundGenerator->InitializeSound(m_pMainWnd->m_hWnd)) {
		// If failed, restore and save default settings
		m_pSettings->DefaultSettings();
		m_pSettings->SaveSettings();
		// Quit program
		AfxMessageBox(IDS_START_ERROR, MB_ICONERROR);
		return FALSE;
	}
	
	// Initialize midi unit
	m_pMIDI->Init();
	
	if (cmdInfo.m_bPlay)
		theApp.StartPlayer(MODE_PLAY);

#ifdef EXPORT_TEST
	if (cmdInfo.m_bVerifyExport) {
		m_bExportTesting = true;
		VerifyExport(cmdInfo.m_strVerifyFile);
	}
	else {
		// Append menu option
		m_pMainWnd->GetMenu()->GetSubMenu(2)->AppendMenu(MF_SEPARATOR);
		m_pMainWnd->GetMenu()->GetSubMenu(2)->AppendMenu(MF_STRING, ID_MODULE_TEST_EXPORT, _T("Test exporter"));
	}
#endif

	// Save the main window handle
	RegisterSingleInstance();

#ifndef _DEBUG
	m_pMainWnd->GetMenu()->GetSubMenu(4)->RemoveMenu(ID_MODULE_CHANNELS, MF_BYCOMMAND);		// // //
#endif

	if (m_pSettings->General.bCheckVersion)		// // //
		CheckNewVersion(true);

	// Initialization is done
	TRACE("App: InitInstance done\n");

	return TRUE;
}