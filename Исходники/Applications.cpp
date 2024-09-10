BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
    HICON   hIcon;
    WCHAR   szText[260];
    BOOL    bHung = FALSE;
    HICON*  xhIcon = (HICON*)&hIcon;

    typedef int (FAR __stdcall *IsHungAppWindowProc)(HWND);
    IsHungAppWindowProc IsHungAppWindow;

    /* Skip our window */
    if (hWnd == CurrenthWnd)
        return TRUE;

    GetWindowTextW(hWnd, szText, 260); /* Get the window text */

    /* Check and see if this is a top-level app window */
    if ((wcslen(szText) <= 0) ||
            !IsWindowVisible(hWnd) ||
            (GetParent(hWnd) != NULL) ||
            (GetWindow(hWnd, GW_OWNER) != NULL) ||
            (GetWindowLongPtrW(hWnd, GWL_EXSTYLE) & WS_EX_TOOLWINDOW))
    {
        return TRUE; /* Skip this window */
    }

    /* Get the icon for this window */
    hIcon = NULL;
    SendMessageTimeoutW(hWnd, WM_GETICON, ICON_SMALL, 0, 0, 1000, (PDWORD_PTR)xhIcon);

    if (!hIcon)
    {
        hIcon = (HICON)(LONG_PTR)GetClassLongPtrW(hWnd, GCL_HICONSM);
        if (!hIcon) hIcon = (HICON)(LONG_PTR)GetClassLongPtrW(hWnd, GCL_HICON);
        if (!hIcon) SendMessageTimeoutW(hWnd, WM_QUERYDRAGICON, 0, 0, 0, 1000, (PDWORD_PTR)xhIcon);
    }

    if (!hIcon)
        hIcon = LoadIconW(NULL, MAKEINTRESOURCEW(IDI_APPLICATION));

    bHung = FALSE;

    IsHungAppWindow = (IsHungAppWindowProc)(FARPROC)GetProcAddress(GetModuleHandleW(L"USER32.DLL"), "IsHungAppWindow");

    if (IsHungAppWindow)
        bHung = IsHungAppWindow(hWnd);

    AddOrUpdateHwnd(hWnd, szText, hIcon, bHung);

    return TRUE;
}