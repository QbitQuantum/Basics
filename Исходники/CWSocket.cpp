ISocket					*CWSocket::receivUdp(char *message, int size, int *received)
{
	sockaddr_in			tmpInfo;
	int					sizeTmp = sizeof(tmpInfo);
	DWORD				flags;
	WSABUF				dataBuf;

	if ((this->_type != ISocket::UDP) || (this->_sock == -1) || (this->_func == ISocket::CLIENT))
		throw Exception("This socket type isn't valid.");
	if (this->_func == ISocket::NONE)
		throw Exception("This socket type isn't initialized.");
	CWSocket			*newSocket = new CWSocket(this);
	dataBuf.buf = message;
	dataBuf.len = size;
	flags = 0;
	if (WSARecvFrom(this->_sock, &dataBuf, 1, (DWORD *)received, &flags, (SOCKADDR*)&tmpInfo, &sizeTmp, NULL, NULL) != 0)
		throw Exception("WSARecvFrom has failed.");
	newSocket->setInfo(tmpInfo);
	return (newSocket);
}