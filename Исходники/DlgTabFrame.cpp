void CDlgTabFrame::Size()
{
	CWnd	*pTab = GetDlgItem( IDC_TAB );
	CWnd	*pBlank = GetDlgItem( IDC_BLANK );

	RECT rect;

	if ( m_bSize )
	{
		GetClientRect( &rect );	
		InflateRect( &rect, -4, -4 );

		// Set tab control position
		if ( pTab != NULL )
		{
			pTab->SetWindowPos(	NULL, rect.left, rect.top,
								rect.right - rect.left,
								rect.bottom - rect.top,
								SWP_NOZORDER | SWP_NOACTIVATE );
		} // end if

	} // end if
	
	// Adjust window to tab control
	if ( pTab != NULL && ::IsWindow( pTab->GetSafeHwnd() ) )
	{
		if ( !m_bSize ) 
		{	pTab->GetWindowRect( &rect );
			ScreenToClient( &rect );
		} // end if

		m_tab.AdjustRect( FALSE, &rect );
		rect.bottom -= 2;

		// Set page parent window position
		if ( pBlank != NULL )
		{
			// Set page parent position
			pBlank->SetWindowPos(	NULL, rect.left, rect.top,
									rect.right - rect.left,
									rect.bottom - rect.top,
									SWP_NOZORDER | SWP_NOACTIVATE );
			m_blank.GetClientRect( &rect );
	//		m_blank.GetWindowRect( &rect );
	//		ScreenToClient( &rect );

		} // end if

		// Set page window position
		if ( m_pg[ m_dwPg ] != NULL && ::IsWindow( m_pg[ m_dwPg ]->GetSafeHwnd() ) )
		{
			// Set the page position
			m_pg[ m_dwPg ]->SetWindowPos(	NULL, rect.left, rect.top,
											rect.right - rect.left,
											rect.bottom - rect.top,
											SWP_NOZORDER | SWP_NOACTIVATE );
			m_pg[ m_dwPg ]->RedrawWindow();
		} // end if

	} // end if
}