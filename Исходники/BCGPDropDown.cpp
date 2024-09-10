//****************************************************************************************
void CBCGPDropDownToolBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rectClient;
	GetClientRect (&rectClient);
	
	if (!m_bCustomizeMode && 
		!rectClient.PtInRect (point))
	{
		CFrameWnd* pParentFrame = GetParentFrame ();
		ASSERT_VALID (pParentFrame);
		
		pParentFrame->DestroyWindow ();
		return;
	}
	
	if (!m_bCustomizeMode && m_iHighlighted >= 0)
	{
		m_iButtonCapture = m_iHighlighted;

		CBCGPToolbarButton* pButton = GetButton (m_iHighlighted);
		ASSERT_VALID (pButton);

		pButton->m_nStyle &= ~TBBS_PRESSED;
	}
	
	CBCGPToolBar::OnLButtonUp (nFlags, point);
}