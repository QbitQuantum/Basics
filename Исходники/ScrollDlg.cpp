void CScrollDlg::SetupScrollbars()
{
	CRect tempRect;
    GetClientRect(&tempRect);
    
    //Max Vertical Scrolling is the difference between size
	//of the Whole Property Page with Controls and that with
	//the current one devided by the Indentation you set

	m_nVertInc = (m_ClientRect.Height() - tempRect.Height())/VERT_PTS;
	
	m_nVscrollMax = max(0, m_nVertInc);
    m_nVscrollPos = min(m_nVscrollPos, m_nVscrollMax);
    SetScrollRange(SB_VERT, 0, m_nVscrollMax, FALSE);
    SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);	

}