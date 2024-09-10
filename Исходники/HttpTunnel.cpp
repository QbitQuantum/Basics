DWORD HttpTunnel::InitializeLocalConnection()
{
	struct sockaddr_in Sin;
	USHORT  LocalPort         = 0;
	DWORD Attempts            = 0;
	DWORD Result              = ERROR_SUCCESS;
	HMODULE hWinsock          = NULL;
	WSASOCKETA pWSASocketA    = NULL;
	WSADATA wsaData;

	hWinsock = LoadLibraryA( "WS2_32.DLL" );
	if( hWinsock == NULL )
	{
  		CPassiveX::Log( TEXT("DownloadSecondStage(): LoadLibraryA for WS2_32.DLL failed.\n") );
		return !ERROR_SUCCESS;
	}

	pWSASocketA = (WSASOCKETA)GetProcAddress( hWinsock, "WSASocketA");
	if( pWSASocketA == NULL )
	{
  		CPassiveX::Log( TEXT("DownloadSecondStage(): GetProcAddress for WSASocketA failed.\n") );
		return !ERROR_SUCCESS;
	}

	if( WSAStartup( MAKEWORD(2,2), &wsaData ) !=  0 )
	{
  		CPassiveX::Log( TEXT("DownloadSecondStage(): WSAStartup failed.\n") );
		return !ERROR_SUCCESS;
	}

	do
	{
		// Create the TCP listener socket
		//LocalTcpListener = pWSASocketA( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0 ,0 );
		LocalTcpListener = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( LocalTcpListener == INVALID_SOCKET )
		{
			LocalTcpListener = 0;
			Result           = WSAGetLastError();
			break;
		}

		// Create the TCP client socket
		LocalTcpClientSide = pWSASocketA( AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0 ,0 );
		if( LocalTcpClientSide == INVALID_SOCKET )
		{
			LocalTcpClientSide = 0;
			Result             = WSAGetLastError();
			break;
		}

		Sin.sin_family      = AF_INET;
		Sin.sin_addr.s_addr = inet_addr("127.0.0.1");

		// Try 256 times to pick a random port
		Sin.sin_port = htons(LocalPort = (rand() % 32000) + 1025);

		while( ( bind( LocalTcpListener, (struct sockaddr *)&Sin, sizeof(Sin) ) == SOCKET_ERROR ) && (Attempts++ < 256) )
		{
			Sin.sin_port = htons(LocalPort = (rand() % 32000) + 1025);
		}

		// If we failed to create the local listener, bomb out
		if (Attempts >= 256)
		{
			Result = WSAGetLastError();
			break;
		}

		// Listen and stuff
		if (listen( LocalTcpListener, 1) == SOCKET_ERROR)
		{
			Result = WSAGetLastError();
			break;
		}

		// Establish a connection to the local listener
		if (connect( LocalTcpClientSide, (struct sockaddr *)&Sin, sizeof(Sin)) == SOCKET_ERROR)
		{
			Result = WSAGetLastError();
			break;
		}

		// Accept the local TCP connection
		if ((LocalTcpServerSide = accept( LocalTcpListener, NULL, NULL)) == SOCKET_ERROR)
		{
			LocalTcpServerSide = 0;
			Result = WSAGetLastError();
			break;
		}

		// Woop!
		Result = ERROR_SUCCESS;

	} while (0);

	return Result;
}