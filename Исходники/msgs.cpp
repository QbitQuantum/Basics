int LoadSendRecvMessageModule(void)
{
	if (FIF == 0) {
		MessageBox(0, TranslateT("The image service plugin (advaimg.dll) is not properly installed.\n\nTabSRMM is disabled."), TranslateT("TabSRMM fatal error"), MB_OK | MB_ICONERROR);
		return 1;
	}

	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC  = ICC_COOL_CLASSES | ICC_BAR_CLASSES | ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	Utils::loadSystemLibrary(L"\\riched20.dll");

	OleInitialize(NULL);
	mREOLECallback = new REOLECallback;
	Win7Taskbar = new CTaskbarInteract;
	Win7Taskbar->updateMetrics();

	ZeroMemory(&nen_options, sizeof(nen_options));
	M.m_hMessageWindowList = WindowList_Create();
	PluginConfig.hUserPrefsWindowList = WindowList_Create();
	sendQueue = new SendQueue;
	Skin = new CSkin;
	sendLater = new CSendLater;

	InitOptions();

	InitAPI();

	PluginConfig.reloadSystemStartup();
	ReloadTabConfig();
	NEN_ReadOptions(&nen_options);

	db_set_b(0, TEMPLATES_MODULE, "setup", 2);
	LoadDefaultTemplates();

	BuildCodePageList();

	return 0;
}