void paint_round_rect_around_hwnd(HDC hdc, HWND hwnd_edit_parent, HWND hwnd_edit, COLORREF col)
{
    RECT    r;
    HBRUSH  br;
    HBRUSH  br_prev;
    HPEN    pen;
    HPEN    pen_prev;
    GetClientRect(hwnd_edit, &r);
    br = CreateSolidBrush(col);
    if (!br) return;
    pen = CreatePen(PS_SOLID, 1, col);
    pen_prev = SelectObject(hdc, pen);
    br_prev = SelectObject(hdc, br);
    rect_client_to_screen(&r, hwnd_edit_parent);
    /* TODO: the roundness value should probably be calculated from the dy of the rect */
    /* TODO: total hack: I manually adjust rectangle to values that fit g_hwnd_edit, as
       found by experimentation. My mapping of coordinates isn't right (I think I need
       mapping from window to window but even then it wouldn't explain -3 for y axis */
    RoundRect(hdc, r.left+4, r.top-3, r.right+12, r.bottom-3, 8, 8);
    if (br_prev)
        SelectObject(hdc, br_prev);
    if (pen_prev)
        SelectObject(hdc, pen_prev);
    DeleteObject(pen);
    DeleteObject(br);
}