LRESULT CALLBACK
WndPauseProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	TEXTMETRIC tm;
	LPPW lppw;
	int cxChar, cyChar, middle;

	lppw = (LPPW)GetWindowLongPtr(hwnd, 0);

	switch(message) {
		case WM_KEYDOWN:
			if (wParam == VK_RETURN)
				SendMessage(hwnd, WM_COMMAND, lppw->bDefOK ? IDOK : IDCANCEL, 0L);
			else if (wParam == VK_ESCAPE)
				SendMessage(hwnd, WM_COMMAND, IDCANCEL, 0L);
			return 0;
		case WM_COMMAND:
			if ((LOWORD(wParam) == IDCANCEL) || (LOWORD(wParam) == IDOK)) {
				lppw->bPauseCancel = LOWORD(wParam);
				lppw->bPause = FALSE;
				break;
			}
			return 0;
		case WM_SETFOCUS:
			SetFocus(lppw->bDefOK ? lppw->hOK : lppw->hCancel);
			return 0;
		case WM_PAINT: {
			hdc = BeginPaint(hwnd, &ps);
			SelectObject(hdc, GetStockObject(SYSTEM_FONT));
			SetTextAlign(hdc, TA_CENTER);
			GetClientRect(hwnd, &rect);
			SetBkMode(hdc,TRANSPARENT);
			TextOut(hdc, (rect.right + rect.left) / 2, (rect.bottom + rect.top) / 6,
				lppw->Message, strlen(lppw->Message));
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_CREATE: {
			int ws_opts = WS_CHILD | WS_TABSTOP;

#ifdef USE_MOUSE
			if (!paused_for_mouse) /* don't show buttons during pausing for mouse or key */
				ws_opts |= WS_VISIBLE;
#endif
			lppw = (LPPW) ((CREATESTRUCT *)lParam)->lpCreateParams;
			SetWindowLongPtr(hwnd, 0, (LONG_PTR)lppw);
			lppw->hWndPause = hwnd;
			hdc = GetDC(hwnd);
			SelectObject(hdc, GetStockObject(SYSTEM_FONT));
			GetTextMetrics(hdc, &tm);
			cxChar = tm.tmAveCharWidth;
			cyChar = tm.tmHeight + tm.tmExternalLeading;
			ReleaseDC(hwnd, hdc);
			middle = ((LPCREATESTRUCT) lParam)->cx / 2;
			lppw->hOK = CreateWindow((LPSTR)"button", (LPSTR)"OK",
					ws_opts | BS_DEFPUSHBUTTON,
					middle - 10 * cxChar, 3 * cyChar,
					8 * cxChar, 7 * cyChar / 4,
					hwnd, (HMENU)IDOK,
					((LPCREATESTRUCT) lParam)->hInstance, NULL);
			lppw->bDefOK = TRUE;
			lppw->hCancel = CreateWindow((LPSTR)"button", (LPSTR)"Cancel",
					ws_opts | BS_PUSHBUTTON,
					middle + 2 * cxChar, 3 * cyChar,
					8 * cxChar, 7 * cyChar / 4,
					hwnd, (HMENU)IDCANCEL,
					((LPCREATESTRUCT) lParam)->hInstance, NULL);
			lppw->lpfnOK = (WNDPROC) GetWindowLongPtr(lppw->hOK, GWLP_WNDPROC);
			SetWindowLongPtr(lppw->hOK, GWLP_WNDPROC, (LONG_PTR)PauseButtonProc);
			lppw->lpfnCancel = (WNDPROC) GetWindowLongPtr(lppw->hCancel, GWLP_WNDPROC);
			SetWindowLongPtr(lppw->hCancel, GWLP_WNDPROC, (LONG_PTR)PauseButtonProc);
			if (GetParent(hwnd))
				EnableWindow(GetParent(hwnd), FALSE);
			return 0;
		}
		case WM_DESTROY:
			GetWindowRect(hwnd, &rect);
			lppw->Origin.x = (rect.right + rect.left) / 2;
			lppw->Origin.y = (rect.bottom + rect.top) / 2;
			lppw->bPause = FALSE;
			if (GetParent(hwnd))
				EnableWindow(GetParent(hwnd), TRUE);
			break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}