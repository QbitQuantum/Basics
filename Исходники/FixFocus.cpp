static void install_toplevel_focus_fix(HWND hwnd)
{
    HWND root_window = GetAncestor(hwnd, GA_ROOT);
    if(GetProp(root_window, "ToplevelFocusHackOldProc") != NULL) {
        /* We already installed the fix, maybe there are 2 browser's
         * embedded? */
        return;
    }
    WNDPROC old_proc = (WNDPROC) SetWindowLongPtr(root_window,
                GWL_WNDPROC, (LONG_PTR)ToplevelFocusHackWndProc);
    SetProp(root_window,"ToplevelFocusHackOldProc", old_proc);
}