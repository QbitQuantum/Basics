BOOL CTangramTabCtrlWnd::SetActiveTab(int iTab)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int nOldIndex = m_nCurSelTab;
	m_nCurSelTab = iTab;
	BOOL bRet = CMFCTabCtrl::SetActiveTab(iTab);
	//int nIndex = GetCurSel();
	CWnd* pWnd = GetActiveWnd();
	if (pWnd)
	{
		CRect rc;
		pWnd->GetWindowRect(rc);
		CWnd* pPWnd = pWnd->GetParent();
		pPWnd->ScreenToClient(rc);
		::SetWindowPos(pWnd->m_hWnd, NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOACTIVATE);
		Invalidate();
		::SendMessage(m_hWnd, WM_TABCHANGE, m_nCurSelTab, nOldIndex);
	}
	return bRet;// CMFCTabCtrl::SetActiveTab(iTab);
}