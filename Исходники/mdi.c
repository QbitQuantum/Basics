static void DrawMdiIcon( HDC hdc, an_MDI_icon *MDI_icon, RECT *r )
{
    BITMAP              bm;
    HDC                 memDC;
    POINT               src_org, src_size;
    POINT               dst_org, dst_size;

    dst_size.y = r->bottom - r->top + 1;
    dst_size.x = r->right - r->left + 1;
    DPtoLP( hdc, &dst_size, 1 );

    dst_org.x = r->left;
    dst_org.y = r->top;
    DPtoLP( hdc, &dst_org, 1 );

    GetObject( MDI_icon->AND_bitmap, sizeof( BITMAP ), (LPSTR) &bm );

    memDC = CreateCompatibleDC( hdc );
    SelectObject( memDC, MDI_icon->AND_bitmap );

    src_size.x = bm.bmWidth;
    src_size.y = bm.bmHeight;
    DPtoLP( hdc, &src_size, 1 );

    src_org.x = 0;
    src_org.y = 0;
    DPtoLP( hdc, &src_org, 1 );

    StretchBlt( hdc, dst_org.x, dst_org.y, dst_size.x, dst_size.y,
        memDC, src_org.x, src_org.y, src_size.x, src_size.y, SRCAND );

    SelectObject( memDC, MDI_icon->XOR_bitmap );

    StretchBlt( hdc, dst_org.x, dst_org.y, dst_size.x, dst_size.y,
        memDC, src_org.x, src_org.y, src_size.x, src_size.y, SRCCOPY );

    DeleteDC( memDC );
} /* DrawMdiIcon */