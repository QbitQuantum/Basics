int main(int argc, char *argv[])
{
	WNDCLASSW wc;
	MSG msg;

	ZeroMemory(&wc, sizeof (WNDCLASSW));
	wc.lpszClassName = L"mainwin";
	wc.lpfnWndProc = wndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIconW(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	RegisterClassW(&wc);

	mainwin = CreateWindowExW(0,
		L"mainwin", L"mainwin",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		400, 400,
		NULL, NULL, GetModuleHandle(NULL), NULL);

	if (argc > 1)
		dialog = CreateWindowExW(WS_EX_CONTROLPARENT,
			WC_DIALOG, L"",
			WS_CHILD | WS_VISIBLE,
			100, 100, 200, 200,
			mainwin, NULL, GetModuleHandle(NULL), NULL);
	else {
		const BYTE dlgtemplate[] = {
			0x01, 0x00,				// version
			0xFF, 0xFF,				// signature
			0x00, 0x00, 0x00, 0x00,		// help
			0x00, 0x00, 0x01, 0x00,		// WS_EX_CONTROLPARENT
			0x00, 0x00, 0x00, 0x50,		// WS_CHILD | WS_VISIBLE
			0x00, 0x00,				// no controls
			100, 0,					// X/Y/Width/Height
			100, 0,
			100, 0,
			100, 0,
			0x00, 0x00,				// menu
			0x00, 0x00,				// class
			0x00, 0x00,				// title
			0x00, 0x00, 0x00, 0x00,		// some padding
			0x00, 0x00, 0x00, 0x00,		// more padding
			0x00, 0x00, 0x00, 0x00,		// just to be safe
		};

		dialog = CreateDialogIndirectW(GetModuleHandle(NULL), (LPCDLGTEMPLATEW) dlgtemplate, mainwin, dlgproc);
	}
	printf("%I32X\n", EnableThemeDialogTexture(dialog, ETDT_ENABLE | ETDT_USETABTEXTURE | ETDT_ENABLETAB));

	ShowWindow(mainwin, SW_SHOWDEFAULT);
	UpdateWindow(mainwin);

	while (GetMessageW(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}