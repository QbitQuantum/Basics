TCPWin32AccountHandler::TCPWin32AccountHandler()
	: TCPAccountHandler(),
	m_pWin32Dialog(NULL),
	m_hInstance(NULL),
	m_hServerEntry(NULL),
	m_hPortEntry(NULL),
	m_hServerRadio(NULL),
	m_hJoinRadio(NULL),
	m_hServerLabel(NULL),
	m_hPortLabel(NULL),
	m_hAllowAllCheck(NULL),
	m_hAutoconnectCheck(NULL)
{
	AbiCollabSessionManager * pSessionManager = AbiCollabSessionManager::getManager();
	if (pSessionManager)
	{
		m_hInstance = pSessionManager->getInstance();
	}
}