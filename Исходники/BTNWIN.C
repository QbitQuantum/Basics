void draw_button( int button_id, DRAWITEMSTRUCT FAR * draw )
{
    HBITMAP     bmp;
    HBITMAP oldbmp;
    HPEN blackpen, shadowpen, brightpen, facepen;
    HPEN oldpen;
    BITMAP      bitmap;
    HDC memdc;
    HINSTANCE inst;
    int shift;

    inst = GET_HINSTANCE( draw->hwndItem );
    bmp = LoadBitmap( inst, MAKEINTRESOURCE( button_id ) );
    if( !bmp ) return;
    GetObject( bmp, sizeof(BITMAP), &bitmap );
    memdc = CreateCompatibleDC( draw->hDC );
    oldbmp = SelectObject( memdc, bmp );
    if( draw->itemState & ODS_SELECTED ) {
        shift = 4;
    } else {
        shift = 2;
    }
    BitBlt( draw->hDC, draw->rcItem.left + shift, draw->rcItem.top + shift,
        bitmap.bmWidth, bitmap.bmHeight, memdc, 0, 0, SRCCOPY );
    SelectObject( memdc, oldbmp );
    DeleteDC( memdc );
    DeleteObject( bmp );
    // Draw four sides of the button except one pixel in each corner
    blackpen = CreatePen( PS_SOLID, 0, RGB(0,0,0) );
    brightpen = CreatePen( PS_SOLID, 0, RGB(255,255,255) );
    shadowpen = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNSHADOW ) );
    facepen = CreatePen( PS_SOLID, 0, GetSysColor( COLOR_BTNFACE ) );
    oldpen = SelectObject( draw->hDC, blackpen );
    horizontal( draw, draw->rcItem.top );
    horizontal( draw, draw->rcItem.bottom - 1 );
    vertical( draw, draw->rcItem.left );
    vertical( draw, draw->rcItem.right - 1 );
   // Now the shading
    SelectObject( draw->hDC, shadowpen );
    if( draw->itemState & ODS_SELECTED ) {
        horizontal( draw, draw->rcItem.top + 1 );
        vertical( draw, draw->rcItem.left + 1 );
        SelectObject( draw->hDC, facepen );
        horizontal( draw, draw->rcItem.top + 2 );
        vertical( draw, draw->rcItem.left + 2 );
        horizontal( draw, draw->rcItem.top + 3 );
        vertical( draw, draw->rcItem.left + 3 );
    } else {
        horizontal( draw, draw->rcItem.bottom - 2 );
        horizontal( draw, draw->rcItem.bottom - 3 );
        vertical( draw, draw->rcItem.right - 2 );
        vertical( draw, draw->rcItem.right - 3 );
        SelectObject( draw->hDC, brightpen );
        horizontal( draw, draw->rcItem.top + 1 );
        vertical( draw, draw->rcItem.left + 1 );
    }
    SelectObject( draw->hDC, oldpen );
    DeleteObject( blackpen );
    DeleteObject( brightpen );
    DeleteObject( shadowpen );
    DeleteObject( facepen );
}