void
TZNoteBook::SelectPoint( CPoint pt )
{
#ifdef DEBUG_ALL
   TracePoint( "TZNoteBook::SelectPoint", pt );
#endif
   if ( mIs_hWnd( m_hWnd ) == 0 )
      return;

   PostMoveCtrl( );
   m_bDeletable = TRUE;    // mark it as deletable

   CWnd *pWndDlgItem = GetDlgItem( 1 );
   if ( pWndDlgItem )
   {
   // MessageBox( "TZNoteBook::SelectPoint", "Found DlgItem" );
   // TraceLineX( "TZNoteBook::SelectPoint DlgItem: ",
   //             (zLONG) pWndDlgItem->m_hWnd );
      CWnd *pWndChild = ChildWindowFromPoint( pt, CWP_SKIPINVISIBLE );
      if ( pWndChild )
      {
      // TraceLineX( "TZNoteBook::SelectPoint ChildFromPt: ",
      //             (zLONG) pWndChild->m_hWnd );
         if ( pWndDlgItem->m_hWnd == pWndChild->m_hWnd )
         {
            ClientToScreen( &pt );
            pWndDlgItem->ScreenToClient( &pt );
            pWndDlgItem->SendMessage( WM_LBUTTONDOWN, 0, MAKELONG( pt.x, pt.y ) );
            pWndDlgItem->SendMessage( WM_LBUTTONUP, 0, MAKELONG( pt.x, pt.y ) );
            return;
         }
      }
   }

   SendMessage( WM_LBUTTONDOWN, 0, MAKELONG( pt.x, pt.y ) );
   SendMessage( WM_LBUTTONUP, 0, MAKELONG( pt.x, pt.y ) );
//x   zSHORT nActiveTabNbr = GetActivePage( );
// TraceLineI( "TZNoteBook::Select New ActiveTab = ", nActiveTabNbr );
//xif ( nActiveTab != m_nActiveTabNbr )
//x      ActivateTab( nActiveTabNbr );

// TraceLineI( "TZNoteBook::Select Activating tab IdNbr ", GetTabID( ) );
// TraceLineI( "                         tab number ", m_nActiveTabNbr );
// TraceLineI( "                    real tab number ", GetTab( ) );
}