VDStringW VDGetWindowTextW32(HWND hwnd) {
	union {
		wchar_t w[256];
		char a[512];
	} buf;

	if (VDIsWindowsNT()) {
		int len = GetWindowTextLengthW(hwnd);

		if (len > 255) {
			vdblock<wchar_t> tmp(len + 1);
			len = GetWindowTextW(hwnd, tmp.data(), tmp.size());

			VDStringW text(tmp.data(), len);
			return text;
		} else if (len > 0) {
			len = GetWindowTextW(hwnd, buf.w, 256);

			VDStringW text(buf.w, len);
			return text;
		}
	} else {
		int len = GetWindowTextLengthA(hwnd);

		if (len > 511) {
			vdblock<char> tmp(len + 1);
			len = GetWindowTextA(hwnd, tmp.data(), tmp.size());

			VDStringW text(VDTextAToW(tmp.data(), len));
			return text;
		} else if (len > 0) {
			len = GetWindowTextA(hwnd, buf.a, 512);

			VDStringW text(VDTextAToW(buf.a, len));
			return text;
		}
	}

	return VDStringW();
}