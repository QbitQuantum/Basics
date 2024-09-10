Monitor DisplayManager::MonitorAtPoint(POINT &pt, bool workingArea) {
    Monitor m;
    HMONITOR monitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONULL);
    if (monitor != NULL) {
        MONITORINFO mInfo = Info(monitor);
        if (workingArea) {
            return Monitor(monitor, L"Monitor@Point", mInfo.rcWork);
        } else {
            return Monitor(monitor, L"Monitor@Point", mInfo.rcMonitor);
        }
    }

    return m;
}