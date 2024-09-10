long CHFServer::Uninitialize()
{
	if (::InterlockedDecrement(&m_nCount) == 0 && m_hThread)
	{
		SetEvent(m_hEventStop);
		//m_Strategy.Stop();
		m_spBatchPerfMon = NULL;
		Terminate();
		return m_nStatus;
	}
	return DBA_ERR_NO_ERROR;
}