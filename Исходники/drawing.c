void
Bezier(HDC hdc, POINT p1, POINT p2, POINT p3, POINT p4, COLORREF color, int thickness)
{
    HPEN oldPen;
    POINT fourPoints[4];
    fourPoints[0] = p1;
    fourPoints[1] = p2;
    fourPoints[2] = p3;
    fourPoints[3] = p4;
    oldPen = SelectObject(hdc, CreatePen(PS_SOLID, thickness, color));
    PolyBezier(hdc, fourPoints, 4);
    DeleteObject(SelectObject(hdc, oldPen));
}