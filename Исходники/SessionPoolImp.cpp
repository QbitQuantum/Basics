Session_t SessionPoolImp::ISessionPool_connect(const string & connect_addr)
{
	ACE_SOCK_Connector connector;
	ACE_INET_Addr addr;
	
	addr.set(connect_addr.c_str());
	CellSession * cell_session = new CellSession(true);

	if (connector.connect(cell_session->peer(), addr) == -1)
	{
		DEF_LOG_ERROR("failed to connect the addr : <%s>, last error is <%d>\n", connect_addr.c_str(), ACE_OS::last_error());
		return 0;
	}

	if (cell_session->setReadEvent() == -1)
	{
		DEF_LOG_ERROR("failed to call open of cell session, last error is <%d>\n", ACE_OS::last_error());
		return 0;
	}

	if (m_socket_intput_buffer_size > 0)
	{
		cell_session->setBufSize(m_socket_intput_buffer_size, m_socket_output_buffer_size);
	}

	cell_session->setHandleInput(this);
	m_input_session_pool.handleSession(cell_session);
	m_output_session_pool.handleSession(cell_session);


	DEF_LOG_INFO("success to connect the addr <%s>\n", connect_addr.c_str());
	if (NULL != m_handle_session_event)
	{
		m_handle_session_event->ISessionPoolEvent_newConnection(cell_session, cell_session->isClientSide());
	}

	return cell_session;
}