long	UPSF::hMetaFile_To_UBit(
	HGLOBAL&	hUniv,
	long&			univSize,
	HMETAFILE	hMetaFile,
	long			natvLen)

	{
	if(natvLen != (long)sizeof(HMETAFILE))
		return AUPSF_SIZEERROR;

	HDC	hDC = CreateIC("DISPLAY", NULL, NULL, NULL);
	HDC hDCMem = CreateCompatibleDC(hDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, GetDeviceCaps(hDC, HORZRES), GetDeviceCaps(hDC, VERTRES));
	SelectBitmap(hDCMem, hBitmap);

	// play the metafile
  PlayMetaFile(hDCMem, hMetaFile);

	DeleteDC(hDCMem);
	DeleteDC(hDC);

	// we are left with the bitmap with the meta file
	BITMAP	bitmap;
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bitmap);

  long		bitmapSize = (long)bitmap.bmHeight * (long)bitmap.bmWidthBytes * (long)bitmap.bmPlanes;
	HGLOBAL	hBits = GlobalAlloc(MEMFLAGS, bitmapSize);
	if(!hBits)
		{
  	DeleteObject(hBitmap);
		return AUPSF_MEMORYERROR;
    }

	bitmap.bmBits = GlobalLock(hBits);
	if(!bitmap.bmBits)
		{
  	DeleteObject(hBitmap);
		return AUPSF_MEMORYERROR;
    }

	long ret = BITMAP_To_UBit(hUniv, univSize, bitmap, hBitmap);

	// clean up and exit
  DeleteObject(hBitmap);
	GlobalUnlock(hBits);
	GlobalFree(hBits);  
	return ret;
	}