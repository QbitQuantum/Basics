/**
 * @brief Application entry point.
 * @param hInstance - Handle to the current instance of the application.
 * @param hPrevInstance - Handle to the previous instance of the application. This parameter is always NULL.
 * @param pszCmdLine - Pointer to a null-terminated string specifying the command line for the application, excluding the program name.
 * @param nCmdShow - Specifies how the window is to be shown.
 */
int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, PTSTR pszCmdLine, int nCmdShow)
{
#ifdef _CRTDBG_MAP_ALLOC
	// Watch for memory leaks.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	HRESULT hRes = OleInitialize(NULL);
	ATLASSERT(SUCCEEDED(hRes));

	// This resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used.
	::DefWindowProc(NULL, 0, 0, 0L);

	AtlInitCommonControls(ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES);	// Add flags to support other controls.

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(pszCmdLine, nCmdShow);

	_Module.Term();
	OleUninitialize();

	return nRet;
}