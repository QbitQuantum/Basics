//! Entrypoint used to make another window become subclassed.
bool BlueWindow::SubclassNewWindow(HWND hwnd)
{
    DWORD windowpid;
    
    if (hwnd != NULL && IsWindow(hwnd) && 
        GetWindowThreadProcessId(hwnd, &windowpid) && 
        windowpid == GetCurrentProcessId() &&
        OldWindowProcs.find(hwnd) == OldWindowProcs.end())
    {
        // Found the window that is from our process.  Subclass it.
        WNDPROC lpfnOldWindowProc = (WNDPROC) LongToPtr(GetWindowLongPtr(hwnd, GWL_WNDPROC));
        OldWindowProcs.insert(std::make_pair<HWND, WNDPROC>(hwnd, lpfnOldWindowProc));
        SetWindowLongPtr(hwnd, GWL_WNDPROC, PtrToLong(BlueWindow::SubclassProc));
        ForceNonclientRepaint(hwnd);
        return true;
    }

    return false;       // could not successfully subclass specified window.
}