bool GdiPrintContext::swapBuffer()
{
	//if (!isActivated() || isDrawing()) return false;
	if (isDrawing()) return false;
	if (NULL == memBmp_ || NULL == memDC_ || NULL == printDC_) return false;
	setDrawing(true);

	// copy off-screen buffer to window's DC
#if  1
	// method #1: [use DDB & DIB] the image is not scaled to fit the rectangle
	const bool ret = TRUE == BitBlt(
		printDC_,
		drawRegion_.left, drawRegion_.bottom, drawRegion_.getWidth(), drawRegion_.getHeight(), 
		memDC_,
		0, 0,  //drawRegion_.left, drawRegion_.bottom,
		SRCCOPY
	);
#elif 0
	// method #2: [use DDB & DIB] the image is scaled to fit the rectangle
	// caution:
	// all negative coordinate values are ignored.
	// instead, these values are regarded as absolute(positive) values.
	const bool ret = TRUE == StretchBlt(
		printDC_,
		drawRegion_.left, drawRegion_.bottom, drawRegion_.getWidth(), drawRegion_.getHeight(),
		memDC_,
		//(int)std::floor(viewingRegion_.left + 0.5), (int)std::floor(viewingRegion_.bottom + 0.5), (int)std::floor(viewingRegion_.getWidth() + 0.5), (int)std::floor(viewingRegion_.getHeight() + 0.5),
		0, 0, (int)std::floor(viewingRegion_.getWidth() + 0.5), (int)std::floor(viewingRegion_.getHeight() + 0.5),
		SRCCOPY
	);
#else
	// method #3: [use DIB] the image is scaled to fit the rectangle
	// caution:
	// all negative coordinate values are ignored.
	// instead, these values are regarded as absolute(positive) values.
	const bool ret = TRUE == StretchDIBits(
		printDC_,
		drawRegion_.left, drawRegion_.bottom, drawRegion_.getWidth(), drawRegion_.getHeight(),
		//(int)std::floor(viewingRegion_.left + 0.5), (int)std::floor(viewingRegion_.bottom + 0.5), (int)std::floor(viewingRegion_.getWidth() + 0.5), (int)std::floor(viewingRegion_.getHeight() + 0.5),
		0, 0, (int)std::floor(viewingRegion_.getWidth() + 0.5), (int)std::floor(viewingRegion_.getHeight() + 0.5),
		dibBits_,
		&bmiDIB,
		!isPaletteUsed_ ? DIB_RGB_COLORS : DIB_PAL_COLORS,
		SRCCOPY
	);
#endif

	setDrawing(false);
	return ret;
}