BOOL SaveIconBmpToFile(HICON hIcon, LPCTSTR pszFile, COLORREF clrBkGnd )
{
	if (hIcon == NULL || pszFile == NULL)
		return FALSE;

	CClientDC dcDesk(GetDesktopWindow());

	CIconHandle icon = hIcon;

	ICONINFO iconInfo = { 0 };

	if ( !icon.GetIconInfo( &iconInfo ) )
		return FALSE;

	CBitmapHandle bmpIcon = iconInfo.hbmColor;

	BITMAP bmpInfo = { 0 };
	bmpIcon.GetBitmap(&bmpInfo);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap( dcDesk, bmpInfo.bmWidth, bmpInfo.bmHeight);

	CDC dcMem;
	dcMem.CreateCompatibleDC( dcDesk );

	HBITMAP hOldBmp = dcMem.SelectBitmap( bmp );

	RECT rcBkGnd = { 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight };

	dcMem.FillSolidRect(&rcBkGnd , clrBkGnd);

	::DrawIconEx( dcMem, 0, 0, 
		hIcon, bmpInfo.bmWidth, bmpInfo.bmHeight,
		0, NULL,  DI_NORMAL );

	dcMem.SelectBitmap( hOldBmp );


	SaveBitmapToFile(dcMem,  bmp, pszFile);

	//must delete bitmap object
	if (iconInfo.hbmColor)
		::DeleteObject( iconInfo.hbmColor );

	//must delete bitmap object
	if ( iconInfo.hbmMask )
		::DeleteObject( iconInfo.hbmMask );

	return TRUE;
}