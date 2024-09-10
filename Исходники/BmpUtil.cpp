int CBitmap::SetClipboard() {
	HANDLE hGMem = GlobalAlloc(GHND, m_bmpInfoHeader.biSize + m_image.buf.size());
	BITMAPINFOHEADER *pBih = (BITMAPINFOHEADER *)GlobalLock(hGMem);
	*pBih = *(BITMAPINFOHEADER *)&m_bmpInfoHeader;
	//pBih->biBitCount = 32;
	//pBih->biCompression = BI_RGB;
	
	int width	= m_image.width;
	int height	= m_image.height;
	int bytesPerPixel = m_bmpInfoHeader.biBitCount / 8;
	int bytesPerLine = ( (width + (m_bmpInfoHeader.biBitCount % 32 != 0) ) * bytesPerPixel >> 2) << 2;
//	int writeSize = bytesPerLine * height;
	
	printf("Setting... w=%d, h=%d", width, height);
	int offset = pBih->biSize + pBih->biClrUsed * (pBih->biBitCount > 24 ? sizeof(RGBQuad) : sizeof(RGBTriple));
	u8 *imgData = (u8 *)pBih + offset;
	u32 *pBuf = (u32 *)&m_image.buf[0];
	
	switch(m_bmpInfoHeader.biBitCount) {
		case 24: {
			if(m_bmpInfoHeader.biHeight < 0) // Top to bottom
				REP(y, height)	REP(x, width) *(RGBTriple *)&imgData[bytesPerLine*y + 3*x] = *(RGBTriple *)&pBuf[width*y+x];
			else // Bottom to top
				REV(y, height)	REP(x, width) *(RGBTriple *)&imgData[bytesPerLine*y + 3*x] = *(RGBTriple *)&pBuf[width*y+x];
		} break;
		
		case 32: {
			if(m_bmpInfoHeader.biHeight < 0) // Top to bottom
				REP(y, height)	REP(x, width) *(u32 *)&imgData[(width*y+x)*4] = pBuf[width*y+x];
			else // Bottom to top
				REV(y, height)	REP(x, width) *(u32 *)&imgData[(width*y+x)*4] = pBuf[width*y+x];
		} break;
	}
	GlobalUnlock(hGMem);
	
	if( !OpenClipboard(NULL) ) return -1;
	EmptyClipboard();
	SetClipboardData(CF_DIB, hGMem);
	CloseClipboard();
	
	puts("OK");
	return 0;
}