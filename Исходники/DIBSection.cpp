// Copy from DIB's color table to DIB section's color table
UINT KDIBSection::SetColorTable(void)
{
	int width, height;

	if ( (GetDepth()>8) || ! Prepare(width, height) ) // create memory DC
		return 0;

	return SetDIBColorTable(m_hMemDC, 0, m_nClrUsed, m_pRGBQUAD);
}