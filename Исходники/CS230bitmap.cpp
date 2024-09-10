void SetPalette(CSBitmap* pBitmap, int StartColor, int NumColors, RGBQUAD* pColors)
{
	assert(HasBitmap(pBitmap));
	assert(GetChannels(pBitmap) == 1);
	assert(StartColor >= 0);
	assert(StartColor + NumColors <= 256);
	SetDIBColorTable(GetDrawSurface(pBitmap), StartColor, NumColors, pColors);
}