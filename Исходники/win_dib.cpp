BOOL CDIB::CreatePalette()
{
    //m_hPal DeleteObject();

    if (!m_hBitmap)
        return FALSE;

    // Create a 256 color halftone palette if there is no color table in the DIBSection
    if (m_iColorTableSize == 0)
        return CreateHalftonePalette(m_hPal, 256);

    // Get space for the color entries
    RGBQUAD *pRGB = new RGBQUAD[m_iColorTableSize];
    if (!pRGB)
        return CreateHalftonePalette(m_hPal, m_iColorTableSize);

    HDC hDC = ::GetDC(NULL);
    if (!hDC)
    {
        delete [] pRGB;
        return FALSE;
    }

    // Create a memory DC compatible with the current DC
    HDC hMemDC = CreateCompatibleDC(hDC);
    if (!hMemDC)
    {
        delete [] pRGB;
		ReleaseDC(NULL, hDC);
        return CreateHalftonePalette(m_hPal, m_iColorTableSize);
    }
    ReleaseDC(NULL, hDC);
    
    HBITMAP hOldBitmap = (HBITMAP) SelectObject(hMemDC, m_hBitmap);
    if (!hOldBitmap)
    {
        delete [] pRGB;
        return CreateHalftonePalette(m_hPal, m_iColorTableSize);
    }

    // Get the colors used. WinCE does not support GetDIBColorTable so if you
    // are using this on a CE device with palettes, then you need to replace
    // the call with code that manually gets the color table from the m_DIBinfo structure.
    int nColors = CEGetDIBColorTable(hDC, 0, m_iColorTableSize, pRGB);

    // Clean up
    SelectObject(hMemDC, hOldBitmap);

    if (!nColors)   // No colors retrieved => the bitmap in the DC is not a DIB section
    {
        delete [] pRGB;
        return CreateHalftonePalette(m_hPal, m_iColorTableSize);
    }   
    
    // Create and fill a LOGPALETTE structure with the colors used.
    PALETTEINFO PaletteInfo;
    PaletteInfo.palNumEntries = m_iColorTableSize;
                        
    for (int ii = 0; ii < nColors; ii++)
    {
        PaletteInfo.palPalEntry[ii].peRed   = pRGB[ii].rgbRed;
        PaletteInfo.palPalEntry[ii].peGreen = pRGB[ii].rgbGreen;
        PaletteInfo.palPalEntry[ii].peBlue  = pRGB[ii].rgbBlue;
        PaletteInfo.palPalEntry[ii].peFlags = 0;
    }

    delete [] pRGB;

    // Create Palette!
	m_hPal = ::CreatePalette( &PaletteInfo );
    return (NULL != m_hPal);
}