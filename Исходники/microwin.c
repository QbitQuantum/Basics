BOOL IntersectClipRect(HDC hdc, int x, int y,
                                int right, int bottom)
{
    /* TODO */
    HRGN rgn = CreateRectRgn(x, y, right, bottom);

    BOOL ret = (ExtSelectClipRgn(hdc, rgn, RGN_AND) != ERROR);
    DeleteObject(rgn);
    return ret;
}