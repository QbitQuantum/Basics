void setPixel(int x, int y, COLORREF color, HWND sHwnd) {
	HDC hdc = GetDC(sHwnd);
	SetPixel(hdc, x, y, color);
	ReleaseDC(sHwnd, hdc);
	return;
}