BOOL CScrollView::OnScroll( UINT nScrollCode, UINT nPos, BOOL bDoScroll )
/***********************************************************************/
{
    CRect rectClient;
    GetClientRect( &rectClient );

    BOOL    bHasX = m_totalDev.cx > rectClient.Width();
    BOOL    bHasY = m_totalDev.cy > rectClient.Height();
    
    int nHorzPos = GetScrollPos( SB_HORZ );
    switch( LOBYTE( nScrollCode ) ) {
    case SB_LEFT:
        nHorzPos = 0;
        break;
    case SB_LINELEFT:
        nHorzPos -= m_lineDev.cx;
        break;
    case SB_LINERIGHT:
        nHorzPos += m_lineDev.cx;
        break;
    case SB_PAGELEFT:
        nHorzPos -= m_pageDev.cx;
        break;
    case SB_PAGERIGHT:
        nHorzPos += m_pageDev.cx;
        break;
    case SB_RIGHT:
        nHorzPos = m_totalDev.cx;
        break;
    case SB_THUMBPOSITION:
        nHorzPos = nPos;
        break;
    case SB_THUMBTRACK:
        nHorzPos = nPos;
        break;
    }
    
    int nVertPos = GetScrollPos( SB_VERT );
    switch( HIBYTE( nScrollCode ) ) {
    case SB_BOTTOM:
        nVertPos = m_totalDev.cy;
        break;
    case SB_LINEDOWN:
        nVertPos += m_lineDev.cy;
        break;
    case SB_LINEUP:
        nVertPos -= m_lineDev.cy;
        break;
    case SB_PAGEDOWN:
        nVertPos += m_pageDev.cy;
        break;
    case SB_PAGEUP:
        nVertPos -= m_pageDev.cy;
        break;
    case SB_THUMBPOSITION:
        nVertPos = nPos;
        break;
    case SB_THUMBTRACK:
        nVertPos = nPos;
        break;
    case SB_TOP:
        nVertPos = 0;
        break;
    }
    if( nVertPos < 0 ) {
        nVertPos = 0;
    }

    return( OnScrollBy( CSize( nHorzPos - GetScrollPos( SB_HORZ ),
                               nVertPos - GetScrollPos( SB_VERT ) ), bDoScroll ) );
}