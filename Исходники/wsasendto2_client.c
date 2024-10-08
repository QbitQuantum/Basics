/**
 * main
 * 
 * executable entry point
 */
INT __cdecl main(INT argc, CHAR **argv)
{
    int     i;
    int     err;    
    struct  sockaddr_in mySockaddr;
    WSADATA wsaData;    

    /* Variables needed for WSASendTo */
    WSABUF        wsaBuf[RECV_BUF_COUNT];
    DWORD         dwNbrOfBuf  = RECV_BUF_COUNT;
    DWORD         dwNbrOfByteSent;
    DWORD         dwSendFlags = 0;
    WSAOVERLAPPED wsaOverlapped;
    BOOL          testFailed = TRUE;

    char myBuffer[RECV_BUF_SIZE] = "violets are blue, roses are red"; 
    
    /* Sockets descriptor */
    const int numSockets = 1;    /* number of sockets used in this test */

    SOCKET testSockets[NUM_OF_SOCKETS];

    /* Socket DLL version */
    const WORD wVersionRequested = MAKEWORD(2,2);

    /* Sockets initialization to INVALID_SOCKET */
    for( i = 0; i < NUM_OF_SOCKETS; i++ )
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
         Fail("ERROR: Unexpected failure: "
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

        DoWSATestCleanup( testSockets,
                      numSockets );        
        
        Fail("");        
    }

    /* create an overlapped UDP socket in AF_INET domain */

    testSockets[0] = WSASocketA( AF_INET, 
                           SOCK_DGRAM, 
                           IPPROTO_UDP,
                           NULL, 
                           0, 
                           WSA_FLAG_OVERLAPPED ); 


    if( testSockets[0] == INVALID_SOCKET )

    {
        Trace("ERROR: Unexpected failure: "
              "WSASocketA"
              "(AF_INET,SOCK_DGRAM,IPPROTO_UDP,NULL,0,WSA_FLAG_OVERLAPPED)) "
              " returned %d\n",
              GetLastError());

        DoWSATestCleanup( testSockets,
                      numSockets );        
        
        Fail("");    
    }

    /* prepare the sockaddr structure */

    mySockaddr.sin_family           = AF_INET;
    mySockaddr.sin_port             = getRotorTestPort();
    mySockaddr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");

    memset( &(mySockaddr.sin_zero), 0, 8);    
    
    /* Initialize the WSAOVERLAPPED to 0 */
    memset(&wsaOverlapped, 0, sizeof(WSAOVERLAPPED));    

    wsaOverlapped.hEvent = CreateEvent ( 
                                 NULL, 
                                 FALSE, 
                                 FALSE, 
                                 NULL );
                                 
    if (NULL == wsaOverlapped.hEvent)
    {
        Trace("Unable to create event object (LastError=%d)\n", GetLastError());

        DoWSATestCleanup( testSockets,
                      numSockets );        
        
        Fail("");    
    }

    /* Initialize the WSABUF structure */
    wsaBuf[0].buf = myBuffer;
    wsaBuf[0].len = RECV_BUF_SIZE;
   
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

    if( err != SOCKET_ERROR)      
    {
        
        Trace("ERROR: "
              "WSASendTo(...) "
              "returned %d, expected SOCKET_ERROR\n",
              err );
              
        goto cleanup;
    }      
    else
    {
        DWORD dwLastError;

        dwLastError = GetLastError();
        
        /* pending overlapped operation.
           we need to retrieve the last error from the internal
           field of WSAOVERLAPPED.
        */
        if ( dwLastError == WSA_IO_PENDING)
        {
            DWORD dwWaitResult;
        
            dwWaitResult = WaitForSingleObject(
                                wsaOverlapped.hEvent, 
                                waitTimeout);
                                
            switch(dwWaitResult)
            {
            case WAIT_OBJECT_0:
                /* last error is set in Internal field */
                dwLastError = wsaOverlapped.Internal;
                break;
            default:
                Trace("overlapped operation was not signaled in time."
                      "WFSO returned %d\n", dwWaitResult);
                goto cleanup;
            }
        }
        else
        {
            /* operation got carried over right away. LastError value
               correspond to the result of the requested operaton.
               Nothing to do. */
        }
       
        if( dwLastError != WSAEACCES)
        {
        
            Trace("ERROR: "
                  "WSASendTo(...) sets LastError to %d expected WSAEACCES\n",
                  dwLastError );

            goto cleanup;
        }

    }
    testFailed = FALSE;

cleanup:
    if (FALSE == CloseHandle(wsaOverlapped.hEvent))
    {
        Trace("ERROR: "
              "Could not close handle %x. LastError is %d\n",
              wsaOverlapped.hEvent,
              GetLastError());
    }
    
    wsaOverlapped.hEvent = NULL;
    DoWSATestCleanup( testSockets,
                      numSockets );

    if (testFailed == TRUE)
    {
        Fail("");
    }

    PAL_Terminate();
    return PASS;
}