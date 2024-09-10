int		UDPClientSocketWindows::SNWrite(const char *msg, unsigned int size)
{
	WSABUF	DataBuff;
	DWORD SendBytes;
	DWORD Flags = 0;

	DataBuff.buf = const_cast <char *> (msg);
	DataBuff.len = size;
	if (WSASendTo(this->_socket, &DataBuff, 1, &SendBytes, Flags, (SOCKADDR *)&(this->_servaddr), sizeof(this->_servaddr), NULL, NULL) == SOCKET_ERROR)
		{
			this->_error = CANTWRITE;
			return (-1);
		}
	this->_error = NOERRORSOCKET;
	return (SendBytes);
}