void CFlatToolbar::OnCancelMode()
{
	CControlBar::OnCancelMode();

	if (m_iButtonCapture >= 0)
	{
		AFX_TBBUTTON* pTBB = _GetButtonPtr(m_iButtonCapture);
		ASSERT(!(pTBB->nStyle & TBBS_SEPARATOR));
		UINT nNewStyle = (pTBB->nStyle & ~TBBS_PRESSED);
		if (GetCapture() == this)
			ReleaseCapture();
		SetButtonStyle(m_iButtonCapture, nNewStyle);
		m_iButtonCapture = -1;
		UpdateWindow();
	}
}