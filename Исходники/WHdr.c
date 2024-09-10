void
Headr_OnDrawItem
(
    HWND                    hWnd,
    HDC                     hDC, 
	HEADERDATA*	            pthis,
    int                     iItem,
    PHEADERITEM             pItm
)
{
    RECT                    rcDraw;
    HFONT                   hOFont;
    HPEN                    hOPen;
    UINT                    fmt;
	HPEN                    hGPen = CreatePen ( PS_SOLID, 1, GetSysColor ( COLOR_BTNSHADOW ) );
	HPEN                    hWPen = GetStockObject ( WHITE_PEN );

    CopyRect ( &rcDraw, &pItm->rc );
	FillRect ( hDC, &rcDraw, GetStockObject ( LTGRAY_BRUSH ) );
    InflateRect ( &rcDraw, -HDMETRIC_CYBORDER, -2 );
    if ( pthis->eMouse == eItemClk )
        OffsetRect ( &rcDraw, 1, 1 );
    fmt = DT_VCENTER;        
    fmt |= ( pItm->data.fmt & HDF_CENTER )? DT_CENTER :
           ( pItm->data.fmt & HDF_RIGHT )? DT_RIGHT : DT_LEFT;
    if ( ( pItm->data.fmt & HDF_STRING ) && pItm->text )
    {
        hOFont = SelectObject ( hDC, pthis->hFont );
        SetBkMode ( hDC, TRANSPARENT );
        Headr_IDrawFittedString ( hDC, pItm->text, fmt, &rcDraw );
        SelectObject ( hDC, hOFont );
    }
    else
    if ( ( pItm->data.fmt & HDF_BITMAP ) && pItm->data.hbm )
        Headr_IDrawBitmap ( hDC, pItm->data.hbm, fmt, &rcDraw );
    else
    if ( pItm->data.fmt & HDF_OWNERDRAW )
    {
        Headr_IOwnerDraw ( hWnd, hDC, pthis, iItem, pItm ); 
        goto EndDrawItem;
    }

    if ( pthis->eMouse == eItemClk )
    {
		hOPen = SelectObject ( hDC, hGPen );
		MoveToEx ( hDC, pItm->rc.left, pItm->rc.bottom, ( LPPOINT )NULL );
		LineTo ( hDC, pItm->rc.left, pItm->rc.top );
		LineTo ( hDC, pItm->rc.right, pItm->rc.top );
		SelectObject ( hDC, hWPen );
		LineTo ( hDC, pItm->rc.right, pItm->rc.bottom );
		LineTo ( hDC, pItm->rc.left, pItm->rc.bottom );
		SelectObject ( hDC, hOPen );
    }
    else
    {
		hOPen = SelectObject ( hDC, hGPen );
		MoveToEx ( hDC, pItm->rc.right, pItm->rc.top, ( LPPOINT )NULL );
		LineTo ( hDC, pItm->rc.right, pItm->rc.bottom );
		LineTo ( hDC, pItm->rc.left, pItm->rc.bottom );
        if ( pthis->uStyles & HDS_BUTTONS )
        {
		    MoveToEx ( hDC, pItm->rc.right-1, pItm->rc.top+1, ( LPPOINT )NULL );
		    LineTo ( hDC, pItm->rc.right-1, pItm->rc.bottom-1 );
		    LineTo ( hDC, pItm->rc.left, pItm->rc.bottom-1 );
            SelectObject ( hDC, hWPen );
        }

        LineTo ( hDC, pItm->rc.left, pItm->rc.top );
		LineTo ( hDC, pItm->rc.right, pItm->rc.top );
		SelectObject ( hDC, hOPen );
    }

EndDrawItem:    
    DeleteObject ( hGPen );

}