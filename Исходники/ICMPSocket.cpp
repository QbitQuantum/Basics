BOOL ICMPSocket::Create( LPCTSTR listenIPOrHost )
{
	tstring iporhost;
	if (NULL == listenIPOrHost)
	{
		char hostname[128] = {0};
		gethostname(hostname, 128);
		iporhost = a2t(hostname);
	}
	else
	{
		iporhost = listenIPOrHost;
	}

	Close();

	m_listenIP = INADDR_NONE;
	if (! MySocket::IPOrHostname2IP(iporhost.c_str(), m_listenIP))
	{
		errorLog(_T("invalid listeniporhost [%s]"), listenIPOrHost);
		return FALSE;
	}

	if (! CreateListenSocket(m_listenIP, m_sock))
	{
		errorLog(_T("create listen socket failed"));
		m_sock = INVALID_SOCKET;

		return FALSE;
	}

	return TRUE;
}