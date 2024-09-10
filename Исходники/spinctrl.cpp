void CSpinCtrlPage::CreateSpinCtrl()
{
DWORD dwStyles=0;

	// Build styles mask
	if ( 1 == m_iAlignment )
		dwStyles |= UDS_ALIGNLEFT;		// Control is placed to the left of buddy, if set
										// (default = unattached)
	else if ( 2 == m_iAlignment )
		dwStyles |= UDS_ALIGNRIGHT;		// Control is placed to the right of buddy, if set
										// (default = unattached)
	if ( m_bArrowkeys )
		dwStyles |= UDS_ARROWKEYS;		// Up/Down arrow keys inc/decrement, if set

	if ( m_bAutobuddy )
		dwStyles |= UDS_AUTOBUDDY;		// Previous (in Z-order) edit used as buddy, if set

	if ( m_bNothousands )
		dwStyles |= UDS_NOTHOUSANDS;	// No thousands seperator used, if set

	if ( 1 == m_iOrientation )
		dwStyles |= UDS_HORZ;			// Control is horizontal, if set (default = vert)

	if ( m_bSetbuddyint )
		dwStyles |= UDS_SETBUDDYINT;	// Control updates buddy edit with position, if set

	if ( m_bWrap )
		dwStyles |= UDS_WRAP;			// Position wraps when range exceeded, if set

	// Get edit control and change Z-order (created controls go at bottom of Z-order)
	CWnd* pEdit = GetDlgItem( IDC_SPIN_EDIT );
	pEdit->SetWindowPos( &wndBottom, m_EditRect.left, m_EditRect.top,
						 m_EditRect.Width(), m_EditRect.Height(), SWP_SHOWWINDOW );

	// Create spin (up-down) control
	CWnd* pWnd = GetDlgItem( IDC_SPIN_POS );
	CRect rect;
	pWnd->GetWindowRect( &rect );
	ScreenToClient( &rect );

	m_Spin.Create( WS_VISIBLE|WS_CHILD|dwStyles, rect, this, IDC_SPIN );
	m_Spin.SetRange( m_uiRangeFrom, m_uiRangeTo );	// Sends UDM_SETRANGE

	// Prime edit control with initial value
	TCHAR buf[32];
	int pos = m_Spin.GetPos();						// Sends UDM_GETPOS
	wsprintf( buf, _T("%d"), pos );
	pWnd = m_Spin.GetBuddy();						// Sends UDM_GETBUDDY
	if ( pWnd != NULL )
		pWnd->SetWindowText( buf );
}