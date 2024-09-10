/*! Create a DIB from current bitmap
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::CreateDib(HDC hdcSRC)
{
    BITMAP        bm;
    UINT          iColorDataType;   // color data type (palette or RGB values)
    ::GetObject( m_hCurrentBitmap, sizeof(bm), (LPVOID)&bm );
    
    HDC hdcComp = CreateCompatibleDC(hdcSRC);
    
    iColorDataType = DIB_RGB_COLORS;
    
    // create a DIB
    DIBINFO DIBinfo;
    BITMAPINFOHEADER& bih = DIBinfo.bmiHeader;
    bih.biSize          = sizeof(BITMAPINFOHEADER);
    bih.biWidth         = bm.bmWidth ; 
    bih.biHeight        = bm.bmHeight;
    bih.biPlanes        = 1;                // Must always be 1 according to docs
    bih.biBitCount      = bm.bmBitsPixel;
    bih.biCompression   = BI_RGB;
    bih.biSizeImage     = BytesPerLine(bm.bmHeight, bm.bmBitsPixel) * bm.bmWidth;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed       = 0;
    bih.biClrImportant  = 0;
    
    if (!::GetDIBits(hdcComp, m_hCurrentBitmap, 0, bm.bmHeight, NULL, DIBinfo, iColorDataType))
    {
        ATLTRACE("Unable to GetDIBits\n");
    }
    
    BYTE* pvBitsSRC = (BYTE*)bm.bmBits;
    BYTE* pvBitsDST = NULL;
    
    
    
    // create dib for rotated image with bitmap set to all null
    HBITMAP hCurrentDib = ::CreateDIBSection(hdcComp , (const BITMAPINFO*) DIBinfo, DIB_RGB_COLORS, (VOID**)&pvBitsDST, NULL, 0);
    ATLASSERT( hCurrentDib != NULL);
    
    DWORD dwImageSize = DIBinfo.bmiHeader.biSizeImage;
    if (dwImageSize == 0)
    {
        int nBytesPerLine = BytesPerLine(DIBinfo.bmiHeader.biWidth, 
            DIBinfo.bmiHeader.biBitCount);
        dwImageSize = nBytesPerLine * DIBinfo.bmiHeader.biHeight;
    }
    
    
    CreateHalftonePalette(DIBinfo, 256);
    
    m_hCurrentBitmap = hCurrentDib;
    
    //memcpy(pvBitsDST, pvBitsSRC, dwImageSize);
    
    
    return TRUE;
}