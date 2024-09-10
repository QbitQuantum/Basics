bool CKinectXboxSyncThread::Initialize()
{
	ILog* iLog = gEnv->pLog;
	m_XboxListenSocket	=	SOCKET_ERROR;

	// Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
	{
		iLog->LogError("ERROR: CKinectXboxSyncThread::Initialize: Failed to initialize Winsock\n");
		return false;
	}

	int Err = SOCKET_ERROR;

	// if IP is provided in CVar then use that one directly, else try to retrieve using XBDM
	string XboxIP = g_pInputCVars->i_kinectXboxConnectIP->GetString();
	if (XboxIP.length() == 0)
		XboxIP = GetXboxIP();

	// if we still don't have a valid IP then don't bother connecting
	if (XboxIP.length() == 0)
	{
		iLog->LogError("ERROR: CKinectXboxSyncThread::Initialize: can't get valid XBox IP address (either have a default Xbox IP in the neighbourhood or provide one with i_kinectXboxConnectIP)\n");
		return false;
	}

	m_XboxListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_XboxListenSocket == INVALID_SOCKET)
	{
		iLog->LogError("ERROR: CKinectXboxSyncThread::Initialize: can't create client socket: error %i\n",m_XboxListenSocket);
		return false;
	}

	int arg = 1;
	setsockopt(m_XboxListenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&arg, sizeof arg);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(g_pInputCVars->i_kinectXboxConnectPort); 
	addr.sin_addr.s_addr = inet_addr(XboxIP.c_str());

	Err = connect(m_XboxListenSocket, (struct sockaddr *)&addr, sizeof addr);

	if(Err<0)
	{
		int WSAError = WSAGetLastError();
		iLog->LogError("ERROR: CKinectXboxSyncThread::Initialize: could not connect to %s (error %i, sys_net_errno=%i)\n", XboxIP.c_str(), Err, WSAError);

		// if buffer is full try sleeping a bit before retrying
		// (if you keep getting this issue then try using same shutdown mechanism as server is doing (see server code))
		// (for more info on windows side check : http://www.proxyplus.cz/faq/articles/EN/art10002.htm)
		if (WSAError == WSAENOBUFS)
		{
			Sleep(5000);
		}

		//socketclose(s);
		//return (size_t)-1;
		struct timeval tv;
		struct fd_set emptySet;
		FD_ZERO(&emptySet);
		tv.tv_sec = 1;
		tv.tv_usec = 0;
		closesocket(m_XboxListenSocket);
		m_XboxListenSocket = INVALID_SOCKET;
		return false;
	}

	if (m_XboxListenSocket == INVALID_SOCKET)
	{
		iLog->LogError("ERROR: CKinectXboxSyncThread::Initialize: invalid socket after trying to connect: error %i, sys_net_errno=%i\n", Err, WSAGetLastError() );
		return false;
	}

	{
		char szIPAddress[1024];
		if(gethostname(szIPAddress, sizeof(szIPAddress)) == SOCKET_ERROR)
		{
			iLog->LogError("ERROR: CKinectXboxSyncThread::Initialize: invalid return value on gethostname: sys_net_errno=%i\n", WSAGetLastError() );
			return false;
		}

		struct hostent *host = gethostbyname(szIPAddress);
		if(host == NULL)
		{
			iLog->LogError("ERROR: CKinectXboxSyncThread::Initialize: invalid return value on gethostbyname: sys_net_errno=%i\n", WSAGetLastError() );
			return false;
		}

		//Obtain the computer's IP
		unsigned char b1, b2, b3, b4;
		b1 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b1;
		b2 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b2;
		b3 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b3;
		b4 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b4;

		sprintf_s(szIPAddress, 128, "%d.%d.%d.%d", b1, b2 , b3, b4);

		// tell the app about our IP address
		char acSendData[128];
		sprintf_s(acSendData, 128, "IP:%s", szIPAddress);
		::send(m_XboxListenSocket, acSendData, 128, 0);
	}

	{
		// tell the app that we are listening
		char acData[128];
		sprintf_s(acData, 128, "Status:2");
		::send(m_XboxListenSocket, acData, 128, 0);
	}

	return true;
}