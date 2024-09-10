void SetThemeRegion(HWND hWnd, PWND_CONTEXT pcontext)
{
    HTHEME hTheme;
    RECT rcWindow;
    HRGN hrgn, hrgn1;
    int CaptionHeight, iPart;
    WINDOWINFO wi;

    if(!IsAppThemed())
    {
        if(pcontext->HasThemeRgn)
        {
            pcontext->HasThemeRgn = FALSE;
            user32ApiHook.SetWindowRgn(hWnd, 0, TRUE);
        }
        return;
    }

    wi.cbSize = sizeof(wi);

    GetWindowInfo(hWnd, &wi);
            
    if((wi.dwStyle & WS_CAPTION)!=WS_CAPTION)
    {
        return;
    }

    /* Get the caption part id */
    if (wi.dwExStyle & WS_EX_TOOLWINDOW)
        iPart = WP_SMALLCAPTION;
    else if (wi.dwStyle & WS_MAXIMIZE)
        iPart = WP_MAXCAPTION;
    else
        iPart = WP_CAPTION;

    pcontext->HasThemeRgn = TRUE;

    CaptionHeight = wi.cyWindowBorders;
    CaptionHeight += GetSystemMetrics(wi.dwExStyle & WS_EX_TOOLWINDOW ? SM_CYSMCAPTION : SM_CYCAPTION );

    GetWindowRect(hWnd, &rcWindow);
    rcWindow.right -= rcWindow.left;
    rcWindow.bottom = CaptionHeight;
    rcWindow.top = 0;
    rcWindow.left = 0;

    hTheme = OpenThemeData (hWnd, L"WINDOW");

    GetThemeBackgroundRegion(hTheme, 0, iPart, FS_ACTIVE, &rcWindow, &hrgn);

    CloseThemeData(hTheme);

    GetWindowRect(hWnd, &rcWindow);
    rcWindow.right -= rcWindow.left;
    rcWindow.bottom -= rcWindow.top;
    rcWindow.top = CaptionHeight;
    rcWindow.left = 0;
    hrgn1 = CreateRectRgnIndirect(&rcWindow);

    CombineRgn(hrgn, hrgn, hrgn1, RGN_OR );

    DeleteObject(hrgn1);

    user32ApiHook.SetWindowRgn(hWnd, hrgn, TRUE);
}