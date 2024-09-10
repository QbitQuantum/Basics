CTortoiseProcApp::CTortoiseProcApp()
{
	CTraceToOutputDebugString::Instance()(_T(__FUNCTION__) _T(": Constructor\n"));
	SetDllDirectory(L"");
	// prevent from inheriting %GIT_DIR% from parent process by resetting it,
	// use MSVC function instead of Windows API because MSVC runtime caches environment variables
	_tputenv(_T("GIT_DIR="));
	CCrashReport::Instance().AddUserInfoToReport(L"CommandLine", GetCommandLine());
	EnableHtmlHelp();
	SYS_IMAGE_LIST();
	CHooks::Create();
	git_threads_init();
	m_bLoadUserToolbars = FALSE;
	m_bSaveState = FALSE;
	retSuccess = false;
	m_gdiplusToken = NULL;
#if defined (_WIN64) && _MSC_VER >= 1800
	_set_FMA3_enable(0);
#endif
}