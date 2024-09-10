// Get the desktop dimensions - for the monitor containing most of the active window
//-----------------------------------------------------------------------------
void CPUTWindowWin::GetDesktopDimensions(int *pX, int *pY, int *pWidth, int *pHeight)
{
    RECT windowRect;
    GetWindowRect(mhWnd, &windowRect);
    HMONITOR hMonitor = MonitorFromRect(&windowRect, MONITOR_DEFAULTTONEAREST);
    MONITORINFO monitorInfo;
    monitorInfo.cbSize = sizeof(monitorInfo);
    GetMonitorInfo(hMonitor, &monitorInfo);

    *pX      = monitorInfo.rcMonitor.left;
    *pY      = monitorInfo.rcMonitor.top;
    *pWidth  = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
    *pHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;
}