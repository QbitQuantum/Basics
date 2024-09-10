/* Create the basic bitmaps for the color picker buttons */
static VOID
InitColorButtons(HWND hwndDlg, GLOBALS* g)
{
	INT i;
	HDC hdcColorButton, hdcCompat;
	RECT rect;
	HBRUSH hbrush;
	HPEN hPen;
	HWND hwndColorButton;
	HGDIOBJ hgdiTemp;
    THEME *theme = &g->ThemeAdv;

	const POINT Points[3] = {{29,6},{33,6},{31,8}};

	hwndColorButton = GetDlgItem(hwndDlg, IDC_ADVAPPEARANCE_COLOR1_B);
	hdcColorButton = GetDC(hwndColorButton);
	for (i = 0; i <= 2; i++)
	{
		/* Create a DC to draw on */
		hdcCompat = CreateCompatibleDC(hdcColorButton);

		/* Create the button image */
		g->hbmpColor[i] = CreateCompatibleBitmap(hdcColorButton, 36, 15);

		/* Select the button image to the DC */
		hgdiTemp = SelectObject(hdcCompat, g->hbmpColor[i]);

		/* Draw the buttons background color */
		rect.left = 0;
		rect.top = 0;
		rect.right = 36;
		rect.bottom = 15;
		hbrush = CreateSolidBrush(theme->crColor[COLOR_BTNFACE]);
		FillRect(hdcCompat, &rect, hbrush);
		DeleteObject(hbrush);

		/* Draw the rectangle */
		rect.left = 1;
		rect.top = 1;
		rect.right = 23;
		rect.bottom = 14;
		hbrush = CreateSolidBrush(theme->crColor[COLOR_BTNTEXT]);
		FillRect(hdcCompat, &rect, hbrush);
		DeleteObject(hbrush);

		/* Draw left side of line */
		hPen = CreatePen(PS_SOLID, 1, theme->crColor[COLOR_BTNSHADOW]);
		SelectObject(hdcCompat, hPen);
		MoveToEx(hdcCompat, 26, 1, NULL);
		LineTo(hdcCompat, 26, 14);
		SelectObject(hdcCompat, GetStockObject(BLACK_PEN));
		DeleteObject(hPen);

		/* Draw right side of line */
		hPen = CreatePen(PS_SOLID, 1, theme->crColor[COLOR_BTNHIGHLIGHT]);
		SelectObject(hdcCompat,hPen);
		MoveToEx(hdcCompat, 27, 1, NULL);
		LineTo(hdcCompat, 27, 14);
		SelectObject(hdcCompat, GetStockObject(BLACK_PEN));
		DeleteObject(hPen);

		/* Draw triangle */
		hPen = CreatePen(PS_SOLID, 1, theme->crColor[COLOR_BTNTEXT]);
		hbrush = CreateSolidBrush(theme->crColor[COLOR_BTNTEXT]);
		SelectObject(hdcCompat, hPen);
		SelectObject(hdcCompat, hbrush);
		SetPolyFillMode(hdcCompat, WINDING);

		/* FIXME: HACK, see Points definition */
		Polygon(hdcCompat, Points, 3);

		/* Cleanup */
		SelectObject(hdcCompat,hgdiTemp);
		DeleteDC(hdcCompat);
		DeleteObject(hPen);
		DeleteObject(hbrush);
	}

	ReleaseDC(hwndColorButton, hdcColorButton);

	/* Set the images of the buttons */
	SendDlgItemMessage(hwndDlg, IDC_ADVAPPEARANCE_COLOR1_B, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g->hbmpColor[0]);
	SendDlgItemMessage(hwndDlg, IDC_ADVAPPEARANCE_COLOR2_B, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g->hbmpColor[1]);
	SendDlgItemMessage(hwndDlg, IDC_ADVAPPEARANCE_FONTCOLOR_B, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g->hbmpColor[2]);
}