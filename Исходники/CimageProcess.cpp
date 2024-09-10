/////////////////////////////////////////////////////////////////////////////////////////////////
// Method name	: DisplayContrast
// Arguments	:
//	1) HDC hMemDC		-- Device context
//	2) RECT &r			-- Rectangle position
//	3) int nContrastVal -- Contrast value(Value between 0 to 200)
// Return type	: void
// Description  : It have 2 type. 1) Low contrast 2) High contrast
// Formula		: Color = ((Color-128)*nContrastVal)/100 +128;
// Precondition	: 1)gdiplus should be intialize 2) Image should be load
// Postcondition: 
/////////////////////////////////////////////////////////////////////////////////////////////////
void CImageProcess::DisplayContrast(HDC hMemDC, RECT &r, int nContrastVal)
{
	BITMAPINFO bi;
	BOOL bRes;
	char *buf;
	
	// Bitmap header
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = m_nWidth;
	bi.bmiHeader.biHeight = m_nHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = m_nWidth * 4 * m_nHeight;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;

	buf = (char *) malloc(m_nWidth * 4 * m_nHeight);
	bRes = GetDIBits(hMemDC, m_hBitmap, 0, m_nHeight, buf, &bi,
					   DIB_RGB_COLORS);	

	long nCount=0;	
	for (int i=0; i<m_nHeight; ++i)
	{
		for (int j=0; j<m_nWidth; ++j)
		{			
			long lVal=0;
			memcpy(&lVal, &buf[nCount], 4);
			// Get from buffer in reverse order
			int b = GetRValue(lVal);
			int g = GetGValue(lVal);
			int r = GetBValue(lVal);

			r = ((r-128)*nContrastVal)/100 +128;
			g = ((g-128)*nContrastVal)/100 +128;
			b = ((b-128)*nContrastVal)/100 +128;			
			
			// Red
			if (r >255)
			{
				r = 255;
			}
			if (r <0)
			{
				r = 0;
			}
			
			// Green
			if (g>255)
			{
				g = 255;
			}
			if (g<0)
			{
				g = 0;
			}

			// Blue			
			if (b >255)
			{
				b = 255;
			}
			if (b<0)
			{
				b = 0;
			}

			// Store in reverse order			
			lVal = RGB((int)b, (int)g, (int)r);
			
			memcpy(&buf[nCount], &lVal, 4);

			nCount+=4;
		}
	}

	SetDIBits(hMemDC, m_hBitmap, 0, bRes, buf,  &bi,
					   DIB_RGB_COLORS);
	free(buf);

	RECT tmpRect = r;
	tmpRect.right += 16;
	tmpRect.bottom += 16;
	
	InvalidateRect(GetActiveWindow(), &tmpRect, FALSE);
}