static HWND CreateTestWindow()
{
    MSG msg;
    WNDCLASSA  wclass;
    HANDLE hInstance = GetModuleHandleA( NULL );
    HWND hWndTest;

    wclass.lpszClassName = "MouseInputTestClass";
    wclass.style         = CS_HREDRAW | CS_VREDRAW;
    wclass.lpfnWndProc   = WndProc;
    wclass.hInstance     = hInstance;
    wclass.hIcon         = LoadIconA( 0, IDI_APPLICATION );
    wclass.hCursor       = LoadCursorA( NULL, IDC_ARROW );
    wclass.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );
    wclass.lpszMenuName = 0;
    wclass.cbClsExtra    = 0;
    wclass.cbWndExtra    = 0;
    RegisterClassA( &wclass );
    /* create the test window that will receive the keystrokes */
    hWndTest = CreateWindowA( wclass.lpszClassName, "MouseInputTestTest",
                              WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 100, 100,
                              NULL, NULL, hInstance, NULL);
    assert( hWndTest );
    ShowWindow( hWndTest, SW_SHOWMAXIMIZED);
    SetWindowPos( hWndTest, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE );
    SetForegroundWindow( hWndTest );
    UpdateWindow( hWndTest);
    SetFocus(hWndTest);

    /* flush pending messages */
    while (PeekMessage( &msg, 0, 0, 0, PM_REMOVE )) DispatchMessageA( &msg );

    return hWndTest;
}