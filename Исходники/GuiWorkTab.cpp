void CGuiWorkTab::SizeScroll()
{
	SCROLLINFO sCrollInfo;
	ASSERT_VALID(this);	
	
	if (!m_pArray.GetSize()) 
		return;
	
	CGuiTab* ct  = (CGuiTab*) m_pArray[m_iSelectTab];
	CWnd* ViewAc = ct->pParent;
	
	memset(&sCrollInfo, 0, sizeof(SCROLLINFO));
	sCrollInfo.cbSize = sizeof(SCROLLINFO);
	sCrollInfo.fMask  = SIF_ALL;
	
	ViewAc->GetScrollInfo(SB_HORZ, &sCrollInfo);
	if (::IsWindow(m_scroll.GetSafeHwnd()))
		m_scroll.SetScrollInfo(&sCrollInfo);
	
	ViewAc->ShowScrollBar(SB_HORZ, FALSE);
	ViewAc->ModifyStyle(WS_HSCROLL, 0, SWP_DRAWFRAME);	
}