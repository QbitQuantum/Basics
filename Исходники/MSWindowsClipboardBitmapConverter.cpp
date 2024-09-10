String
MSWindowsClipboardBitmapConverter::toIClipboard(HANDLE data) const
{
	// get datator
	const char* src = (const char*)GlobalLock(data);
	if (src == NULL) {
		return String();
	}
	UInt32 srcSize = (UInt32)GlobalSize(data);

	// check image type
	const BITMAPINFO* bitmap = reinterpret_cast<const BITMAPINFO*>(src);
	LOG((CLOG_INFO "bitmap: %dx%d %d", bitmap->bmiHeader.biWidth, bitmap->bmiHeader.biHeight, (int)bitmap->bmiHeader.biBitCount));
	if (bitmap->bmiHeader.biPlanes == 1 &&
		(bitmap->bmiHeader.biBitCount == 24 ||
		bitmap->bmiHeader.biBitCount == 32) &&
		bitmap->bmiHeader.biCompression == BI_RGB) {
		// already in canonical form
		String image(src, srcSize);
		GlobalUnlock(data);
		return image;
	}

	// create a destination DIB section
	LOG((CLOG_INFO "convert image from: depth=%d comp=%d", bitmap->bmiHeader.biBitCount, bitmap->bmiHeader.biCompression));
	void* raw;
	BITMAPINFOHEADER info;
	LONG w               = bitmap->bmiHeader.biWidth;
	LONG h               = bitmap->bmiHeader.biHeight;
	info.biSize          = sizeof(BITMAPINFOHEADER);
	info.biWidth         = w;
	info.biHeight        = h;
	info.biPlanes        = 1;
	info.biBitCount      = 32;
	info.biCompression   = BI_RGB;
	info.biSizeImage     = 0;
	info.biXPelsPerMeter = 1000;
	info.biYPelsPerMeter = 1000;
	info.biClrUsed       = 0;
	info.biClrImportant  = 0;
	HDC dc      = GetDC(NULL);
	HBITMAP dst = CreateDIBSection(dc, (BITMAPINFO*)&info,
							DIB_RGB_COLORS, &raw, NULL, 0);

	// find the start of the pixel data
	const char* srcBits = (const char*)bitmap + bitmap->bmiHeader.biSize;
	if (bitmap->bmiHeader.biBitCount >= 16) {
		if (bitmap->bmiHeader.biCompression == BI_BITFIELDS &&
			(bitmap->bmiHeader.biBitCount == 16 ||
			bitmap->bmiHeader.biBitCount == 32)) {
			srcBits += 3 * sizeof(DWORD);
		}
	}
	else if (bitmap->bmiHeader.biClrUsed != 0) {
		srcBits += bitmap->bmiHeader.biClrUsed * sizeof(RGBQUAD);
	}
	else {
		//http://msdn.microsoft.com/en-us/library/ke55d167(VS.80).aspx
		srcBits += (1i64 << bitmap->bmiHeader.biBitCount) * sizeof(RGBQUAD);
	}

	// copy source image to destination image
	HDC dstDC         = CreateCompatibleDC(dc);
	HGDIOBJ oldBitmap = SelectObject(dstDC, dst);
	SetDIBitsToDevice(dstDC, 0, 0, w, h, 0, 0, 0, h,
							srcBits, bitmap, DIB_RGB_COLORS);
	SelectObject(dstDC, oldBitmap);
	DeleteDC(dstDC);
	GdiFlush();

	// extract data
	String image((const char*)&info, info.biSize);
	image.append((const char*)raw, 4 * w * h);

	// clean up GDI
	DeleteObject(dst);
	ReleaseDC(NULL, dc);

	// release handle
	GlobalUnlock(data);

	return image;
}