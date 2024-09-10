void CMDIChildWnd::OnMDIActivate( BOOL bActivate, CWnd *pActivateWnd,
                                  CWnd *pDeactivateWnd )
/******************************************************/
{
    UNUSED_ALWAYS( pDeactivateWnd );

    CView *pView = GetActiveView();
    if( pView != NULL ) {
        if( !bActivate ) {
            pView->OnActivateView( FALSE, pView, pView );
        } else {
            pView->OnActivateView( TRUE, pView, pView );
        }
    }

    OnUpdateFrameMenu( bActivate, pActivateWnd, NULL );
    CMDIFrameWnd *pFrame = GetMDIFrame();
    ASSERT( pFrame != NULL );
    pFrame->DrawMenuBar();
}