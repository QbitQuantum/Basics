int Main(HINSTANCE hInstance)
{
	WNDCLASSEX wcx;
	HWND       wnd;
	MSG        msg;

	if ((wnd = FindWindow(App.Class, App.Title)) != NULL) {
		/* reload config */
		PostMessage(wnd, WM_APP_RELOAD, 0, 0);
		return 0;
	}

	CoInitializeEx(0, COINIT_MULTITHREADED);
	CoInitializeSecurity(NULL, -1, NULL, NULL,
		RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	WinAPI_Initialize();
	Global_Initialize();
	Status_Initialize();
	Config_Initialize();

	SpecialKey_Initialize();

	ExtractIconEx(AppIcon.File, IsVistaOrGreater() ? AppIcon.Index.Vista : AppIcon.Index.XP,
		&Global.hIconLarge, &Global.hIconSmall, 1);

	ZeroMemory(&wcx, sizeof wcx);
	wcx.cbSize        = sizeof wcx;
	wcx.style         = CS_NOCLOSE;
	wcx.lpfnWndProc   = WndProc;
	wcx.hInstance     = hInstance;
	wcx.hCursor       = (HCURSOR)LoadImage(NULL, IDC_ARROW,
	                    IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcx.lpszClassName = App.Class;
	wcx.hIcon         = Global.hIconLarge;
	wcx.hIconSm       = Global.hIconSmall;
	RegisterClassEx(&wcx);
	CreateWindowEx(0, wcx.lpszClassName, App.Title, WS_POPUP,
		CW_USEDEFAULT, 0, 10, 10, NULL, NULL, wcx.hInstance, NULL);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DestroyIcon(Global.hIconLarge);
	DestroyIcon(Global.hIconSmall);

	WinAPI_Uninitialize();
	CoUninitialize();
	return (int)msg.wParam;
}