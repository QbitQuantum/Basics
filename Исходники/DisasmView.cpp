void DisasmView_DrawJump(HDC hdc, int yFrom, int delta, int x, int cyLine)
{
    int dist = abs(delta);
    if (dist < 2) dist = 2;
    if (dist > 20) dist = 16;

    int yTo = yFrom + delta * cyLine;
    yFrom += cyLine / 2;

    HGDIOBJ oldPen = SelectObject(hdc, CreatePen(PS_SOLID, 1, COLOR_JUMP));

    POINT points[4];
    points[0].x = x;  points[0].y = yFrom;
    points[1].x = x + dist * 4;  points[1].y = yFrom;
    points[2].x = x + dist * 12;  points[2].y = yTo;
    points[3].x = x;  points[3].y = yTo;
    PolyBezier(hdc, points, 4);
    MoveToEx(hdc, x - 4, points[3].y, NULL);
    LineTo(hdc, x + 4, yTo - 1);
    MoveToEx(hdc, x - 4, points[3].y, NULL);
    LineTo(hdc, x + 4, yTo + 1);

    SelectObject(hdc, oldPen);
}