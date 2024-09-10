void COXStatusBar::OnLButtonDblClk(UINT nFlags, CPoint point)
	{
	UNREFERENCED_PARAMETER(nFlags);

	CRect PaneRect;
	// first walk through to calculate extra space
	for (int i=0; i < m_nCount; i++)
		{
		GetItemRect(i, PaneRect);
		if (PaneRect.PtInRect(point) != 0)
			{
			GetParent()->SendMessage(WM_STAT_DBLCLICK, (WPARAM)GetItemID(i));
			break;
			}
		}
	
	}