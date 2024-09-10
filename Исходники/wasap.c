int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
	char *pb;
	char *pe;
	WNDCLASS wc;
	HWND hWnd;
	HMENU hMainMenu;
	MSG msg;

	for (pb = lpCmdLine; *pb == ' ' || *pb == '\t'; pb++);
	for (pe = pb; *pe != '\0'; pe++);
	while (--pe > pb && (*pe == ' ' || *pe == '\t'));
	/* Now pb and pe point at respectively the first and last
	   non-blank character in lpCmdLine. If pb > pe then the command line
	   is blank. */
	if (*pb == '"' && *pe == '"')
		pb++;
	else
		pe++;
	*pe = '\0';
	/* Now pb contains the filename, if any, specified on the command line. */

	hWnd = FindWindow(WND_CLASS_NAME, NULL);
	if (hWnd != NULL) {
		/* as instance of WASAP is already running */
		if (*pb != '\0') {
			/* pass the filename */
			COPYDATASTRUCT cds = { 'O', (DWORD) (pe + 1 - pb), pb };
			SendMessage(hWnd, WM_COPYDATA, (WPARAM) NULL, (LPARAM) &cds);
		}
		else {
			/* bring the open dialog to top */
			HWND hChild = GetLastActivePopup(hWnd);
			if (hChild != hWnd)
				SetForegroundWindow(hChild);
		}
		return 0;
	}

	wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WND_CLASS_NAME;
	RegisterClass(&wc);

	hWnd = CreateWindow(WND_CLASS_NAME,
		APP_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	hStopIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STOP));
	hPlayIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAY));
	hMainMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_TRAYMENU));
	hTrayMenu = GetSubMenu(hMainMenu, 0);
	hSongMenu = CreatePopupMenu();
	InsertMenu(hTrayMenu, 1, MF_BYPOSITION | MF_ENABLED | MF_STRING | MF_POPUP,
	           (UINT_PTR) hSongMenu, "So&ng");
	hQualityMenu = GetSubMenu(hTrayMenu, 3);
	SetMenuDefaultItem(hTrayMenu, 0, TRUE);
	Tray_Add(hWnd, hStopIcon);
	SetQuality(hWnd, use_16bit, quality);
	if (*pb != '\0') {
		memcpy(strFile, pb, pe + 1 - pb);
		LoadFile(hWnd);
	}
	else
		SelectAndLoadFile(hWnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	WaveOut_Close();
	Tray_Delete(hWnd);
	DestroyMenu(hMainMenu);
	return 0;
}