bool CFloodFill2::DrawLineH(int x1, int x2, int y, COLORREF Color, const CRect& Rect)
{
	if (!m_pDib)
		return false;

	if (!m_bRedEye && Color == CLR_NONE)
		return false;

	if (x1 > x2)
		x1^=x2, x2^=x1, x1^=x2;

	if (x1 < 0 && x2 < 0)
		return false;

	LONG nWidth = GetWidth();
	if (x1 >= nWidth && x2 >= nWidth)
		return false;

	if (x1 < 0)
		x1 = 0;

	if (x2 >= nWidth)
		x2 = nWidth - 1;

	int x = x1;
	LPBYTE pPixel = DibPtrXYExact(m_pDib, x1, y);
	LPBYTE pEnd = DibPtrXYExact(m_pDib, x2, y);

	while (pPixel <= pEnd)
	{
		if (m_pBufferDib)
		{
			if (!m_bRedEye)
				Color = m_pBufferDib->GetPixel(x++, y);
			else
			{
				Color = GetPixel(x++, y); 
				RedEyeRemove(Color);
			}
		}

		*pPixel++ = GetBValue(Color);
		*pPixel++ = GetGValue(Color);
		*pPixel++ = GetRValue(Color);
	}

	return true;
}