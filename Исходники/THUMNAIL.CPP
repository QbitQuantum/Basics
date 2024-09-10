void CThumbnail::UpdateView()
{
//	if (m_pView->m_drawing) return;
	CRect rect;
	GetClientRect(rect);
	CRButton* button;
	button=GETDLGITEM(IDJ_TITLE);
	CRect buttonrect;
	button->GetClientRect(buttonrect);
	rect.top=buttonrect.bottom;
//	CPoint oldscrollpoint=m_pView->m_scrollpoint;
	m_pView->m_scrollpoint=CPoint((((m_point.x-(m_boxSize.cx/2))*m_pView->m_size.cx)/rect.right)+1,
								  (((m_point.y-(m_boxSize.cy/2)-rect.top)*m_pView->m_size.cy)/(rect.Height()))+1);
	if (m_pView->m_scrollpoint.x<0) m_pView->m_scrollpoint.x=0;
	if (m_pView->m_scrollpoint.y<0) m_pView->m_scrollpoint.y=0;
//	if (m_pView->m_scrollpoint!=oldscrollpoint)
//	{
//		m_pView->m_drawing=TRUE;
//		m_pView->UpdateScrollbars();
//		m_pView->m_mapdlg.ScrollWindow(oldscrollpoint.x-m_pView->m_scrollpoint.x,oldscrollpoint.y-m_pView->m_scrollpoint.y);
//	}
	m_pView->m_mapdlg.Invalidate();
	m_pView->UpdateScrollbars();
}