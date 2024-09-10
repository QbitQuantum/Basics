void configwnd_create()
{
	WNDCLASS wc;
	HWND wnd;
	MSG msg;
	HACCEL acctable = CreateAcceleratorTable((LPACCEL)&c_AccelTable, sizeof(c_AccelTable) / sizeof(ACCEL));
	InitCommonControls();
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(g_hInstance, OPTWND_ICON_NAME);
	wc.hInstance = g_hInstance;
	wc.lpszMenuName = NULL;
	wc.style = CS_PARENTDC | CS_DBLCLKS;
	wc.lpfnWndProc = configwnd_msgproc;
	wc.lpszClassName = OPTWND_CLASS_NAME;
	RegisterClass(&wc);
	g_hFont = CreateFont(-10, 0, 0, 0, FW_NORMAL, 0,
				0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, OPTWND_FONT_NAME);
	wnd = CreateWindowEx(0, OPTWND_CLASS_NAME, OPTWND_WINDOW_NAME, WS_VISIBLE | WS_SYSMENU | WS_OVERLAPPED | DS_SYSMODAL,
			(GetSystemMetrics(SM_CXSCREEN) - OPTWND_WINDOW_WIDTH) / 2,
			(GetSystemMetrics(SM_CYSCREEN) - OPTWND_WINDOW_HEIGHT) / 2,
			OPTWND_WINDOW_WIDTH, OPTWND_WINDOW_HEIGHT, g_hwndOlly, NULL, g_hInstance, NULL);
	ShowWindow(wnd, SW_SHOWNORMAL);
	UpdateWindow(wnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(wnd, acctable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	DeleteObject(g_hFont);
	UnregisterClass(OPTWND_CLASS_NAME, g_hInstance);
	DestroyAcceleratorTable(acctable);
}