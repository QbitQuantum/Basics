void CRollupGripper::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rClientRect;
	GetClientRect(&rClientRect);

	if(point.x >= rClientRect.left && point.x <= rClientRect.right &&
		point.y >= rClientRect.top && point.y <= rClientRect.bottom)
	{
		if(!m_bMouseOver)
		{
			m_bMouseOver = true;
			SetCapture();
			if(m_iState < GRIPPER_STATE_MOUSEOVER)
			{
				m_iState = GRIPPER_STATE_MOUSEOVER;
				Invalidate();
			}
		}
	}
	else
	{
		m_bMouseOver = false;

		if(!m_bLButtonDown)
		{
			m_iState = GRIPPER_STATE_NORMAL;
			ReleaseCapture();
			Invalidate();
		}
	}

	if(m_bLButtonDown)
	{
		CWnd* pParent = GetParent();
		if(!pParent) pParent = GetDesktopWindow();

		CRect ParentRect;							// Parent client area (Parent coords)
		pParent->GetClientRect(ParentRect);

		ClientToScreen(&point);						// Convert point to parent coords
		pParent->ScreenToClient(&point);

		CRect ButtonRect;							// Button Dimensions (Parent coords)
		GetWindowRect(ButtonRect);
		pParent->ScreenToClient(ButtonRect);

		if(point != m_cpLastPoint)
		{
			m_iLastMove = m_cpLastPoint.y - point.y;

			if(m_iLastMove != 0)
				GetParent()->SendMessage(WM_COMMAND, USRMSG_GRIPPERMOVE, (long)m_hWnd);

			m_cpLastPoint = point;
		}
	}
	
	CWnd::OnMouseMove(nFlags, point);
}