//截屏函数
void CopyScreenToBitmap()
{
	int right=GetSystemMetrics(SM_CXSCREEN),left=0,top=0,bottom=GetSystemMetrics(SM_CYSCREEN);//定义截屏范围此处设为全屏

	int nWidth, nHeight;

	HDC hSrcDC = NULL, hMemDC = NULL;
	HBITMAP hBitmap = NULL, hOldBitmap = NULL;

	hSrcDC = CreateDC(L"DISPLAY", NULL, NULL, NULL);
	hMemDC = CreateCompatibleDC(hSrcDC);

	nWidth = right - left;
	nHeight = bottom - top;

	hBitmap = CreateCompatibleBitmap(hSrcDC, nWidth, nHeight);
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	BitBlt(hMemDC, 0, 0, nWidth, nHeight, hSrcDC, left, top , SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);

	BITMAP bmp;
	int nChannels,depth;
	BYTE *pBuffer;

	GetObject(hBitmap,sizeof(BITMAP),&bmp);

	image_nchannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel/8 ;
	image_depth = bmp.bmBitsPixel == 1 ? IPL_DEPTH_1U : IPL_DEPTH_8U;
	image_width=bmp.bmWidth;
	image_height=bmp.bmHeight;

	if(flag==0)
	{
		screemImage=cvCreateImage(cvSize(image_width,image_height),image_depth,image_nchannels);
		flag=1;
	}

	pBuffer = new BYTE[image_width*image_height*image_nchannels];
	GetBitmapBits(hBitmap,image_height*image_width*image_nchannels,pBuffer);
	memcpy(screemImage->imageData,pBuffer,image_height*image_width*image_nchannels);

	delete pBuffer;

	SelectObject(hMemDC,hOldBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMemDC);

	SelectObject(hSrcDC,hBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hSrcDC);
	
}