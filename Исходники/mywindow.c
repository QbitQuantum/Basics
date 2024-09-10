DWORD WINAPI MyWndThread(LPVOID lpParameter)
{
    MSG msg;
    HANDLE hMemory;
    PWNDCLASS pWndClass;
    BOOL bSuccess;
    CHAR lpBuffer[128];
    HANDLE myEvent = *((HANDLE *)lpParameter);
    RECT windowRect;

    hMemory = LocalAlloc(LPTR, sizeof(WNDCLASS));
    if(!hMemory){
	return(FALSE);
    }

    pWndClass = (PWNDCLASS) LocalLock(hMemory);
    pWndClass->hCursor = LoadCursor(NULL, IDC_ARROW);
    pWndClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    pWndClass->lpszMenuName = NULL;
    pWndClass->lpszClassName = (LPSTR) "ECE291Render";
    pWndClass->hbrBackground = NULL;//GetStockObject(WHITE_BRUSH);
    pWndClass->hInstance = GetInstance();
    pWndClass->style = 0;
    pWndClass->lpfnWndProc = (WNDPROC)MyWndProc;

    bSuccess = RegisterClass(pWndClass);

    LocalUnlock(hMemory);
    LocalFree(hMemory);

    if(*WindowedMode) {
	RECT windowRect;
	windowRect.left = 100; windowRect.top = 100;
	windowRect.right = 100 + windowWidth - 1;
	windowRect.bottom = 100 + windowHeight - 1;
	AdjustWindowRect(&windowRect, WS_OVERLAPPED | WS_CAPTION, FALSE);

	hWnd = CreateWindowEx(0,
	    "ECE291Render",
	    "ECE 291 Graphics Driver Display",
	    WS_OVERLAPPED | WS_CAPTION,
	    CW_USEDEFAULT,
	    CW_USEDEFAULT,
	    windowRect.right - windowRect.left,//CW_USEDEFAULT,
	    windowRect.bottom - windowRect.top,//CW_USEDEFAULT,
	    NULL,
	    NULL,
	    GetInstance(),
	    NULL);
    } else {
	hWnd = CreateWindowEx(0,
	    "ECE291Render",
	    "ECE 291 Graphics Driver Display",
	    //WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
	    WS_POPUP,
	    0,//CW_USEDEFAULT,
	    0,//CW_USEDEFAULT,
	    windowWidth,//CW_USEDEFAULT,
	    windowHeight,//CW_USEDEFAULT,
	    NULL,
	    NULL,
	    GetInstance(),
	    NULL);
    }

    if (!hWnd)
	return FALSE;

    ShowWindow(hWnd, SW_SHOW);
    SetForegroundWindow(hWnd);
    UpdateWindow(hWnd);

    SetEvent(myEvent);

    for(;;) {
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
	    TranslateMessage(&msg);
	    DispatchMessage(&msg);
	    if (msg.message == WM_CLOSE)
		break;
	}
    }

    DestroyWindow(hWnd);
    UnregisterClass("ECE291Render", GetInstance());

    SetEvent(myEvent);

    ExitThread(0);
}