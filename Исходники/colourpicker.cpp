static LRESULT CALLBACK ColourPickerWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_CREATE:
		SetWindowLongPtr(hwnd, 0, 0);
		SetWindowLongPtr(hwnd, sizeof(COLORREF), 0);
		break;

	case CPM_SETDEFAULTCOLOUR:
		SetWindowLongPtr(hwnd, sizeof(COLORREF), lParam);
		break;

	case CPM_GETDEFAULTCOLOUR:
		return GetWindowLongPtr(hwnd, sizeof(COLORREF));

	case CPM_SETCOLOUR:
		SetWindowLongPtr(hwnd, 0, lParam);
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case CPM_GETCOLOUR:
		return GetWindowLongPtr(hwnd, 0);

	case WM_LBUTTONUP:
		{
			COLORREF custColours[16] = { 0 };
			custColours[0] = GetWindowLongPtr(hwnd, sizeof(COLORREF));

			CHOOSECOLOR cc = { 0 };
			cc.lStructSize = sizeof(CHOOSECOLOR);
			cc.hwndOwner = hwnd;
			cc.hInstance = (HWND)g_hInst;
			cc.rgbResult = GetWindowLongPtr(hwnd, 0);
			cc.lpCustColors = custColours;
			cc.Flags = CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT;
			if (ChooseColor(&cc)) {
				SetWindowLongPtr(hwnd, 0, cc.rgbResult);
				SendMessage(GetParent(hwnd), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(hwnd), CPN_COLOURCHANGED), (LPARAM)hwnd);
				InvalidateRect(hwnd, NULL, FALSE);
			}
		}
		break;

	case WM_ENABLE:
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_NCPAINT:
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc1 = BeginPaint(hwnd, &ps);

		RECT rc;
		GetClientRect(hwnd, &rc);
		DrawEdge(hdc1, &rc, EDGE_ETCHED, BF_RECT);
		InflateRect(&rc, -2, -2);

		HBRUSH hBrush = (IsWindowEnabled(hwnd)) ? CreateSolidBrush(GetWindowLongPtr(hwnd, 0)) : CreateHatchBrush(HS_BDIAGONAL, GetSysColor(COLOR_GRAYTEXT));
		SetBkColor(hdc1, GetSysColor(COLOR_BTNFACE));
		FillRect(hdc1, &rc, hBrush);
		DeleteObject(hBrush);

		EndPaint(hwnd, &ps);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}