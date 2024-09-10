void CMainWnd::OnDestroy()
{
	WTSUnRegisterSessionNotification(GetSafeHwnd());

	DestroyPcDlg();

	if (m_lpDataXMReceiver != NULL)
	{
		delete m_lpDataXMReceiver;
		m_lpDataXMReceiver = NULL;
	}

	CWnd::OnDestroy();
}