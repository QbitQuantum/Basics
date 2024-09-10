void ColorNode(HDC hDC, COLORREF rgb, COLORREF bgc, 
               int left, int top, int right, int bottom)
{
    WORD wWidth = right - left;
    WORD wHeight = bottom - top;

    if (GetDeviceCaps(hDC, NUMCOLORS) <= 2)
        PatBlt(hDC, left, top, wWidth, wHeight, DSTINVERT);
    else
    {
        HBRUSH hBrush = CreateSolidBrush(rgb);
        HDC hMemDC = CreateCompatibleDC(hDC);
        HBITMAP hBitmap;
        DWORD dwExt;
        POINT pt;
    
        SetMapMode(hMemDC, GetMapMode(hDC));
        dwExt = GetWindowExt(hDC);
        SetWindowExt(hMemDC, LOWORD(dwExt), HIWORD(dwExt));
        dwExt = GetViewportExt(hDC);
        SetViewportExt(hMemDC, LOWORD(dwExt), HIWORD(dwExt));
    
        pt.x = wWidth;
        pt.y = wHeight;
        LPtoDP(hMemDC, &pt, 1);

        hBitmap = CreateBitmap(pt.x, pt.y, 1, 1, NULL);
        SelectObject(hMemDC, hBitmap);
        
        SetBkColor(hDC, bgc);
        BitBlt(hMemDC, 0, 0, wWidth, wHeight, hDC, left, top, SRCCOPY);
        
        SetBkColor(hDC, rgb);
        BitBlt(hDC, left, top, wWidth, wHeight, hMemDC, 0, 0, SRCCOPY);
        
        DeleteDC(hMemDC);
        DeleteObject(hBitmap);
        SelectObject(hDC, GetStockObject(WHITE_BRUSH));
        DeleteObject(hBrush);
        
        SetBkColor(hDC, GetSysColor(COLOR_WINDOW));
    }
}