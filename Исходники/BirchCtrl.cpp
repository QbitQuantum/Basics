void CBirchCtrl::ResetScrollBar()
{
	// Flag to avoid a call from OnSize while resetting the scrollbar
	m_bScrollBarMessage = TRUE;

	CRect rFrame;

	GetClientRect( rFrame );

	// Need for scrollbars?
	if( rFrame.Height() > m_iDocHeight + 8 )
	{
		ShowScrollBar( SB_VERT, FALSE );	// Hide it
		SetScrollPos( SB_VERT, 0 );
	}
	else
	{
		SCROLLINFO	si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE | SIF_RANGE;
		si.nPage = rFrame.Height()/*/m_iLineHeight*/;
		si.nMax = (m_iDocHeight + 8)/*/m_iLineHeight*/;
		si.nMin = 0 ;

		SetScrollInfo( SB_VERT, &si );
		EnableScrollBarCtrl( SB_VERT, TRUE );
	}

	m_bScrollBarMessage = FALSE;
}