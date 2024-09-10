int main(int argc, char *argv[])
{
	D2D1_FACTORY_OPTIONS opts;
	WNDCLASSW wc;
	HWND mainwin;
	MSG msg;
	HRESULT hr;

	CoInitialize(NULL);
	ZeroMemory(&opts, sizeof (D2D1_FACTORY_OPTIONS));
	opts.debugLevel = D2D1_DEBUG_LEVEL_NONE;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
		IID_ID2D1Factory,
		&opts,
		(void **) (&d2dfactory));
	if (hr != S_OK) {
		loghr("D2D1CreateFactory()", hr);
		return 1;
	}

	ZeroMemory(&wc, sizeof (WNDCLASSW));
	wc.lpszClassName = L"mainwin";
	wc.lpfnWndProc = wndproc;
	wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
	RegisterClassW(&wc);

	mainwin = CreateWindowExW(0,
		L"mainwin", L"mainwin",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		640, 480,
		NULL, NULL, NULL, NULL);

	ShowWindow(mainwin, SW_SHOWDEFAULT);
	UpdateWindow(mainwin);

	while (GetMessageW(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	d2dfactory->Release();
	CoUninitialize();
	return msg.wParam;
}