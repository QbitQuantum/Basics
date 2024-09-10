/* Draw themed border */
static void nc_paint (HTHEME theme, HWND hwnd, HRGN region)
{
    HRGN cliprgn = region;
    DWORD exStyle = GetWindowLongW (hwnd, GWL_EXSTYLE);
    if (exStyle & WS_EX_CLIENTEDGE)
    {
        HDC dc;
        RECT r;
        int cxEdge = GetSystemMetrics (SM_CXEDGE),
            cyEdge = GetSystemMetrics (SM_CYEDGE);
        int part = EP_EDITTEXT;
        int state = ETS_NORMAL;
        DWORD dwStyle = GetWindowLongW (hwnd, GWL_STYLE);
    
        if (!IsWindowEnabled (hwnd))
            state = ETS_DISABLED;
        else if (dwStyle & ES_READONLY)
            state = ETS_READONLY;
        else if (GetFocus() == hwnd)
            state = ETS_FOCUSED;
    
        GetWindowRect(hwnd, &r);
    
        /* New clipping region passed to default proc to exclude border */
        cliprgn = CreateRectRgn (r.left + cxEdge, r.top + cyEdge,
            r.right - cxEdge, r.bottom - cyEdge);
        if (region != (HRGN)1)
            CombineRgn (cliprgn, cliprgn, region, RGN_AND);
        OffsetRect(&r, -r.left, -r.top);
    
        dc = GetDCEx(hwnd, region, DCX_WINDOW|DCX_INTERSECTRGN);
        OffsetRect(&r, -r.left, -r.top);
    
        if (IsThemeBackgroundPartiallyTransparent (theme, part, state))
            DrawThemeParentBackground(hwnd, dc, &r);
        DrawThemeBackground (theme, dc, part, state, &r, 0);
        ReleaseDC(hwnd, dc);
    }

    /* Call default proc to get the scrollbars etc. also painted */
    DefWindowProcW (hwnd, WM_NCPAINT, (WPARAM)cliprgn, 0);
}