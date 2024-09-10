void GDisplay::SaveAsJpeg(LPCTSTR pszFileName)
{
	const int req_comps = 3; // request RGB image

	HDC hdcClient = GetDC(m_hWnd); 
	HDC hdcCompatible = CreateCompatibleDC(hdcClient); 
	HBITMAP hBmp = CreateCompatibleBitmap(hdcClient, m_nClientWidth, m_nClientHeight);
	HGDIOBJ hOldBmp = SelectObject(hdcCompatible, hBmp); 

	BitBlt(hdcCompatible, 
		0,0, 
		m_nClientWidth, m_nClientHeight, 
		hdcClient, 
		0,0, 
		SRCCOPY);


	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);    
	bi.biWidth = m_nClientWidth;    
	bi.biHeight = m_nClientHeight;  
	bi.biPlanes = 1;    
	bi.biBitCount = 24;				// RGB mode is 24 bits
	bi.biCompression = BI_RGB;    
	bi.biSizeImage = 0;				// can be 0 for 24 bit images
	bi.biXPelsPerMeter = 0x0ec4;	// paint and PSP use this values 
	bi.biYPelsPerMeter = 0x0ec4;    
	bi.biClrUsed = 0;				// we are in RGB mode and have no palette
	bi.biClrImportant = 0;			// all colors are important

	SIZE_T dwBmpSize = ((m_nClientWidth*bi.biBitCount + 31)/24)*4*m_nClientHeight;

	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize); 
	if (hDIB)
	{
		PUCHAR lpBits = (PUCHAR)GlobalLock(hDIB);

		if (!GetDIBits(hdcClient, hBmp, 0, (WORD)bi.biHeight,
			lpBits, (LPBITMAPINFO)&bi,
			DIB_RGB_COLORS))
		{
			// error handler here...
		}

		// MUST be free later !!!
		PUCHAR pRGBBits = ConvertBMPToRGBBuffer(lpBits,
			m_nClientWidth,
			m_nClientHeight);

		// Fill in the compression parameter structure.
		jpge::params params;
		params.m_quality = 80;
		params.m_subsampling = jpge::H2V2;
		params.m_two_pass_flag = false;

		CHAR szAnsiFileName[MAX_PATH];

#ifndef _UNICODE
		StringCbCopy(szAnsiFileName, MAX_PATH, pszFileName);
#else
		_wcstombsz(szAnsiFileName, pszFileName, MAX_PATH);
#endif

		if (!jpge::compress_image_to_jpeg_file(szAnsiFileName,
			m_nClientWidth, m_nClientHeight,
			req_comps, pRGBBits, params))
		{
			// error handler here...
		}


		//Unlock and Free the DIB from the heap
		GlobalUnlock(hDIB);

		// DON'T forget free this !!!
		delete pRGBBits;
	}
   
	GlobalFree(hDIB);



	SelectObject(hdcCompatible, hOldBmp);
	DeleteDC(hdcCompatible);
	DeleteObject(hBmp);

}