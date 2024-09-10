BOOL ClientControlPanelManager::OpenControlPanel( LPCTSTR clientid )
{
	BOOL bAlreadyExists = TRUE;
	CPanelDlg* pPanel = NULL;
	CString strClientId = clientid;

	m_mapSection.Enter();
	{
		PanelMap::iterator iter = m_map.find(strClientId);
		if (iter == m_map.end())
		{
			bAlreadyExists = FALSE;

			pPanel = new CPanelDlg();
			m_map.insert(PanelMap::value_type(strClientId, pPanel));
			pPanel->SetClientID(strClientId);
		}
		else
		{
			pPanel = iter->second;
			SwitchToThisWindow(pPanel->GetSafeHwnd(),TRUE);
			pPanel = NULL;
		}
	}
	m_mapSection.Leave();

	if (NULL != pPanel)
	{
		pPanel->DoModal();
		NotifyControlPanelClosed(strClientId);
	}
	return !bAlreadyExists;
}