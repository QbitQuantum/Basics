void CDockContext::ToggleDocking()
{
	if (m_pBar->IsFloating())
	{
		// Dock it only if is allowed to be docked
		if (m_pBar->m_dwDockStyle & CBRS_ALIGN_ANY)
		{
			ASSERT((m_uMRUDockID >= AFX_IDW_DOCKBAR_TOP &&
				m_uMRUDockID <= AFX_IDW_DOCKBAR_BOTTOM) ||
				m_uMRUDockID == 0);

			CRect rect = m_rectMRUDockPos;
			CDockBar* pDockBar = NULL;
			if (m_uMRUDockID != 0)
			{
				pDockBar = (CDockBar*)m_pDockSite->GetControlBar(m_uMRUDockID);
				pDockBar->ClientToScreen(&rect);
			}

			// dock it at the specified position, RecalcLayout will snap
			m_pDockSite->ReDockControlBar(m_pBar, pDockBar, &rect);
			m_pDockSite->RecalcLayout();
		}
	}
	else
	{
		CPoint ptFloat = m_ptMRUFloatPos;
		if (ptFloat.x < 0 || ptFloat.y < 0)
		{
			ptFloat = m_rectMRUDockPos.TopLeft();
			m_pBar->GetParent()->ClientToScreen(&ptFloat);
		}
		m_pDockSite->FloatControlBar(m_pBar, ptFloat, m_dwMRUFloatStyle);
	}
}