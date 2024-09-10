LPBITMAPINFO GRenderWinG::GetLPBits( INT32 Width, INT32 Height, INT32 Depth, LPBYTE*lplpBits)
{
	// get a bitmap header with no bits
	const LPBITMAPINFO bmInfo = AllocDIB( Width, Height, Depth, NULL );
	if (!bmInfo)
		return NULL;

	// tell it the sort of palette we want - we want Gavin's
	if (Depth==8)
	{
	#if 0
		RGBQUAD *rgb = bmInfo->bmiColors;
		LPPALETTEENTRY lpPal = GetRecommendedPalette()->palPalEntry;

		size_t i ;
		for ( i=0 ; i<256 ; i++ )
		{
			rgb->rgbRed = lpPal->peRed;
			rgb->rgbGreen = lpPal->peGreen;
			rgb->rgbBlue = lpPal->peBlue;
			rgb->rgbReserved = 0;
			rgb ++;
			lpPal++;
		}
	#else

		GetSystemPaletteEntries (
			RenderDC->m_hDC, 0, 256, (LPPALETTEENTRY) bmInfo->bmiColors
		) ;
		RGBQUAD *rgb = bmInfo->bmiColors ;					// Swap R and B.
		size_t i ;
		for ( i=0 ; i<256 ; i++ )
		{
			BYTE t = rgb->rgbRed ;
			rgb->rgbRed = rgb->rgbBlue ;
			rgb->rgbBlue = t ;
			rgb ++ ;
		}
	#endif
	}

	// if WinG wants it upside-down then go for it
	if (RecommendedDIB.biHeight == -1)
	{
		Inverted = TRUE;
		bmInfo->bmiHeader.biHeight = -bmInfo->bmiHeader.biHeight;
	}
	else
		Inverted = FALSE;

	// now get a lovely WinG bitmap
	WinGBitmap = pWinGCreateBitmap( OffScreenDC, bmInfo, (void FAR* FAR *)lplpBits );
	if (WinGBitmap==NULL)
	{
		TRACE( _T("WinGCreateBitmap failed\n"));
		FreeDIB( bmInfo, NULL );
		return NULL;
	}

	// turn it back the other way else Gavin is likely to get confused
	if (Inverted)
		bmInfo->bmiHeader.biHeight = -bmInfo->bmiHeader.biHeight;

	//TRACE( _T("WinG Alloc %lx=%lx:%lx\n"), this, bmInfo, *lplpBits);
	return bmInfo;
}