int WEventSocket::EventSelect(long events)
{
	return WSAEventSelect(m_hSocket,m_hEvent,events);
}