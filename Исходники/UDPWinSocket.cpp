bool	UDPWinSocket::Send_data(ClientMessage *send_msg)
{
	DWORD				send_flags = 0;
	DWORD				sent_bytes = 0;
	WSABUF				sendbuff[1];
	char				buff[8192];
	int					server_length;

	sendbuff[0].len = 8192;
	sendbuff[0].buf = buff;
	server_length = (int)sizeof(struct sockaddr_in);

	//on memset le buff
	memset(buff, '\0', 8192);
	//on copie les bails
	memcpy(&buff, (void *)send_msg, sizeof(ClientMessage));
	if ((WSASendTo(_socket, sendbuff, 1, &sent_bytes, send_flags, (struct sockaddr *)&_server, server_length, NULL, NULL)) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
			return (true);
		else
		{
			std::cerr << "coudldn't use send to" << std::endl;
			return (true);
		}
	}
	return (true);
}