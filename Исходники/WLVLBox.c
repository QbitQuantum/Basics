void
LVLBox_OnVScroll
(
    HWND                    hWnd,
    int                     iCode,
    int                     iPos
)
{
    RECT                    rc;
    int                     iminPos;
    int                     imaxPos;
    int                     iPageSize;
    int                     iLineSize;
    UINT                    uStyleMask;
	HGLOBAL		            hRsrc   	= ( HGLOBAL )NULL;
	LISTVIEWDATA*	        pthis		= ( LISTVIEWDATA* )NULL;
    BOOL                    bRedraw     = FALSE;

    hRsrc = LView_IGetResource ( hWnd, &pthis );
    assert ( hRsrc );
    uStyleMask = pthis->uStyles & LVS_TYPEMASK;
    GetScrollRange ( hWnd, SB_VERT, &iminPos, &imaxPos );
    GetClientRect ( hWnd, &rc );
    iLineSize = pthis->psLBox.ItmHeight;
    iPageSize = rc.bottom / pthis->psLBox.ItmHeight;
    switch ( iCode )
    {
        case    SB_LINEUP:    if ( pthis->psLBox.ptOrg.y > 0 )
                              {
                                iLineSize = 0 - pthis->psLBox.ItmHeight;
                                if ( uStyleMask == LVS_REPORT ||
                                     uStyleMask == LVS_LIST )
                                     iLineSize = -1;
                                bRedraw = TRUE;
                              }
                              break;
        case    SB_LINEDOWN:  if ( pthis->psLBox.ptOrg.y + iLineSize > imaxPos )
                                iLineSize = imaxPos - pthis->psLBox.ptOrg.y;
                              if ( iLineSize > 0 )
                              {
                                if ( uStyleMask == LVS_REPORT ||
                                     uStyleMask == LVS_LIST )
                                     iLineSize = 1;
                                bRedraw = TRUE;
                              }
                              break;
        case    SB_PAGEUP:    if ( pthis->psLBox.ptOrg.y > 0 )
                              {
                                pthis->psLBox.lTopIndx -= iPageSize;
                                if ( pthis->psLBox.lTopIndx < 0 )
                                  pthis->psLBox.lTopIndx = 0;
                                iLineSize = 0 - iPageSize;
                                bRedraw = TRUE;
                              }
                              break;
        case    SB_PAGEDOWN:  if ( pthis->psLBox.ptOrg.y + iPageSize <= imaxPos )
                                  iPageSize = imaxPos - pthis->psLBox.ptOrg.y;
                              if ( iPageSize > 0 )
                              {
                                pthis->psLBox.lTopIndx += iPageSize;
                                if ( pthis->psLBox.lTopIndx >= pthis->psLBox.lCount - iPageSize )
                                  pthis->psLBox.lTopIndx = pthis->psLBox.lCount - iPageSize;
                                if ( pthis->psLBox.lTopIndx < 0 )
                                  pthis->psLBox.lTopIndx = 0;
                                iLineSize = iPageSize;
                                bRedraw = TRUE;
                              }
                              break;
        case    SB_THUMBPOSITION:
        case    SB_THUMBTRACK: pthis->psLBox.lTopIndx = iPos;
                               iLineSize = 0;
                               bRedraw = TRUE;
                               break;

    }
    if ( bRedraw )
        LView_OnScroll ( hWnd, pthis, 0, iLineSize ); 
    LView_IReleaseResource ( hRsrc, pthis );
}