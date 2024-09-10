// Create a monochrome mask bitmap from a source DC
BOOL KDDBMask::Create(HDC hDC, int nX, int nY, int nWidth, int nHeight, UINT crTransparent)
{
	Release();

	RECT rect = { nX, nY, nX + nWidth, nY + nHeight };
	LPtoDP(hDC, (POINT *) & rect, 2);								  
	
	m_nMaskWidth  = abs(rect.right - rect.left);
	m_nMaskHeight = abs(rect.bottom - rect.top);					  // get real size

	m_hMemDC = CreateCompatibleDC(hDC);
	m_hMask  = CreateBitmap(m_nMaskWidth, m_nMaskHeight, 1, 1, NULL); // monochrome bitmap
	m_hOld   = (HBITMAP) SelectObject(m_hMemDC, m_hMask);

	COLORREF oldBk = SetBkColor(hDC, crTransparent);	// map crTransparent to 1, white
	BOOL rslt = StretchBlt(m_hMemDC, 0, 0, m_nMaskWidth, m_nMaskHeight, hDC, nX, nY, nWidth, nHeight, SRCCOPY);
	SetBkColor(hDC, oldBk);

	return rslt;
}