BOOL CALLBACK VBoxEnumFunc(HWND hwnd, LPARAM lParam)
{
    PVBOX_ENUM_PARAM    lpParam = (PVBOX_ENUM_PARAM)lParam;
    DWORD               dwStyle, dwExStyle;
    RECT                rectWindow, rectVisible;

    dwStyle   = GetWindowLong(hwnd, GWL_STYLE);
    dwExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    if (   !(dwStyle & WS_VISIBLE)
        ||  (dwStyle & WS_CHILD))
        return TRUE;

    Log(("VBoxTray: VBoxEnumFunc %x\n", hwnd));
    /* Only visible windows that are present on the desktop are interesting here */
    if (GetWindowRect(hwnd, &rectWindow))
    {
        char szWindowText[256];
        szWindowText[0] = 0;
        OSVERSIONINFO OSinfo;
        HWND hStart = NULL;
        GetWindowText(hwnd, szWindowText, sizeof(szWindowText));
        OSinfo.dwOSVersionInfoSize = sizeof (OSinfo);
        GetVersionEx (&OSinfo);
        if (OSinfo.dwMajorVersion >= 6)
        {
            hStart = ::FindWindowEx(GetDesktopWindow(), NULL, "Button", "Start");
            if (  hwnd == hStart && szWindowText != NULL
                && !(strcmp(szWindowText, "Start"))
               )
            {
                /* for vista and above. To solve the issue of small bar above
                 * the Start button when mouse is hovered over the start button in seamless mode.
                 * Difference of 7 is observed in Win 7 platform between the dimensionsof rectangle with Start title and its shadow.
                 */
                rectWindow.top += 7;
                rectWindow.bottom -=7;
            }
        }
        rectVisible = rectWindow;

#ifdef LOG_ENABLED
        DWORD pid = 0;
        DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
#endif

        /* Filter out Windows XP shadow windows */
        /** @todo still shows inside the guest */
        if (   szWindowText[0] == 0
            && (
                    (dwStyle == (WS_POPUP|WS_VISIBLE|WS_CLIPSIBLINGS)
                            && dwExStyle == (WS_EX_LAYERED|WS_EX_TOOLWINDOW|WS_EX_TRANSPARENT|WS_EX_TOPMOST))
                 || (dwStyle == (WS_POPUP|WS_VISIBLE|WS_DISABLED|WS_CLIPSIBLINGS|WS_CLIPCHILDREN)
                            && dwExStyle == (WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_NOACTIVATE))
                 || (dwStyle == (WS_POPUP|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN)
                                       && dwExStyle == (WS_EX_TOOLWINDOW))
                            ))
        {
            Log(("VBoxTray: Filter out shadow window style=%x exstyle=%x\n", dwStyle, dwExStyle));
            Log(("VBoxTray: Enum hwnd=%x rect (%d,%d) (%d,%d) (filtered)\n", hwnd, rectWindow.left, rectWindow.top, rectWindow.right, rectWindow.bottom));
            Log(("VBoxTray: title=%s style=%x exStyle=%x\n", szWindowText, dwStyle, dwExStyle));
            Log(("VBoxTray: pid=%d tid=%d\n", pid, tid));
            return TRUE;
        }

        /** @todo will this suffice? The Program Manager window covers the whole screen */
        if (strcmp(szWindowText, "Program Manager"))
        {
            Log(("VBoxTray: Enum hwnd=%x rect (%d,%d) (%d,%d) (applying)\n", hwnd, rectWindow.left, rectWindow.top, rectWindow.right, rectWindow.bottom));
            Log(("VBoxTray: title=%s style=%x exStyle=%x\n", szWindowText, dwStyle, dwExStyle));
            Log(("VBoxTray: pid=%d tid=%d\n", pid, tid));

            HRGN hrgn = CreateRectRgn(0,0,0,0);

            int ret = GetWindowRgn(hwnd, hrgn);

            if (ret == ERROR)
            {
                Log(("VBoxTray: GetWindowRgn failed with rc=%d\n", GetLastError()));
                SetRectRgn(hrgn, rectVisible.left, rectVisible.top, rectVisible.right, rectVisible.bottom);
            }
            else
            {
                /* this region is relative to the window origin instead of the desktop origin */
                OffsetRgn(hrgn, rectWindow.left, rectWindow.top);
            }
            if (lpParam->hrgn)
            {
                /* create a union of the current visible region and the visible rectangle of this window. */
                CombineRgn(lpParam->hrgn, lpParam->hrgn, hrgn, RGN_OR);
                DeleteObject(hrgn);
            }
            else
                lpParam->hrgn = hrgn;
        }
        else
        {
            Log(("VBoxTray: Enum hwnd=%x rect (%d,%d) (%d,%d) (ignored)\n", hwnd, rectWindow.left, rectWindow.top, rectWindow.right, rectWindow.bottom));
            Log(("VBoxTray: title=%s style=%x\n", szWindowText, dwStyle));
            Log(("VBoxTray: pid=%d tid=%d\n", pid, tid));
        }
    }
    return TRUE; /* continue enumeration */
}