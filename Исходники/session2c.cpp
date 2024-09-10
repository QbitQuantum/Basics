bool Session2c::open()
{
	QMutexLocker ml(&m_mutex);
	// Initialize a "session" that defines who we're going to talk to
	netsnmp_session session;
	initSession(session);

	session.version = SNMP_VERSION_2c;
	
	session.community = new u_char[m_community.length()+1];
	memcpy(session.community, m_community.latin1(), m_community.length()+1);
	session.community_len = m_community.length();
	
	m_session = snmp_open(&session);
	
	delete session.community;
	delete session.peername;
	
	if ( ! m_session )
		return false;
	
	return true;
}