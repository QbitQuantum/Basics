BOOL CALLBACK EnumFindProcessWnd(HWND hwnd, LPARAM lParam)
{
    DWORD procid = 0;
    TCHAR WindowClass [40];
    GetWindowThreadProcessId(hwnd, &procid);
    GetClassName(hwnd, WindowClass, countof(WindowClass));

    if (procid == GetCurrentProcessId() &&
            (_tcscmp(WindowClass, _l("MediaPlayerClassicW")) == 0 || // MPC-HC window
             _tcscmp(WindowClass, _l("WMPlayerApp")) == 0 || // WMPlayer window
             _tcscmp(WindowClass, _l("eHome Render Window")) == 0 // WMC window
            )
       ) {
        HWND* pWnd = (HWND*) lParam;
        *pWnd = hwnd;
        return FALSE;
    }
    return TRUE;
}