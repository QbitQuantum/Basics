void CMonitorWnd::UpdateWnd()
{
	if(!IsWindowVisible() || IsIconic())
	{
		return;
	}

	CRect rectContainer;
	GetClientRect(&rectContainer);
	GetShowRect(&rectContainer);
//	rectContainer.DeflateRect(1,1);

	if(m_bAutoAdjustPos)
	{
		AdjustRect(&rectContainer);
	}

	if(m_bMultiScreen)
	{
		CRect rect;
		int nCount = m_PageList.GetCount();
		int i = 0;
		for(POSITION pos = m_PageList.GetHeadPosition(); pos != NULL; i++)
		{
			CWnd *pWnd = m_PageList.GetNext(pos);

			rect = rectContainer;
			CalcPageRect(&rect, i, nCount);
			rect.DeflateRect(WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE); // 窗口之间的间隔
			pWnd->MoveWindow(&rect);
			pWnd->ShowWindow(SW_SHOW);
		}
	}
	else
	{
		for(POSITION pos = m_PageList.GetHeadPosition(); pos!=NULL;)
		{
			CWnd *pWnd = m_PageList.GetNext(pos);
			if(pWnd == m_pActivePage)
			{
				CRect rect = rectContainer;
				rect.DeflateRect(WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE, WINDOW_PAGE_SPACE);
				pWnd->MoveWindow(&rect);
				pWnd->ShowWindow(SW_SHOW);
			}
			else 
			{
				pWnd->MoveWindow(rectContainer.right+1, rectContainer.bottom+1, 1, 1);
//				pWnd->ShowWindow(SW_HIDE);
			}
		}
	}

	if(m_bDrawActive && m_PageList.GetCount() > 1)
	{
		DrawActivePage(TRUE);
	}
}