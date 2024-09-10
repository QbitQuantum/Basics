int	SockConnector::connect(SockStream &stream, InetAddr &addr, TimeValue &tv)
{	
	int rv = 0;

	// non-block socket
	stream.set_nonblocking();
	
	#ifdef _WIN32

	// connect
	rv = ::connect(stream.get_handle(), (const struct sockaddr *) addr.get_addr(), (socklen_t)addr.get_addr_size());
	if (rv != -1) {
		rv = 0;
	}
	else  {
		if (WSAGetLastError() == WSAEWOULDBLOCK) 
		{
			//printf("connect InProgress [%d]\n", sock);
			fd_set rset;
			fd_set wset;

			FD_ZERO(&rset);
			FD_ZERO(&wset);
			FD_SET(stream.get_handle(), &rset);			
			FD_SET(stream.get_handle(), &wset);			
			
			rv = ::select(0, &rset, &wset, NULL, (struct  timeval*)tv.timeval());
			if (rv == 0) {				
				perror("connect timeout");
				rv = -1;
			}
			else if (FD_ISSET(stream.get_handle(), &rset) || FD_ISSET(stream.get_handle(), &wset)) {
				int error = 0;
				socklen_t len = sizeof(error);
				if (getsockopt(stream.get_handle(), SOL_SOCKET, SO_ERROR, (char *)&error, &len) == 0) {
					// select error
					if (error == 0) {
						rv = 0;
					}
					else {
						closesocket(stream.get_handle());						
						perror("connect");		
						rv = -1;
					}	
				}
			}
			else {
				perror("connect");		
				rv = -1;

			}
		} 
		else {
			perror("connect");
			rv = -1;
		}
	}
	#endif

	// restore file status flags
	stream.set_blocking();
	
	return rv;
}