int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;

	szTitle = GString(IDS_APP_TITLE);
	szWindowClass = GString(IDC_LAUNCHBROWSER);
	OptionsKeyName = Format(TEXT("Software\\%s"), szTitle.c_str());
	
	// if it's running already, pop the options dialog
	HWND existingWindow = FindWindow(szWindowClass.c_str(), szTitle.c_str());
	if(existingWindow != NULL)
	{
		SendNotifyMessage(existingWindow, WM_COMMAND, ID_FILE_OPTIONS, 0);
		return FALSE;
	}

	RegisterWindowClass(hInstance);

	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	Browser::ScanRegistryForBrowsers();
	SearchEngine::InitSearchEngines();

	MouseDoubleClickTime = GetDoubleClickTime() / 1000.0;

	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, fnKeyboardHook, hInstance, 0);

	if(LoadOptionsFromRegistry() == FALSE)
	{
		PostMessage(hMainWindow, WMU_POP_OPTIONS_DIALOG, 0, 0);
	}

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}