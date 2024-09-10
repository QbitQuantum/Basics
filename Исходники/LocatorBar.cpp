void CLocatorBar::OnMouseMove(UINT nFlags, CPoint point)
{
	m_MousePos = point;
	if (!m_bMouseWithin)
	{
		m_bMouseWithin = TRUE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		_TrackMouseEvent(&tme);
	}

	if (nFlags & MK_LBUTTON)
	{
		CRect rect;
		GetClientRect(rect);
		int nLine = point.y*m_nLines/rect.Height();

		if (nLine < 0)
			nLine = 0;
		if ((m_pMainFrm)&&(m_pMainFrm->m_pwndBottomView))
			m_pMainFrm->m_pwndBottomView->GoToLine(nLine, FALSE);
		if ((m_pMainFrm)&&(m_pMainFrm->m_pwndLeftView))
			m_pMainFrm->m_pwndLeftView->GoToLine(nLine, FALSE);
		if ((m_pMainFrm)&&(m_pMainFrm->m_pwndRightView))
			m_pMainFrm->m_pwndRightView->GoToLine(nLine, FALSE);
	}
	Invalidate();
}