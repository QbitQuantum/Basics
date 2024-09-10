void
ZListTip::OnMouseMove( UINT uFlags, CPoint pt )
{
#ifdef DEBUG_ALL
   TraceRect( "ZListTip::OnMouseMove rectTitle: ", m_rectTitle );
   TracePoint( "ZListTip::OnMouseMove pt: ", pt );
#endif
   if ( m_rectTitle.PtInRect( pt ) == FALSE )
   {
#ifdef DEBUG_ALL
   TracePoint( "ZListTip::OnMouseMove PtInRect: ", pt );
#endif

#if 0
      if ( GetCapture( ) == this )
         ReleaseCapture( );

      SetWindowPos( 0, 0, 0, 0, 0,
                    SWP_HIDEWINDOW | SWP_NOMOVE | SWP_NOSIZE |
                      SWP_NOZORDER | SWP_NOACTIVATE );
#else
      Hide( );
#endif

      // Forward the message
      ClientToScreen( &pt );
      CWnd *pWnd = WindowFromPoint( pt );
      if ( pWnd == this )
         pWnd = m_pParentWnd;

      CWnd *pWndTemp = GetFocus( );
      if ( pWndTemp != pWnd )
         pWnd->SetFocus( );

      zLONG lParam = MAKELONG( pt.x, pt.y );
      int nHitTest = (int) pWnd->SendMessage( WM_NCHITTEST, 0, lParam );
      if ( nHitTest == HTCLIENT )
      {
         pWnd->ScreenToClient( &pt );
         lParam = MAKELONG( pt.x, pt.y );
         pWnd->PostMessage( WM_MOUSEMOVE, uFlags, lParam );
      }
      else
      {
         pWnd->PostMessage( WM_NCMOUSEMOVE, nHitTest, lParam );
      }
   }
}