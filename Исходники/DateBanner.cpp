void CDateBanner::CRightArrowButton::PaintForeground(HDC dc, int w, int h)
{
    DWORD lc1 = c1;
    DWORD lc2 = c2;
    DWORD lc3 = c3;
	DWORD blk = 0;
	DWORD dash = dashColor;
    if(m_state & ButtonMouseOver)
    {
		SetDCPenColor(dc, hiliteFill);
		SetDCBrushColor(dc, hiliteFill);
        Rectangle(dc, 1, 1, w - 1, h - 1);
        if(m_state & ButtonPressed)
		{
			lc1 = lc2 = lc3 = blk;
			dash = hiliteDash;
		}
    }
	SetDCPenColor(dc, dash);
	MoveToEx(dc, 2, 2, 0);
	POINT pts[] = { { w - 2, 2 }, { w - 2, h - 2 }, { 2, h - 2 }, { 2, 2 } };
	PolylineTo(dc, pts, 4);

    HPEN p2 = CreatePen(PS_DASH, 2, lc3);
	HGDIOBJ oldPen = SelectObject(dc, p2);

    MoveToEx(dc, 5, 5, 0);
	LineTo(dc, 15, 20);
	LineTo(dc, 5, 35);

	HPEN p1 = CreatePen(PS_DASH, 2, lc2);
	SelectObject(dc, p1);
	DeleteObject(p2);
	
	MoveToEx(dc, 5, 10, 0);
	LineTo(dc, 25, 20);
	LineTo(dc, 5, 30);

	p2 = CreatePen(PS_DASH, 2, lc1);
	SelectObject(dc, p2);
	DeleteObject(p1);

	MoveToEx(dc, 5, 15, 0);
	LineTo(dc, 35, 20);
    LineTo(dc, 5, 25);

	SelectObject(dc, oldPen);
	DeleteObject(p2);
}