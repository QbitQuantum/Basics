void DrawScreen( ScreenBitmap *info, HDC dc, POINT *dstpos, POINT *dstsize,
                POINT *srcpos, POINT *srcsize ) {

    BOOL        own_dc;

    own_dc = FALSE;
    if( dc == NULL ) {
        dc = GetDC( info->hwnd );
        own_dc = TRUE;
    }
    StretchBlt( dc, dstpos->x, dstpos->y, dstsize->x, dstsize->y,
                info->memdc, srcpos->x, srcpos->y,
                srcsize->x, srcsize->y, SRCCOPY );
    if( own_dc ) ReleaseDC( info->hwnd, dc );
}