LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	static TCHAR szHeading[]	= TEXT("Mapping Mode            Left   Right     Top  Bottom");
	static TCHAR szUndLine[]	= TEXT("------------            ----   -----     ---  ------");
	static int cxChar, cyChar;
	HDC			hdc;
	PAINTSTRUCT	ps;
	TEXTMETRIC	tm;

	switch (message) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));

		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cyChar = tm.tmHeight + tm.tmExternalLeading;

		ReleaseDC(hwnd, hdc);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));

		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, 1, 1, NULL);
		SetViewportExtEx(hdc, cxChar, cyChar, NULL);

		TextOut(hdc, 1, 1, szHeading, lstrlen(szHeading));
		TextOut(hdc, 1, 2, szUndLine, lstrlen(szUndLine));

		Show(hwnd, hdc, 1, 3, MM_TEXT,		TEXT("TEXT (pixels)"));
		Show(hwnd, hdc, 1, 4, MM_LOMETRIC,	TEXT("LOMETRIC (.1mm)"));
		Show(hwnd, hdc, 1, 5, MM_HIMETRIC,	TEXT("HIMETRIC (.01mm)"));
		Show(hwnd, hdc, 1, 6, MM_LOENGLISH,	TEXT("LOENGLISH (.01in)"));
		Show(hwnd, hdc, 1, 7, MM_HIENGLISH,	TEXT("HIENGLISH (.001in)"));
		Show(hwnd, hdc, 1, 8, MM_TWIPS,		TEXT("TWIPs (1/1440in)"));

		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}