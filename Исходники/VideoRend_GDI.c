// Video initialize
int VideoRend_GDI_Init(HWND hWnd, int width, int height, int fullscreen)
{
	BITMAPINFO BitmapInfo;
	RECT fsRect;

	// Bitmap Structure
	BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
	BitmapInfo.bmiHeader.biWidth = width;
	BitmapInfo.bmiHeader.biHeight = -height;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32;
	BitmapInfo.bmiHeader.biCompression = BI_RGB;
	BitmapInfo.bmiHeader.biSizeImage = 0;
	BitmapInfo.bmiHeader.biXPelsPerMeter = 96;
	BitmapInfo.bmiHeader.biYPelsPerMeter = 96;
	BitmapInfo.bmiHeader.biClrUsed = 0;
	BitmapInfo.bmiHeader.biClrImportant = 0;
	RendHDC[0] = CreateCompatibleDC(NULL);
	RendHDC[1] = CreateCompatibleDC(NULL);
	if (!RendHDC[0] || !RendHDC[1]) {
		MessageBox(0, "Can't create compatible DC", "GDI Video", MB_OK | MB_ICONERROR);
		VideoRend_GDI_Terminate();
		return 0;
	}

	// Create DIB Bitmap
	RendImgWidth = width;
	RendImgHeight = height;
	RendBitmap[0] = CreateDIBSection(RendHDC[0], &BitmapInfo, DIB_RGB_COLORS, (void **)&RendVideoBuff[0], NULL, 0);
	RendBitmap[1] = CreateDIBSection(RendHDC[1], &BitmapInfo, DIB_RGB_COLORS, (void **)&RendVideoBuff[1], NULL, 0);
	if (!RendBitmap[0] || !RendBitmap[1]) {
		MessageBox(0, "Can't create bitmap", "GDI Video", MB_OK | MB_ICONERROR);
		VideoRend_GDI_Terminate();
		return 0;
	}

	// Assign DIB Bitmap into the device
	GdiFlush();
	SelectObject(RendHDC[0], RendBitmap[0]);
	SelectObject(RendHDC[1], RendBitmap[1]);

	// Fullscreen
	if (fullscreen) {
		GetWindowRect(GetDesktopWindow(), &fsRect);
		MoveWindow(hWnd, 0, 0, fsRect.right, fsRect.bottom, 0);
	}

	// Clear the image
	RendFrame = 0;
	RendWasInit = 1;
	VideoRend_GDI_ClearVideo();
	VideoRend_GDI_Flip(hWnd);
	VideoRend_GDI_ClearVideo();

	return 32;
}