/**
 * Initilises the listening socket
 * @param udp_port the UDP listening port  
 */
bool vrpn_Tracker_JsonNet::_network_init(int udp_port) {
	int iResult;
#ifdef _WIN32
	{
		// Initialize Winsock
		WORD versionRequested =  MAKEWORD(2,2);
		WSADATA wsaData;

		iResult = WSAStartup(versionRequested, &wsaData);
		if (iResult != 0) {
		    printf("WSAStartup failed with error: %d\n", iResult);
		    return false;
		}
    }
#endif

#ifdef _WIN32
	{
		// Create a SOCKET for connecting to server
		_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (_socket == INVALID_SOCKET) {
		    printf("socket failed with error: %ld\n", WSAGetLastError());
		    //freeaddrinfo(result);
		    WSACleanup();
		    return false;
		}
	}
#else
	{
		int usock;
		
		usock = socket(PF_INET, SOCK_DGRAM, 0);
	
		if (usock < 0){
			return false;
		}
		_socket = usock;
	}
#endif
	struct sockaddr_in localSocketAddress;
	localSocketAddress.sin_family = AF_INET;
	localSocketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	localSocketAddress.sin_port = htons(udp_port);

    // Setup the listening socket
	iResult = bind( _socket, (struct sockaddr*)&localSocketAddress, sizeof(localSocketAddress));
    if (iResult < 0) {
#ifdef _WIN32
        printf("bind failed with error: %d\n", WSAGetLastError());
#else
        printf("bind failed.");
#endif
        //freeaddrinfo(result);
		_network_release();
        return false;
    }

    //freeaddrinfo(result);
	return true;

}