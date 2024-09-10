DROPEFFECT CBCGPPlannerDropTarget::OnDragScroll(CWnd* pWnd, DWORD dwKeyState, CPoint point)
{
	if (m_pPlanner == NULL)
	{
		return DROPEFFECT_NONE;
	}

	ASSERT_VALID (m_pPlanner);

	DROPEFFECT dropEffect = m_pPlanner->OnDragScroll(dwKeyState, point);

	// DROPEFFECT_SCROLL means do the default
	if (dropEffect != DROPEFFECT_SCROLL)
		return dropEffect;

	// get client rectangle of destination window
	CRect rectClient;
	m_pPlanner->GetDragScrollRect(rectClient);
	CRect rect = rectClient;

	// hit-test against inset region
	UINT nTimerID = MAKEWORD(-1, -1);
	rect.InflateRect(-nScrollInset, -nScrollInset);

	if (rectClient.PtInRect(point) && !rect.PtInRect(point))
	{
		// determine which way to scroll along both X & Y axis
		if (point.x < rect.left)
		{
			nTimerID = MAKEWORD(SB_LINEUP, HIBYTE(nTimerID));
		}
		else if (point.x >= rect.right)
		{
			nTimerID = MAKEWORD(SB_LINEDOWN, HIBYTE(nTimerID));
		}

		if (point.y < rect.top)
		{
			nTimerID = MAKEWORD(LOBYTE(nTimerID), SB_LINEUP);
		}
		else if (point.y >= rect.bottom)
		{
			nTimerID = MAKEWORD(LOBYTE(nTimerID), SB_LINEDOWN);
		}

		ASSERT(nTimerID != MAKEWORD(-1, -1));

		BOOL bEnableScroll = m_pPlanner->OnScroll(nTimerID, 0, FALSE);

		if (!bEnableScroll)
		{
			nTimerID = MAKEWORD(-1, -1);
		}
	}

	if (m_nTimerID == MAKEWORD(-1, -1) && nTimerID != MAKEWORD(-1, -1))
	{
		// send fake OnDragEnter when transition from scroll->normal
		COleDataObject dataObject;
		dataObject.Attach(m_lpDataObject, FALSE);
		OnDragEnter(pWnd, &dataObject, dwKeyState, point);
	}

	if (nTimerID == MAKEWORD(-1, -1))
	{
		if (m_nTimerID != MAKEWORD(-1, -1))
		{
			// send fake OnDragEnter when transition from scroll->normal
			//COleDataObject dataObject;
			//dataObject.Attach(m_lpDataObject, FALSE);
			//OnDragEnter(pWnd, &dataObject, dwKeyState, point);
			m_nTimerID = MAKEWORD(-1, -1);
		}
		
		return DROPEFFECT_NONE;
	}

	// save tick count when timer ID changes
	DWORD dwTick = GetTickCount();
	if (nTimerID != m_nTimerID)
	{
		m_dwLastTick = dwTick;
		m_nScrollDelay = nScrollDelay;
	}

	// scroll if necessary
	if (dwTick - m_dwLastTick > m_nScrollDelay)
	{
		m_pPlanner->OnScroll(nTimerID, 0, TRUE);

		m_dwLastTick = dwTick;
		m_nScrollDelay = nScrollInterval;
	}
	
	if (m_nTimerID == MAKEWORD(-1, -1))
	{
		// send fake OnDragLeave when transitioning from normal->scroll
		//OnDragLeave(pWnd);
	}

	m_nTimerID = nTimerID;
/*
	// check for force link
	if ((dwKeyState & (MK_CONTROL | MK_SHIFT)) == (MK_CONTROL | MK_SHIFT))
		dropEffect = DROPEFFECT_SCROLL|DROPEFFECT_LINK;
	// check for force copy
	else */if ((dwKeyState & MK_CONTROL) == MK_CONTROL)
		dropEffect = DROPEFFECT_SCROLL | DROPEFFECT_COPY;
	// check for force move
	else if ((dwKeyState & MK_ALT) == MK_ALT ||
		(dwKeyState & MK_SHIFT) == MK_SHIFT)
		dropEffect = DROPEFFECT_SCROLL | DROPEFFECT_MOVE;
	// default -- recommended action is move
	else
		dropEffect = DROPEFFECT_SCROLL | DROPEFFECT_MOVE;
	
	return dropEffect;
}