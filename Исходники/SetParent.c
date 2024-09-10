static
LRESULT
CALLBACK
WndProc(
    _In_ HWND hWnd,
    _In_ UINT message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
    HWND hTest;
    int iwnd = get_iwnd(hWnd, TRUE);

    ok(GetCurrentThreadId() == dwThreadId, "Thread 0x%lx instead of 0x%lx\n", GetCurrentThreadId(), dwThreadId);
    if (message > WM_USER || IsDWmMsg(message) || IseKeyMsg(message))
        return DefWindowProcW(hWnd, message, wParam, lParam);

    RECORD_MESSAGE(iwnd, message, SENT, wParam, lParam);

    switch(message)
    {
    case WM_DESTROY:
        if (GetParent(hWnd))
        {
            /* child window */
            ok(EnumThreadWindows(dwThreadId, EnumProc, (LPARAM)hWnd), "Child window %p (%d) enumerated\n", hWnd, iwnd);
            ok(!EnumChildWindows(GetParent(hWnd), EnumProc, (LPARAM)hWnd), "Child window %p (%d) not enumerated\n", hWnd, iwnd);
            ok(!EnumThreadWindows(dwThreadId, EnumProc, (LPARAM)GetParent(hWnd)), "Parent window of %p (%d) not enumerated\n", hWnd, iwnd);
        }
        else
        {
            /* top-level window */
            ok(!EnumThreadWindows(dwThreadId, EnumProc, (LPARAM)hWnd), "Window %p (%d) not enumerated in WM_DESTROY\n", hWnd, iwnd);
        }
        if (hWnd == hWndList[3])
        {
            hTest = SetParent(hWndList[4], hWndList[2]);
            ok_hwnd(hTest, hWndList[1]);
            hTest = SetParent(hWndList[5], hWndList[1]);
            ok_hwnd(hTest, hWndList[2]);

            ok_hwnd(GetParent(hWndList[1]), NULL);
            ok_hwnd(GetParent(hWndList[2]), NULL);
            ok_hwnd(GetParent(hWndList[3]), hWndList[1]);
            ok_hwnd(GetParent(hWndList[4]), hWndList[2]);
            ok_hwnd(GetParent(hWndList[5]), hWndList[1]);
        }
        break;
    }

    return DefWindowProcW(hWnd, message, wParam, lParam);
}