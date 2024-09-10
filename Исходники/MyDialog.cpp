void CMyDialog::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bTracked)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = 1;
		m_bTracked = _TrackMouseEvent(&tme);
		m_bTracked=TRUE;
	}
	if (point.y<=30)
	{
		if (m_rcClose.PtInRect(point))
		{
			if (!m_bCloseHover)
			{
				m_bCloseHover=TRUE;
				DrawCloseButton(GetDC(),DTS_HOVER);
				m_bMinHover=FALSE;
				DrawMinButton(GetDC(),DTS_NORMAL);
			}
		}
		else if (m_rcMin.PtInRect(point))
		{
			if (!m_bMinHover)
			{
				m_bMinHover=TRUE;
				DrawMinButton(GetDC(),DTS_HOVER);
				m_bCloseHover=FALSE;
				DrawCloseButton(GetDC(),DTS_NORMAL);
			}
		}
		else
		{
			if (m_bCloseHover)
			{
				m_bCloseHover=FALSE;
				DrawCloseButton(GetDC(),DTS_NORMAL);
			}
			if (m_bMinHover)
			{
				m_bMinHover=FALSE;
				DrawMinButton(GetDC(),DTS_NORMAL);
			}
		}
	}

	CDialog::OnMouseMove(nFlags, point);
}