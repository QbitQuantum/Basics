void UDPStream::FlushRecv()
{
	struct timeval time_val;
	time_val.tv_sec = 0;
	time_val.tv_usec = 0;

	fd_set rset;
	FD_ZERO(&rset);
	FD_SET(m_socket, &rset);

	if(select(static_cast<int>(m_socket + 1), &rset, NULL, NULL, &time_val) >= 0)
	{
		if(FD_ISSET(m_socket, &rset) > 0)
		{
			RecvFrom();
		}
	}	
}