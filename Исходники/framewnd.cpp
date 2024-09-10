void CFrameWnd::DockControlBar( CControlBar *pBar, UINT nDockBarID, LPCRECT lpRect )
/**********************************************************************************/
{
    CDockBar *pDockBar = NULL;
    if( nDockBarID != 0 ) {
         pDockBar = (CDockBar *)GetControlBar( nDockBarID );
         if( pDockBar == NULL ) {
             // We're trying to dock to a dock bar that doesn't exist, so just don't do
             // anything.
             return;
         }
         if( !(pBar->m_dwDockStyle & (pDockBar->m_dwStyle & CBRS_ALIGN_ANY)) ) {
             // We don't support docking to a bar of this style, so just don't do
             // anything.
             return;
         }
         ASSERT( pDockBar->IsKindOf( RUNTIME_CLASS( CDockBar ) ) );
         if( lpRect != NULL ) {
            RECT    rectJunk;
            CRect   rectBar;
            pDockBar->GetWindowRect( &rectBar );
            if( rectBar.left == rectBar.right ) {
                rectBar.left--;
                rectBar.right++;
            }
            if( rectBar.top == rectBar.bottom ) {
                rectBar.top--;
                rectBar.bottom++;
            }
            if( !::IntersectRect( &rectJunk, &rectBar, lpRect ) ) {
                // The rectangle and the dock bar identifier don't coincide, so just
                // don't do anything.
                return;
            }
        }
    } else if( lpRect != NULL ){
        CanDock( *lpRect, pBar->m_dwDockStyle, &pDockBar );
    } else {
        CanDock( CRect( 0, 0, 32767, 32767 ), pBar->m_dwDockStyle, &pDockBar );
    }
    if( pDockBar != NULL ) {
        ASSERT( pDockBar->IsKindOf( RUNTIME_CLASS( CDockBar ) ) );
        pDockBar->DockControlBar( pBar, lpRect );
    }
}