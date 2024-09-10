bool CGetScreenInfo::_BitmapToData(HBITMAP hBitmap, WORD nwBitCount)
{
	if(m_bIsLock)
		return false;
	HDC hDC;
	//当前分辨率下每象素所占字节数
	int iBits;
	//位图中每象素所占字节数
	WORD wBitCount;
	//定义调色板大小， 位图中像素字节大小 ，位图文件大小 ， 写入文件字节数
	DWORD dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0;
	//位图属性结构
	BITMAP Bitmap;
	//位图文件头结构
	BITMAPFILEHEADER bmfHdr;
	//位图信息头结构
	BITMAPINFOHEADER bi;
	//指向位图信息头结构
	LPBITMAPINFOHEADER lpbi;
	//定义文件，分配内存句柄，调色板句柄
	HANDLE  /*hDib,*/ hPal,hOldPal=NULL;

	//计算位图文件每个像素所占字节数
//	hDC = CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	hDC = GetDC(GetDesktopWindow());
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
//	DeleteDC(hDC);
	ReleaseDC(GetDesktopWindow(), hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else
		wBitCount = 24;
	wBitCount = nwBitCount;
	if (wBitCount <= 8) 
		dwPaletteSize = (1 <<  wBitCount) *  sizeof(RGBQUAD);

	GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 0;
	//	     dwBmBitsSize=          Bitmap.bmWidthBytes*Bitmap.bmHeight;
	dwBmBitsSize= ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;
	//为位图内容分配内存 
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	if(m_ScreenData.dwBufLen < dwDIBSize)
	{
		if(m_ScreenData.pScreenData != NULL)
			delete m_ScreenData.pScreenData;
		m_ScreenData.pScreenData = new BYTE[dwDIBSize];
		
		if( !m_ScreenData.pScreenData )
		{
			m_ScreenData.dwBufLen = 0;
			return false;
		}
		m_ScreenData.dwBufLen = dwDIBSize ;

	}
	lpbi = (LPBITMAPINFOHEADER)(m_ScreenData.pScreenData + sizeof(BITMAPFILEHEADER));
	*lpbi = bi;
	// 处理调色板  
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{ 
		hDC = GetDC(NULL);
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER) 
		+dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);
	//恢复调色板
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	// 设置位图文件头 
	bmfHdr.bfType = 0x4D42; // "BM"
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	memcpy(m_ScreenData.pScreenData, &bmfHdr, sizeof(BITMAPFILEHEADER));


	return true;
}