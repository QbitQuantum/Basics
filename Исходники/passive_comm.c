void runstub(const int port) {
	struct sockaddr_in stSockAddr;
	int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(-1 == SocketFD)
	{
		perror("can not create socket");
		exit(EXIT_FAILURE);
	}

	memset(&stSockAddr, 0, sizeof(stSockAddr));

	stSockAddr.sin_family = AF_INET;
	stSockAddr.sin_port = htons(port);
	stSockAddr.sin_addr.s_addr = INADDR_ANY;

	if(-1 == bind(SocketFD,(struct sockaddr *)&stSockAddr, sizeof(stSockAddr)))
	{
		perror("error bind failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}

	if(-1 == listen(SocketFD, 10))
	{
		perror("error listen failed");
		close(SocketFD);
		exit(EXIT_FAILURE);
	}

	for(;;)
	{
		int ConnectFD = accept(SocketFD, NULL, NULL);

		if(0 > ConnectFD)
		{
			perror("error accept failed");
			close(SocketFD);
			exit(EXIT_FAILURE);
		}

		/* perform read write operations ... 
		   read(ConnectFD,buff,size)*/
		union {
			struct stubdata s;
			struct socket_stubdata ss;
		} u;
		u.ss.fd = ConnectFD;
		u.s.inbuffer  = malloc(sizeof(char) * IN_BUFFER_SIZE);
		u.s.outbuffer = malloc(sizeof(char) * OUT_BUFFER_SIZE);
		u.s.inbuffersize  = 0;
		u.s.outbuffersize = 0;
		// TODO handle malloc errors
		handlestub(&u.s);
		free(u.s.inbuffer);
		free(u.s.outbuffer);

		if (-1 == shutdown(ConnectFD, SHUT_RDWR))
		{
			perror("can not shutdown socket");
			close(ConnectFD);
			exit(EXIT_FAILURE);
		}
		close(ConnectFD);
	}
}