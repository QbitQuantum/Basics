void CTabSplitterWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CSplitterWnd::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	if (m_nCurRow >= 0 && m_nCurCol >= 0) 
	{
		SetActivePane(m_nCurRow,m_nCurCol);
		CWnd *pWnd = GetPane(m_nCurRow,m_nCurCol);
		pWnd->SetFocus();
	}
}