void RoundRect(HDC hdc, RECT *rect, int cx, int cy, COLORREF fg, COLORREF bg)
{
	SetDCBrushColor(hdc, bg);
	SetDCPenColor(hdc, fg);
//	HBRUSH hBr = CreateSolidBrush(bg);
//	HPEN   hPn = CreatePen(0, PS_SOLID, fg);

//	HANDLE hOldBr  = SelectObject(hdc, hBr);
//	HANDLE hOldPen = SelectObject(hdc, hPn);

	RoundRect(hdc, rect->left, rect->top, rect->right, rect->bottom, cx, cy);

//	SelectObject(hdc, hOldBr);
//	SelectObject(hdc, hOldPen);
//	DeleteObject(hBr);
//	DeleteObject(hPn);
}