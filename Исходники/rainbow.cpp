void Rainbow::draw() const
{
    if(isVisible())
    {

    HPEN pen = CreatePen (PS_SOLID, 2, decodeColor(getBorderColor()));
    SelectObject (dc, pen);

    MoveToEx(dc, x+r, y, NULL);
    ArcTo(dc, x-R, y-R, x+R, y+R, x+R, y, x-R, y);
    MoveToEx(dc, x+r, y, NULL);
    ArcTo(dc, x-r, y-r, x+r, y+r, x+r, y, x-r, y);
    LineTo(dc, x-R, y);

    }
}