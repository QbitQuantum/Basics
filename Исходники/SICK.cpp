int SICK::SICKConnect()
{
	// Declare and initialize variables 	
	WSADATA wsaData;	
	int iResult;	
	//----------------------
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2,1), &wsaData);
	if (iResult != NO_ERROR) {
		m_SickConnectionInfo.m_SICKConnectErrorCode=1;		 //SOCKET初始化错误
		return m_SickConnectionInfo.m_SICKConnectErrorCode ;
	}	
	//----------------------
	// Create a SOCKET for connecting to server
	m_SickConnectionInfo.m_SICKSOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_SickConnectionInfo.m_SICKSOCKET  == INVALID_SOCKET) {
		WSACleanup();
		m_SickConnectionInfo.m_SICKConnectErrorCode=2;		//无法创建客户端SOCKET
		return m_SickConnectionInfo.m_SICKConnectErrorCode ;
	}			
	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	m_SickConnectionInfo.clientService.sin_family = AF_INET;
	CString strSICKIP;
	IN_ADDR ia; 	
	ia.S_un.S_addr=htonl(m_SickSetting.m_SICKIP); 
	strSICKIP=inet_ntoa(ia);
	m_SickConnectionInfo.clientService.sin_addr.s_addr = inet_addr(strSICKIP);
	m_SickConnectionInfo.clientService.sin_port = htons(unsigned short(m_SickSetting.m_SICKPort));	
	//----------------------
	// Connect to server.	
	iResult = connect(m_SickConnectionInfo.m_SICKSOCKET, 
		(SOCKADDR*) &m_SickConnectionInfo.clientService, sizeof(m_SickConnectionInfo.clientService) );
	if ( iResult == SOCKET_ERROR) {
		closesocket (m_SickConnectionInfo.m_SICKSOCKET);
		WSACleanup();
		m_SickConnectionInfo.m_SICKConnectErrorCode=3;		//无法连接服务器
		Invalidate();
		return m_SickConnectionInfo.m_SICKConnectErrorCode ;
	}
	WSAAsyncSelect(m_SickConnectionInfo.m_SICKSOCKET,m_hWnd,WM_SICKSOCKET_READ_CLOSE,FD_READ|FD_CLOSE);
	// 产生相应传递给窗口的消息为WM_LASER_CLIENT_READ_CLOSE ，这是自定义消息	
	//set Laser .	
	m_SickConnectionInfo.m_SICKConnectErrorCode=-1;
	return m_SickConnectionInfo.m_SICKConnectErrorCode;
}