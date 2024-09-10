LRESULT CALLBACK
CardImageWndProc(HWND hwnd,
                 UINT msg,
                 WPARAM wParam,
                 LPARAM lParam)
{
    PCARDBACK pCardBack = (PCARDBACK)GetWindowLongPtr(hwnd,
                                                      GWL_USERDATA);
    static WNDPROC hOldProc = NULL;

    if (!hOldProc && pCardBack)
        hOldProc = pCardBack->hOldProc;

    switch (msg)
    {
    case WM_PAINT:
    {
        HDC hdc;
        PAINTSTRUCT ps;
        HPEN hPen, hOldPen;
        HBRUSH hBrush, hOldBrush;
        RECT rc;

        hdc = BeginPaint(hwnd, &ps);

        if (pCardBack->bSelected)
        {
            hPen = CreatePen(PS_SOLID, 2, RGB(0,0,0));
        }
        else
        {
            DWORD Face = GetSysColor(COLOR_3DFACE);
            hPen = CreatePen(PS_SOLID, 2, Face);
        }

        GetClientRect(hwnd, &rc);
        hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        hOldPen = (HPEN)SelectObject(hdc, hPen);
        hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        Rectangle(hdc,
                  rc.left+1,
                  rc.top+1,
                  rc.right,
                  rc.bottom);

        StretchBlt(hdc,
                   2,
                   2,
                   CARDBACK_OPTIONS_WIDTH,
                   CARDBACK_OPTIONS_HEIGHT,
                   __hdcCardBitmaps,
                   pCardBack->hdcNum * __cardwidth,
                   0,
                   __cardwidth,
                   __cardheight,
                   SRCCOPY);

        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);

        EndPaint(hwnd, &ps);

        break;
    }

    case WM_LBUTTONDOWN:
        pCardBack->bSelected = pCardBack->bSelected ? FALSE : TRUE;
        break;
    }

    return CallWindowProc(hOldProc,
                          hwnd,
                          msg,
                          wParam,
                          lParam);
}