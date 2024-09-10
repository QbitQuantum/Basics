void VDUIHotKeyExControlW32::OnPaint() {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(mhwnd, &ps);
	if (!hdc)
		return;

	RECT r;
	if (GetClientRect(mhwnd, &r)) {
		VDVERIFY(DrawEdge(hdc, &r, EDGE_SUNKEN, BF_ADJUST | BF_RECT));
		VDVERIFY(FillRect(hdc, &r, (HBRUSH)(COLOR_WINDOW + 1)));

		int cx = GetSystemMetrics(SM_CXEDGE);
		int cy = GetSystemMetrics(SM_CYEDGE);

		r.left += cx;
		r.top += cy;
		r.right -= cx;
		r.bottom -= cy;

		if (r.right > r.left && r.bottom > r.top) {
			SetBkColor(hdc, GetSysColor(COLOR_WINDOW));
			SetTextColor(hdc, GetSysColor(COLOR_BTNTEXT));
			SetTextAlign(hdc, TA_TOP | TA_LEFT);

			HGDIOBJ holdFont = SelectObject(hdc, mhfont);
			if (holdFont) {
				ExtTextOutW(hdc, r.left, r.top, ETO_CLIPPED, &r, mBuffer.c_str(), mBuffer.size(), NULL);
				SelectObject(hdc, holdFont);
			}
		}
	}

	EndPaint(mhwnd, &ps);
}