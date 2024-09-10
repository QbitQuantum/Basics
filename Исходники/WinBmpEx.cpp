//////////////////////////////////////////////////////////////////////
// Draw DIB on caller's DC. Does stretching from source to destination
// rectangles. Generally, you can let the following default to zero/NULL:
//
//    nStretchMode= 0 means 'use DrawDib'; any other value must be
//                  a valid stretch-mode and will force GDI usage		
//    hPal        = palette, default=NULL, (use DIB's palette)
//    bForeground = realize in foreground (default true)
//
// If you are handling palette messages, you should use bForeground=false,
// since you will realize the foreground palette in WM_QUERYNEWPALETTE.
//
BOOL PLWinBmpEx::DrawEx( HDC dc, const RECT* rcDst, const RECT* rcSrc,
		        HPALETTE hPal, bool bForeground,
			int nStretchMode, DWORD ropcode )
{
    // Select, realize palette
    if (hPal==NULL)        // no palette specified:
        hPal = GetLogPalette();    // use default
    HPALETTE hOldPal = ::SelectPalette(dc, hPal, !bForeground);
    ::RealizePalette(dc);

    // Compute rectangles where NULL specified
    RECT rc;
    if (!rcSrc)
    {  // if no source rect, use whole bitmap
        rc.left = rc.top = 0;
        rc.right    = GetWidth();
        rc.bottom   = GetHeight();
        rcSrc = &rc;
    }
    if (!rcDst) // if no destination rect, use source
        rcDst = rcSrc;

    BOOL bRet = false;

#ifndef _WITHOUT_VFW_
    bool bUseDrawDib = nStretchMode < 0;
    if (bUseDrawDib)
    {
        if (!m_hdd)  VERIFY(m_hdd = DrawDibOpen());

        // Let DrawDib do the work!
        bRet = ::DrawDibDraw( m_hdd, dc,
                              rcDst->left,
                              rcDst->top,
                              rcDst->right  - rcDst->left,
                              rcDst->bottom - rcDst->top,
                              GetBMI(),
                              GetBits(),
                              rcSrc->left,
                              rcSrc->top,
                              rcSrc->right  - rcSrc->left,
                              rcSrc->bottom - rcSrc->top,
                              bForeground ? 0 : DDF_BACKGROUNDPAL);
    }
    else      // use normal draw function
#endif
    {
	// If user wanted DrawDib but vfw support is not linked in,
	// then try to use best looking GDI mode
	if (nStretchMode < 0) nStretchMode = HALFTONE;
	int osm = 0;
	if (nStretchMode > 0) osm = ::SetStretchBltMode( dc, nStretchMode );
#if 0	// way too slooooooooooooooooooow!        
	bRet = GDI_ERROR != ::StretchDIBits(
	                dc,
                        rcDst->left,
                        rcDst->top,
                        rcDst->right  - rcDst->left,
                        rcDst->bottom - rcDst->top,
                        rcSrc->left,
                        rcSrc->top,
                        rcSrc->right  - rcSrc->left,
                        rcSrc->bottom - rcSrc->top,
                        GetBits(),       // Pointer to bits
                        (BITMAPINFO*) GetBMI(),        // BITMAPINFO
                        DIB_RGB_COLORS,  // Options
                        ropcode);        // Raster operator code
#else
	HDC hSrcDC;
	hSrcDC = CreateCompatibleDC (dc);
	HGDIOBJ hOldBmp = ::SelectObject (hSrcDC, GetHandle());
	if (m_pClrTab)	// uses associated colormap
	    (void) ::SetDIBColorTable (hSrcDC, 0, 256, (RGBQUAD *)m_pClrTab);

	bRet = ::StretchBlt (	dc,
				rcDst->left,
				rcDst->top,
				rcDst->right  - rcDst->left,
				rcDst->bottom - rcDst->top,
				hSrcDC,
				rcSrc->left,
				rcSrc->top,
				rcSrc->right  - rcSrc->left,
				rcSrc->bottom - rcSrc->top,
				ropcode );

	::SelectObject (hSrcDC, hOldBmp);
	::DeleteDC(hSrcDC);

	// restore GDI stretch-mode
	if (osm) 
	    (void) ::SetStretchBltMode( dc, osm );
    }
#endif	// _WITHOUT_VFW_

    // restore DC palette
    if (hOldPal)
        ::SelectPalette(dc, hOldPal, true);

    return bRet;
}