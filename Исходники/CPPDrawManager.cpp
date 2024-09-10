void CPPDrawManager::AlphaBitBlt(HDC hDestDC, int nDestX, int nDestY, DWORD dwWidth, DWORD dwHeight, HDC hSrcDC, int nSrcX, int nSrcY, int percent /* = 100 */)
{
	_ASSERT ((NULL != hDestDC) || (NULL != hSrcDC));

	if (percent >= 100)
	{
		::BitBlt(hDestDC, nDestX, nDestY, dwWidth, dwHeight, hSrcDC, nSrcX, nSrcY, SRCCOPY);
		return;
	} //if

	HDC hTempDC = ::CreateCompatibleDC(hDestDC);
	if (NULL == hTempDC)
		return;
	
	//Creates Source DIB
	LPBITMAPINFO lpbiSrc;
	// Fill in the BITMAPINFOHEADER
	lpbiSrc = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
	lpbiSrc->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpbiSrc->bmiHeader.biWidth = dwWidth;
	lpbiSrc->bmiHeader.biHeight = dwHeight;
	lpbiSrc->bmiHeader.biPlanes = 1;
	lpbiSrc->bmiHeader.biBitCount = 32;
	lpbiSrc->bmiHeader.biCompression = BI_RGB;
	lpbiSrc->bmiHeader.biSizeImage = dwWidth * dwHeight;
	lpbiSrc->bmiHeader.biXPelsPerMeter = 0;
	lpbiSrc->bmiHeader.biYPelsPerMeter = 0;
	lpbiSrc->bmiHeader.biClrUsed = 0;
	lpbiSrc->bmiHeader.biClrImportant = 0;
	
	COLORREF* pSrcBits = NULL;
	HBITMAP hSrcDib = CreateDIBSection (
		hSrcDC, lpbiSrc, DIB_RGB_COLORS, (void **)&pSrcBits,
		NULL, NULL);
	
	if ((NULL != hSrcDib) && (NULL != pSrcBits))
	{
		HBITMAP hOldTempBmp = (HBITMAP)::SelectObject (hTempDC, hSrcDib);
		::BitBlt (hTempDC, 0, 0, dwWidth, dwHeight, hSrcDC, nSrcX, nSrcY, SRCCOPY);
		::SelectObject (hTempDC, hOldTempBmp);
		
		//Creates Destination DIB
		LPBITMAPINFO lpbiDest;
		// Fill in the BITMAPINFOHEADER
		lpbiDest = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
		lpbiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		lpbiDest->bmiHeader.biWidth = dwWidth;
		lpbiDest->bmiHeader.biHeight = dwHeight;
		lpbiDest->bmiHeader.biPlanes = 1;
		lpbiDest->bmiHeader.biBitCount = 32;
		lpbiDest->bmiHeader.biCompression = BI_RGB;
		lpbiDest->bmiHeader.biSizeImage = dwWidth * dwHeight;
		lpbiDest->bmiHeader.biXPelsPerMeter = 0;
		lpbiDest->bmiHeader.biYPelsPerMeter = 0;
		lpbiDest->bmiHeader.biClrUsed = 0;
		lpbiDest->bmiHeader.biClrImportant = 0;
		
		COLORREF* pDestBits = NULL;
		HBITMAP hDestDib = CreateDIBSection (
			hDestDC, lpbiDest, DIB_RGB_COLORS, (void **)&pDestBits,
			NULL, NULL);
		
		if ((NULL != hDestDib) && (NULL != pDestBits))
		{
			::SelectObject (hTempDC, hDestDib);
			::BitBlt (hTempDC, 0, 0, dwWidth, dwHeight, hDestDC, nDestX, nDestY, SRCCOPY);
			::SelectObject (hTempDC, hOldTempBmp);

			double src_darken = (double)percent / 100.0;
			double dest_darken = 1.0 - src_darken;
			
			for (DWORD pixel = 0; pixel < dwWidth * dwHeight; pixel++, pSrcBits++, pDestBits++)
			{
				*pDestBits = PixelAlpha(*pSrcBits, src_darken, *pDestBits, dest_darken);
			} //for
			
			::SelectObject (hTempDC, hDestDib);
			::BitBlt (hDestDC, nDestX, nDestY, dwWidth, dwHeight, hTempDC, 0, 0, SRCCOPY);
			::SelectObject (hTempDC, hOldTempBmp);

			delete lpbiDest;
			::DeleteObject(hDestDib);
		} //if
		delete lpbiSrc;
		::DeleteObject(hSrcDib);
	} //if

	::DeleteDC(hTempDC);
} //End AlphaBitBlt