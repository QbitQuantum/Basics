static unsigned char* uncompress_dib(LPBITMAPINFO lpbmi1, int infosize, void *lpbits1)
{
	LPBITMAPINFOHEADER lpdib2;
	unsigned char *lpbits2;
	void *whatever;
	int linesize, bitssize;
	HBITMAP hb;
	HDC hdc;
	HGDIOBJ rvgdi;
	int rvi;
	int width,height;
	LPBITMAPINFOHEADER lpdib1;

	lpdib1=(LPBITMAPINFOHEADER)lpbmi1;
	width=lpdib1->biWidth;
	height=lpdib1->biHeight;

	linesize= (((width * lpdib1->biBitCount)+31)/32)*4;
	bitssize= linesize*height;

	lpdib2= (LPBITMAPINFOHEADER)malloc(infosize);
	if(!lpdib2) return NULL;

	//  create a header for the new uncompressed DIB
	CopyMemory((void*)lpdib2,(void*)lpdib1,infosize);
	lpdib2->biCompression=BI_RGB;
	lpdib2->biSizeImage=0;

	lpbits2= (unsigned char*)malloc(bitssize);
	if(!lpbits2) { free((void*)lpdib2); return NULL; }


	// Windows bitmap handling functions are not exactly convenient,
	// especially when trying to deal with DIBs. Every function wants
	// to convert them into DDBs. We have to play stupid games and
	// convert back and forth. This probably uses too much memory,
	// and I'm not 100% sure it is exactly correct, but it seems to
	// work for me.

	hb=CreateDIBSection(NULL,(LPBITMAPINFO)lpdib2,DIB_RGB_COLORS,&whatever,NULL,0);

	hdc=CreateCompatibleDC(NULL);
	rvgdi=SelectObject(hdc,hb);
	//SetStretchBltMode(hdc,COLORONCOLOR);
	rvi=StretchDIBits(hdc,
		0,0,width,height,
		0,0,width,height,
		lpbits1, (LPBITMAPINFO)lpdib1,
		DIB_RGB_COLORS,SRCCOPY);
	rvi=GetDIBits(hdc,hb,0,height, (LPVOID)lpbits2,
		(LPBITMAPINFO)lpdib2,DIB_RGB_COLORS);

	DeleteDC(hdc);
	DeleteObject(hb);
	free((void*)lpdib2);

	return lpbits2;
}