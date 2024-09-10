void FW_DropDownWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_buttonRect.PtInRect(point))
	{
		// Raise the button if it is not already.
		if (m_nDropDownState != 1)
		{
			m_nDropDownState = 1;
			Invalidate();

			// Start mouse tracking if it is not already running.
			if (!m_bMouseTracking)
			{
				TRACKMOUSEEVENT tme;
				memset(&tme, 0, sizeof(tme));
				tme.cbSize = sizeof(tme);
				tme.hwndTrack = GetSafeHwnd();
				tme.dwFlags = TME_LEAVE;
				if (_TrackMouseEvent(&tme))
					m_bMouseTracking = true;
			}
		}
	}

	// Reset the button if it is raised.
	else if (m_nDropDownState == 1)
	{
		m_nDropDownState = 0;
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}