UINT WINAPI SHAppBarMessage(DWORD dwMessage, PAPPBARDATA pabd)
{
    HWND hwndTray;
    COPYDATASTRUCT cds;
    TRAYAPPBARDATA tabd;
    BOOL fret;
    LPRECT lprc = NULL;

    hwndTray = FindWindow(c_szTrayClass, NULL);
    if (!hwndTray || (pabd->cbSize > SIZEOF(tabd.abd)))
    {
        return(FALSE);
    }

    tabd.abd = *pabd;
    tabd.dwMessage = dwMessage;
    tabd.hSharedRect = NULL;
    tabd.dwProcId = GetCurrentProcessId();

    cds.dwData = TCDM_APPBAR;
    cds.cbData = SIZEOF(tabd);
    cds.lpData = &tabd;

    switch (dwMessage) {
    case ABM_QUERYPOS:
    case ABM_SETPOS:
    case ABM_GETTASKBARPOS:
        tabd.hSharedRect = SHAllocShared(NULL, SIZEOF(RECT), tabd.dwProcId);
        if (tabd.hSharedRect == NULL)
            return FALSE;
        break;
    }

    fret = (SendMessage(hwndTray, WM_COPYDATA, (WPARAM)pabd->hWnd, (LPARAM)&cds));

    if (tabd.hSharedRect) {
        lprc = (LPRECT)SHLockShared(tabd.hSharedRect,tabd.dwProcId);
        if (lprc == NULL)
        {
            fret = FALSE;
        }
        else
        {
            pabd->rc = *lprc;
            SHUnlockShared(lprc);
        }
        SHFreeShared(tabd.hSharedRect,tabd.dwProcId);
    }
    return fret;
}