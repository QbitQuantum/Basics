bool GetScreenSelection(HINSTANCE hInstance, RECT *rcSelection, HWND target)
{
	char* szClassName = "SelectionClass";
	DWORD style = WS_POPUP | WS_EX_TOPMOST;// | WS_VISIBLE;
	DWORD styleEx = WS_EX_TOOLWINDOW;
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = hInstance;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursor(NULL, IDC_CROSS);
	wcex.lpfnWndProc = SelectionProc;
	wcex.lpszClassName = szClassName;

	SelectionState state = { 0 };
	state.Result = FALSE;

	HDC hDeviceContext = GetDC(target);
	if (!GetClientRect(target, &state.Window.Rect))
	{
		goto cleanup;
	}

	state.Window.hBitmap = CreateCompatibleBitmap(hDeviceContext, state.Window.Rect.right, state.Window.Rect.bottom);
	if (!state.Window.hBitmap)
		goto cleanup;
	state.Window.hDeviceContext = CreateCompatibleDC(hDeviceContext);
	if (!state.Window.hDeviceContext)
		goto cleanup;

	state.Selection.hBitmap = CreateCompatibleBitmap(hDeviceContext, state.Window.Rect.right, state.Window.Rect.bottom);
	if (!state.Selection.hBitmap)
		goto cleanup;

	state.Selection.hDeviceContext = CreateCompatibleDC(hDeviceContext);
	if (!state.Selection.hDeviceContext)
		goto cleanup;

	SelectObject(state.Window.hDeviceContext, state.Window.hBitmap);
	SelectObject(state.Selection.hDeviceContext, state.Selection.hBitmap);

	BitBlt(state.Window.hDeviceContext,
		0, 0, state.Window.Rect.right, state.Window.Rect.bottom,
		hDeviceContext,
		state.Window.Rect.left, state.Window.Rect.top,
		SRCCOPY);

	ReleaseDC(NULL, hDeviceContext);
	hDeviceContext = NULL;

	HWND hWndSelect = Win32CreateWindow(hInstance, wcex, styleEx, style, "Selection Window",
		state.Window.Rect.right, state.Window.Rect.bottom, state.Window.Rect.left, state.Window.Rect.top, HWND_DESKTOP, &state);

	if (!hWndSelect)
	{
		goto cleanup;
	}

	SetForegroundWindow(target);
	SetForegroundWindow(hWndSelect);

	ShowWindow(hWndSelect, SW_SHOW);
	UpdateWindow(hWndSelect);

	MSG msg;
	state.Wait = TRUE;
	while (state.Wait)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			PostQuitMessage(msg.wParam);
		}
	}

	if (state.Result)
	{
		CopyRect(rcSelection, &state.Selection.Rect);
	}

cleanup:
	if (hDeviceContext)
		ReleaseDC(NULL, hDeviceContext);

	CleanUp(state.Window);
	CleanUp(state.Selection);

	return state.Result;
};