static void	__fastcall Repaint(HWND	hWnd,RECT & updata,RECT& upbmp,HDC hdc)
{
	PAINTSTRUCT ps={0};
	HDRAWDIB	hdd;
	HBITMAP		hbmp;
	BITMAPINFOHEADER	bi={sizeof(bi)};
	void*		bits=LocalAlloc(LPTR,4096*4096*5);
	
	POINTS	bmprc;
	*((DWORD*)(&bmprc))= GetWindowLong(hWnd,FIELD_OFFSET(ShowPicClass,bmRC));

	hdd=DrawDibOpen();

	if(!hdc)
		hdc =BeginPaint(hWnd,&ps);

	hbmp=(HBITMAP)GetWindowLong(hWnd,FIELD_OFFSET(ShowPicClass,hbmp));
	
	BITMAP	bm;

	GetObject(hbmp,sizeof(bm),&bm);
	bi.biBitCount=32;
	bi.biWidth = bm.bmWidth;
	bi.biPlanes = 1;
	bi.biHeight = bm.bmHeight ;
	
	ExcludeClipRect(hdc,updata.left,updata.top,updata.right,updata.bottom);

	FillRect(hdc,&ps.rcPaint,(HBRUSH)1);
	
	SelectClipRgn(hdc,NULL);

	GetDIBits(hdc,hbmp,0,bi.biHeight,bits,(LPBITMAPINFO)&bi,DIB_RGB_COLORS);

	DrawDibDraw(hdd,hdc,updata.left,updata.top,updata.right-updata.left,updata.bottom-updata.top,
		&bi,bits,upbmp.left,upbmp.top,upbmp.right-upbmp.left,upbmp.bottom-upbmp.top,0);
	
	LocalFree(bits);

	DrawDibClose(hdd);
	
	if(ps.hdc)
		EndPaint(hWnd,&ps);
	
}