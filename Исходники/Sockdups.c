void DoParent(char *pszIPAddress, char *pszPort, char *pszChildProcName)
{
    int nFromLen;
    SOCKADDR_STORAGE saFrom;
    DWORD dwProcID;
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo *pAddr;
    int i;

    // Install the CTRL+BREAK and CTRL+C Handler
    if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleCtrlHandler,
                TRUE)
            == FALSE) 
        fprintf(stderr,"SetConsoleCtrlHandler failed: %d", GetLastError());

    dwProcID = GetCurrentProcessId();

    printf("Parent process %lu started ...\n", dwProcID);

    // prepare the hints for the type of socket we are interested in.
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // since we're going to bind on this socket.

    // getaddrinfo is the protocol independent version of GetHostByName.
    // the res contains the result.
    if (getaddrinfo(pszIPAddress, 
                pszPort,
                &hints, 
                &res) != NO_ERROR)
    {
        fprintf(stderr,"getaddrinfo failed. Error = %d\n", WSAGetLastError());
        goto CLEANUP;
    }

    printf("getaddrinfo successful.Enumerating the returned addresses ...\n\n");

    // for each returned interface, create a listening socket.
    gsListen = INVALID_SOCKET;
    for (pAddr = res, i = 1; pAddr != NULL; pAddr = pAddr->ai_next, i++)
    {
        printf("Trying Address : %d from getaddrinfo\n", i);
        PrintAddressString(pAddr->ai_addr, (DWORD) pAddr->ai_addrlen);
        // create a suitable socket for this interface.
        gsListen = WSASocket(pAddr->ai_family, 
                pAddr->ai_socktype,
                pAddr->ai_protocol,
                NULL,
                0,
                0);
        if (gsListen != INVALID_SOCKET)
            break;

        fprintf(stderr,"WSASocket failed. Error = %d\n", WSAGetLastError());
        fprintf(stderr,"Ignoring this address and continuing with the next. \n\n");
    }

    if (pAddr == NULL)
    {
        fprintf(stderr, "Couldn't find any suitable socket\n");
        goto CLEANUP;
    }

    gsListen = WSASocket(pAddr->ai_family,
            pAddr->ai_socktype,
            pAddr->ai_protocol,
            (LPWSAPROTOCOL_INFO) NULL,
            0,
            WSA_FLAG_OVERLAPPED);

    if (gsListen == INVALID_SOCKET)
    {
        fprintf(stderr, "\nWSASocket() failed to obtain the listen socket: %d\n",
                WSAGetLastError());
        goto CLEANUP;
    }

    // bind() associates a local address and port
    // combination with the socket just created. 
    if (bind(gsListen, (struct sockaddr*)pAddr->ai_addr, (int) pAddr->ai_addrlen)
            == SOCKET_ERROR)
    {
        fprintf(stderr, "\nbind() failed: %d\n",
                WSAGetLastError());
        closesocket(gsListen);
        gsListen = INVALID_SOCKET;
        goto CLEANUP;
    }

    // start listening on the socket for incoming connections
    if (listen(gsListen,5) == SOCKET_ERROR)
    {
        fprintf(stderr, "\nlisten() failed: %d\n",
                WSAGetLastError());
        closesocket(gsListen);
        gsListen = INVALID_SOCKET;      
        goto CLEANUP;
    }

    nFromLen = sizeof(saFrom);

    printf("Listening on %s:%s\n", pszIPAddress? pszIPAddress : "localhost", pszPort);

    while(TRUE)
    {
        printf("Waiting for new connection (Type CTRL+C to exit) ...\n\n");

        gsAccept = WSAAccept(gsListen,
                (struct sockaddr*)&saFrom,
                &nFromLen,
                (LPCONDITIONPROC)NULL,
                0);

        if(gsAccept == INVALID_SOCKET)
        {
            fprintf(stderr, "\nWSAAccept() failed: %d\n",
                    WSAGetLastError());
            break;
        }

        // Spawn a child process to handle the I/O.
        DispatchChild(gsAccept, pszChildProcName);

        // Doing a hard shutdown here is a no-no because it
        // will also reset the duplicated child socket.
        /*
           LINGER lingerStruct;

           lingerStruct.l_onoff = 1;
           lingerStruct.l_linger = 0;
           setsockopt(gsAccept, SOL_SOCKET, SO_LINGER,
           (char *)&lingerStruct, sizeof(lingerStruct));
         */

        closesocket(gsAccept);
        gsAccept = INVALID_SOCKET;      
    }

CLEANUP:

    if (gsListen != INVALID_SOCKET)
    {
        closesocket(gsListen);
        gsListen = INVALID_SOCKET;   
    }

    if (res != NULL)
    {
        freeaddrinfo(res);
        res = NULL;
    }
}