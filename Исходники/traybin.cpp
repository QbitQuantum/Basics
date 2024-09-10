HICON CreateTimeIcon(SYSTEMTIME* time) {
	WORD matrix[][2] = { {10, 10}, {10, 5}, {10, 0}, {5, 10}, {5, 5}, {5, 0}, {0, 10}, {0, 5}, {0, 0} };
	HDC hdc0, hdc1;
	HGDIOBJ undo;
	HBITMAP bmp, mask;
	HICON ret;
	ICONINFO ii = {TRUE};
	HBRUSH brush0, brush1;
	RECT rect;
	WORD x;

	brush0 = CreateSolidBrush(RGB(0, 0, 0));
	brush1 = CreateSolidBrush(RGB(255, 255, 255));

	hdc0 = GetDC(NULL);
	bmp = CreateCompatibleBitmap(hdc0, 16, 16);
	mask = CreateCompatibleBitmap(hdc0, 16, 16);
	hdc1 = CreateCompatibleDC(hdc0);

	rect.left = 0; rect.top = 0; rect.right = 16; rect.bottom = 16;
	undo = SelectObject(hdc1, mask); FillRect(hdc1, &rect, brush1);

	x = time->wMinute + (time->wHour % 6 << 6);
	for (int i = 0; i < 9; i++, x /= 2) {
		if (x % 2) {
			rect.left = matrix[i][0]; rect.top = matrix[i][1]; rect.right = rect.left + 6; rect.bottom = rect.top + 6;
			SelectObject(hdc1, mask); FillRect(hdc1, &rect, brush0);
			rect.left++; rect.top++; rect.right--; rect.bottom--;
			SelectObject(hdc1, bmp); FillRect(hdc1, &rect, brush1);
		}
	}

	ReleaseDC(NULL, hdc0);
	SelectObject(hdc1, undo); DeleteDC(hdc1);
	DeleteObject(brush0);
	DeleteObject(brush1);

	ii.hbmColor = bmp;
	ii.hbmMask = mask;
	ret = CreateIconIndirect(&ii);

	DeleteObject(bmp);
	DeleteObject(mask);
	return ret;
}