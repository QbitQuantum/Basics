int __cdecl main(int argc, char *argv[])
{

    WORD VersionRequested = MAKEWORD(2, 2);
    WSADATA WsaData;
    int err;
    int InvalidSocketID = -1; /*set an invalid socket descriptor*/
    struct sockaddr_in mySockaddr;
    const char *data = "sendto and recvfrom test";
    int nBuffer=strlen(data);

    /*Initialize the PAL environment*/
    err = PAL_Initialize(argc, argv);
    if(0 != err)
    {
        return FAIL;
    }
    /*initialize to use winsock2 .dll*/
    err = WSAStartup(VersionRequested, &WsaData);
    if(err != 0)
    {
        Fail("\nFailed to find a usable WinSock DLL!\n");
    }

    /*Confirm that the WinSock DLL supports 2.2.*/
    if(LOBYTE( WsaData.wVersion ) != 2 ||
            HIBYTE( WsaData.wVersion ) != 2)
    {
        Trace("\nFailed to find a usable WinSock DLL!\n");
        err = WSACleanup();
        if(SOCKET_ERROR == err)
        {
            Trace("\nFailed to call WSACleanup API!\n");
       }
        Fail("");
    }

    /*prepare the sockaddr_in structure*/
    mySockaddr.sin_family = AF_INET;
    mySockaddr.sin_port = getRotorTestPort();
    mySockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    memset(&(mySockaddr.sin_zero), 0, 8);


    /*call sendto by passing an invalid socket*/
    err=sendto(InvalidSocketID, data, nBuffer, 0, 
                (struct sockaddr *)&mySockaddr, sizeof(struct sockaddr));

    if(WSAENOTSOCK != GetLastError() || SOCKET_ERROR != err)
    {
        Trace("\nFailed to call sendto API for a negative test "
                "by passing invalid socket!\n");
	
        err = WSACleanup();
        if(SOCKET_ERROR == err)
        {
            Trace("\nFailed to call WSACleanup API!\n");
        }
        Fail("");
    }

    err = WSACleanup();
    if(SOCKET_ERROR == err)
    {
        Fail("\nFailed to call WSACleanup API!\n");
    }

    PAL_Terminate();
    return PASS;
}