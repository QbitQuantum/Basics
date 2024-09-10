int _tmain(int argc, _TCHAR* argv[])
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
	SOCKET client_socket = INVALID_SOCKET;
    sockaddr_in sock; 

	if(argc < 2)
	{
		Usage();

		return -1;
	}


    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, 
		             &wsaData);
    if (err != 0) 
	{
		// Check if error = WSAVERNOTSUPPORTED and if is --
		// It means ws2_32.dll is too old.  This system needs a serious update.
        wprintf(L"WSAStartup failed with error: %d\n", err);

        return -1;
    }

	//
	// Create a socket 
	//
	client_socket = socket(AF_INET, 
		                   SOCK_STREAM, 
						   IPPROTO_TCP);
    if (client_socket == INVALID_SOCKET) 
	{
        wprintf(L"Create socket failed. Error: %u\n", WSAGetLastError());

        WSACleanup();

        return -1;
    }

	//
	// Fill in sockaddr_in -- Address family, IP address, port
	//
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = inet_addr("127.0.0.1");    //(INADDR_ANY);     //("127.0.0.1");
    sock.sin_port = htons(6000);

	//
	// Connect to server
	//
    err = connect(client_socket, (SOCKADDR *) & sock, sizeof (sock));
    if(err == SOCKET_ERROR) 
	{
        wprintf(L"Connect() failed. Error: %ld\n", WSAGetLastError());

		closesocket(client_socket);
        WSACleanup();

        return -1;
    }

	//
	// Send Command
	//

	if(_wcsicmp(argv[1], L"-heart") == 0)
	{
		SendHeartCheck(client_socket);
	}
	else if(_wcsicmp(argv[1], L"-execute") == 0)
	{
		SendProcessExecute(argv[2],
			               client_socket);
	}
	else if(_wcsicmp(argv[1], L"-kill") == 0)
	{
		SendTerminateProcess(_wtoi(argv[2]),
			                client_socket);
	}
	else if(_wcsicmp(argv[1], L"-ps") == 0)
	{
		SendEnumerateProcess(client_socket);
	}
	else
	{
		wprintf(L"Error: Unkown Command!\n");

		Usage();
	}
	

	//
	// Cleanup
	//

	closesocket(client_socket);
    WSACleanup();

	return 0;
}