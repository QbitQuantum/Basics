static BOOL init_procs(void)
{
    WNDCLASSA cls;
    HANDLE user32 = GetModuleHandleA("user32.dll");
    pBroadcastA = (PBROADCAST)GetProcAddress(user32, "BroadcastSystemMessageA");
    if (!pBroadcastA)
        pBroadcastA = (PBROADCAST)GetProcAddress(user32, "BroadcastSystemMessage");
    ok(pBroadcastA != NULL, "No BroadcastSystemMessage found\n");
    if (!pBroadcastA)
    {
        win_skip("BroadcastA is not available\n");
        return FALSE;
    }

    pBroadcastW = (PBROADCAST)GetProcAddress(user32, "BroadcastSystemMessageW");
    pBroadcastExA = (PBROADCASTEX)GetProcAddress(user32, "BroadcastSystemMessageExA");
    pBroadcastExW = (PBROADCASTEX)GetProcAddress(user32, "BroadcastSystemMessageExW");

    hevent = CreateEventA(NULL, TRUE, FALSE, "Asynchronous checking event");

    cls.style = CS_DBLCLKS;
    cls.lpfnWndProc = main_window_procA;
    cls.cbClsExtra = 0;
    cls.cbWndExtra = 0;
    cls.hInstance = GetModuleHandleA(0);
    cls.hIcon = 0;
    cls.hCursor = LoadCursorA(0, (LPCSTR)IDC_ARROW);
    cls.hbrBackground = GetStockObject(WHITE_BRUSH);
    cls.lpszMenuName = NULL;
    cls.lpszClassName = "MainWindowClass";

    if (!RegisterClassA(&cls))
        return FALSE;

    if (!CreateWindowExA(0, "MainWindowClass", "Main window", WS_CAPTION | WS_SYSMENU |
                               WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_POPUP, 100, 100, 200,
                               200, 0, 0, GetModuleHandleA(NULL), NULL))
        return FALSE;
    return TRUE;
}