int WINAPI
WinMain (
         _In_ HINSTANCE hInstance,
         _In_opt_ HINSTANCE hPrevInstance,
         _In_ PSTR szCmdLine,
         _In_ int iCmdShow)
/*++

Routine Description:

    Entry point for app. Registers class, creates window.

--*/
{
    CHAR        szAppClassName[] = "w1394_AppClass";
    CHAR        szTitleBar[] = "WDF 1394 Hybrid Test Application";
    MSG         Msg;
    WNDCLASSEX  WndClassEx;
    HWND        hWnd;

    UNREFERENCED_PARAMETER (hPrevInstance);
    UNREFERENCED_PARAMETER (szCmdLine);


    g_hInstance = hInstance;

    // main window app...
    WndClassEx.cbSize = sizeof(WNDCLASSEX);
    WndClassEx.style = CS_DBLCLKS | CS_BYTEALIGNWINDOW | CS_GLOBALCLASS;
    WndClassEx.lpfnWndProc = w1394_AppWndProc;
    WndClassEx.cbClsExtra = 0;
    WndClassEx.cbWndExtra = 0;
    WndClassEx.hInstance = g_hInstance;
    WndClassEx.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    WndClassEx.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    WndClassEx.hCursor = NULL;
    WndClassEx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    WndClassEx.lpszMenuName = "AppMenu";
    WndClassEx.lpszClassName = szAppClassName;

    RegisterClassEx( &WndClassEx );

    hWnd = CreateWindowEx ( 
        WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES,
        szAppClassName,
        szTitleBar,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        g_hInstance,
        NULL);

    ShowWindow(hWnd, iCmdShow);

    while (GetMessage(&Msg, NULL, 0, 0)) 
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    if (g_hTestDevice)
    {
        CloseHandle (g_hTestDevice);
    }

    return (int)(Msg.wParam);
} // WinMain