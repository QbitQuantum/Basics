void COXDockTabCtrl::ShowSelectedTab()
{
	int iSelected = GetCurSel();

	// Show first
	for (int i = 0; i < GetItemCount(); i++)
	{
		CControlBar* pBar = GetBar(i);
		if (iSelected == i)
		{
			pBar->GetDockingFrame()->ShowControlBar(pBar, TRUE, TRUE); // show
		}
		else
		{
			pBar->GetDockingFrame()->ShowControlBar(pBar, FALSE, TRUE); // hide
		}
	}

	CRect rect;
	m_pSizeDockBar->GetClientRect(rect);

	CControlBar* pBar = GetBar(iSelected);
	if (pBar != NULL)
	{
		COXSizeControlBar* pSizeBar = DYNAMIC_DOWNCAST(COXSizeControlBar, pBar);
		if (m_pSizeDockBar->IsBarHorizontal())
		{
			if (m_pLastSelectedBar != NULL)
			{
				pSizeBar->m_HorzDockSize.cx = m_pLastSelectedBar->m_HorzDockSize.cx;
			}
			m_pLastSelectedBar = pSizeBar;
		}
		else // vertical
		{
			CFrameWnd* pMF = (CFrameWnd*) GetParentFrame();//AfxGetMainWnd();
			if (pMF != NULL)
			{
				if (pMF->GetControlBar(AFX_IDW_DOCKBAR_LEFT) == m_pSizeDockBar)
					rect.right -= 3;

				if (pMF->GetControlBar(AFX_IDW_DOCKBAR_RIGHT) == m_pSizeDockBar)
					rect.left += 4;
			}
			
			rect.bottom -= m_pSizeDockBar->GetTabHeight();

			pBar->MoveWindow(rect, TRUE);

			COXSizeControlBar* pSizeBar = DYNAMIC_DOWNCAST(COXSizeControlBar, pBar);
			if (pSizeBar)
			{
				pSizeBar->m_VertDockSize.cx = rect.Width();
				pSizeBar->m_VertDockSize.cy = rect.Height() + 5;
			}
		}
	}
}