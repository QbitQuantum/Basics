void DrawHeader(HDC hdc, TCHAR *s, int y, int width) {

	SelectObject(hdc, hfontSegoe);

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);

	RECT r = {8, y, width, y + tm.tmHeight*3/2};

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 51, 153));
	DrawTextEx(hdc, s, -1, &r, DT_LEFT | DT_VCENTER | DT_SINGLELINE, NULL);

	DrawTextEx(hdc, s, -1, &r, DT_LEFT | DT_CALCRECT | DT_VCENTER | DT_SINGLELINE, NULL);
	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(176, 191, 222));
	MoveToEx(hdc, r.right + tm.tmAveCharWidth/2, (r.bottom - r.top)/2 + 1, NULL);
	LineTo(hdc, width - 28, (r.bottom - r.top)/2 + 1);
}