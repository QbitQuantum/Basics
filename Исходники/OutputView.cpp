BOOL COutputView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	//let the trl to route command
	CWnd* pFocus = GetFocus();
	if (pFocus)
	{
		CWnd* pParent = pFocus->GetParent();

		if (pFocus == &m_progressWnd || pParent == &m_progressWnd )
		{
			if (m_progressWnd.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
				return TRUE;
		}

		if (pFocus == &m_messageWnd || pParent == &m_messageWnd)
		{
			if (m_messageWnd.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
				return TRUE;
		}

		
	}

	return CView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}