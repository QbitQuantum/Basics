const Point2F& TextImage::buildText (const char* text, const Point2F&, 
								UV& getUV)//建立文字貼圖
{

	enum {MAX_TEXT_W = 512, MAX_TEXT_H = 32} ;
	if (bInit == false)
	{
		assert (hMemDC == NULL) ;
		assert (hBMP == NULL) ;
		bInit = true ;
		//建立mem dc, bitmap
		HDC screenDC = GetDC (NULL) ;
		hMemDC = CreateCompatibleDC (screenDC) ;
		ReleaseDC (NULL, screenDC) ;

		//背景色
//		SetBkColor (hMemDC, RGB (0, 0, 0)) ;

		BITMAPINFO bmpInfo ;
		memset (&bmpInfo, 0, sizeof (bmpInfo)) ;
		bmpInfo.bmiHeader.biSize = sizeof (bmpInfo.bmiHeader) ;
		bmpInfo.bmiHeader.biWidth = MAX_TEXT_W ;
		bmpInfo.bmiHeader.biHeight = MAX_TEXT_H ;
		bmpInfo.bmiHeader.biPlanes = 1 ;
		bmpInfo.bmiHeader.biBitCount = 32 ;
		bmpInfo.bmiHeader.biCompression = BI_RGB ;
		bmpInfo.bmiHeader.biSizeImage = 0 ;
		bmpInfo.bmiHeader.biXPelsPerMeter = 10 ;
		bmpInfo.bmiHeader.biYPelsPerMeter = 10 ;
		bmpInfo.bmiHeader.biClrUsed = 0 ;
		bmpInfo.bmiHeader.biClrImportant = 0 ;

		hBMP = CreateDIBSection (hMemDC, &bmpInfo, DIB_RGB_COLORS, &pPixel,
									NULL, 0) ;

//		HPEN hPen = (HPEN)GetStockObject (WHITE_PEN) ;
//		SelectObject (hMemDC, hPen) ;

		SelectObject (hMemDC, hBMP) ;
	}

	//確保字串空間夠大
	assert (strlen (text) < sizeof (Text)-1) ;

	if ((strcmp (Text, text) == 0))
	{
		//相同,什麼都不做
		getUV = uv ;
		return textSize ;
	}
	//--------------------

	//複製字串
	strcpy_s (Text, sizeof (Text), text) ;

	SIZE txtSize ;
	//寫字
	BOOL bOK = TextOutA (hMemDC, 0, 0, Text, strlen (Text)) ;
	//取得大小
	GetTextExtentPointA (hMemDC, Text, strlen (Text), &txtSize) ;
	textSize.x = (float32)txtSize.cx ;
	textSize.y = (float32)txtSize.cy ;

	//取得uv
	uv.u = (float)txtSize.cx/MAX_TEXT_W ;
	uv.v = (float)txtSize.cy/MAX_TEXT_H ;

	assert (uv.u <= 1.0f) ;
	assert (uv.v <= 1.0f) ;

	setPixel (MAX_TEXT_W, MAX_TEXT_H, pPixel) ;

	getUV = uv ;
	return textSize ;
}