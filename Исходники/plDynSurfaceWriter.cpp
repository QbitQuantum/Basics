void    plDynSurfaceWriter::plWinSurface::Allocate( uint16_t w, uint16_t h )
{
    int         i;
    BITMAPINFO  *bmi;


    Release();

    fWidth = w;
    fHeight = h;

    /// Initialize a bitmap info struct to describe our surface
    if( IBitsPerPixel() == 8 )
        bmi = (BITMAPINFO *)( new uint8_t[ sizeof( BITMAPINFOHEADER ) + sizeof( RGBQUAD ) * 256 ] );
    else
        bmi = new BITMAPINFO;

    memset( &bmi->bmiHeader, 0, sizeof( BITMAPINFOHEADER ) );
    bmi->bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
    bmi->bmiHeader.biWidth = (int)fWidth;
    bmi->bmiHeader.biHeight = -(int)fHeight;
    bmi->bmiHeader.biPlanes = 1;
    bmi->bmiHeader.biCompression = BI_RGB;
    bmi->bmiHeader.biBitCount = IBitsPerPixel();
    if( IBitsPerPixel() == 8 )
    {
        // Set up map for grayscale bitmap
        for( i = 0; i < 256; i++ )
        {
            bmi->bmiColors[ i ].rgbRed = i;
            bmi->bmiColors[ i ].rgbGreen = i;
            bmi->bmiColors[ i ].rgbBlue = i;
            bmi->bmiColors[ i ].rgbReserved = i;
        }
    }
    
    /// Create a screen-compatible DC
    fDC = CreateCompatibleDC( nil );
    if( fDC == nil )
    {
        char msg[ 256 ];
        FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nil, GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), msg, sizeof( msg ), nil );
        char *ret = strrchr( msg, '\n' );
        if( ret != nil )
            *ret = 0;

        plStatusLog::AddLineS( "pipeline.log", 0xffff0000, "Unable to allocate DC for dynamic text map (%s, %d DCs allocated already)", msg, sNumDCsAllocated );
        if (IBitsPerPixel() == 8 )
            delete [] bmi;
        else
            delete bmi;
        return;
    }
    sNumDCsAllocated++;

    /// Create a bitmap using the DC and the bitmapInfo struct we filled out
    fBitmap = CreateDIBSection( fDC, bmi, DIB_RGB_COLORS, (void **)&fBits, nil, 0 );
    if( fBitmap == nil )
    {
        char msg[ 256 ];
        FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nil, GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), msg, sizeof( msg ), nil );
        char *ret = strrchr( msg, '\n' );
        if( ret != nil )
            *ret = 0;

        plStatusLog::AddLineS( "pipeline.log", 0xffff0000, "Unable to allocate RGB DIB section for dynamic text map (%s, %d bitmaps allocated already)", msg, sNumBitmapsAllocated );
        if (IBitsPerPixel() == 8 )
            delete [] bmi;
        else
            delete bmi;
        return;
    }
    sNumBitmapsAllocated++;

    /// Set up some basic props
    SetMapMode( fDC, MM_TEXT );
    SetBkMode( fDC, TRANSPARENT );
    SetTextAlign( fDC, TA_TOP | TA_LEFT );

    fSaveNum = SaveDC( fDC );
    
    SelectObject( fDC, fBitmap );

    if (IBitsPerPixel() == 8 )
        delete [] bmi;
    else
        delete bmi;
}