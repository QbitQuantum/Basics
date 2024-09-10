UINT ExtractIcons::_ExtractFromBMP( LPCTSTR pFileName, int iconIndex, 
                                   int cxIcon, int cyIcon, 
                                   HICON* phicon, UINT flags )
{
    if( iconIndex >= 1 )
        return 0;

    flags |= LR_LOADFROMFILE;
    HBITMAP hbm = (HBITMAP)LoadImage( NULL, pFileName, IMAGE_BITMAP,
                                      cxIcon, cyIcon, flags );
    if( hbm == NULL )
        return 0;

    if( phicon == NULL )
    {
        DeleteObject(hbm);
        return 1;
    }

    HBITMAP hbmMask = CreateBitmap( cxIcon, cyIcon, 1, 1, NULL );

    HDC hdc = CreateCompatibleDC(NULL);
    SelectObject( hdc, hbm );

    HDC hdcMask = CreateCompatibleDC(NULL);
    SelectObject(hdcMask, hbmMask);

    SetBkColor( hdc, GetPixel(hdc, 0, 0) );
// this ROP Code will leave bits in the destination bitmap the same color if the
// corresponding source bitmap's bit are black.
// all other bits in the destination (where source bits are not black)
// are turned to black.
#define DSTERASE 0x00220326 // dest = dest & (~src) :
    BitBlt( hdcMask, 0, 0, cxIcon, cyIcon, hdc, 0, 0, SRCCOPY );
    BitBlt( hdc, 0, 0, cxIcon, cyIcon, hdcMask, 0, 0, DSTERASE );

    ICONINFO ii;
    ii.fIcon    = TRUE;
    ii.xHotspot = 0;
    ii.yHotspot = 0;
    ii.hbmColor = hbm;
    ii.hbmMask  = hbmMask;
    HICON hicon = CreateIconIndirect( &ii );

    DeleteObject(hdc);
    DeleteObject(hbm);
    DeleteObject(hdcMask);
    DeleteObject(hbmMask);

    *phicon = hicon;
    return 1;
}