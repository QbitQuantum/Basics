int DrawMe(HWND hwnd, TCHAR *string, COLORREF color)
{
	logmsg("DrawMe");
	if (!string) string = _T("bullshit");

	plgsettings plgs;
	loadDBSettings(&plgs);
	HFONT fh = CreateFontIndirect(&(plgs.lf));

	PAINTSTRUCT	ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	SetBkMode(hdc, TRANSPARENT);

	RECT rect;
	GetClientRect(hwnd, &rect);
	HBRUSH bkb = CreateSolidBrush(plgs.bkclr);
	FillRect(hdc, &rect, bkb);

	DeleteObject(bkb);

	HGDIOBJ oo = SelectObject(hdc, fh);

	UINT talign = 0;
	RECT rect2 = rect;
	DrawText(hdc, string, -1, &rect2, DT_WORDBREAK | DT_CALCRECT);

	if (plgs.align <= 3)
		rect.top = 0;
	else if (plgs.align <= 6)
		rect.top = (rect.bottom - rect2.bottom) / 2;
	else if (plgs.align <= 9)
		rect.top = rect.bottom - rect2.bottom;

	if (((plgs.align - 1) % 3) == 0)
		rect.left = 0;
	else if (((plgs.align - 2) % 3) == 0)
		rect.left = (rect.right - rect2.right) / 2;
	else if (((plgs.align - 3) % 3) == 0)
		rect.left = rect.right - rect2.right;

	rect.bottom = rect.top + rect2.bottom;
	rect.right = rect.left + rect2.right;

	//draw shadow
	if (plgs.showShadow) {
		int sxo, syo;
		logmsg("DrawMe::showShadow");
		if (plgs.salign <= 3)
			syo = -plgs.distance;
		else if (plgs.salign <= 6)
			syo = 0;
		else if (plgs.salign <= 9)
			syo = plgs.distance;
		else
			syo = 0;

		if (((plgs.salign - 1) % 3) == 0)
			sxo = -plgs.distance;
		else if (((plgs.salign - 2) % 3) == 0)
			sxo = 0;
		else if (((plgs.salign - 3) % 3) == 0)
			sxo = plgs.distance;
		else
			sxo = 0;

		SetTextColor(hdc, plgs.clr_shadow);
		if (plgs.altShadow == 0) {
			rect2 = rect;
			OffsetRect(&rect, sxo, syo);

			DrawText(hdc, string, -1, &rect2, DT_WORDBREAK | talign);
		}
		else {
			rect2 = rect;
			rect2.left += plgs.distance;
			DrawText(hdc, string, -1, &rect2, DT_WORDBREAK | talign);

			rect2 = rect;
			rect2.left -= plgs.distance;
			DrawText(hdc, string, -1, &rect2, DT_WORDBREAK | talign);

			rect2 = rect;
			rect2.top -= plgs.distance;
			DrawText(hdc, string, -1, &rect2, DT_WORDBREAK | talign);

			rect2 = rect;
			rect2.top += plgs.distance;
			DrawText(hdc, string, -1, &rect2, DT_WORDBREAK | talign);

			OffsetRect(&rect, sxo / 2, syo / 2);
		}
	}

	//draw text
	SetTextColor(hdc, color);
	DrawText(hdc, string, -1, &rect, DT_WORDBREAK);

	SelectObject(hdc, oo);
	DeleteObject(fh);
	EndPaint(hwnd, &ps);

	return 0;
}