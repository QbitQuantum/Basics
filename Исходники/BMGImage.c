/*******************************************************************************
// extracts the dimensional information, pixel array, and color table from an
// HBITMAP.
// hBitmap can be a handle to a DIB or a DDB.  This function assumes that DDBs
// will not have a palette.  If you create a DDB on a 256-color graphics card,
// then the DDB will have a palette and this function will fail.
//
// returns BMK_OK if successfull, and error state otherwise.
********************************************************************************/
BMGError GetDataFromBitmap( HBITMAP hBitmap,
                            struct BMGImageStruct *img,
                            int remove_alpha )
{
    unsigned int        DIBScanWidth;
    DIBSECTION          DS;
    HWND                hWnd = GetForegroundWindow();
    HDC                 hDC = NULL;
    HDC                 hMemDC = NULL;
    unsigned char       red, green, blue;
    int                 FreelpBits = 0;
    unsigned int        numBytes;
    size_t              soDIBSECTION = sizeof(DIBSECTION);
    size_t              soBITMAP = sizeof(BITMAP);

    unsigned char *p, *q, *lpBits, alpha;

    jmp_buf err_jmp;
    int error;
    BMGError bmgerr;

    /* error handler */
    error = setjmp( err_jmp );
    if ( error != 0 )
    {
        if ( hMemDC != NULL )
            DeleteDC( hMemDC );
        if ( hDC != NULL )
            ReleaseDC( hWnd, hDC );
        if ( FreelpBits )
            free( lpBits );
        FreeBMGImage( img );
        SetLastBMGError( (BMGError)error );
        return (BMGError)error;
    }

    SetLastBMGError( BMG_OK );
    /* check for valid bitmap*/
    if ( !hBitmap )
        longjmp( err_jmp, (int)errInvalidBitmapHandle );

    /* Extract DIBSECTION info from the HBITMAP.  numBytes will equal
    // soDIBSECTION (84) if hBitmap is a handle to a DIBSECTION (DIB).
    // numBytes will equal soBITMAP (24) if hBitmap is a handle to a
    // BITMAP (DDB). */
    numBytes = GetObject( hBitmap, sizeof(DIBSECTION), &DS );
    if ( numBytes == 0 )
        longjmp( err_jmp, (int)errWindowsAPI );

    img->opt_for_bmp = 1;
    if ( numBytes == soDIBSECTION )
    {
        img->width = DS.dsBmih.biWidth;
        img->height = DS.dsBmih.biHeight;
        img->bits_per_pixel = (unsigned char)DS.dsBmih.biBitCount;
        if ( img->bits_per_pixel <= 8 && DS.dsBmih.biClrUsed > 0 )
            img->palette_size = (unsigned short)DS.dsBmih.biClrUsed;
        lpBits = (unsigned char *)DS.dsBm.bmBits;
    }
    /* this may be a DDB which must be handled differently */
    else if ( numBytes == soBITMAP )
    {
        BITMAP bm;
        BITMAPINFO bmi;

        if ( GetObject( hBitmap, sizeof(BITMAP), &bm ) == 0 )
            longjmp( err_jmp, (int)errWindowsAPI );

        /* DDB with a palette */
        if ( bm.bmBitsPixel <= 8 )
            longjmp( err_jmp, (int)errInvalidPixelFormat );

        img->width = bm.bmWidth;
        img->height = bm.bmHeight;
        img->bits_per_pixel = (unsigned char)bm.bmBitsPixel;
        bmi = InternalCreateBMI( bm.bmWidth, bm.bmHeight, bm.bmBitsPixel,
                                 BI_RGB );

        lpBits = (unsigned char *)calloc( bm.bmHeight * bm.bmWidthBytes,
                                          sizeof(unsigned char) );
        if ( lpBits == 0 )
            longjmp( err_jmp, (int)errMemoryAllocation );
        FreelpBits = 1;
        hDC = GetDC( hWnd );
        if ( GetDIBits(hDC, hBitmap, 0, bm.bmHeight, (void *)lpBits, &bmi,
                       DIB_RGB_COLORS ) == 0 )
            longjmp( err_jmp, (int)errWindowsAPI );
        ReleaseDC( hWnd, hDC );
        hDC = NULL;
    }
    else /* I have no idea what this is */
        longjmp( err_jmp, (int)errInvalidBitmapHandle );

    /* allocate memory */
    bmgerr = AllocateBMGImage( img );
    if ( bmgerr != BMG_OK )
        longjmp( err_jmp, (int)bmgerr );

    /* dimensions */
    DIBScanWidth = ( img->width * img->bits_per_pixel + 7 )/8;
    if ( DIBScanWidth % 4 )
        DIBScanWidth += 4 - DIBScanWidth % 4;

    p = img->bits;
    for ( q = lpBits; q < lpBits + DIBScanWidth * img->height;
            p += img->scan_width, q += DIBScanWidth )
    {
        memcpy( (void *)p, (void *)q, DIBScanWidth );
    }

    /* "un-blend" the image if requested.  NOTE: unblending only works with
    // bland backgrounds */
    if ( remove_alpha > 0 &&
         img->bits_per_pixel == 32 &&
         numBytes == soDIBSECTION )
    {
        unsigned char *color = GetBackgroundColor();
        red   = color[2];
        green = color[1];
        blue  = color[0];

        for ( p = img->bits; p < img->bits + img->scan_width * img->height;
              p += 4 )
        {
            alpha = p[3];
            p[2] = InverseAlphaComp( p[2], alpha, blue);
            p[1] = InverseAlphaComp( p[1], alpha, green);
            p[0] = InverseAlphaComp( p[0], alpha, red);
        }
    }

    /* 32-bit DDBs must have the alpha channel set to 0xFF before they are
    // saved to a file. This may not be true for all devices that generate
    // 32-bit DDBs.  I have only created 32-bit DDBs using an Intense3D Wildcat
    // 4110 card.  The alpha channel was always 0. */
    if (img->bits_per_pixel == 32 && numBytes == soBITMAP )
    {
        for ( p = img->bits + 3; p < img->bits + img->scan_width * img->height;
                                 p += 4 )
        {
            *p = 0xFF;
        }
    }

    /* create palette if necessary */
    if ( img->bits_per_pixel <= 8 )
    {
        hDC = GetDC( hWnd );
        hMemDC = CreateCompatibleDC( hDC );
        SelectObject( hMemDC, hBitmap );
        if ( !GetDIBColorTable( hMemDC, 0, img->palette_size,
                                (RGBQUAD *)img->palette ) )
        {
            longjmp( err_jmp, (int)errWindowsAPI );
        }
        DeleteDC( hMemDC );
        ReleaseDC( hWnd, hDC );
    }

    if ( FreelpBits )
        free( lpBits );

    return BMG_OK;
}