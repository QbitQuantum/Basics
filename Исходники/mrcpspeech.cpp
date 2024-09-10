MrcpConnection::~MrcpConnection()
{
    s_mutex.lock();
    s_conns.remove(this,false);
    s_mutex.unlock();
    if (m_socket) {
	m_socket->terminate();
	delete m_socket;
	m_socket = 0;
    }
}