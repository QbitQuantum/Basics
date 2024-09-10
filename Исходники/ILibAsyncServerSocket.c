/*! \fn ILibCreateAsyncServerSocketModule(void *Chain, int MaxConnections, int PortNumber, int initialBufferSize, ILibAsyncServerSocket_OnConnect OnConnect,ILibAsyncServerSocket_OnDisconnect OnDisconnect,ILibAsyncServerSocket_OnReceive OnReceive,ILibAsyncServerSocket_OnInterrupt OnInterrupt, ILibAsyncServerSocket_OnSendOK OnSendOK)
\brief Instantiates a new ILibAsyncServerSocket
\param Chain The chain to add this module to. (Chain must <B>not</B> be running)
\param MaxConnections The max number of simultaneous connections that will be allowed
\param PortNumber The port number to bind to. 0 will select a random port
\param initialBufferSize The initial size of the receive buffer
\param OnConnect Function Pointer that triggers when a connection is established
\param OnDisconnect Function Pointer that triggers when a connection is closed
\param OnReceive Function Pointer that triggers when data is received
\param OnInterrupt Function Pointer that triggers when connection interrupted
\param OnSendOK Function Pointer that triggers when pending sends are complete
\returns An ILibAsyncServerSocket module
*/
ILibAsyncServerSocket_ServerModule ILibCreateAsyncServerSocketModule(void *Chain, int MaxConnections, unsigned short PortNumber, int initialBufferSize, int loopbackFlag, ILibAsyncServerSocket_OnConnect OnConnect, ILibAsyncServerSocket_OnDisconnect OnDisconnect, ILibAsyncServerSocket_OnReceive OnReceive, ILibAsyncServerSocket_OnInterrupt OnInterrupt, ILibAsyncServerSocket_OnSendOK OnSendOK)
{
	int i;
	int ra = 1;
	int off = 0;
	int receivingAddressLength = sizeof(struct sockaddr_in6);
	struct sockaddr_in6 localif;
	struct sockaddr_in6 localAddress;
	struct ILibAsyncServerSocketModule *RetVal;

	memset(&localif, 0, sizeof(struct sockaddr_in6));
	if (loopbackFlag != 2 && ILibDetectIPv6Support())
	{
		// Setup the IPv6 any or loopback address, this socket will also work for IPv4 traffic on IPv6 stack
		localif.sin6_family = AF_INET6;
		localif.sin6_addr = (loopbackFlag != 0?in6addr_loopback:in6addr_any);
		localif.sin6_port = htons(PortNumber);
	}
	else
	{
		// IPv4-only detected
		localif.sin6_family = AF_INET;
#ifdef WINSOCK2
		((struct sockaddr_in*)&localif)->sin_addr.S_un.S_addr = htonl((loopbackFlag != 0?INADDR_LOOPBACK:INADDR_ANY));
#else 
		((struct sockaddr_in*)&localif)->sin_addr.s_addr = htonl((loopbackFlag != 0?INADDR_LOOPBACK:INADDR_ANY));
#endif
		((struct sockaddr_in*)&localif)->sin_port = htons(PortNumber);
	}

	// Instantiate a new AsyncServer module
	RetVal = (struct ILibAsyncServerSocketModule*)malloc(sizeof(struct ILibAsyncServerSocketModule));
	if (RetVal == NULL) { ILIBMARKPOSITION(253); return NULL; }
	memset(RetVal, 0, sizeof(struct ILibAsyncServerSocketModule));
	RetVal->PreSelect = &ILibAsyncServerSocket_PreSelect;
	RetVal->PostSelect = &ILibAsyncServerSocket_PostSelect;
	RetVal->Destroy = &ILibAsyncServerSocket_Destroy;
	RetVal->Chain = Chain;
	RetVal->OnConnect = OnConnect;
	RetVal->OnDisconnect = OnDisconnect;
	RetVal->OnInterrupt = OnInterrupt;
	RetVal->OnSendOK = OnSendOK;
	RetVal->OnReceive = OnReceive;
	RetVal->MaxConnection = MaxConnections;
	RetVal->AsyncSockets = (void**)malloc(MaxConnections * sizeof(void*));
	if (RetVal->AsyncSockets == NULL) { free(RetVal); ILIBMARKPOSITION(253); return NULL; }
	RetVal->portNumber = (unsigned short)PortNumber;

	// Get our listening socket
	if ((RetVal->ListenSocket = socket(localif.sin6_family, SOCK_STREAM, IPPROTO_TCP)) == -1) { free(RetVal->AsyncSockets); free(RetVal); return 0; }

	// Setup the IPv6 & IPv4 support on same socket
	if (localif.sin6_family == AF_INET6) if (setsockopt(RetVal->ListenSocket, IPPROTO_IPV6, IPV6_V6ONLY, (char*)&off, sizeof(off)) != 0) ILIBCRITICALERREXIT(253);

#if defined(WIN32)
	// On Windows. Lets make sure no one else can bind to this addr/port. This stops socket hijacking (not a problem on Linux).
	if (setsockopt(RetVal->ListenSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&ra, sizeof(ra)) != 0) ILIBCRITICALERREXIT(253);
#else
	// On Linux. Setting the re-use on a TCP socket allows reuse of the socket even in timeout state. Allows for fast stop/start (Not a problem on Windows).
	if (setsockopt(RetVal->ListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&ra, sizeof(ra)) != 0) ILIBCRITICALERREXIT(253);
#endif

	// Bind the socket
#if defined(WIN32)
	if (bind(RetVal->ListenSocket, (struct sockaddr*)&localif, INET_SOCKADDR_LENGTH(localif.sin6_family)) != 0) { closesocket(RetVal->ListenSocket); free(RetVal->AsyncSockets); free(RetVal); return 0; }
#else
	if (bind(RetVal->ListenSocket, (struct sockaddr*)&localif, INET_SOCKADDR_LENGTH(localif.sin6_family)) != 0) { close(RetVal->ListenSocket); free(RetVal->AsyncSockets); free(RetVal); return 0; }
#endif

	// Fetch the local port number
#if defined(WINSOCK2)
	getsockname(RetVal->ListenSocket, (struct sockaddr*)&localAddress, (int*)&receivingAddressLength);
#else
	getsockname(RetVal->ListenSocket, (struct sockaddr*)&localAddress, (socklen_t*)&receivingAddressLength);
#endif
	if (localAddress.sin6_family == AF_INET6) RetVal->portNumber = ntohs(localAddress.sin6_port); else RetVal->portNumber = ntohs(((struct sockaddr_in*)&localAddress)->sin_port);

	// Create our socket pool
	for(i = 0; i < MaxConnections; ++i)
	{
		RetVal->AsyncSockets[i] = ILibCreateAsyncSocketModule(Chain, initialBufferSize, &ILibAsyncServerSocket_OnData, &ILibAsyncServerSocket_OnConnectSink, &ILibAsyncServerSocket_OnDisconnectSink, &ILibAsyncServerSocket_OnSendOKSink);
		//
		// We want to know about any buffer reallocations, because anything above us may want to know
		//
		ILibAsyncSocket_SetReAllocateNotificationCallback(RetVal->AsyncSockets[i], &ILibAsyncServerSocket_OnBufferReAllocated);
	}
	ILibAddToChain(Chain,RetVal);

	return(RetVal);
}