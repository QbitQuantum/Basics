BYTE *ServerVideoManager::getPartialScreenshot(RECT r)
{
	HDC hDC = GetDC(0);
	int w=(int)((r.right - r.left)/scale_fact);
	int h=(int)((r.bottom - r.top)/scale_fact);
	HDC tmp = CreateCompatibleDC(hDC);
	HBITMAP tmp_bmp = CreateCompatibleBitmap(hDC,w,h);

	SelectObject(tmp,tmp_bmp);

	if(!StretchBlt(	tmp,
					0,0,
					w,h,
					hDC,
					r.left,
					r.top,
					r.right-r.left,
					r.bottom-r.top,
					SRCCOPY
	))
		printError(L"StretchBlt");

	POINT curPos;
	GetCursorPos(&curPos);

	if(	curPos.x>=r.left	&&	curPos.x<r.right	&&
		curPos.y>=r.top		&&	curPos.y<r.bottom)
	{
		// The cursor is inside the area; display it
		ICONINFO iconInfo;

		GetIconInfo(GetCursor(), &iconInfo);
		curPos.x -= ((int) iconInfo.xHotspot) + r.left ;
		curPos.y -= ((int) iconInfo.yHotspot) + r.top;
		
		// Draw the cursor
		DrawIconEx(	tmp,
					(int)(curPos.x/scale_fact), (int)(curPos.y/scale_fact),
					hCursor,
					0,0,
					0,NULL, DI_NORMAL);
	}


	BITMAP bmp;
	if(!GetObject(tmp_bmp,sizeof(BITMAP),&bmp))
		printError(L"GetObject");

	bytes_per_pixel=bmp.bmBitsPixel/8;
	int size=bmp.bmWidthBytes*bmp.bmHeight;

	BITMAPINFOHEADER  bi;
	bi.biSize = sizeof(BITMAPINFOHEADER);    
	bi.biWidth = w;    
	bi.biHeight = h;  
	bi.biBitCount = bmp.bmBitsPixel;    
	bi.biCompression = BI_RGB;    
	bi.biSizeImage = size; 
	bi.biPlanes = 1; 
	bi.biXPelsPerMeter = 0;    
	bi.biYPelsPerMeter = 0;    
	bi.biClrUsed = 0;    
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((bmp.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmp.bmHeight;


	HANDLE hDIB = GlobalAlloc(GHND,dwBmpSize); 
	BYTE *lpbitmap = (BYTE *)GlobalLock(hDIB); 

	
	// Gets the "bits" from the bitmap and copies them into a buffer 
	// which is pointed to by lpbitmap.
	if(!GetDIBits(	hDC, tmp_bmp, 0,
					(UINT)bmp.bmHeight,
					reinterpret_cast<LPVOID>(lpbitmap),
					(BITMAPINFO *)&bi, DIB_RGB_COLORS))
		printError(L"GetDIBits");
	
	BYTE *bmp_copy=new BYTE[size];
	memcpy(bmp_copy,lpbitmap,size);
	
	GlobalUnlock(hDIB);    
	GlobalFree(hDIB);
	

	DeleteDC(tmp);
	DeleteObject(tmp_bmp);

	ReleaseDC(0,hDC);

	return bmp_copy;
}