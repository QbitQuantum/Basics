bool XAP_Win32Slurp::disconnectSlurper(void)
{
	if (m_hszServerName)
		DdeFreeStringHandle(m_idDdeServerInst,m_hszServerName);
	if (m_hszTopic)
		DdeFreeStringHandle(m_idDdeServerInst,m_hszTopic);
	
	DdeUninitialize(m_idDdeServerInst);
	m_idDdeServerInst = 0;

	m_bInitialized = false;
	return true;
}