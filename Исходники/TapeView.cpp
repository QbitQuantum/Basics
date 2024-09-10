void CreateTapeView(HWND hwndParent, int x, int y, int width, int height)
{
    ASSERT(hwndParent != NULL);

    g_hwndTape = CreateWindow(
            CLASSNAME_TOOLWINDOW, NULL,
            WS_CHILD | WS_VISIBLE,
            x, y, width, height,
            hwndParent, NULL, g_hInst, NULL);
    SetWindowText(g_hwndTape, _T("Tape"));

    // ToolWindow subclassing
    m_wndprocTapeToolWindow = (WNDPROC) LongToPtr( SetWindowLongPtr(
            g_hwndTape, GWLP_WNDPROC, PtrToLong(TapeViewWndProc)) );

    RECT rcClient;  GetClientRect(g_hwndTape, &rcClient);

    m_hwndTapeFile = CreateWindow(
            _T("STATIC"), NULL,
            WS_CHILD | WS_VISIBLE | SS_PATHELLIPSIS,
            8, 4, 500, 18,
            g_hwndTape, NULL, g_hInst, NULL);
    m_hwndTapeCurrent = CreateWindow(
            _T("STATIC"), NULL,
            WS_CHILD | WS_VISIBLE,
            8, 62, 100, 18,
            g_hwndTape, NULL, g_hInst, NULL);
    m_hwndTapeTotal = CreateWindow(
            _T("STATIC"), NULL,
            WS_CHILD | WS_VISIBLE | SS_RIGHT,
            500 + 8 + 4, 4, rcClient.right - 8 * 2 - 500 - 4, 18,
            g_hwndTape, NULL, g_hInst, NULL);
    m_hwndTapeGraph = CreateWindow(
            _T("STATIC"), NULL,
            WS_CHILD | WS_VISIBLE | SS_OWNERDRAW,
            8, 22, TAPE_BUFFER_SIZE, 32,
            g_hwndTape, NULL, g_hInst, NULL);
    m_hwndTapePlay = CreateWindow(
            _T("BUTTON"), _T("Play"),
            WS_CHILD | WS_VISIBLE | WS_DISABLED,
            8 + 100 + 16, 60, 96, 22,
            g_hwndTape, NULL, g_hInst, NULL);
    m_hwndTapeRewind = CreateWindow(
            _T("BUTTON"), _T("<< Rewind"),
            WS_CHILD | WS_VISIBLE | WS_DISABLED,
            8 + 100 + 16 + 4 + 96, 60, 96, 22,
            g_hwndTape, NULL, g_hInst, NULL);
    m_hwndTapeOpen = CreateWindow(
            _T("BUTTON"), _T("Open WAV"),
            WS_CHILD | WS_VISIBLE,
            rcClient.right - 96 - 4 - 96 - 8, 60, 96, 22,
            g_hwndTape, NULL, g_hInst, NULL);
    m_hwndTapeSave = CreateWindow(
            _T("BUTTON"), _T("Save WAV"),
            WS_CHILD | WS_VISIBLE,
            rcClient.right - 96 - 8, 60, 96, 22,
            g_hwndTape, NULL, g_hInst, NULL);

    m_hfontTape = CreateDialogFont();
    SendMessage(m_hwndTapeCurrent, WM_SETFONT, (WPARAM) m_hfontTape, 0);
    SendMessage(m_hwndTapeTotal, WM_SETFONT, (WPARAM) m_hfontTape, 0);
    SendMessage(m_hwndTapeFile, WM_SETFONT, (WPARAM) m_hfontTape, 0);
    SendMessage(m_hwndTapePlay, WM_SETFONT, (WPARAM) m_hfontTape, 0);
    SendMessage(m_hwndTapeRewind, WM_SETFONT, (WPARAM) m_hfontTape, 0);
    SendMessage(m_hwndTapeOpen, WM_SETFONT, (WPARAM) m_hfontTape, 0);
    SendMessage(m_hwndTapeSave, WM_SETFONT, (WPARAM) m_hfontTape, 0);

    TapeView_ClearGraph();
}