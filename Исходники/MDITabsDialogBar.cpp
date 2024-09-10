void _DrawGradient(CDC &dc, const CRect &rect, COLORREF c1, COLORREF c2)
{
    TRIVERTEX vertices[2];
    vertices[0].Alpha = 0;
    vertices[0].Red = GetRValue(c1) << 8;
    vertices[0].Green = GetGValue(c1) << 8;
    vertices[0].Blue = GetBValue(c1) << 8;
    vertices[0].x = rect.left;
    vertices[0].y = rect.top;
    vertices[1].Alpha = 0;
    vertices[1].Red = GetRValue(c2) << 8;
    vertices[1].Green = GetGValue(c2) << 8;
    vertices[1].Blue = GetBValue(c2) << 8;
    vertices[1].x = rect.right;
    vertices[1].y = rect.bottom;
    GRADIENT_RECT rc;
    rc.UpperLeft = 0;
    rc.LowerRight = 1;
    dc.GradientFill(vertices, ARRAYSIZE(vertices), &rc, 1, GRADIENT_FILL_RECT_V);
}