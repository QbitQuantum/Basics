	unsigned int run()
	{
		MSG msg;
		WNDCLASSA wc;
		HWND hwnd;

		wc.lpszClassName = DUMMY_WINDOW_CLASS;
		wc.lpfnWndProc = DummyWndProc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hInstance = g.hInstance;
		wc.hIcon = NULL;
		wc.hCursor = NULL;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszMenuName = NULL;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;

		if(!RegisterClassA(&wc))
			return -1;

		hwnd = CreateWindowExA(0, DUMMY_WINDOW_CLASS, DUMMY_WINDOW_CLASS, 0,
			0, 0, 32, 32, NULL, NULL, g.hInstance, NULL);

		if(!hwnd)
		{
			UnregisterClassA(DUMMY_WINDOW_CLASS, g.hInstance);
			return -2;
		}

		g.hwndDummy = hwnd;

		while(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g.hwndDummy = NULL;

		UnregisterClassA(DUMMY_WINDOW_CLASS, g.hInstance);

		return 0;
	}