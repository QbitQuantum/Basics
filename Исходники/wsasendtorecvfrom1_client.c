/**
 * main
 * 
 * executable entry point
 */
INT __cdecl main(INT argc, CHAR **argv)
{
    int     i;
    WSADATA wsaData;
    int     err;
    struct  sockaddr_in mySockaddr;

    /* Sockets descriptor */
    const int numSockets = 2;    /* number of sockets used in this test */

    SOCKET testSockets[2];

    /* Variables for WSASend */
    WSABUF wsaBuf[BUF_NUMBER];
    DWORD  dwNbrOfByteSent;
    DWORD  dwNbrOfBuf  = BUF_NUMBER;    
    DWORD  dwSendFlags = 0;
    char   myBuffer[BUFSIZE]="This is a string passed through an UDP socket";
    
    WSAOVERLAPPED wsaOverlapped;

    /*  Socket DLL version */
    const WORD wVersionRequested = MAKEWORD(2,2);

    /* Sockets initialization to INVALID_SOCKET */
    for( i = 0; i < numSockets; i++ )
    {
        testSockets[i] = INVALID_SOCKET;
    }

    /* PAL initialization */
    if( PAL_Initialize(argc, argv) != 0 )
    {
        return FAIL;
    }
   
    /* Initialize to use winsock2.dll */
    err = WSAStartup(wVersionRequested,
                     &wsaData);

    if(err != 0)
    {
         Fail( "ERROR: Unexpected failure: "
              "WSAStartup(%i) "
              "returned %d\n",
              wVersionRequested, 
              GetLastError() );
    }

    /* Confirm that the WinSock DLL supports 2.2. 
       Note that if the DLL supports versions greater    
       than 2.2 in addition to 2.2, it will still return
       2.2 in wVersion since that is the version we      
       requested.                                        
    */
 
    if ( wsaData.wVersion != wVersionRequested ) 
    {      
        Trace("ERROR: Unexpected failure "
              "to find a usable version of WinSock DLL\n");

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }

    /* create a stream socket in AF_INET domain */
    testSockets[0] = WSASocketA( AF_INET, 
                           SOCK_DGRAM, /*SOCK_RDM*/
                           IPPROTO_UDP,
                           NULL, 
                           0, 
                           WSA_FLAG_OVERLAPPED ); 

    if( testSockets[0] == INVALID_SOCKET )

    {
        Trace("ERROR: Unexpected failure: "
              "WSASocketA"
              "(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED)) "
              " returned %d\n",
              GetLastError());

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }   
    
    /*  prepare the sockaddr_in structure */
    mySockaddr.sin_family           = AF_INET;
    mySockaddr.sin_port             = getRotorTestPort();
    mySockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    memset( &(mySockaddr.sin_zero), 0, 8);

    /* UDP: Do not connect to a server */            

    /* Set the WSABUF structure */
    wsaBuf[0].len = BUFSIZE;
    wsaBuf[0].buf = myBuffer;

    /* Set the WSAOVERLAPPED to zero */
    memset(&wsaOverlapped, 0, sizeof(WSAOVERLAPPED));

    /* Send some data directly to server opened socket */  
    err=WSASendTo(
            testSockets[0],
            wsaBuf,
            dwNbrOfBuf,
            &dwNbrOfByteSent,
            dwSendFlags,
            (struct sockaddr FAR *)&mySockaddr,
            sizeof(mySockaddr),
            &wsaOverlapped,
            0);
    

    if(err == SOCKET_ERROR )
    {
        Trace("ERROR: "
              "WSASendTo(...) "
              "returned %d\n",
              GetLastError() );

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    } 

    /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

    PAL_Terminate();
    return PASS;
};