bool		TCPWinServSocket::Connect(int port, Selector &sel)
{
	struct sockaddr_in    s_in;
	u_short				  ret;

	// Socket creation
	_fathersocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, NULL, WSA_FLAG_OVERLAPPED);
	if (_fathersocket == INVALID_SOCKET)
		return (false);
	//Socket binding
	s_in.sin_family = AF_INET;
	s_in.sin_addr.s_addr = INADDR_ANY;
	if ((WSAHtons(_fathersocket, port, &ret)) == SOCKET_ERROR)
		return (false);
	
	s_in.sin_port = ret;
	if ((bind(_fathersocket, (const struct sockaddr *)&s_in, sizeof(s_in))) == SOCKET_ERROR)
		return (false);

	//Socket listening
	if ((listen(_fathersocket, SOMAXCONN)) == SOCKET_ERROR)
		return (false);
	//Add to selector for monitoring
	sel.Add_to_checkread(_fathersocket);
	return (true);
}