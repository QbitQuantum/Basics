DWORD FWindowsNativeFeedbackContext::SlowTaskThreadProc(void* ThreadParam)
{
	FWindowsNativeFeedbackContext* Context = (FWindowsNativeFeedbackContext*)ThreadParam;

	HINSTANCE HInstance = (HINSTANCE)GetModuleHandle(NULL);

	WNDCLASSEX WndClassEx;
	ZeroMemory(&WndClassEx, sizeof(WndClassEx));
	WndClassEx.cbSize = sizeof(WndClassEx);
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW | (Context->bShowCancelButton? 0 : CS_NOCLOSE);
	WndClassEx.lpfnWndProc = &SlowTaskWindowProc;
	WndClassEx.hIcon = LoadIcon(HInstance, MAKEINTRESOURCE(FWindowsPlatformMisc::GetAppIcon()));
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.hInstance = HInstance;
	WndClassEx.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	WndClassEx.lpszClassName = TEXT("FFeedbackContextWindows");
	ATOM WndClassAtom = RegisterClassEx(&WndClassEx);

	NONCLIENTMETRICS NonClientMetrics;
	NonClientMetrics.cbSize = sizeof(NonClientMetrics);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NonClientMetrics), &NonClientMetrics, 0);
	HANDLE hFont = CreateFontIndirect(&NonClientMetrics.lfMessageFont);

	int FontHeight = -MulDiv(8, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72);
	HANDLE hLogFont = CreateFont(FontHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH | FF_MODERN, TEXT("Courier New"));

	TEXTMETRIC TextMetric;
	HDC hDC = CreateCompatibleDC(NULL);
	HGDIOBJ hPrevObj = SelectObject(hDC, hFont);
	GetTextMetrics(hDC, &TextMetric);
	SelectObject(hDC, hPrevObj);
	DeleteDC(hDC);

	FWindowParams Params;
	Params.Context = Context;
	Params.ScaleX = TextMetric.tmAveCharWidth;
	Params.ScaleY = TextMetric.tmHeight;
	Params.StandardW = Params.ScaleX * 80;
	Params.StandardH = Params.ScaleY * 4;
	Params.bLogVisible = false;

	DWORD WindowStyle = WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;

	RECT WindowRect;
	ZeroMemory(&WindowRect, sizeof(WindowRect));
	WindowRect.left = (GetSystemMetrics(SM_CXSCREEN) - Params.StandardW) / 2;
	WindowRect.top = (GetSystemMetrics(SM_CYSCREEN) - Params.StandardH) / 2;
	WindowRect.right = WindowRect.left + Params.StandardW;
	WindowRect.bottom = WindowRect.top + Params.StandardH;
	AdjustWindowRectEx(&WindowRect, WindowStyle, 0, 0);

	const TCHAR* WindowClassName = MAKEINTATOM( WndClassAtom );
	HWND hWnd = CreateWindow(WindowClassName, TEXT("Unreal Engine"), WindowStyle, WindowRect.left, WindowRect.top, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, NULL, NULL, HInstance, NULL);
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&Params);
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, 0);

	HWND hWndOpenLog = CreateWindow(WC_BUTTON, TEXT("Show log"), BS_CENTER | BS_VCENTER | BS_PUSHBUTTON | BS_TEXT | WS_CHILD | WS_VISIBLE, 10, 10, 10, 10, hWnd, (HMENU)ShowLogCtlId, HInstance, NULL);
	SendMessage(hWndOpenLog, WM_SETFONT, (WPARAM)hFont, 0);

	HWND hWndStatus = CreateWindow(WC_STATIC, TEXT(""), SS_CENTER | WS_CHILD | WS_VISIBLE, 10, 10, 10, 10, hWnd, (HMENU)StatusCtlId, HInstance, NULL);
	SendMessage(hWndStatus, WM_SETFONT, (WPARAM)hFont, 0);

	HWND hWndProgress = CreateWindowEx(0, PROGRESS_CLASS, TEXT(""), WS_CHILD | WS_VISIBLE, 10, 10, 10, 10, hWnd, (HMENU)ProgressCtlId, HInstance, NULL);
	SendMessage(hWndProgress, PBM_SETRANGE32, 0, 1000);

	HWND hWndLogOutput = CreateWindowEx(WS_EX_STATICEDGE, WC_EDIT, TEXT(""), ES_MULTILINE | ES_READONLY | WS_HSCROLL | WS_VSCROLL | WS_CHILD | WS_VISIBLE, 10, 10, 10, 10, hWnd, (HMENU)LogOutputCtlId, HInstance, NULL);
	SendMessage(hWndLogOutput, WM_SETFONT, (WPARAM)hLogFont, 0);

	LayoutControls(hWnd, &Params);
	SetEvent(Context->hUpdateEvent);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	SetForegroundWindow(hWnd);

	FString PrevStatus;
	float PrevProgress = 0.0f;
	int32 PrevLogOutputLength = 0;
	for(;;)
	{
		HANDLE Handles[] = { Context->hCloseEvent, Context->hUpdateEvent };
		DWORD Result = MsgWaitForMultipleObjects(2, Handles, 0, INFINITE, QS_ALLEVENTS);
		if(Result == WAIT_OBJECT_0)
		{
			break;
		}
		else if(Result == WAIT_OBJECT_0 + 1)
		{
			FScopeLock Lock(&Context->CriticalSection);
			if(Context->Status != PrevStatus)
			{
				SetWindowText(hWndStatus, *Context->Status);
				PrevStatus = Context->Status;
			}
			if(Context->Progress != PrevProgress)
			{
				SendMessage(hWndProgress, PBM_SETPOS, (int32)(Context->Progress * 1000.0f), 0);
				PrevProgress = Context->Progress;
			}
			if(Context->LogOutput.Len() > PrevLogOutputLength)
			{
				SendMessage(hWndLogOutput, EM_SETSEL, PrevLogOutputLength, PrevLogOutputLength);
				SendMessage(hWndLogOutput, EM_REPLACESEL, FALSE, (LPARAM)(*Context->LogOutput + PrevLogOutputLength));
				SendMessage(hWndLogOutput, EM_SCROLLCARET, 0, 0);
				PrevLogOutputLength = Context->LogOutput.Len();
			}
		}

		MSG Msg;
		while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}

	DestroyWindow(hWnd);
	DeleteObject(hLogFont);
	DeleteObject(hFont);
	UnregisterClass(WindowClassName, HInstance);

	return 0;
}