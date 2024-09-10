static void draw_hilight_box (HWND hWnd, HDC hdc, COOLBARITEMDATA* item)
{
    int  l,r,t,b; 
    WINDOWINFO *info = (WINDOWINFO*)GetWindowInfo (hWnd);
    DWORD color;
    DWORD mainc = GetWindowElementAttr (hWnd, WE_MAINC_THREED_BODY);

    l = item->RcTitle.left;
    t = item->RcTitle.top;
    r = item->RcTitle.right - 1;
    b = item->RcTitle.bottom - 1;

    color = info->we_rdr->calc_3dbox_color (mainc, LFRDR_3DBOX_COLOR_DARKER);
    SetPenColor (hdc,
            RGBA2Pixel (hdc, GetRValue (color), GetGValue (color), 
                GetBValue (color), GetAValue (color)));
    MoveTo (hdc, l, t);
    LineTo (hdc, l, b);
    MoveTo (hdc, r - 1, t);
    LineTo (hdc, r - 1, b);

    color = info->we_rdr->calc_3dbox_color (mainc, LFRDR_3DBOX_COLOR_LIGHTER);
    SetPenColor (hdc,
            RGBA2Pixel (hdc, GetRValue (color), GetGValue (color), 
                GetBValue (color), GetAValue (color)));
    MoveTo (hdc, l + 1, t);
    LineTo (hdc, l + 1, b);
    MoveTo (hdc, r, t);
    LineTo (hdc, r, b);
}