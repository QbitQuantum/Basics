HICON IconFromSurface( const RageSurface *pSrcImg )
{
    RageSurface *pImg;

    {
        /* Round the width up to a multiple of 8, convert to 32-bit BGR, and reduce
         * to one-bit alpha. */
        int iWidth = pSrcImg->w;
        iWidth = (iWidth+7) & ~7;

        pImg = CreateSurface( iWidth, pSrcImg->h, 32,
                              0x00FF0000,
                              0x0000FF00,
                              0x000000FF,
                              0x80000000 );
        RageSurfaceUtils::Blit( pSrcImg, pImg );
    }

    RageSurfaceUtils::FlipVertically( pImg );

    int iSize = sizeof(BITMAPINFOHEADER);
    int iSizeImage = 0;
    iSizeImage += pImg->h * pImg->pitch; /* image */
    iSizeImage += (pImg->h * pImg->w) / 8; /* mask */

    BITMAPINFOHEADER *pBitmap = (BITMAPINFOHEADER *) malloc( iSize + iSizeImage );
    memset( pBitmap, 0, iSize + iSizeImage );

    pBitmap->biSize  = sizeof(BITMAPINFOHEADER);
    pBitmap->biWidth = pImg->w;
    pBitmap->biHeight = pImg->h * 2;
    pBitmap->biPlanes = 1;
    pBitmap->biBitCount = 32;
    pBitmap->biCompression = BI_RGB;
    pBitmap->biSizeImage = pImg->h * pImg->pitch;

    uint8_t *pImage = ((uint8_t *) pBitmap) + iSize;
    uint8_t *pMask = pImage + pImg->h * pImg->pitch;

    memcpy( pImage, pImg->pixels, pImg->h * pImg->pitch );

    int iMaskPitch = pImg->w/8;
    for( int y = 0; y < pImg->h; ++y )
    {
        int bit = 0x80;
        uint32_t *pRow = (uint32_t *) (pImage + y*pImg->pitch);
        uint8_t *pMaskRow = pMask + y*iMaskPitch;
        for( int x = 0; x < pImg->w; ++x )
        {
            if( !(pRow[x] & pImg->fmt.Mask[3]) )
            {
                /* Transparent; set this mask bit. */
                *pMaskRow |= bit;
                pRow[x] = 0;
            }

            bit >>= 1;
            if( bit == 0 )
            {
                bit = 0x80;
                ++pMaskRow;
            }
        }
    }

    HICON icon = CreateIconFromResourceEx( (BYTE *) pBitmap, iSize + iSizeImage, TRUE, 0x00030000, pImg->w, pImg->h, LR_DEFAULTCOLOR );

    delete pImg;
    pImg = NULL;
    free( pBitmap );

    if( icon == NULL )
    {
        LOG->Trace( "%s", werr_ssprintf( GetLastError(), "CreateIconFromResourceEx" ).c_str() );
        return NULL;
    }

    return icon;
}