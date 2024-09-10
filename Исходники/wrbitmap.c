static HBITMAP WRReadBitmap( BYTE *data, long offset, BOOL core, bitmap_info *info )
{
    DWORD               size;           /* generic size - used repeatedly */
    BYTE _HUGE          *mask_ptr;      /* pointer to bit array in memory */
    HDC                 hdc;
    HPALETTE            new_palette, old_palette;
    BITMAPINFO          *bm_info = NULL;
    BITMAPCOREINFO      *bm_core = NULL;
    HBITMAP             bitmap_handle;
    int                 pos;

    bitmap_handle = (HBITMAP)NULL;

    if( core ) {
        bm_core = WRReadCoreInfo( &data );
        if( bm_core == NULL ) {
            return( bitmap_handle );
        }
        size = BITS_TO_BYTES( bm_core->bmciHeader.bcWidth * bm_core->bmciHeader.bcBitCount,
                              bm_core->bmciHeader.bcHeight );
    } else {
        bm_info = WRReadDIBInfo( &data );
        if( bm_info == NULL ) {
            return( bitmap_handle );
        }
        size = BITS_TO_BYTES( bm_info->bmiHeader.biWidth * bm_info->bmiHeader.biBitCount,
                              bm_info->bmiHeader.biHeight );
    }

    pos = offset;
    mask_ptr = __halloc( size, 1 );
    if( mask_ptr != NULL ) {
        WRReadInPieces( mask_ptr, data, size );
        if( core ) {
            BITMAPCOREHEADER    *h;

            h = &bm_core->bmciHeader;
            /*
             * This will cause a GP Fault!
             */
            bitmap_handle = CreateBitmap( h->bcWidth, h->bcHeight, h->bcPlanes,
                                          h->bcBitCount, mask_ptr );
        } else {
            if( bm_info->bmiHeader.biBitCount < 9 ) {
                /* Bitmap has palette, create it */            
                new_palette = CreateDIBPalette( bm_info );
                if( new_palette != NULL ) {
                    hdc = GetDC( (HWND)NULL );
                    old_palette = SelectPalette( hdc, new_palette, FALSE );
                    RealizePalette( hdc );
                    bitmap_handle = CreateDIBitmap( hdc, &bm_info->bmiHeader, CBM_INIT,
                                                    mask_ptr, bm_info, DIB_RGB_COLORS );
                    SelectPalette( hdc, old_palette, FALSE );
                    DeleteObject( new_palette );
                    ReleaseDC( (HWND)NULL, hdc );
                }
            } else {
                /* Bitmap with no palette*/
                hdc = GetDC( (HWND)NULL );
                bitmap_handle = CreateDIBitmap( hdc, &bm_info->bmiHeader, CBM_INIT,
                                                mask_ptr, bm_info, DIB_RGB_COLORS );
                ReleaseDC( (HWND)NULL, hdc );
            }
        }
        __hfree( mask_ptr );
    }
    if( core ) {
        if( info != NULL ) {
            info->u.bm_core = bm_core;
        } else {
            MemFree( bm_core );
        }
    } else {
        if( info != NULL ) {
            info->u.bm_info = bm_info;
        } else {
            MemFree( bm_info );
        }
    }
    return( bitmap_handle );
}