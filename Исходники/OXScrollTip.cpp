void COXScrollTip::Redraw() 
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Redraws the window with the new rect and text contents
	{
	// First adjust the position
	if (m_bRectChanged)
		{
		// First repaint the area we will not use anymore
		CRect oldRect;
		GetWindowRect(oldRect);
		CRect divRect;
		divRect.SubtractRect(oldRect, m_rect);

		// Move scroll tip window
		SetWindowPos(&CWnd::wndTop, m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(), 
			SWP_NOACTIVATE);

		if (m_bFastBackgroundRepaint)
			RedrawBackground(divRect);
		}

	// Then adjust the text
	if (m_bTextChanged)
		SetWindowText(m_sText);

	// ... If the window is still invisible, show it now
	if (!m_bVisible)
		Show(TRUE);
	ASSERT(m_bVisible);

	// Redraw the window if position or text have changed
	if (m_bRectChanged || m_bTextChanged)
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASENOW);

	m_bRectChanged = FALSE;
	m_bTextChanged = FALSE;
	}