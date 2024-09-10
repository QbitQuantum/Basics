int _tmain(int argc, _TCHAR* argv[])
{

		
#if defined(TEST)

	WSADATA wsa;	

	//Initialise Winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		printf("WSAStartup() failed.\n");
		return 1;
	}
    printf("Initialised");

	//----------------------
    // Create a SOCKET for connecting to server
	SOCKET ConnectSocket;
    struct sockaddr_in clientService; 

	DWORD locations[3] = {0x00300025,0x002f0025,0x002e0025};
	DWORD timestamp = 0x00fb3000;
	DWORD serverinfo = 0x0002ae05;
	DWORD area = 0x0000138c;
	MovePacket packet(locations,3,timestamp,serverinfo,area);

    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( TEST_SERVER );
    clientService.sin_port = htons( DEFAULT_PORT );

    //----------------------
    // Connect to server.
	int iResult;
    iResult = connect( ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
    if (iResult == SOCKET_ERROR) {
        printf( "connect failed with error: %d\n", WSAGetLastError() );
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
  }

    //----------------------
    // Send an initial buffer
	iResult = send( ConnectSocket, (const char*)packet.GetData(), packet.GetSize(), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send() failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %d\n", iResult);

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

	while(1);

	return 1;
#else

	SOCKET sniffer;
	struct in_addr addr;
	DWORD in;	
	
	char hostname[100];
	struct hostent *local;
	WSADATA wsa;	

	fopen_s(&logfile,"log.txt","w");
	if(logfile==NULL) printf("Unable to create file.");

	//Initialise Winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		printf("WSAStartup() failed.\n");
		return 1;
	}
    printf("Initialised");

		//Create a RAW Socket
	printf("\nCreating RAW Socket...");
	sniffer = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if (sniffer == INVALID_SOCKET)
	{
		printf("Failed to create raw socket.\n");
		return 1;
	}
    printf("Created.");
		
	//Retrive the local hostname
	if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) 
	{
        printf("Error : %d",WSAGetLastError());
		return 1;
    }
	printf("\nHost name : %s \n",hostname);
	
	//Retrive the available IPs of the local host
	local = gethostbyname(hostname);
    printf("\nAvailable Network Interfaces : \n");
	if (local == NULL) 
	{
        printf("Error : %d.\n",WSAGetLastError());
        return 1;
    }

    for (i = 0; local->h_addr_list[i] != 0; ++i) 
	{
		memcpy(&addr, local->h_addr_list[i], sizeof(struct in_addr));
        printf("Interface Number : %d Address : %s\n",i,inet_ntoa(addr));
    }

	printf("Enter the interface number you would like to sniff : ");
	scanf_s("%d",&in);
	
	memset(&dest, 0, sizeof(dest));
	memcpy(&dest.sin_addr.s_addr,local->h_addr_list[in],sizeof(dest.sin_addr.s_addr));
	dest.sin_family      = AF_INET;
	dest.sin_port        = 0;
    
	printf("\nBinding socket to local system and port 0 ...");
	if (bind(sniffer,(struct sockaddr *)&dest,sizeof(dest)) == SOCKET_ERROR)
	{
		printf("bind(%s) failed.\n", inet_ntoa(addr));
		return 1;
	}
    printf("Binding successful"); 
		
	//Enable this socket with the power to sniff : SIO_RCVALL is the key Receive ALL ;)
	
	j=1;
	printf("\nSetting socket to sniff...");
	if (WSAIoctl(sniffer, SIO_RCVALL, &j, sizeof(j), 0, 0, &in,0, 0) == SOCKET_ERROR)
	{
		printf("WSAIoctl() failed.\n");
		return 1;
	}
    printf("Socket set.");
	
	//Begin
	printf("\nStarted Sniffing\n");
	printf("Packet Capture Statistics...\n");
	StartSniffing(sniffer);   //Happy Sniffing
	
	//End
	closesocket(sniffer);
	WSACleanup();

	return 0;
#endif


}