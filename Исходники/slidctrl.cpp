BOOL CSliderCtrlPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// Initially create slider control in horizontal position
	CWnd* pWnd =
		GetDlgItem( IDC_SLIDER_HORZPOS );
	CRect rect;
	pWnd->GetWindowRect( &rect );
	ScreenToClient( &rect );

	// Initialise controls
	m_Slider.Create( WS_VISIBLE|WS_CHILD|TBS_HORZ|TBS_BOTH|TBS_AUTOTICKS,
					 rect, this, IDC_SLIDER );
	m_Slider.SetTicFreq( m_uiTickFreq );    // Send TBM_SETTICFREQ
	m_Slider.SetLineSize( m_uiLine );       // Send TBM_SETLINESIZE
	m_Slider.SetPageSize( m_uiPage );       // Send TBM_SETPAGESIZE
	m_Slider.SetRange( m_uiRangeFrom, m_uiRangeTo, TRUE );
											// Send TBM_SETRANGE
	return TRUE;
}