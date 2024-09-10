static void DoPaint(HWND hwnd, HDC hDC, LPPAINTSTRUCT lpPaint, RECT *r, struct resRes *menuData)
{
    RECT r1;
    NONCLIENTMETRICS m;
    HFONT font;
    SIZE sz;
    HDC compatDC, arrowDC;
    HBITMAP compatBitmap, arrowBitmap;
    int fontHeight;
    m.cbSize = sizeof(NONCLIENTMETRICS);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS),&m, NULL);
    fontHeight = (m.lfMenuFont.lfHeight < 0 ? - m.lfMenuFont.lfHeight : m.lfMenuFont.lfHeight)+6;
    font = CreateFontIndirect(&m.lfMenuFont);
    compatDC = CreateCompatibleDC(hDC);
    arrowDC = CreateCompatibleDC(hDC);
    font = SelectObject(compatDC, font);
    sz.cx = 0; 
    sz.cy = 0;
    GetSizeTopRow(compatDC, menuData->resource->u.menu->items, 0, 0, fontHeight, &sz);
    sz.cx +=GetSystemMetrics(SM_CXBORDER) * 2;
    sz.cy +=GetSystemMetrics(SM_CYBORDER) * 2;
    if (sz.cx < r->right)
        sz.cx = r->right;
    if (sz.cy < r->bottom)
        sz.cy = r->bottom;
    arrowBitmap = arrImage;
    arrowBitmap = SelectObject(arrowDC, arrowBitmap);
    compatBitmap = CreateCompatibleBitmap(hDC, 1000, 1000);
    compatBitmap = SelectObject(compatDC, compatBitmap);
    r1.left = r1.top = 0;
    r1.right = 1000;
    r1.bottom = 1000;
    FillRect(compatDC,&r1, (HBRUSH)(COLOR_APPWORKSPACE + 1));
    SetTextColor(compatDC, GetSysColor(COLOR_WINDOWTEXT));
    PaintTopRow(compatDC, arrowDC, menuData->resource->u.menu->items, menuData->gd.selectedMenu, 0, 0, font, fontHeight);
    font = SelectObject(compatDC, font);
    menuData->gd.scrollMax.x = sz.cx;
    menuData->gd.scrollMax.y = sz.cy;
    if (sz.cx <= r->right)
    {
        menuData->gd.scrollPos.x = 0;
    }
    else
    {
        SetScrollRange(hwnd, SB_HORZ, 0, sz.cx, FALSE);
        r->bottom -= GetSystemMetrics(SM_CYHSCROLL);
    }
    ShowScrollBar(hwnd, SB_HORZ, sz.cx > r->right);
    ShowScrollBar(hwnd, SB_VERT, sz.cy > r->bottom);
    if (sz.cy <= r->bottom)
    {
        menuData->gd.scrollPos.y = 0;
    }
    else
    {
        SetScrollRange(hwnd, SB_VERT, 0, sz.cy, FALSE);
        r->right -= GetSystemMetrics(SM_CXVSCROLL);
    }
    menuData->gd.scrollMax.x = sz.cx;
    menuData->gd.scrollMax.y = sz.cy;
    BitBlt(hDC, r->left+10, r->top+10, r->right+10, r->bottom+10,
           compatDC, menuData->gd.scrollPos.x, menuData->gd.scrollPos.y, SRCCOPY);
    compatBitmap = SelectObject(compatDC, compatBitmap);
    arrowBitmap = SelectObject(arrowDC, arrowBitmap);
    DeleteObject(compatBitmap);
    DeleteDC(compatDC);
    DeleteDC(arrowDC);
    DeleteObject(font);
}