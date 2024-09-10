//
// IsFullscreenWindow
// 
HMONITOR FullscreenMonitor::IsFullscreenWindow(HWND hWnd)
{
    if (!IsWindow(hWnd))
    {
        return nullptr;
    }
    
    HMONITOR hMonFS = nullptr;
    EnumThreadWindows(GetWindowThreadProcessId(hWnd, nullptr), _EnumThreadFSWnd, (LPARAM)&hMonFS);
    
    return hMonFS;
}