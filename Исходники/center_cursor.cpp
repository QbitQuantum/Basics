int _tmain(int argc, _TCHAR* argv[])
{
    const POINT ptZero = { 0, 0 };
    HMONITOR hMon = MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);

    MONITORINFO monInfo;
    monInfo.cbSize = sizeof monInfo;

    if (GetMonitorInfo(hMon, &monInfo) == TRUE)
    {
        LONG width = monInfo.rcMonitor.right - monInfo.rcMonitor.left;
        LONG height = monInfo.rcMonitor.bottom - monInfo.rcMonitor.top;

        if (SetCursorPos(width / 2, height / 2) != TRUE)
        {
            std::cout << "SetCursorPos() failed, error : " << GetLastError() << "\n";
            return 1;
        }
    }
    else
    {
        std::cout << "GetMonitorInfo() failed, error : " << GetLastError() << "\n";
        return 2;
    }

	return 0;
}