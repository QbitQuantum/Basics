BOOL fipWinImage::captureWindow(HWND hWndApplicationWindow, HWND hWndSelectedWindow) {
	int xScreen, yScreen, xshift, yshift;
	RECT r;

	// Get window size
	GetWindowRect(hWndSelectedWindow, &r);

	// Check if the window is out of the screen or maximixed
	xshift = 0;
	yshift = 0;
	xScreen = GetSystemMetrics(SM_CXSCREEN);
	yScreen = GetSystemMetrics(SM_CYSCREEN);
	if(r.right > xScreen)
		   r.right = xScreen;
	if(r.bottom > yScreen)
		   r.bottom = yScreen;
	if(r.left < 0) {
		   xshift = -r.left;
		   r.left = 0;
	}
	if(r.top < 0){
		   yshift = -r.top;
		   r.top = 0;
	}
	
	int width  = r.right  - r.left;
	int height = r.bottom - r.top;

	if(width <= 0 || height <= 0)
		return FALSE;

	// Hide the application window. 
	ShowWindow(hWndApplicationWindow, SW_HIDE); 
	// Bring the window at the top most level
	SetWindowPos(hWndSelectedWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	// Give enough time to refresh the window
	Sleep(500);

	// Prepare the DCs
	HDC dstDC = GetDC(NULL);
    HDC srcDC = GetWindowDC(hWndSelectedWindow); // full window (GetDC(hWndSelectedWindow) = clientarea)
	HDC memDC = CreateCompatibleDC(dstDC);
	
	// Copy the screen to the bitmap
	HBITMAP bm = CreateCompatibleBitmap(dstDC, width, height);
	HBITMAP oldbm = (HBITMAP)SelectObject(memDC, bm);
	BitBlt(memDC, 0, 0, width, height, srcDC, xshift, yshift, SRCCOPY);

	// Redraw the application window. 
	ShowWindow(hWndApplicationWindow, SW_SHOW); 

	// Restore the position
	SetWindowPos(hWndSelectedWindow, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	SetWindowPos(hWndApplicationWindow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	
	// Convert the HBITMAP to a FIBITMAP
	copyFromBitmap(bm);

	// Free objects
	DeleteObject(SelectObject(memDC, oldbm));
	DeleteDC(memDC);

	// Convert 32-bit images to 24-bit
	if(getBitsPerPixel() == 32) {
		convertTo24Bits();
	}

	return TRUE;
}