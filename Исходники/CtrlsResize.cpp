int CCtrlResize::FixControls()
{
	if (!m_pWnd)
		return 1;

	m_pWnd->GetClientRect(&m_rectInitialParent);
	m_pWnd->ScreenToClient(&m_rectInitialParent);
	
	for (INT_PTR i = 0; i < m_aCtrls.GetSize(); i++) {
		CControlInfo* pInfo = m_aCtrls.GetAt(i);
		CWnd* pControlWnd = pInfo->m_pControlWnd ? pInfo->m_pControlWnd :
			m_pWnd->GetDlgItem (pInfo->controlID);
		if (pControlWnd) {
			pControlWnd->GetWindowRect (&pInfo->rectInitial);
			m_pWnd->ScreenToClient (&pInfo->rectInitial);
		}
	}
	return 0;
}