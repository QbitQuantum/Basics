void CSearchAdvancedBox::OnSize(UINT nType, int cx, int cy) 
{
	CTaskBox::OnSize( nType, cx, cy );
	
	HDWP hDWP = BeginDeferWindowPos( 3 );

	if ( m_wndCheckBoxG2.m_hWnd != NULL )
		DeferWindowPos( hDWP, m_wndCheckBoxG2, NULL, BOX_MARGIN + 21, 28, 
			( cx - BOX_MARGIN * 3 ) / 2 - 20, 14,
			SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER );
	if ( m_wndCheckBoxG1.m_hWnd != NULL )
		DeferWindowPos( hDWP, m_wndCheckBoxG1, NULL, BOX_MARGIN + 21, 48, 
			( cx - BOX_MARGIN * 3 ) / 2 - 20, 14,
			SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER );
	if ( m_wndCheckBoxED2K.m_hWnd != NULL )
		DeferWindowPos( hDWP, m_wndCheckBoxED2K, NULL, ( cx / 2 ) + BOX_MARGIN / 2 + 26, 28, 
			( cx - BOX_MARGIN * 3 ) / 2 - 20, 14,
			SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER );
	if ( m_wndCheckBoxDC.m_hWnd != NULL )
		DeferWindowPos( hDWP, m_wndCheckBoxDC, NULL, ( cx / 2 ) + BOX_MARGIN / 2 + 26, 48, 
			( cx - BOX_MARGIN * 3 ) / 2 - 20, 14,
			SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER );
	if ( m_wndSizeMin.m_hWnd != NULL )
	{
		int width = ( cx - BOX_MARGIN * 6 ) / 2;
		DeferWindowPos( hDWP, m_wndSizeMin, NULL, BOX_MARGIN, 81,
			width, 219, SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER );
		DeferWindowPos( hDWP, m_wndSizeMax, NULL, cx - BOX_MARGIN - width, 81,
			width, 219, SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER );
		DeferWindowPos( hDWP, m_wndSizeMinMax, NULL, BOX_MARGIN + width, 81 + 2,
			BOX_MARGIN * 4, 18, SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER );
	}
	
	EndDeferWindowPos( hDWP );
}