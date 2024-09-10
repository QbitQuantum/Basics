void WINLcdFlip::updateWindow(void)
{
// フリップしているので、普通の転送は不可

	int x, y;
	unsigned char const *p;

	int realHeight;
	int realWidth;

	realHeight = cmlcd->getRealHeight240();
	realWidth  = cmlcd->getRealWidth320();

	for(y=0; y < realHeight; y++)
	{
		p = cmlcd->getCMLcdFunc()->getPixelArray(0, y);

		for(x=0; x < realWidth; x++, p++)
		{
	//			*(dibData + (realWidth - 1 - x) * byte_per_line + (realHeight - 1 - y)) = *p;
			*(dibData + x * byte_per_line + (realHeight - 1 - y)) = *p;
		}
	}

	GdiFlush();
	BitBlt(hDC_wnd, 0, 0, realHeight, realWidth, hDC, 0, 0, SRCCOPY);

}