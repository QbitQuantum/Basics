bool CDDB::PutBitmap( int x, int y, CDC *pDC, int xSrc, int ySrc, int dxSrc, int dySrc, int width, int height, DWORD dwRop, int alpha)
{
	// Coordinate mode is not relative
	if ( m_CoordinateMode != CM_RELATIVE)
		GetRelativeCoordinate( &xSrc, &ySrc, &dxSrc, &dySrc);


	// Copy alphablended memory DC
	if ( alpha < 255)
	{
		BLENDFUNCTION blendFunc = { AC_SRC_OVER, 0, alpha, 0 };

		// Copy memory bitmap
		AlphaBlend( m_DC, x, y, width, height, pDC->m_hDC, xSrc, ySrc, dxSrc, dySrc, blendFunc);
	}

	// Copy transparent memory DC
	else if ( dwRop == TRANSPARENT)
	{
		// Copy memory bitmap
		TransparentBlt( m_DC, x, y, width, height, pDC->m_hDC, xSrc, ySrc, dxSrc, dySrc, m_nTransColor);
	}

	// Copy memory DC
	else
	{
		// Copy memory bitmap
		m_DC.StretchBlt( x, y, width, height, pDC, xSrc, ySrc, dxSrc, dySrc, dwRop);
	}


	return true;
}