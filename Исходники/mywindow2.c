DWORD WINAPI MyWndThread2(LPVOID lpParameter)
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
    pWndClass->lpszClassName = (LPSTR) "ECE291Socket";
    pWndClass->hbrBackground = NULL;//GetStockObject(WHITE_BRUSH);
    pWndClass->hInstance = GetInstance();
    pWndClass->style = 0;
    pWndClass->lpfnWndProc = (WNDPROC)MyWndProc2;

    bSuccess = RegisterClass(pWndClass);

    LocalUnlock(hMemory);
    LocalFree(hMemory);

    hWnd = CreateWindowEx(0,
	"ECE291Socket",
	"ECE 291 Sockets Handler",
	WS_ICONIC,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	CW_USEDEFAULT,
	NULL,
	NULL,
	GetInstance(),
	NULL);

    if (!hWnd)
	return FALSE;

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
    UnregisterClass("ECE291Socket", GetInstance());

    SetEvent(myEvent);

    ExitThread(0);
}