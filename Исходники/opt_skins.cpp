static void BoxPreview_OnPaint(HWND hwnd, HDC mydc, int mode)
{
	RECT rc;

	switch (mode) {
	case 0:
		{ // Avatar
			HDC hdcAvatar = CreateCompatibleDC(mydc);
			HBITMAP hbmSave = (HBITMAP)SelectObject(hdcAvatar, hbmNoAvatar);
			GetClientRect(hwnd, &rc);
			BITMAP bmp;
			GetObject(hbmNoAvatar, sizeof(bmp), &bmp);
			StretchBlt(mydc, 0, 0, rc.right, rc.bottom, hdcAvatar, 0, 0, abs(bmp.bmWidth), abs(bmp.bmHeight), SRCCOPY);
			SelectObject(hdcAvatar, hbmSave);
			DeleteDC(hdcAvatar);
			HRGN rgn = CreateRoundRectRgn(0, 0, rc.right, rc.bottom, 2 * PopupOptions.avatarRadius, 2 * PopupOptions.avatarRadius);
			FrameRgn(mydc, rgn, (HBRUSH)GetStockObject(BLACK_BRUSH), 1, 1);
			DeleteObject(rgn);
			break;
		}
	case 1:
		{ // Opacity
			HBRUSH hbr = CreateSolidBrush(fonts.clBack);
			HFONT hfnt = (HFONT)SelectObject(mydc, fonts.title);
			GetClientRect(hwnd, &rc);
			FillRect(mydc, &rc, hbr);
			DrawIconEx(mydc, 10, (rc.bottom-rc.top-16)/2, IcoLib_GetIcon(ICO_POPUP_ON,0), 16, 16, 0, hbr, DI_NORMAL);
			SetBkMode(mydc, TRANSPARENT);
			GetClientRect(hwnd, &rc);
			rc.left += 30; // 10+16+4 -- icon
			rc.right -= (rc.right-rc.left)/3;
			rc.bottom -= (rc.bottom-rc.top)/3;
			DrawText(mydc, _T(MODULNAME_LONG), lstrlen(_T(MODULNAME_LONG)), &rc, DT_CENTER|DT_NOPREFIX|DT_SINGLELINE|DT_VCENTER);
			GetClientRect(hwnd, &rc);
			rc.left += 30; // 10+16+4 -- icon
			rc.left += (rc.right-rc.left)/3;
			rc.top += (rc.bottom-rc.top)/3;
			DrawText(mydc, _T(MODULNAME_LONG), lstrlen(_T(MODULNAME_LONG)), &rc, DT_CENTER|DT_NOPREFIX|DT_SINGLELINE|DT_VCENTER);
			GetClientRect(hwnd, &rc);
			FrameRect(mydc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
			SelectObject(mydc, hfnt);
			DeleteObject(hbr);
		}
		break;

	case 2:
		{ // Position
			HBRUSH hbr = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
			GetClientRect(hwnd, &rc);
			FillRect(mydc, &rc, hbr);
			DeleteObject(hbr);

			hbr = CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
			GetClientRect(hwnd, &rc);
			rc.right -= 100;
			rc.top += 100;
			FillRect(mydc, &rc, hbr);
			DeleteObject(hbr);

			HPEN hpen = (HPEN)SelectObject(mydc, CreatePen(PS_DOT, 1, RGB(0,0,0)));
			MoveToEx(mydc,   0, 100, NULL);
			LineTo  (mydc, 201, 100);
			MoveToEx(mydc, 100,   0, NULL);
			LineTo  (mydc, 100, 201);
			DeleteObject(SelectObject(mydc, hpen));

			HRGN hrgn = CreateRectRgn(0,0,0,0);
			GetWindowRgn(hwnd, hrgn);
			FrameRgn(mydc, hrgn, (HBRUSH)GetStockObject(BLACK_BRUSH), 1, 1);
			DeleteObject(hrgn);
		}
		break;
	}
}