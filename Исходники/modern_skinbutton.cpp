static LRESULT CALLBACK ModernSkinButtonWndProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ModernSkinButtonCtrl* bct = (msg != WM_NCCREATE) ? (ModernSkinButtonCtrl *)GetWindowLongPtr(hwndDlg, GWLP_USERDATA) : nullptr;
	if (bct) {
		if (bct->HandleService && IsBadStringPtrA(bct->HandleService, 255))
			bct->HandleService = nullptr;
		else if (bct->HandleService && ServiceExists(bct->HandleService)) {
			HandleServiceParams MSG = {};
			MSG.hwnd = hwndDlg;
			MSG.msg = msg;
			MSG.wParam = wParam;
			MSG.lParam = lParam;
			int t = CallService(bct->HandleService, (WPARAM)&MSG, 0);
			if (MSG.handled) return t;
		}
	}

	switch (msg) {
	case WM_NCCREATE:
		SetWindowLongPtr(hwndDlg, GWL_STYLE, GetWindowLongPtr(hwndDlg, GWL_STYLE) | BS_OWNERDRAW);
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, 0);
		if (((CREATESTRUCT *)lParam)->lpszName) SetWindowText(hwndDlg, ((CREATESTRUCT *)lParam)->lpszName);
		return TRUE;

	case WM_DESTROY:
		if (bct == nullptr)
			break;

		if (hwndToolTips) {
			mir_cslock lck(csTips);
			TOOLINFO ti = { 0 };
			ti.cbSize = sizeof(ti);
			ti.uFlags = TTF_IDISHWND;
			ti.hwnd = bct->hwnd;
			ti.uId = (UINT_PTR)bct->hwnd;
			if (SendMessage(hwndToolTips, TTM_GETTOOLINFO, 0, (LPARAM)&ti))
				SendMessage(hwndToolTips, TTM_DELTOOL, 0, (LPARAM)&ti);

			if (SendMessage(hwndToolTips, TTM_GETTOOLCOUNT, 0, (LPARAM)&ti) == 0) {
				DestroyWindow(hwndToolTips);
				hwndToolTips = nullptr;
			}
		}
		mir_free(bct->ID);
		mir_free(bct->CommandService);
		mir_free(bct->StateService);
		mir_free(bct->HandleService);
		mir_free(bct->Hint);
		mir_free(bct->ValueDBSection);
		mir_free(bct->ValueTypeDef);
		mir_free(bct);
		SetWindowLongPtr(hwndDlg, GWLP_USERDATA, 0);
		break;	// DONT! fall thru

	case WM_SETCURSOR:
		{
			HCURSOR hCurs1 = LoadCursor(nullptr, IDC_ARROW);
			if (hCurs1) SetCursor(hCurs1);
			if (bct) SetToolTip(hwndDlg, bct->Hint);
		}
		return 1;

	case WM_PRINT:
		if (IsWindowVisible(hwndDlg))
			ModernSkinButtonPaintWorker(hwndDlg, (HDC)wParam);
		break;

	case WM_PAINT:
		if (IsWindowVisible(hwndDlg) && !g_CluiData.fLayered) {
			PAINTSTRUCT ps = {};
			BeginPaint(hwndDlg, &ps);
			ModernSkinButtonPaintWorker(hwndDlg, (HDC)ps.hdc);
			EndPaint(hwndDlg, &ps);
		}
		return DefWindowProc(hwndDlg, msg, wParam, lParam);

	case WM_CAPTURECHANGED:
		if (bct) {
			bct->hover = 0;
			bct->down = 0;
			ModernSkinButtonPaintWorker(bct->hwnd, nullptr);
		}
		break;

	case WM_MOUSEMOVE:
		if (bct) {
			if (!bct->hover) {
				SetCapture(bct->hwnd);
				bct->hover = 1;
				ModernSkinButtonPaintWorker(bct->hwnd, nullptr);
			}
			else {
				POINT t = UNPACK_POINT(lParam);
				ClientToScreen(bct->hwnd, &t);
				if (WindowFromPoint(t) != bct->hwnd)
					ReleaseCapture();
			}
		}
		return 0;

	case WM_LBUTTONDOWN:
		if (bct) {
			bct->down = 1;
			SetForegroundWindow(GetParent(bct->hwnd));
			ModernSkinButtonPaintWorker(bct->hwnd, nullptr);
			if (bct->CommandService && IsBadStringPtrA(bct->CommandService, 255))
				bct->CommandService = nullptr;
			if (bct->fCallOnPress) {
				if (bct->CommandService) {
					if (!_CallServiceStrParams(bct->CommandService, nullptr) && (bct->ValueDBSection && bct->ValueTypeDef))
						ModernSkinButtonToggleDBValue(bct->ValueDBSection, bct->ValueTypeDef);
				}
				bct->down = 0;

				ModernSkinButtonPaintWorker(bct->hwnd, nullptr);
			}
		}
		return 0;

	case WM_LBUTTONUP:
		if (bct && bct->down) {
			ReleaseCapture();
			bct->hover = 0;
			bct->down = 0;
			ModernSkinButtonPaintWorker(bct->hwnd, nullptr);
			if (bct->CommandService && IsBadStringPtrA(bct->CommandService, 255))
				bct->CommandService = nullptr;
			if (bct->CommandService)
				if (_CallServiceStrParams(bct->CommandService, nullptr)) {
				}
				else if (bct->ValueDBSection && bct->ValueTypeDef)
					ModernSkinButtonToggleDBValue(bct->ValueDBSection, bct->ValueTypeDef);
		}
	}
	return DefWindowProc(hwndDlg, msg, wParam, lParam);
}