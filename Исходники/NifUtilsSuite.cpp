//-----  InitInstance()  ------------------------------------------------------
BOOL CNifUtilsSuiteApp::InitInstance()
{
	//  init common controls (since Win95)
	INITCOMMONCONTROLSEX	InitCtrls;

	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC  = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	//  init own instance
	CWinAppEx::InitInstance();

	//  no interaction with Win7 taskbar
	EnableTaskbarInteraction(FALSE);

	//  init RichEdit
	AfxInitRichEdit2();

	//  initialize configuration
	CStringA	configName;
	bool		hasConfig(false);

	GetModuleFileNameA(NULL, configName.GetBuffer(MAX_PATH), MAX_PATH);
	configName.ReleaseBuffer();
	configName.Replace(".exe", ".xml");
	hasConfig = Configuration::initInstance((const char*) configName);

	//  initialize Havok  (HK_MEMORY_USAGE bytes of physics solver buffer)
	hkMemoryRouter*		pMemoryRouter(hkMemoryInitUtil::initDefault(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(HK_MEMORY_USAGE)));
	hkBaseSystem::init(pMemoryRouter, errorReport);

	//  initialize material map
	Configuration*	pConfig(Configuration::getInstance());

	NifUtlMaterialList::initInstance(pConfig->_pathNifXML, pConfig->_matScanTag, pConfig->_matScanName);


	// Register the application's document templates.
	CSingleDocTemplate*	pDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,
															RUNTIME_CLASS(CNifUtilsSuiteDoc),
															RUNTIME_CLASS(CNifUtilsSuiteFrame),
															RUNTIME_CLASS(CFormNifConvertView))
															);
	if (!pDocTemplate)		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo	cmdInfo;

	ParseCommandLine(cmdInfo);
	if (!ProcessShellCommand(cmdInfo))		return FALSE;

	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	if (!hasConfig)
	{
		AfxMessageBox(L"Seems you're running NifUtilsSuite for the first time.\nYou're redirected to Settings now.");
		m_pMainWnd->PostMessage(WM_COMMAND, ID_OPTIONS_EDIT);
	}

	return TRUE;
}