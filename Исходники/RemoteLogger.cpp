int RemoteLogger::connectRemoteServer()
{
	ACE_SOCK_Connector connector;
	ACE_INET_Addr addr(m_remote_addr.c_str());
	m_logger_session = new LoggerSession();
	ACE_Time_Value conn_time_out(1, 0);
	if (connector.connect(m_logger_session->peer(), addr, &conn_time_out) == -1)
	{
		m_remote_logger_enable = false;
		return -1;
	}
	else
	{
		m_logger_session->reactor(NULL);
		m_logger_session->open(NULL);

		m_manage_logger_input.setLoggerSession(m_logger_session, this);
		m_manage_logger_output.setLoggerSession(m_logger_session, this);

		if (m_manage_logger_input.init() == -1)
		{
			return -1;
		}

		if (m_manage_logger_output.init() == -1)
		{
			return -1;
		}

		m_remote_session_reference_no = 2;

		char * first_log = ManageLogger::instance()->getBuffer();
		strcpy(first_log, m_log_identify.c_str());
		memcpy(first_log + m_log_identify.length(), "\n", 1);
		m_manage_logger_output.handleLogBuffer(first_log);

		m_remote_logger_enable = true;

		return 0;
	}
}