//To on and off the scrollbars of the listbox
void COXMultiComboBox::COXComboLBox::AdjustHScroll()
{
	int nTotalHeight = ((COXMultiComboBox*)m_pWndCombo)->GetTotalHeight();
	int nTotalWidth = ((COXMultiComboBox*)m_pWndCombo)->GetTotalWidth();
	int nBorderWidth = GetSystemMetrics(SM_CXBORDER);
	int nBorderHeight = GetSystemMetrics(SM_CYBORDER);
	int nScrollbarWidth = GetSystemMetrics(SM_CXVSCROLL);
	int nScrollbarHeight = GetSystemMetrics(SM_CYHSCROLL);
	CRect rcDrop;
	((COXMultiComboBox*)m_pWndCombo)->GetDroppedControlRect(&rcDrop);
	if( (nTotalHeight > rcDrop.Height()-2*nBorderHeight) ||
		((nTotalWidth > rcDrop.Width() - 2*nBorderWidth) &&
		(nTotalHeight > rcDrop.Height()-nScrollbarHeight - 2*nBorderHeight)) )
		m_fVertScrollVisible = TRUE;
	else
		m_fVertScrollVisible = FALSE;

	int nMargin=nTotalWidth-rcDrop.Width()+2*nBorderWidth;
	if(m_fVertScrollVisible)
		nMargin+=nScrollbarWidth;
	if( nMargin>0 )
		m_fHorzScrollVisible = TRUE;
	else
		m_fHorzScrollVisible = FALSE;

	if(m_fHorzScrollVisible)
		ShowScrollBar(SB_BOTH,TRUE);
	else
		ShowScrollBar(SB_HORZ,FALSE);
	ShowScrollBar(SB_VERT,m_fVertScrollVisible);

}