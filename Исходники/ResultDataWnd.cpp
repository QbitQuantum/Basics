BOOL CResultDataWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	//let the view to route command
	CWnd* pFocus = GetFocus();
	if (pFocus)
	{
		CWnd* pParent = pFocus->GetParent();

		if (pFocus == &m_grid || pParent == &m_grid || pParent == &m_wndToolBar)
		{
			if (m_grid.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
				return TRUE;
		}

		//if (pFocus == &m_wndToolBar || pParent == &m_wndToolBar)
		//{
	
		//}

	}
	
	if (m_wndToolBar.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	return CDockablePane::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}