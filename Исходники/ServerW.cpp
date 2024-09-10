void	ServerW::init()
{
	WSADATA			wsaData;
	SOCKADDR_IN		sin;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		throw(std::exception("Error on WSAStartup"));

	_socket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (_socket == INVALID_SOCKET)
		throw(std::exception("Error on WSASocketW"));

	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4242);
	if ((bind(_socket, (struct sockaddr*)&sin, sizeof(sin)) == -1)
		|| (listen(_socket, SOMAXCONN) == -1))
		throw(std::exception("Error on bind or listen"));

	memset(_fdType, FD_FREE, MAX_FD);
	_fdType[_socket] = FD_SERVER;
}