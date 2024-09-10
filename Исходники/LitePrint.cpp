int	 CLitePrint::PrintBitmap(CString sPath, EAlign fmt, CSize* dest)
{
// This code shows how to print a resource bitmap or a .bmp file using StretchDIBits.
// The bitmap must not be compressed (BI_RGB compression type, check MSDN).

	LPBITMAPINFO info;           // Structure for storing the DIB information,
								 // it will be used by 'StretchDIBits()'
	HBITMAP      hbit;           // Handle to the bitmap to print
	BITMAP       bm;             // Structure used for obtaining information
								 // about the bitmap (size, color depth...)
	int          nColors  = 0;   // Used to store the number of colors the DIB has
	int          sizeinfo = 0;   // Will contain the size of info
	RGBQUAD      rgb[256];       // Used to store the DIB color table

	// The following line loads the bitmap from a file
	hbit = (HBITMAP) LoadImage(0,
							   sPath,
							   IMAGE_BITMAP,
							   0,
							   0,
							   LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	
	// The following line loads the bitmap from resource bitmap
	//hbit = (HBITMAP) LoadImage(AfxGetInstanceHandle(),
	//						   MAKEINTRESOURCE(ResourceIDColor),
	//						   IMAGE_BITMAP,
	//						   0,
	//						   0,
	//						   LR_CREATEDIBSECTION);
	

	// Obtain information about 'hbit' and store it in 'bm'
	GetObject(hbit, sizeof(BITMAP), (LPVOID) &bm);

	nColors = (1 << bm.bmBitsPixel);
	if(nColors > 256)
	  nColors=0;           // This is when DIB is 24 bit.
						   // In this case there is not any color table information

	// Now we need to know how much size we have to give for storing "info" in memory.
	// This involves the proper BITMAPINFO size and the color table size.
	// Color table is only needed when the DIB has 256 colors or less.
	sizeinfo = sizeof(BITMAPINFO) + (nColors * sizeof(RGBQUAD));   // This is the size required

	info = (LPBITMAPINFO) malloc(sizeinfo);                        // Storing info in memory

	// Before 'StretchDIBits()' we have to fill some "info" fields.
	// This information was stored in 'bm'.
	info->bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
	info->bmiHeader.biWidth         = bm.bmWidth;
	info->bmiHeader.biHeight        = bm.bmHeight;
	info->bmiHeader.biPlanes        = 1;
	info->bmiHeader.biBitCount      = bm.bmBitsPixel * bm.bmPlanes;
	info->bmiHeader.biCompression   = BI_RGB;
	info->bmiHeader.biSizeImage     = bm.bmWidthBytes * bm.bmHeight;
	info->bmiHeader.biXPelsPerMeter = 0;
	info->bmiHeader.biYPelsPerMeter = 0;
	info->bmiHeader.biClrUsed       = 0;
	info->bmiHeader.biClrImportant  = 0;

	int xx,yy;
	if (dest == NULL)
	{
		xx = bm.bmWidth;
		yy = bm.bmHeight;
	}
	else
	{
		xx = dest->cx;
		yy = dest->cy;
	}

	int xpos;
	if (fmt == FORMAT_LEFT)
		xpos = m_info.m_Margins.left;
	else if (fmt == FORMAT_RIGHT)
		xpos = m_info.m_DimDraw.cx-m_info.m_Margins.right-xx;
	else
		xpos = m_info.m_DimDraw.cx/2 - xx/2;


	// If the bitmap is a compressed bitmap (BI_RLE for example), the 'biSizeImage' can not
	// be calculated that way. A call to 'GetDIBits()' will fill the 'biSizeImage' field with
	// the correct size.

	// Now for 256 or less color DIB we have to fill the "info" color table parameter
	if(nColors <= 256)
	{
	  HBITMAP hOldBitmap;
	  HDC     hMemDC     = CreateCompatibleDC(NULL);      // Creating an auxiliary device context

	  hOldBitmap = (HBITMAP) SelectObject(hMemDC, hbit);  // Select 'hbit' in 'it'
	  GetDIBColorTable(hMemDC, 0, nColors, rgb);          // Obtaining the color table information

	  // Now we pass this color information to "info"
	  for(int iCnt = 0; iCnt < nColors; ++iCnt)
	  {
		info->bmiColors[iCnt].rgbRed   = rgb[iCnt].rgbRed;
		info->bmiColors[iCnt].rgbGreen = rgb[iCnt].rgbGreen;
		info->bmiColors[iCnt].rgbBlue  = rgb[iCnt].rgbBlue;
	  }
	      
	  SelectObject(hMemDC, hOldBitmap);
	  DeleteDC(hMemDC);
	}

	// Let's get 'StretchDIBiting'! 'pDC' is the printer DC
	HDC hdc =  m_DC.GetSafeHdc();   // Getting a safe handle

	// Stretching all the bitmap on a destination rectangle of size (size_x, size_y)
	// and upper left corner at (initial_pos_x, initial_pos_y)
	StretchDIBits(hdc,
				  xpos, //initial_pos_x,
				  m_info.m_y,//initial_pos_y,
				  xx,//size_x,
				  yy,//size_y,
				  0,
				  0,
				  bm.bmWidth,
				  bm.bmHeight,
				  bm.bmBits,
				  info,
				  DIB_RGB_COLORS,
				  SRCCOPY);

	// This mode, DIB_RGB_COLORS indicate the color table are pure RGB values
	// The mode DIB_PAL_COLORS indicate the color table items are index to the local palette items

	DeleteObject(hbit);
	free(info);
	return 1;
}