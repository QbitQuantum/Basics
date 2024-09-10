UINT GetTaskbarPos(HWND hwndTaskbar)
{
    if (hwndTaskbar != NULL)
    {
        // See also: Q179908
        APPBARDATA abd = {0};
        abd.cbSize = sizeof abd;
        abd.hWnd = hwndTaskbar;
        SHAppBarMessage(ABM_GETTASKBARPOS, &abd);

        // SHAppBarMessage may fail to get the rectangle...
        CRect rcAppBar(abd.rc);
        if (rcAppBar.IsRectEmpty() || rcAppBar.IsRectNull())
            GetWindowRect(hwndTaskbar, &abd.rc);

        if (abd.rc.top == abd.rc.left && abd.rc.bottom > abd.rc.right)
            return ABE_LEFT;
        else if (abd.rc.top == abd.rc.left && abd.rc.bottom < abd.rc.right)
            return ABE_TOP;
        else if (abd.rc.top > abd.rc.left)
            return ABE_BOTTOM;
        return ABE_RIGHT;
    }
    return ABE_BOTTOM;
}