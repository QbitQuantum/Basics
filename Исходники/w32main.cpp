void DoMessageBox(char *str, int rows, int cols, BOOL error)
{
    EnableWindow(GraphicsWnd, FALSE);
    EnableWindow(TextWnd, FALSE);
    HWND h = GetForegroundWindow();

    // Register the window class for our dialog.
    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(wc);
    wc.style            = CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW | CS_OWNDC;
    wc.lpfnWndProc      = (WNDPROC)MessageProc;
    wc.hInstance        = Instance;
    wc.hbrBackground    = (HBRUSH)COLOR_BTNSHADOW;
    wc.lpszClassName    = "MessageWnd";
    wc.lpszMenuName     = NULL;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = (HICON)LoadImage(Instance, MAKEINTRESOURCE(4000),
                            IMAGE_ICON, 32, 32, 0);
    wc.hIconSm          = (HICON)LoadImage(Instance, MAKEINTRESOURCE(4000),
                            IMAGE_ICON, 16, 16, 0);
    RegisterClassEx(&wc);

    // Create the window.
    MessageString = str;
    RECT r;
    GetWindowRect(GraphicsWnd, &r);
    char *title = error ? "SolveSpace - Error" : "SolveSpace - Message";
    int width  = cols*SS.TW.CHAR_WIDTH + 20,
        height = rows*SS.TW.LINE_HEIGHT + 60;
    MessageWnd = CreateWindowClient(0, "MessageWnd", title,
        WS_OVERLAPPED | WS_SYSMENU,
        r.left + 100, r.top + 100, width, height, NULL, NULL, Instance, NULL);

    OkButton = CreateWindowEx(0, WC_BUTTON, "OK",
        WS_CHILD | WS_TABSTOP | WS_CLIPSIBLINGS | WS_VISIBLE | BS_DEFPUSHBUTTON,
        (width - 70)/2, rows*SS.TW.LINE_HEIGHT + 20,
        70, 25, MessageWnd, NULL, Instance, NULL); 
    SendMessage(OkButton, WM_SETFONT, (WPARAM)FixedFont, TRUE);

    ShowWindow(MessageWnd, TRUE);
    SetFocus(OkButton);

    MSG msg;
    DWORD ret;
    MessageDone = FALSE;
    while((ret = GetMessage(&msg, NULL, 0, 0)) && !MessageDone) {
        if((msg.message == WM_KEYDOWN &&
               (msg.wParam == VK_RETURN ||
                msg.wParam == VK_ESCAPE)) ||
            (msg.message == WM_KEYUP &&
               (msg.wParam == VK_SPACE)))
        {
            MessageDone = TRUE;
            break;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    MessageString = NULL;
    EnableWindow(TextWnd, TRUE);
    EnableWindow(GraphicsWnd, TRUE);
    SetForegroundWindow(GraphicsWnd);
    DestroyWindow(MessageWnd);
}