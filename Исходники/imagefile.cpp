HBITMAP CImageFile::LoadFromMemory(LPCVOID pBuffer, DWORD nLength, HDC hUseDC)
{
	LPSTR				hDIB;
	LPVOID				lpDIBBits;
	BITMAPFILEHEADER	bmfHeader;
	DWORD				bmfHeaderLen;

	bmfHeaderLen = sizeof(bmfHeader);
	strncpy( (LPSTR)&bmfHeader, (LPSTR)pBuffer, bmfHeaderLen );
	if ( bmfHeader.bfType != ((WORD) ('M' << 8) | 'B') ) return NULL;

	hDIB = (LPSTR)pBuffer + bmfHeaderLen;
	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
	int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 1 << bmiHeader.biBitCount; 
	if ( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
		((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

	HDC hDC = hUseDC ? hUseDC : GetDC( 0 );

	return CreateDIBitmap( hDC, &bmiHeader, CBM_INIT, lpDIBBits, &bmInfo, DIB_RGB_COLORS );
}