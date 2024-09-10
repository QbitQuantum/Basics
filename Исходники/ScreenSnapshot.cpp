BOOL ScreenSnapshot::snapshotScreen()
{
	if (m_hMemDC)
	{
		DeleteObject(m_hMemBitmap);
		DeleteDC(m_hMemDC);
		m_hMemBitmap = NULL;
		m_hMemDC = NULL;
	}
	if (m_hBkgMemDC)
	{
		DeleteObject(m_hBkBitmap);
		DeleteDC(m_hBkgMemDC);
		m_hBkBitmap = NULL;
		m_hBkgMemDC = NULL;
	}
	if (m_hDrawMemDC)
	{
		DeleteObject(m_hDrawBitmap);
		DeleteDC(m_hDrawMemDC);
		m_hDrawBitmap = NULL;
		m_hDrawMemDC = NULL;
	}

	//
	HWND hDesktopWnd = GetDesktopWindow();
	HDC hScreenDC = GetDC(hDesktopWnd);

	RECT rc = { 0 };
	GetWindowRect(hDesktopWnd, &rc);
	int cx = rc.right - rc.left;
	int cy = rc.bottom - rc.top;

	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, cx, cy);
	m_hMemDC = CreateCompatibleDC(hScreenDC);
	HGDIOBJ hOldBitmap = SelectObject(m_hMemDC, (HGDIOBJ)hBitmap);
	BitBlt(m_hMemDC, 0, 0, cx, cy, hScreenDC, 0, 0, SRCCOPY);

	m_hBkgMemDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBkgBitmap = CreateCompatibleBitmap(hScreenDC, cx, cy);
	SelectObject(m_hBkgMemDC, (HGDIOBJ)hBkgBitmap);
	BitBlt(m_hBkgMemDC, 0, 0, cx, cy, hScreenDC, 0, 0, SRCCOPY);

	HDC hMaskDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hMaskBitmap = CreateCompatibleBitmap(hScreenDC, cx, cy);
	SelectObject(hMaskDC, (HGDIOBJ)hMaskBitmap);

	BLENDFUNCTION ftn = { AC_SRC_OVER, 0, 100, 0 }; 
	AlphaBlend(m_hBkgMemDC, 0, 0, cx, cy, hMaskDC, 0, 0, cx, cy, ftn);
	DeleteObject(hMaskBitmap);
	DeleteDC(hMaskDC);

	m_hDrawMemDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hDrawBitmap = CreateCompatibleBitmap(hScreenDC, cx, cy);
	SelectObject(m_hDrawMemDC, hDrawBitmap);

	ReleaseDC(hDesktopWnd, hScreenDC);
	return TRUE;
}