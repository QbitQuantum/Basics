eStreamThread::eStreamThread(): m_messagepump(eApp, 0) {
	CONNECT(m_messagepump.recv_msg, eStreamThread::recvEvent);
	m_running = false;
}