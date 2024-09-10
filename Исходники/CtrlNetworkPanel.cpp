void CNetworkTaskBox::OnSize(UINT nType, int cx, int cy) 
{
	CTaskBox::OnSize( nType, cx, cy );
	
	HDWP hDWP = BeginDeferWindowPos( 2 );
	
	DeferWindowPos( hDWP, m_wndChan, NULL, BOX_MARGIN, 27,
		cx - BOX_MARGIN * 2, 80, SWP_NOZORDER );
	
	DeferWindowPos( hDWP, m_wndPlay, NULL, BOX_MARGIN, 80,
		cx - BOX_MARGIN * 2 - 80, 80, SWP_NOZORDER );
	DeferWindowPos( hDWP, m_wndStart, NULL, cx - 80, 79, 72, 24, SWP_SHOWWINDOW|SWP_NOZORDER );
	
	EndDeferWindowPos( hDWP );
}