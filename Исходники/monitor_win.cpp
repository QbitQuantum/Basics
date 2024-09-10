HWND GetTopmostAutoHideTaskbarForEdge(UINT edge, HMONITOR monitor)
{
    APPBARDATA taskbar_data =  { sizeof(APPBARDATA), NULL, 0, edge };
    HWND taskbar = reinterpret_cast<HWND>(SHAppBarMessage(ABM_GETAUTOHIDEBAR,
                                          &taskbar_data));
    return (::IsWindow(taskbar) && (monitor != NULL) &&
            (MonitorFromWindow(taskbar, MONITOR_DEFAULTTONULL) == monitor) &&
            (GetWindowLong(taskbar, GWL_EXSTYLE) & WS_EX_TOPMOST)) ? taskbar : NULL;
}