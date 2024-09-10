void initializeMainThreadPlatform()
{
    if (threadingWindowHandle)
        return;

    HWND hWndParent = 0;
    WNDCLASSW wcex;
    memset(&wcex, 0, sizeof(WNDCLASSW));
    wcex.lpfnWndProc    = ThreadingWindowWndProc;
    wcex.lpszClassName  = kThreadingWindowClassName;
    RegisterClassW(&wcex);
#if !OS(WINCE)
    hWndParent = HWND_MESSAGE;
#endif

    threadingWindowHandle = CreateWindowW(kThreadingWindowClassName, 0, 0,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hWndParent, 0, 0, 0);
    threadingFiredMessage = RegisterWindowMessageW(L"com.apple.WebKit.MainThreadFired");

    initializeCurrentThreadInternal("Main Thread");
}