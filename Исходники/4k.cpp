bool
Initialize () {

    // no WinMain so get the module handle:
    g_hInstance = GetModuleHandle(NULL);
    if (g_hInstance == NULL)
        return false;

    // register the window class:
    WNDCLASS wc;

    wc.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = g_hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = WINDOW_TITLE;

    if (RegisterClass(&wc) == 0)
        return false;

    // create the window:
    g_hWnd = CreateWindow(
        WINDOW_TITLE,                                             // class name
        WINDOW_TITLE,                                             // title
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // style
        CW_USEDEFAULT, CW_USEDEFAULT,                             // position
        CW_USEDEFAULT, CW_USEDEFAULT,                             // size
        NULL,                                                     // no parent
        NULL,                                                     // no menu
        g_hInstance,                                              // instance
        NULL                                                      // no special
    );

    if (g_hWnd == NULL)
        return false;

    // setup double buffering:
    g_hDC = GetDC(g_hWnd);
    if (g_hDC == NULL)
        return false;

    g_hMemDC = CreateCompatibleDC(g_hDC);
    if (g_hMemDC == NULL)
        return false;

    g_hMemBMP = CreateCompatibleBitmap(g_hDC, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (g_hMemBMP == NULL)
        return false;

    SelectObject(g_hMemDC, g_hMemBMP);

    // colors used to draw the effect:
    g_hColor1 = CreateSolidBrush(RGB(184, 178, 251));
    g_hColor2 = CreateSolidBrush(RGB(98, 72, 124));

    if (g_hColor1 == NULL || g_hColor2 == NULL)
        return false;

    return true;
}