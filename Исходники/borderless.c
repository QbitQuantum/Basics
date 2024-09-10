LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg) {
	case WM_CREATE: {
		WINDOWINFO wi;
		wi.cbSize = sizeof(WINDOWINFO);
		GetWindowInfo(hwnd, &wi);
		RECT r;
		r = wi.rcClient;

		btn1 = CreateWindow(L"BUTTON", L"Refresh list", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 2, 2, r.right - r.left - 4, 24, hwnd, NULL, (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
		lb = CreateWindow(L"LISTBOX", NULL, WS_TABSTOP | WS_CHILD | WS_VISIBLE | LBS_STANDARD, 2, 28, r.right - r.left - 4, r.bottom - r.top - 44, hwnd, NULL, (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
		btn2 = CreateWindow(L"BUTTON", L"Make it borderless", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 2, r.bottom - r.top - 26, r.right - r.left - 4, 24, hwnd, NULL, (HINSTANCE) GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

		SendMessage(lb, LB_RESETCONTENT, 0, 0);
		EnumWindows(EnumWindowsProc, 0);

		HFONT f;
		f = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Segoe UI");
		SendMessage(hwnd, WM_SETFONT, (WPARAM) f, TRUE);
		SendMessage(btn1, WM_SETFONT, (WPARAM) f, TRUE);
		SendMessage(btn2, WM_SETFONT, (WPARAM) f, TRUE);

		f = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"Courier New");
		SendMessage(lb, WM_SETFONT, (WPARAM) f, TRUE);
		break;
	}
	case WM_COMMAND:
		if (HIWORD(wp) == BN_CLICKED) {
			if ((HWND) lp == btn1) {
				SendMessage(lb, LB_RESETCONTENT, 0, 0);
				EnumWindows(EnumWindowsProc, 0);
			}
			if ((HWND) lp == btn2) {
				UINT i = (UINT) SendMessage(lb, LB_GETCURSEL, 0, 0);
				LPWSTR x = (LPWSTR) LocalAlloc(LPTR, sizeof(WCHAR) * (UINT) SendMessage(lb, LB_GETTEXTLEN, i, 0));
				SendMessage(lb, LB_GETTEXT, i, (LPARAM) x);
				Borderless(x);
				LocalFree(x);
			}
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return DefWindowProc(hwnd, msg, wp, lp);
	}

	return 0;
}