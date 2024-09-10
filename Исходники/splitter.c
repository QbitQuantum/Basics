/* Create vertical splitter bar */
BOOL
CreateVSplitBar(HWND hwnd)
{
    WCHAR szWindowClass[] = L"VSplitterWindowClass";
    WNDCLASSEXW WndClass = {0};

    WndClass.cbSize        = sizeof(WNDCLASSEXW);
    WndClass.lpszClassName = szWindowClass;
    WndClass.lpfnWndProc   = VSplitterWindowProc;
    WndClass.hInstance     = hInst;
    WndClass.style         = CS_HREDRAW | CS_VREDRAW;
    WndClass.hCursor       = LoadCursor(0, IDC_SIZEWE);
    WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

    if (RegisterClassExW(&WndClass) == (ATOM) 0)
    {
        /* TODO: Show error message */
        return FALSE;
    }

    hVSplitter = CreateWindowExW(WS_EX_TRANSPARENT,
                                 szWindowClass,
                                 NULL,
                                 WS_CHILD | WS_VISIBLE,
                                 201, 28, SPLIT_WIDTH, 350,
                                 hwnd,
                                 NULL,
                                 hInst,
                                 NULL);


    if (!hVSplitter)
    {
        /* TODO: Show error message */
        return FALSE;
    }

    ShowWindow(hVSplitter, SW_SHOW);
    UpdateWindow(hVSplitter);

    return TRUE;
}