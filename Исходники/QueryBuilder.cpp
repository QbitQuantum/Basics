BOOL CQueryBuilderApp::InitInstance()
{
	HRESULT hRes = _Module.Init(NULL, m_hInstance);
	ATLASSERT(SUCCEEDED(hRes));

#ifndef _DEBUG
	// Setup exception handler
	BT_SetAppName(_T("ECL IDE"));
	BT_SetSupportEMail(_T("*****@*****.**"));
	BT_SetFlags(BTF_DETAILEDMODE | BTF_EDITMAIL | BTF_ATTACHREPORT);
    BT_SetSupportURL(_T("http://hpccsystems.com/support"));

	// = BugTrapServer ===========================================
	//BT_SetSupportServer(_T("localhost"), 9999);
	// - or -
	//BT_SetSupportServer(_T("127.0.0.1"), 9999);

	// = BugTrapWebServer ========================================
	//BT_SetSupportServer(_T("http://localhost/BugTrapWebServer/RequestHandler.aspx"), BUGTRAP_HTTP_PORT);

	// required since VS 2005 SP1
	BT_InstallSehFilter();
#endif
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	HINSTANCE hInstanceResources = ::LoadLibrary(_T("en_us.dll"));
	_Module.SetResourceInstance(hInstanceResources);
	AfxSetResourceHandle(hInstanceResources);

	SetApplicationName(_T("eclide.exe"));
	boost::filesystem::path iniPath;
	GetIniPath(iniPath);
	CComPtr<IConfig> ini = CreateIConfig(QUERYBUILDER_INI, iniPath);
	CComPtr<IConfig> config = CreateIConfig(QUERYBUILDER_CFG);

	if (!hGrid)
		hGrid = ::LoadLibrary(SGRID::CGridCtrl::GetLibraryName());

	std::_tstring majorVersion;
	GetAppMajorVersion(majorVersion);

	SetRegistryKey((boost::_tformat(_T("HPCC Systems\\Version%1%")) % majorVersion).str().c_str());
	LoadStdProfileSettings(0);  // Load standard INI file options

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL, RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);
	theApp.EnableTaskbarInteraction(false);

	//const TCHAR * path = _tgetenv(_T("PATH"));
	//if (path)
	//{
	//	const TCHAR * hpccbin = _tgetenv(_T("HPCCBIN"));
	//	if (hpccbin)
	//	{
	//		boost::filesystem::wpath eclccPath = hpccbin;
	//		eclccPath /= _T("eclcc.exe");
	//		if (boost::filesystem::exists(eclccPath))
	//		{
	//			std::_tstring envVar = _T("PATH=");
	//			envVar += hpccbin;
	//			envVar += _T(";");
	//			envVar += path;
	//			_tputenv(envVar.c_str());
	//			ini->Set(GLOBAL_COMPILER_LOCATION, eclccPath.native_file_string());
	//		}

	//		boost::filesystem::wpath stdLibPath = hpccbin;
	//		stdLibPath /= _T("ecllib");
	//		if (boost::filesystem::exists(stdLibPath))
	//		{
	//			ini->Set(GLOBAL_COMPILER_STDLIB, stdLibPath.native_file_string());
	//		}
	//	}
	//}

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMDIFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create main MDI frame window
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	// try to load shared MDI menus and accelerator table
	//TODO: add additional member variables and load calls for
	//	additional menu types your application may need
	//HINSTANCE hInst = AfxGetResourceHandle();
	//m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_QueryBuilderTYPE));
	//m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_QueryBuilderTYPE));

	// The main window has been initialized, so show and update it
	pFrame->ShowWindow(m_nCmdShow);
	pFrame->UpdateWindow();

	return TRUE;
}