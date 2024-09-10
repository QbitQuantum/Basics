extern "C" AFX_EXT_API   HBITMAP  GetObjectBitmap(const char* obID, LPWORD wC)
{
	HBITMAP hBitmap = NULL;
	HRSRC hRsrc = NULL;
	if (strcmp("{0000000000000-0000-0000-000000000001}",obID)==0)
	{
		hRsrc = ::FindResource(Standard2DDLL.hResource, 
			MAKEINTRESOURCE(IDB_PNT32), RT_BITMAP);
		goto lbl;
	}
	if (strcmp("{0000000000000-0000-0000-000000000002}",obID)==0)
	{
		hRsrc = ::FindResource(Standard2DDLL.hResource, 
			MAKEINTRESOURCE(IDB_LINE32), RT_BITMAP);
		goto lbl;	
	}
	if (strcmp("{0000000000000-0000-0000-000000000003}",obID)==0)
	{
		hRsrc = ::FindResource(Standard2DDLL.hResource, 
			MAKEINTRESOURCE(IDB_CIRC32), RT_BITMAP);
		goto lbl;	
	}
	if (strcmp("{0000000000000-0000-0000-000000000004}",obID)==0)
	{
		hRsrc = ::FindResource(Standard2DDLL.hResource, 
			MAKEINTRESOURCE(IDB_ARC32), RT_BITMAP);
		goto lbl;
	}
	if (strcmp("{0000000000000-0000-0000-000000000005}",obID)==0)
	{
		hRsrc = ::FindResource(Standard2DDLL.hResource, 
			MAKEINTRESOURCE(IDB_SPL32), RT_BITMAP);
		goto lbl;
	}
lbl:
	if ( hRsrc ){
		HGLOBAL hglb = LoadResource(Standard2DDLL.hResource, hRsrc);
		if ( hglb ){
			// „итаем заголовок
			LPBITMAPINFO pbi = (LPBITMAPINFO)LockResource(hglb);
			if (pbi ) {
				if ( wC )
					*wC = pbi->bmiHeader.biBitCount;
				// „итаем данные
				HDC hdc = GetDC( NULL );
				BYTE* pData = (BYTE*)pbi + sizeof(BITMAPINFOHEADER) + pbi->bmiHeader.biClrUsed * sizeof(COLORREF);
				hBitmap = CreateDIBitmap( hdc, &pbi->bmiHeader, CBM_INIT, (void*)pData, pbi, DIB_RGB_COLORS);
				::ReleaseDC	(NULL, hdc);
			}
			FreeResource( hglb );
		}	
	}
	return hBitmap;
}