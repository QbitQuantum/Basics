bool GdiBitmapBufferedContext::createOffScreen()
{
	if (NULL == hWnd_) return false;

	// get DC for window
	hDC_ = GetDC(hWnd_);
	if (NULL == hDC_) return false;

	// create an off-screen DC for double-buffering
	memDC_ = CreateCompatibleDC(hDC_);
	if (NULL == memDC_)
	{
		ReleaseDC(hWnd_, hDC_);
		hDC_ = NULL;
		return false;
	}

	//
	isPaletteUsed_ = (GetDeviceCaps(memDC_, RASTERCAPS) & RC_PALETTE) == RC_PALETTE;
	assert(false == isPaletteUsed_);

	const int colorBitCount = GetDeviceCaps(memDC_, BITSPIXEL);
	assert(colorBitCount > 8);
	const int colorPlaneCount = GetDeviceCaps(memDC_, PLANES);
	assert(1 == colorPlaneCount);

	// use palette: when using 256 color
	if (isPaletteUsed_) createPalette(memDC_, colorBitCount);

	if (createOffScreenBitmap(colorBitCount, colorPlaneCount))
		return true;
	else
	{
		DeleteDC(memDC_);
		memDC_ = NULL;

		ReleaseDC(hWnd_, hDC_);
		hDC_ = NULL;
		return false;
	}
}