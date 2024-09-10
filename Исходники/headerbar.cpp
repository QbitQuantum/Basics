static LRESULT MHeaderbar_OnPaint(HWND hwndDlg, MHeaderbarCtrl *mit, UINT  msg, WPARAM wParam, LPARAM lParam)
{
	int iTopSpace = IsAeroMode() ? 0 : 3;
	PAINTSTRUCT ps;
	HBITMAP hBmp, hOldBmp;

	int titleLength = GetWindowTextLength(hwndDlg) + 1;
	TCHAR *szTitle = (TCHAR *)mir_alloc(sizeof(TCHAR) * titleLength);
	GetWindowText(hwndDlg, szTitle, titleLength);

	TCHAR *szSubTitle = _tcschr(szTitle, _T('\n'));
	if (szSubTitle) *szSubTitle++=0;

	HDC hdc = BeginPaint(hwndDlg, &ps);
	HDC tempDC = CreateCompatibleDC(hdc);

	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = mit->width;
	bmi.bmiHeader.biHeight = -mit->height; // we need this for DrawThemeTextEx
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	hBmp = CreateDIBSection(tempDC, &bmi, DIB_RGB_COLORS, NULL, NULL, 0);

	hOldBmp = (HBITMAP)SelectObject(tempDC, hBmp);

	if (IsAeroMode()) {
		RECT temprc;
		temprc.left = 0;
		temprc.right = mit->width;
		temprc.top = 0;
		temprc.bottom = mit->width;
		FillRect(tempDC, &temprc, (HBRUSH)GetStockObject(BLACK_BRUSH));

		MARGINS margins = {0, 0, mit->height, 0};
		dwmExtendFrameIntoClientArea(GetParent(hwndDlg), &margins);

		WTA_OPTIONS opts;
		opts.dwFlags = opts.dwMask = WTNCA_NODRAWCAPTION | WTNCA_NODRAWICON;
		setWindowThemeAttribute(GetParent(hwndDlg), WTA_NONCLIENT, &opts, sizeof(opts));
	}
	else {
		if (IsVSMode())
			MHeaderbar_FillRect(tempDC, 0, 0, mit->width, mit->height, GetSysColor(COLOR_WINDOW));
		else
			MHeaderbar_DrawGradient(tempDC, 0, 0, mit->width, mit->height, &mit->rgbBkgTop, &mit->rgbBkgBottom);

		MHeaderbar_FillRect(tempDC, 0, mit->height-2, mit->width, 1, GetSysColor(COLOR_BTNSHADOW));
		MHeaderbar_FillRect(tempDC, 0, mit->height-1, mit->width, 1, GetSysColor(COLOR_BTNHIGHLIGHT));
	}

	HFONT hFont = mit->hFont;
	SetBkMode(tempDC, TRANSPARENT);
	SetTextColor(tempDC, mit->clText);

	LOGFONT lf;
	GetObject(hFont, sizeof(lf), &lf);
	lf.lfWeight = FW_BOLD;
	HFONT hFntBold = CreateFontIndirect(&lf), hOldFont;

	if (mit->hIcon)
		DrawIcon(tempDC, 10, iTopSpace, mit->hIcon);
	else {
		HICON hIcon = (HICON)SendMessage(GetParent(hwndDlg), WM_GETICON, ICON_BIG, 0);
		if (hIcon == NULL)
			hIcon = (HICON)SendMessage(GetParent(hwndDlg), WM_GETICON, ICON_SMALL, 0);
		DrawIcon(tempDC, 10, iTopSpace, hIcon);
	}

	RECT textRect;
	textRect.left = 50;
	textRect.right = mit->width;
	textRect.top = 2 + iTopSpace;
	textRect.bottom = GetSystemMetrics(SM_CYICON)-2 + iTopSpace;

	if (IsAeroMode()) {
		DTTOPTS dto = {0};
		dto.dwSize = sizeof(dto);
		dto.dwFlags = DTT_COMPOSITED|DTT_GLOWSIZE;
		dto.iGlowSize = 10;

		HANDLE hTheme = OpenThemeData(hwndDlg, L"Window");
		textRect.left = 50;
		hOldFont = (HFONT)SelectObject(tempDC, hFntBold);

		wchar_t *szTitleW = mir_t2u(szTitle);
		drawThemeTextEx(hTheme, tempDC, WP_CAPTION, CS_ACTIVE, szTitleW, -1, DT_TOP|DT_LEFT|DT_SINGLELINE|DT_NOPREFIX|DT_NOCLIP|DT_END_ELLIPSIS, &textRect, &dto);
		mir_free(szTitleW);

		if (szSubTitle) {
			textRect.left = 66;
			SelectObject(tempDC, hFont);

			wchar_t *szSubTitleW = mir_t2u(szSubTitle);
			drawThemeTextEx(hTheme, tempDC, WP_CAPTION, CS_ACTIVE, szSubTitleW, -1, DT_BOTTOM|DT_LEFT|DT_SINGLELINE|DT_NOPREFIX|DT_NOCLIP|DT_END_ELLIPSIS, &textRect, &dto);
			mir_free(szSubTitleW);
		}
		CloseThemeData(hTheme);
	}
	else {
		textRect.left = 50;
		hOldFont = (HFONT)SelectObject(tempDC, hFntBold);
		DrawText(tempDC, szTitle, -1, &textRect, DT_TOP|DT_LEFT|DT_SINGLELINE|DT_NOPREFIX|DT_NOCLIP|DT_END_ELLIPSIS);

		if (szSubTitle) {
			textRect.left = 66;
			SelectObject(tempDC, hFont);
			DrawText(tempDC, szSubTitle, -1, &textRect, DT_BOTTOM|DT_LEFT|DT_SINGLELINE|DT_NOPREFIX|DT_NOCLIP|DT_END_ELLIPSIS);
		}
	}

	DeleteObject(hFntBold);

	mir_free(szTitle);

	//Copy to output
	if (mit->nControlsToRedraw)
	{
		RECT temprc;
		temprc.left = 0;
		temprc.right = mit->width;
		temprc.top = 0;
		temprc.bottom = mit->width;
		HRGN hRgn = CreateRectRgnIndirect(&temprc);

		for (int i=0; i < mit->nControlsToRedraw; i++)
		{
			GetWindowRect(mit->controlsToRedraw[i], &temprc);
			MapWindowPoints(NULL, hwndDlg, (LPPOINT)&temprc, 2);
			HRGN hRgnTmp = CreateRectRgnIndirect(&temprc);
			CombineRgn(hRgn, hRgn, hRgnTmp, RGN_DIFF);
			DeleteObject(hRgnTmp);
		}
		SelectClipRgn(hdc, hRgn);
		DeleteObject(hRgn);
	}

	BitBlt(hdc, mit->rc.left, mit->rc.top, mit->width, mit->height, tempDC, 0, 0, SRCCOPY);

	SelectClipRgn(hdc, NULL);

	SelectObject(tempDC, hOldBmp);
	DeleteObject(hBmp);
	SelectObject(tempDC,hOldFont);
	DeleteDC(tempDC);

	EndPaint(hwndDlg, &ps);

	return TRUE;
}