LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BOOL    bCapturing, bBlocking;
	static HBITMAP hBitmap;
	static HWND    hwndScr;
	static POINT   ptBeg, ptEnd;
	BITMAP         bm;
	HBITMAP        hBitmapClip;
	HDC            hdc, hdcMem;
	int            iEnable;
	PAINTSTRUCT    ps;
	RECT           rect;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		if (!bCapturing)
		{
			if (LockWindowUpdate(hwndScr = GetDesktopWindow()))
			{
				bCapturing = TRUE;
				SetCapture(hwnd);
				SetCursor(LoadCursor(NULL, IDC_CROSS));
			}
			else
				MessageBeep(0);
		}
		return 0;

	case WM_RBUTTONDOWN:
		if (bCapturing)
		{
			bBlocking = TRUE;
			ptBeg.x = LOWORD(lParam);
			ptBeg.y = HIWORD(lParam);
			ptEnd = ptBeg;
			InvertBlock(hwndScr, hwnd, ptBeg, ptEnd);
		}
		return 0;

	case WM_MOUSEMOVE:
		if (bBlocking)
		{
			InvertBlock(hwndScr, hwnd, ptBeg, ptEnd);
			ptEnd.x = LOWORD(lParam);
			ptEnd.y = HIWORD(lParam);
			InvertBlock(hwndScr, hwnd, ptBeg, ptEnd);
		}
		return 0;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		if (bBlocking)
		{
			InvertBlock(hwndScr, hwnd, ptBeg, ptEnd);
			ptEnd.x = LOWORD(lParam);
			ptEnd.y = HIWORD(lParam);

			if (hBitmap)
			{
				DeleteObject(hBitmap);
				hBitmap = NULL;
			}

			hdc = GetDC(hwnd);
			hdcMem = CreateCompatibleDC(hdc);
			hBitmap = CreateCompatibleBitmap(hdc,
				abs(ptEnd.x - ptBeg.x),
				abs(ptEnd.y - ptBeg.y));

			SelectObject(hdcMem, hBitmap);

			StretchBlt(hdcMem, 0, 0, abs(ptEnd.x - ptBeg.x),
				abs(ptEnd.y - ptBeg.y),
				hdc, ptBeg.x, ptBeg.y, ptEnd.x - ptBeg.x,
				ptEnd.y - ptBeg.y, SRCCOPY);

			DeleteDC(hdcMem);
			ReleaseDC(hwnd, hdc);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (bBlocking || bCapturing)
		{
			bBlocking = bCapturing = FALSE;
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			ReleaseCapture();
			LockWindowUpdate(NULL);
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		if (hBitmap)
		{
			GetClientRect(hwnd, &rect);

			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof (BITMAP), (PSTR)&bm);
			SetStretchBltMode(hdc, COLORONCOLOR);

			StretchBlt(hdc, 0, 0, rect.right, rect.bottom,
				hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

			DeleteDC(hdcMem);
		}
		EndPaint(hwnd, &ps);
		return 0;

	case WM_DESTROY:
		if (hBitmap)
			DeleteObject(hBitmap);

		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}