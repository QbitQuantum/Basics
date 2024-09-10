int main(void)
{
	WNDCLASSW wc;
	HWND mainwin;
	RECT r;
	INITCOMMONCONTROLSEX icc;
	MSG msg;

	ZeroMemory(&icc, sizeof (INITCOMMONCONTROLSEX));
	icc.dwSize = sizeof (INITCOMMONCONTROLSEX);
	icc.dwICC = ICC_PROGRESS_CLASS |
		ICC_PROGRESS_CLASS |
		ICC_USEREX_CLASSES;
	if (InitCommonControlsEx(&icc) == 0)
		abort();

	ZeroMemory(&wc, sizeof (WNDCLASSEX));
	wc.lpszClassName = L"mainwin";
	wc.lpfnWndProc = wndproc;
	wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	if (RegisterClassW(&wc) == 0)
		abort();

	r.left = 0;
	r.top = 0;
	r.right = 10 + 400 + 10;
	r.bottom = 10 + 20 + 5 + 20 + 5 + 20 + 10;
	if (AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, 0) == 0)
		abort();
	mainwin = CreateWindowExW(0,
		L"mainwin", L"Main Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		r.right - r.left, r.bottom - r.top,
		NULL, NULL, NULL, NULL);
	if (mainwin == NULL)
		abort();

	pbar = CreateWindowExW(0,
		PROGRESS_CLASSW, L"",
		PBS_SMOOTH | WS_CHILD | WS_VISIBLE,
		10, 10,
		400, 20,
		mainwin, NULL, NULL, NULL);
	if (pbar == NULL)
		abort();
	SendMessageW(pbar, PBM_SETRANGE32, 0, 100);
	SendMessageW(pbar, PBM_SETPOS, 0, 0);
	SendMessageW(pbar, PBM_SETSTATE, (WPARAM) PBST_NORMAL, 0);

	slider = CreateWindowExW(0,
		TRACKBAR_CLASSW, L"",
		TBS_HORZ | TBS_TOOLTIPS | TBS_TRANSPARENTBKGND | WS_TABSTOP | WS_CHILD | WS_VISIBLE,
		10, 10 + 20 + 5,
		400, 20,
		mainwin, NULL, NULL, NULL);
	if (slider == NULL)
		abort();
	SendMessageW(slider, TBM_SETRANGEMIN, (WPARAM) TRUE, 0);
	SendMessageW(slider, TBM_SETRANGEMAX, (WPARAM) TRUE, 100);
	SendMessageW(slider, TBM_SETPOS, (WPARAM) TRUE, 0);

	state = CreateWindowExW(0,
		WC_COMBOBOXEXW, L"",
		CBS_DROPDOWNLIST | WS_CHILD | WS_VISIBLE,
		10, 10 + 20 + 5 + 20 + 5,
		400, 20,
		mainwin, NULL, NULL, NULL);
	if (state == NULL)
		abort();
	addItem(L"Normal");
	addItem(L"Error");
	addItem(L"Paused");
	addItem(L"4 (PBFS_PARTIAL)");
	addItem(L"0 (PBFS_PARTIAL)");
	if (SendMessageW(state, CB_SETCURSEL, 0, 0) == (LRESULT) (CB_ERR))
		abort();

	ShowWindow(mainwin, SW_SHOWDEFAULT);
	UpdateWindow(mainwin);

	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}