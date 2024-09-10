int			GSocketUdpServer::Send(void *s, unsigned int size)
{
#if defined (GWIN)
	int		rc, err;
	WSABUF	DataBuf;
	DWORD	SendBytes = 0;
	DataBuf.len = size;
	DataBuf.buf = (char *)s;
	rc = WSASendTo(this->_socket, &DataBuf, 1, &SendBytes, NULL, reinterpret_cast <sockaddr*> (&this->_sockaddr), DataBuf.len, NULL, NULL);
	if ((rc == SOCKET_ERROR) && (WSA_IO_PENDING != (err = WSAGetLastError())))
	{
		this->_lastError = GSocketUdpServer::ERROR_SEND;
		throw GException("GSocketUdpServer", "Error WSASend() !");
	}
	return (SendBytes);
#else
	int	l = 0;
	l = sendto(this->_socket, s, size, 0, 0, 0);
	if (l < 0)
	{
		this->_lastError = GSocketUdpServer::ERROR_SEND;
		throw GException("GSocketUdpServer", "Error send() !");
	}
	return (l);
#endif
}