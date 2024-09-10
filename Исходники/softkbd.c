BOOL GetNearestMonitorSize(HWND hwndOwner, LPRECT lprc)
{
    if (GetSystemMetrics(SM_CMONITORS) == 1) {
        GetAllMonitorSize(lprc);
    }
    else {
        HMONITOR hmonitor = MonitorFromWindow(hwndOwner, MONITOR_DEFAULTTONEAREST);
        MONITORINFO mInfo = {
            sizeof(MONITORINFO),
        };

        if (hmonitor == NULL) {
            return FALSE;
        }
        GetMonitorInfoW(hmonitor, &mInfo);
        *lprc = mInfo.rcWork;
    }
    return TRUE;
}