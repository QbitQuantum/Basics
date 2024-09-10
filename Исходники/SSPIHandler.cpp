bool CSSPIHandler::InitProtocol(const char *protocol)
{
	if(QuerySecurityPackageInfoA( (char*)protocol, &m_secPackInfo ) != SEC_E_OK)
		return false;
	if(!m_secPackInfo)
		return false;

	m_currentProtocol = protocol;
	return true;
}