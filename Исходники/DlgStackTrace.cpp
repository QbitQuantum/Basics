void CDlgStackTrace::Size()
{_STT();
	if ( !::IsWindow( GetSafeHwnd() ) ) return;

	CWnd *pCtrl;
	RECT rect, ctrl;
	GetClientRect( &rect );

	// Combo
	SetRect( &ctrl, rect.left + 2, rect.top + 2, rect.right - ( 80 * 1 ), rect.top + 24 );
	pCtrl = GetDlgItem( IDC_TAB );
	if ( pCtrl ) { pCtrl->MoveWindow( &ctrl ); pCtrl->RedrawWindow(); }

	// Refresh
	SetRect( &ctrl, rect.right - 80, rect.top, rect.right, rect.top + 24 );
	pCtrl = GetDlgItem( IDC_REFRESH );
	if ( pCtrl ) { pCtrl->MoveWindow( &ctrl ); pCtrl->RedrawWindow(); }

	// Thread combo
	SetRect( &ctrl, rect.left, rect.top + 25, rect.right, rect.top + 50 );
	pCtrl = GetDlgItem( IDC_THREAD );
	if ( pCtrl ) { pCtrl->MoveWindow( &ctrl ); pCtrl->RedrawWindow(); }

	// Tree
	SetRect( &ctrl, rect.left, rect.top + 50, rect.right, rect.bottom );
	pCtrl = GetDlgItem( IDC_LIST );
	if ( pCtrl ) { pCtrl->MoveWindow( &ctrl ); pCtrl->RedrawWindow(); }

	// Set columns
	long w = ( rect.right - rect.left ) - GetSystemMetrics( SM_CXVSCROLL ) - 4;
	if ( ::IsWindow( m_list.GetSafeHwnd() ) )
	{
		int sel = m_tabSource.GetCurSel();
		if ( sel == 2 )
		{	m_list.SetColumnWidth( 0, w - ( w / 4 ) );
			m_list.SetColumnWidth( 1, w / 4 );
		} // end if			
		else m_list.SetColumnWidth( 0, w );
	} // end if

}