bool CBitmap::setPalette(int startColor, int numColors, RGBQUAD *colors)
{	
	// If the CBitmap is not an 8-bit bitmap, CAN NOT set palette
	if(mChannels != 1)
		return false;

	// Returns 0 on failure, number of entries set on success
	if(SetDIBColorTable(mHDC, startColor, numColors, colors))
		return true;
	else
		return false;
}