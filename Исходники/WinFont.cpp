void PrintWinFont( UINT32 uiDestBuf, INT32 iFont, INT32 x, INT32 y, STR16 pFontString, ...)
{
	va_list				 argptr;
	CHAR16									string[512];
	HVSURFACE				hVSurface;
	LPDIRECTDRAWSURFACE2	pDDSurface;
	HDC					 hdc;
	HWINFONT				*pWinFont;
	int					 len;
	
	pWinFont = GetWinFont( iFont );

	if ( pWinFont == NULL )
	{
	return;
	}

	va_start(argptr, pFontString);			// Set up variable argument pointer
	len = vswprintf(string, pFontString, argptr);	// process gprintf string (get output str)
	va_end(argptr);

	// Get surface...
	GetVideoSurface( &hVSurface, uiDestBuf );

	pDDSurface = GetVideoSurfaceDDSurface( hVSurface );

	IDirectDrawSurface2_GetDC( pDDSurface, &hdc );

	SelectObject(hdc, pWinFont->hFont );
	SetTextColor( hdc, pWinFont->ForeColor );
	SetBkColor(hdc, pWinFont->BackColor );
	SetBkMode(hdc, TRANSPARENT);
	SetTextAlign(hdc, TA_TOP|TA_LEFT);

#ifdef DEC_INTERNAL_LEADING
	if (y - pWinFont->InternalLeading >=0)
	{
		y -= pWinFont->InternalLeading;
	}
#endif
	TextOutW( hdc, x, y, string, len );

	IDirectDrawSurface2_ReleaseDC( pDDSurface, hdc );

}