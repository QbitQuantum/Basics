void __cdecl
WinMainCRTStartup()
{
	HWND hWnd;
	HBITMAP bgbm = prepareBackground();
	HBRUSH bgbrush = CreatePatternBrush(bgbm);
	inst = GetModuleHandle(0);

	{
		WNDCLASS wc = {
			0, //style
			winProc, //lpfnWndProc
			0, //cbClsExtra
			0, //cbWndExtra
			inst, //hInstance
			0, //hIcon
			LoadCursor(NULL,IDC_ARROW), //hCursor
			bgbrush,
			0, //lpszMenuName
			TITLE //lpszClassName
		};
		RegisterClass(&wc);
	}

	hWnd = CreateWindow(TITLE, TITLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 0, 0, WIN_WIDTH, WIN_HEIGHT, 0, 0, inst, 0);

	{
		MSG msg;

		while (GetMessage(&msg, 0, 0, 0)) {
			if (!hDlgCurrent || !IsDialogMessage(hDlgCurrent, &msg)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	DestroyWindow(hWnd);
	DeleteObject(bgbrush);
	DeleteObject(bgbm);
	ExitProcess(0);
}