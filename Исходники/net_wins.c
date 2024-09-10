int WINS_Init (void)
{
	int		i;
	struct hostent *local = NULL;
	char	buff[MAXHOSTNAMELEN];
	struct qsockaddr addr;
	char	*p;
	int		r;
	WORD	wVersionRequested;

// initialize the Winsock function vectors (we do this instead of statically linking
// so we can run on Win 3.1, where there isn't necessarily Winsock)
    hInst = LoadLibrary("wsock32.dll");
	
	if (hInst == NULL)
	{
		Con_SafePrintf ("Failed to load winsock.dll\n");
		winsock_lib_initialized = false;
		return -1;
	}

	winsock_lib_initialized = true;

    pWSAStartup = (void *)GetProcAddress(hInst, "WSAStartup");
    pWSACleanup = (void *)GetProcAddress(hInst, "WSACleanup");
    pWSAGetLastError = (void *)GetProcAddress(hInst, "WSAGetLastError");
    psocket = (void *)GetProcAddress(hInst, "socket");
    pioctlsocket = (void *)GetProcAddress(hInst, "ioctlsocket");
    psetsockopt = (void *)GetProcAddress(hInst, "setsockopt");
    precvfrom = (void *)GetProcAddress(hInst, "recvfrom");
    psendto = (void *)GetProcAddress(hInst, "sendto");
    pclosesocket = (void *)GetProcAddress(hInst, "closesocket");
    pgethostname = (void *)GetProcAddress(hInst, "gethostname");
    pgethostbyname = (void *)GetProcAddress(hInst, "gethostbyname");
    pgethostbyaddr = (void *)GetProcAddress(hInst, "gethostbyaddr");
    pgetsockname = (void *)GetProcAddress(hInst, "getsockname");

    if (!pWSAStartup || !pWSACleanup || !pWSAGetLastError ||
		!psocket || !pioctlsocket || !psetsockopt ||
		!precvfrom || !psendto || !pclosesocket ||
		!pgethostname || !pgethostbyname || !pgethostbyaddr ||
		!pgetsockname)
	{
		Con_SafePrintf ("Couldn't GetProcAddress from winsock.dll\n");
		return -1;
	}

	if (COM_CheckParm ("-noudp"))
		return -1;

	if (winsock_initialized == 0)
	{
		wVersionRequested = MAKEWORD(1, 1); 

		r = pWSAStartup (MAKEWORD(1, 1), &winsockdata);

		if (r)
		{
			Con_SafePrintf ("Winsock initialization failed.\n");
			return -1;
		}
	}
	winsock_initialized++;

	// determine my name & address
	if (pgethostname(buff, MAXHOSTNAMELEN) == 0)
	{
		blocktime = Sys_FloatTime();
		WSASetBlockingHook(BlockingHook);
		local = pgethostbyname(buff);
		WSAUnhookBlockingHook();
		if (local == NULL)
		{
			Con_DPrintf ("Winsock TCP/IP Initialization timed out.\n");
			if (--winsock_initialized == 0)
				pWSACleanup ();
			return -1;
		}
	}

	if (local)
	{
		myAddr = *(int *)local->h_addr_list[0];

		// if the quake hostname isn't set, set it to the machine name
		if (strcmp(hostname.string, "UNNAMED") == 0)
		{
			// see if it's a text IP address (well, close enough)
			for (p = buff; *p; p++)
				if ((*p < '0' || *p > '9') && *p != '.')
					break;

			// if it is a real name, strip off the domain; we only want the host
			if (*p)
			{
				for (i = 0; i < 15; i++)
					if (buff[i] == '.')
						break;
				buff[i] = 0;
			}
			Cvar_Set ("hostname", buff);
		}
	}

	if ((net_controlsocket = WINS_OpenSocket (0)) == -1)
	{
		Con_Printf("WINS_Init: Unable to open control socket\n");
		if (--winsock_initialized == 0)
			pWSACleanup ();
		return -1;
	}

	((struct sockaddr_in *)&broadcastaddr)->sin_family = AF_INET;
	((struct sockaddr_in *)&broadcastaddr)->sin_addr.s_addr = INADDR_BROADCAST;
	((struct sockaddr_in *)&broadcastaddr)->sin_port = htons((unsigned short)net_hostport);

	WINS_GetSocketAddr (net_controlsocket, &addr);
	strcpy(my_tcpip_address,  WINS_AddrToString (&addr));
	p = strrchr (my_tcpip_address, ':');
	if (p)
		*p = 0;

	Con_Printf("Winsock TCP/IP Initialized\n");
	tcpipAvailable = true;

	return net_controlsocket;
}