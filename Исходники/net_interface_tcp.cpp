net_socket* net_interface_tcp::connect(const char* c_host, int port)
{
	assert(c_host);
	assert(port > 0);

	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		fprintf(stderr, "can't open listen socket\n");
		return NULL;
	}

	// Set the address.
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	m_port_number = get_proxy_port() > 0 ? get_proxy_port() : port;
	saddr.sin_port = htons(m_port_number);


	hostent* he;
	const char* host = get_proxy_port() > 0 ? get_proxy() : c_host;
	if (host[0] >= '0' && host[0] <= '9')	// absolue address ?
	{
		Uint32 addr = inet_addr(host);
		he = gethostbyaddr((char *) &addr, 4, AF_INET);
	}
	else
	{
		he = gethostbyname(host);
	}

	if (he == NULL)
	{
		fprintf(stderr, "can't find '%s'\n", host);
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		return NULL;
	}

	// get server address
	memcpy(&saddr.sin_addr, he->h_addr, he->h_length);

	//      printf("The IP address is '%d.%d.%d.%d'\n", 
	//				saddr.sin_addr.S_un.S_un_b.s_b1,
	//				saddr.sin_addr.S_un.S_un_b.s_b2,
	//				saddr.sin_addr.S_un.S_un_b.s_b3,
	//				saddr.sin_addr.S_un.S_un_b.s_b4);

	int rc = ::connect(m_socket, (struct sockaddr*) &saddr, sizeof(struct sockaddr));
	if (rc != 0)
	{
		fprintf(stderr, "can't connect to '%s', port %d\n", host, m_port_number);
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		return NULL;
	}

	// Set non-blocking mode for the socket, so that
	// accept() doesn't block if there's no pending
	// connection.
	set_nonblock();

	return new net_socket_tcp(m_socket);
}