	~dht_server()
	{
		m_socket.cancel();
		m_socket.close();
		if (m_thread) m_thread->join();
	}