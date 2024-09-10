static int MergePalette( CDC *pDC, LPRGBQUAD pC, int nColors ) 
{
	WORD	nOldEntries, nNewEntries;
	COLORREF	rgb;
	int	idx, i;

	CPalette*	pPal = pDC->GetCurrentPalette();
	pPal->GetObject( sizeof( nOldEntries ), &nOldEntries );
	LPLOGPALETTE	lp = (LPLOGPALETTE) new BYTE[ sizeof( LOGPALETTE ) + ( nOldEntries + nColors ) * sizeof ( PALETTEENTRY ) ];
	LPPALETTEENTRY	pe = lp->palPalEntry;

	if( pPal->GetPaletteEntries( 0, nOldEntries, pe ) )
		pe += nOldEntries;

	for( i = 0, nNewEntries = 0; i < nColors; i++ ) {
		rgb = RGB(pC->rgbRed,pC->rgbGreen,pC->rgbBlue);
		idx = pPal->GetNearestPaletteIndex( rgb );
		pPal->GetPaletteEntries( idx, 1, pe );
		if( ( pe->peRed != GetRValue( rgb ) )
			|| pe->peGreen != GetGValue( rgb )
			|| pe->peBlue != GetBValue( rgb ) )
		{
			pe->peRed	= GetRValue( rgb );
			pe->peGreen	= GetGValue( rgb );
			pe->peBlue	= GetBValue( rgb );
			pe->peFlags	= NULL;
			pe++;
			nNewEntries++;
		}
		pC++;
	}
	if( nNewEntries > 0 ) {
		lp->palVersion = PALVERSION;
		lp->palNumEntries = nOldEntries + nNewEntries;
		CPalette	pal, *pOldPal;
		pal.CreatePalette( lp );
		pOldPal = pDC->SelectPalette( &pal, FALSE );
		pDC->RealizePalette();
	}
	delete lp;
	return (int) nNewEntries;
}