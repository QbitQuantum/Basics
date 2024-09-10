void UIScreenCaptureMgr::forceForgroundWindow(__in HWND hWnd)
{
    HWND hForegroundWnd = ::GetForegroundWindow();
    DWORD dwPid = GetWindowThreadProcessId(hForegroundWnd, NULL);
    if (!AttachThreadInput(dwPid, GetCurrentThreadId(), TRUE)
        || !::SetForegroundWindow(hWnd) 
        || !::BringWindowToTop(hWnd))
    {
        return;
    }

    SwitchToThisWindow(hWnd, TRUE);
    AttachThreadInput(dwPid, GetCurrentThreadId(), FALSE);
}