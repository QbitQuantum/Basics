bool CTlsSocket::CopySessionData(const CTlsSocket* pPrimarySocket)
{
	size_t session_data_size = 0;

	// Get buffer size
	int res = gnutls_session_get_data(pPrimarySocket->m_session, 0, &session_data_size);
	if (res && res != GNUTLS_E_SHORT_MEMORY_BUFFER )
	{
		m_pOwner->LogMessage(Debug_Warning, _T("gnutls_session_get_data on primary socket failed: %d"), res);
		return true;
	}

	// Get session data
	char *session_data = new char[session_data_size];
	res = gnutls_session_get_data(pPrimarySocket->m_session, session_data, &session_data_size);
	if (res)
	{
		delete [] session_data;
		m_pOwner->LogMessage(Debug_Warning, _T("gnutls_session_get_data on primary socket failed: %d"), res);
		return true;
	}

	// Set session data
	res = gnutls_session_set_data(m_session, session_data, session_data_size );
	delete [] session_data;
	if (res)
	{
		m_pOwner->LogMessage(Debug_Info, _T("gnutls_session_set_data failed: %d. Going to reinitialize session."), res);
		UninitSession();
		if (!InitSession())
			return false;
	}
	else
		m_pOwner->LogMessage(Debug_Info, _T("Trying to resume existing TLS session."));

	return true;
}