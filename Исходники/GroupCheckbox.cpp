static int CALLBACK CheckboxWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	CCheckboxData *dat = (CCheckboxData*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	if (!dat)
		return 0;

	switch (Msg) {
	case UM_INITCHECKBOX:
		{
			HFONT hFont = (HFONT)SendMessage(hWnd, WM_GETFONT, 0, 0);
			if (!hFont)
				hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

			LOGFONT lf;
			GetObject(hFont, sizeof(lf), &lf);
			lf.lfWeight = FW_BOLD;
			dat->hFont = CreateFontIndirect(&lf);
			SendMessage(hWnd, UM_AUTOSIZE, 0, 0);
		}
		return 0;

	case UM_AUTOSIZE:
		{
			HTHEME hTheme = OpenThemeData(hWnd, L"BUTTON");
			int Len = GetWindowTextLength(hWnd) + 1;
			HDC hdc = GetDC(hWnd);
			HFONT hOldFont = (HFONT)SelectObject(hdc, dat->hFont);
			RECT rcText = { 0 };
			if (hTheme) {
				WCHAR *szText = (WCHAR*)_alloca(Len * sizeof(WCHAR));
				GetWindowTextW(hWnd, szText, Len);
				GetThemeTextExtent(hTheme, hdc, BP_GROUPBOX, IsWindowEnabled(hWnd) ? GBS_NORMAL : GBS_DISABLED, szText, -1, DT_CALCRECT | DT_LEFT | DT_VCENTER | DT_SINGLELINE, nullptr, &rcText);
			}
			else {
				SIZE size;
				wchar_t *szText = (wchar_t*)_alloca(Len * sizeof(wchar_t));
				GetWindowText(hWnd, szText, Len);
				GetTextExtentPoint32(hdc, szText, (int)mir_wstrlen(szText), &size);
				rcText.right = size.cx;
				rcText.bottom = size.cy;
			}

			SelectObject(hdc, hOldFont);
			ReleaseDC(hWnd, hdc);
			if (hTheme)
				CloseThemeData(hTheme);

			OffsetRect(&rcText, CG_CHECKBOX_INDENT + CG_CHECKBOX_WIDTH + CG_TEXT_INDENT, 0);
			RECT rc;
			GetClientRect(hWnd, &rc);
			SetWindowPos(hWnd, nullptr, 0, 0, rcText.right + CG_ADDITIONAL_WIDTH, rc.bottom, SWP_NOMOVE | SWP_NOZORDER);
		}
		break;

	case BM_CLICK:
		SendMessage(hWnd, WM_LBUTTONDOWN, 0, 0);
		SendMessage(hWnd, WM_LBUTTONUP, 0, 0);
		return 0;

	case BM_GETCHECK:
		return dat->State & CGSM_ISCHECKED;

	case BM_SETCHECK:
		if ((wParam != BST_UNCHECKED && wParam != BST_CHECKED && wParam != BST_INDETERMINATE) || (wParam == BST_INDETERMINATE && dat->Style != BS_3STATE && dat->Style != BS_AUTO3STATE))
			wParam = BST_CHECKED;
		dat->State &= ~CGSM_ISCHECKED;
		dat->State |= wParam;
		InvalidateRect(hWnd, nullptr, false);
		SendMessage(GetParent(hWnd), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(hWnd), BN_CLICKED), (LPARAM)hWnd);
		return 0;

	case BM_SETSTATE:
		if (wParam)
			dat->State |= CGS_PRESSED;
		else
			dat->State &= ~CGS_PRESSED;
		InvalidateRect(hWnd, nullptr, false);
		return 0;

	case BM_GETSTATE:
		return (dat->State & CGSM_GETSTATE) | ((GetFocus() == hWnd) ? BST_FOCUS : 0);

	case WM_GETDLGCODE:
		return DLGC_BUTTON;

	case WM_THEMECHANGED:
	case WM_ENABLE:
		InvalidateRect(hWnd, nullptr, false);
		return 0;

	case WM_SETTEXT:
		if (CallWindowProc(dat->OldWndProc, hWnd, Msg, wParam, lParam))
			SendMessage(hWnd, UM_AUTOSIZE, 0, 0);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
			SendMessage(hWnd, BM_SETSTATE, true, 0);
		return 0;

	case WM_KEYUP:
		if (wParam == VK_SPACE) {
			SendMessage(hWnd, BM_SETCHECK, (SendMessage(hWnd, BM_GETCHECK, 0, 0) + 1) % ((dat->Style == BS_AUTO3STATE) ? 3 : 2), 0);
			SendMessage(hWnd, BM_SETSTATE, false, 0);
		}
		return 0;

	case WM_CAPTURECHANGED:
		SendMessage(hWnd, BM_SETSTATE, false, 0);
		return 0;

	case WM_ERASEBKGND:
		return true;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		SetFocus(hWnd);
		SendMessage(hWnd, BM_SETSTATE, true, 0);
		SetCapture(hWnd);
		return 0;

	case WM_LBUTTONUP:
		if (GetCapture() == hWnd)
			ReleaseCapture();

		SendMessage(hWnd, BM_SETSTATE, false, 0);
		if (dat->State & CGS_HOVERED && (dat->Style == BS_AUTOCHECKBOX || dat->Style == BS_AUTO3STATE))
			SendMessage(hWnd, BM_SETCHECK, (SendMessage(hWnd, BM_GETCHECK, 0, 0) + 1) % ((dat->Style == BS_AUTO3STATE) ? 3 : 2), 0);
		return 0;

	case WM_MOUSEMOVE:
		{
			TRACKMOUSEEVENT tme = { 0 };
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = HOVER_DEFAULT;
			tme.hwndTrack = hWnd;
			_TrackMouseEvent(&tme);
		}

		POINT pt;
		GetCursorPos(&pt);
		if ((WindowFromPoint(pt) == hWnd) ^ ((dat->State & CGS_HOVERED) != 0)) {
			dat->State ^= CGS_HOVERED;
			InvalidateRect(hWnd, nullptr, false);
		}
		return 0;

	case WM_MOUSELEAVE:
		if (dat->State & CGS_HOVERED) {
			dat->State &= ~CGS_HOVERED;
			InvalidateRect(hWnd, nullptr, false);
		}
		return 0;

	case WM_SETFOCUS:
	case WM_KILLFOCUS:
	case WM_SYSCOLORCHANGE:
		InvalidateRect(hWnd, nullptr, false);
		return 0;

	case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			hdc = BeginPaint(hWnd, &ps);
			RECT rc;
			GetClientRect(hWnd, &rc);
			HDC hdcMem = CreateCompatibleDC(hdc);
			HBITMAP hbmMem = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
			HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);
			HTHEME hTheme = OpenThemeData(hWnd, L"BUTTON");
			if (hTheme)
				DrawThemeParentBackground(hWnd, hdcMem, nullptr);
			else
				FillRect(hdcMem, &rc, GetSysColorBrush(COLOR_3DFACE));

			int StateID = 0;
			switch (SendMessage(hWnd, BM_GETCHECK, 0, 0)) {
			case BST_CHECKED:
				StateID += CBSCHECK_CHECKED;
				break;
			case BST_UNCHECKED:
				StateID += CBSCHECK_UNCHECKED;
				break;
			case BST_INDETERMINATE:
				StateID += CBSCHECK_MIXED;
				break;
			}
			if (!IsWindowEnabled(hWnd))
				StateID += CBSSTATE_DISABLED;
			else if (dat->State & CGS_PRESSED && (GetCapture() != hWnd || dat->State & CGS_HOVERED))
				StateID += CBSSTATE_PRESSED;
			else if (dat->State & CGS_PRESSED || dat->State & CGS_HOVERED)
				StateID += CBSSTATE_HOT;

			rc.left += CG_CHECKBOX_INDENT;
			rc.right = rc.left + CG_CHECKBOX_WIDTH; // left-align the image in the client area
			rc.top += CG_CHECKBOX_VERTINDENT;
			rc.bottom = rc.top + CG_CHECKBOX_WIDTH; // exact rc dimensions are necessary for DrawFrameControl to draw correctly
			if (hTheme)
				DrawThemeBackground(hTheme, hdcMem, BP_CHECKBOX, StateID, &rc, &rc);
			else {
				int dfcStates[] =
				{ 0, 0, DFCS_PUSHED, DFCS_INACTIVE,
				DFCS_CHECKED, DFCS_CHECKED, DFCS_CHECKED | DFCS_PUSHED, DFCS_CHECKED | DFCS_INACTIVE,
				DFCS_BUTTON3STATE | DFCS_CHECKED, DFCS_BUTTON3STATE | DFCS_CHECKED, DFCS_BUTTON3STATE | DFCS_INACTIVE | DFCS_CHECKED | DFCS_PUSHED, DFCS_BUTTON3STATE | DFCS_INACTIVE | DFCS_CHECKED | DFCS_PUSHED };
				_ASSERT(StateID >= 1 && StateID <= _countof(dfcStates));
				DrawFrameControl(hdcMem, &rc, DFC_BUTTON, dfcStates[StateID - 1]);
			}

			GetClientRect(hWnd, &rc);
			rc.left += CG_CHECKBOX_INDENT + CG_CHECKBOX_WIDTH + CG_TEXT_INDENT;

			int Len = GetWindowTextLength(hWnd) + 1;
			wchar_t *szTextT = (wchar_t*)_alloca(Len * sizeof(wchar_t));
			GetWindowText(hWnd, szTextT, Len);

			HFONT hOldFont = (HFONT)SelectObject(hdcMem, dat->hFont);
			SetBkMode(hdcMem, TRANSPARENT);
			if (hTheme)
				DrawThemeText(hTheme, hdcMem, BP_GROUPBOX, IsWindowEnabled(hWnd) ? GBS_NORMAL : GBS_DISABLED, szTextT, -1, DT_LEFT | DT_VCENTER | DT_SINGLELINE, 0, &rc);
			else
				DrawText(hdcMem, szTextT, -1, &rc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

			if (GetFocus() == hWnd) {
				RECT rcText = { 0 };
				if (hTheme)
					GetThemeTextExtent(hTheme, hdcMem, BP_GROUPBOX, IsWindowEnabled(hWnd) ? GBS_NORMAL : GBS_DISABLED, szTextT, -1, DT_CALCRECT | DT_LEFT | DT_VCENTER | DT_SINGLELINE, nullptr, &rcText);
				else {
					SIZE size;
					GetTextExtentPoint32(hdcMem, szTextT, (int)mir_wstrlen(szTextT), &size);
					rcText.right = size.cx;
					rcText.bottom = size.cy;
				}
				rcText.bottom = rc.bottom;
				OffsetRect(&rcText, rc.left, 0);
				InflateRect(&rcText, 1, -1);
				DrawFocusRect(hdcMem, &rcText);
			}
			SelectObject(hdcMem, hOldFont);
			if (hTheme)
				CloseThemeData(hTheme);

			BitBlt(hdc, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, hbmOld);
			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps);
		}
		return 0;

	case WM_DESTROY:
		if (dat->hFont)
			DeleteObject(dat->hFont);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
		CallWindowProc(dat->OldWndProc, hWnd, Msg, wParam, lParam);
		delete dat;
		return 0;
	}
	return CallWindowProc(dat->OldWndProc, hWnd, Msg, wParam, lParam);
}