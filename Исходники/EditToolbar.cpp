void EditToolbarUI::paintWindow(__in const RECT *rcWnd)
{
	const int DRAW_PEN_WIDTH = 2;

	RECT rc = { 0 };
	memcpy(&rc, rcWnd, sizeof(rc));

	HDC hRectDC = GetDC(m_hwnd);
	HPEN hDrawPen = CreatePen(PS_SOLID, DRAW_PEN_WIDTH, RGB(255, 0, 0));
	HGDIOBJ hPrevPen = SelectObject(hRectDC, hDrawPen);

	int x = rc.left;
	int y = rc.top;
	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;

	POINT ptArray[] = { { x, y },{ x + cx, y },{ x + cx, y + cy },{ x, y + cy },{ x, y }};
	Polyline(hRectDC, ptArray, 5);

	SelectObject(hRectDC, (HGDIOBJ)hPrevPen);
	DeleteObject(hDrawPen);
	ReleaseDC(m_hwnd, hRectDC);
}