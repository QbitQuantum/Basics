WINBOOL SetForegroundWindowEx(HWND hWnd)
{
    //Attach foreground window thread to our thread
    const DWORD ForeGroundID = GetWindowThreadProcessId(::GetForegroundWindow(), NULL);
    const DWORD CurrentID   = GetCurrentThreadId();
    WINBOOL retval;

    AttachThreadInput(ForeGroundID, CurrentID, TRUE);
    //Do our stuff here
    HWND hLastActivePopupWnd = GetLastActivePopup(hWnd);
    retval = SetForegroundWindow(hLastActivePopupWnd);

    //Detach the attached thread
    AttachThreadInput(ForeGroundID, CurrentID, FALSE);
    return retval;
}// End SetForegroundWindowEx