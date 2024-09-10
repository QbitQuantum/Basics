/**
 * main
 * 
 * executable entry point
 */
INT __cdecl main(INT argc, CHAR **argv)
{
    int     i;
    int     err;    
    int     addrlen = sizeof(struct sockaddr);
    struct  sockaddr_in mySockaddr;
    WSADATA wsaData;
    HANDLE  hReadEvent;
    DWORD   waitResult;

    /* Thread variable */
    HANDLE hThreadClient;
    DWORD dwThreadClient;     
    DWORD dwClientParam[2]; 

    HANDLE hThreadEvent; 

    /* Sockets descriptor */
    const int numSockets = 2;    /* number of sockets used in this test */

    SOCKET testSockets[2];

    /* variable for iocltsocket */
    u_long argp;

     /* Variables needed for setsockopt */
    BOOL bReuseAddr = TRUE;
    

    /* Variables needed for select */
    struct timeval waitTime;
    fd_set readFds;
    int    socketFds;

    /* Variables needed for WSARecv */
    WSABUF        wsaBuf;
    DWORD         dwNbrOfBuf  = 1;
    DWORD         dwNbrOfByteSent;
    DWORD         dwRecvFlags = 0;
    WSAOVERLAPPED wsaRecvOverlapped;
    
    /* Variable used to store transmitted data */
    unsigned char myBuffer[300];    
    
    /* Socket DLL version */
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
    err = WSAStartup( wVersionRequested,
                      &wsaData);

    if(err != 0)
    {
        Fail( "Server error: Unexpected failure: "
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
        Trace("Server error: Unexpected failure "
              "to find a usable version of WinSock DLL\n");

        /* Do some cleanup */
        DoWSATestCleanup( 0, 0);

        Fail("");
    }

    /* create an overlapped stream socket in AF_INET domain */

    testSockets[0] = WSASocketA( AF_INET, 
                                 SOCK_STREAM, 
                                 IPPROTO_TCP,
                                 NULL, 
                                 0, 
                                 WSA_FLAG_OVERLAPPED ); 


    if( testSockets[0] == INVALID_SOCKET )
    {   
        Trace("Server error: Unexpected failure: "
              "WSASocketA"
              "(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED)) "
              " returned %d\n",
              GetLastError());

        /* Do some cleanup */
        DoWSATestCleanup( 0, 0);

        Fail("");
    }

    /* Allows the socket to be bound to an address that is already in use. */
    err = setsockopt( testSockets[0],
                      SOL_SOCKET,
                      SO_REUSEADDR,
                      (const char *)&bReuseAddr,
                      sizeof( BOOL ) );

    if( err == SOCKET_ERROR )
    {
        Trace("Server error: Unexpected failure: "
              "setsockopt(.., SOL_SOCKET,SO_REUSEADDR, ..) "
              "returned %d\n",
              GetLastError() );

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }

    /* enable non blocking socket */
    argp=1;
    err = ioctlsocket(testSockets[0], FIONBIO, (u_long FAR *)&argp);

    if (err==SOCKET_ERROR )
    {
        Trace("ERROR: Unexpected failure: "
              "ioctlsocket(.., FIONBIO, ..) "
              "returned %d\n",
              GetLastError() );

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );
        
        Fail("");
    }


    /* prepare the sockaddr structure */
    mySockaddr.sin_family           = AF_INET;
    mySockaddr.sin_port             = getRotorTestPort();
    mySockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    memset( &(mySockaddr.sin_zero), 0, 8);

    /* bind local address to a socket */
    err = bind( testSockets[0],
                (struct sockaddr *)&mySockaddr,
                sizeof(struct sockaddr) );


    if( err == SOCKET_ERROR )
    {
        Trace("ERROR: Unexpected failure: "
              "bind() socket with local address "
              "returned %d\n",
              GetLastError() );

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }

    /* listen to the socket */
    err = listen( testSockets[0], 
                  listenBacklog );

    if( err == SOCKET_ERROR )
    {
        Trace("ERROR: Unexpected failure: "
              "listen() to sockets "
              "returned %d\n",
              GetLastError() );

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }

    /* set the server waiting time as 10 seconds */
    waitTime.tv_sec = 10L;
    waitTime.tv_usec = 0L;

    /* initialize the except socket set  */
    FD_ZERO( &readFds );

    /* add socket to readable socket set */
    FD_SET( testSockets[0], 
            &readFds );

    
    /* Create a Event with initial owner. */
    hThreadEvent = CreateEvent( NULL, /* no security   */
                             FALSE,   /* reset type    */
                             FALSE,   /* initial state */
                             "EventClientServer" );  /* object name   */

    if (hThreadEvent == NULL) 
    {        
        /* Check for error. */
        Trace( "Server Error: Unexpected failure: "
              "CreateEvent() "
              "returned NULL\n");

          /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }    
    
    /* create a client thread */

    hThreadClient = 
        CreateThread( 
                NULL,                        /* no security attributes */
                0,                           /* use default stack size */
                (LPTHREAD_START_ROUTINE)Thread_Client,/* thread function    */
                (LPVOID)&dwClientParam,      /* argument to thread function */
                0,                           /* use default creation flags  */
                &dwThreadClient);            /* returns the thread identifier*/

    if(hThreadClient==NULL)
    {        
        Trace( "Server Error: Unexpected failure: "
              "CreateThread() "
              "returned NULL\n");

        CloseEventHandle(hThreadEvent);        

          /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }
   
    Sleep(500);

    if(SetEvent(hThreadEvent)==0)
    {
        Trace("Server error: Unexpected failure: "
            "SetEvent has not set hThreadEvent as expected"
            "GetLastError returned = %d.\n",GetLastError());

        WaitForClientThreadToFinish(hThreadClient);

        CloseThreadHandle(hThreadClient);

        CloseEventHandle(hThreadEvent);        

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                        numSockets );

        Fail("");
    }
    
    /* set the server waiting time as 10 seconds */
    waitTime.tv_sec = 10L;
    waitTime.tv_usec = 0L;

    /* initialize the except socket set  */
    FD_ZERO( &readFds );

    /* add socket to readable socket set */
    FD_SET( testSockets[0], 
            &readFds );

    /* monitor the readable socket set 
       to determine when a connection is ready to be accepted
    */
    socketFds = select( 0,
                        &readFds,
                        NULL,
                        NULL,
                        &waitTime);
    

    if( socketFds == SOCKET_ERROR )
    {
        Trace("ERROR: Unexpected failure "
              "with select\n");

        WaitForClientThreadToFinish(hThreadClient);

        CloseThreadHandle(hThreadClient);

        CloseEventHandle(hThreadEvent);

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }

    if( socketFds == 0 )
    {
        Trace("ERROR: Unexpected select "
              "timed out\n");

        WaitForClientThreadToFinish(hThreadClient);

        CloseThreadHandle(hThreadClient);

        CloseEventHandle(hThreadEvent);   

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }

    if(CloseEventHandle(hThreadEvent)==0)
    {
        WaitForClientThreadToFinish(hThreadClient);

        CloseThreadHandle(hThreadClient);        

        Fail("");
    }

    /* accept connection */
    testSockets[1] = accept( testSockets[0],
                             (struct sockaddr *)&mySockaddr,
                             &addrlen );

    if( testSockets[1] == INVALID_SOCKET )
    {
        Trace("ERROR: Unexpected failure: "
              "accept() connection on socket "
              "returned %d\n",
              GetLastError());

        WaitForClientThreadToFinish(hThreadClient);

        CloseThreadHandle(hThreadClient);        

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }

    /* enable non blocking socket */
    argp=1;
    err = ioctlsocket(testSockets[1], FIONBIO, (u_long FAR *)&argp);

    if (err==SOCKET_ERROR )
    {
        Trace("ERROR: Unexpected failure: "
              "ioctlsocket(.., FIONBIO, ..) "
              "returned %d\n",
              GetLastError() );

        WaitForClientThreadToFinish(hThreadClient);

        CloseThreadHandle(hThreadClient);        

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }

    
    /* create an event */
    hReadEvent = CreateEvent( NULL, /* no security   */
                             FALSE,   /* reset type    */
                             FALSE,   /* initial state */
                             NULL );  /* object name   */
            
    if( hReadEvent == NULL )
    {            
        Trace("Server error: Unexpected failure: "
              "CreateEvent() "
              "returned %d\n",
              GetLastError());

        WaitForClientThreadToFinish(hThreadClient);        

        CloseThreadHandle(hThreadClient);        

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
        
    }



    /* Initialize the WSABUF structure */
    memset(myBuffer, 0, 300);
    wsaBuf.buf = myBuffer;
    wsaBuf.len = 150;
    
    
    for(i=0;i<2;i++)
    {
        /* Initialize the WSAOVERLAPPED to 0 */
        memset(&wsaRecvOverlapped, 0, sizeof(WSAOVERLAPPED));

        /* Specify which event to signal when data is arrived*/
        wsaRecvOverlapped.hEvent = hReadEvent;        

         /* Prepare to receive data */
        err = WSARecvFrom( testSockets[1],
                    &wsaBuf,
                    dwNbrOfBuf,
                    &dwNbrOfByteSent,
                    &dwRecvFlags,                    
                    (struct sockaddr FAR *)NULL,
                    (int)NULL,
                    &wsaRecvOverlapped,
                    0 );

        if( err != SOCKET_ERROR )
        {            
            /* on the second iteration it is expected to return no error
               see explanation below.
            */
            if(dwNbrOfByteSent!=150&&dwNbrOfByteSent!=105)
            {   
                Trace("Server error: WSARecv() "
                    "returned immediately and dwNbrOfByteSent is %d,"
                    "expected 150 of 105.\n",
                    dwNbrOfByteSent);
                
                WaitForClientThreadToFinish(hThreadClient);                

                CloseThreadHandle(hThreadClient);

                CloseEventHandle(hReadEvent);                

                /* Do some cleanup */
                DoWSATestCleanup( testSockets,
                                numSockets );

                Fail("");
            }
        }
        else if(GetLastError()!=WSA_IO_PENDING)
        {
            Trace("Server error: WSARecv() "
                    "returned %d, expected WSA_IO_PENDING\n",
                    err );
                
            WaitForClientThreadToFinish(hThreadClient);            
            
            CloseThreadHandle(hThreadClient);

            CloseEventHandle(hReadEvent);
            
            /* Do some cleanup */
            DoWSATestCleanup( testSockets,
                            numSockets );
    
            Fail("");
        }
        else
        {
            waitResult = WaitForSingleObject( hReadEvent,
                                            10000 );           
            
            if (waitResult!=WAIT_OBJECT_0)
            {                   
                Trace("Server error: Unexpected failure: "
                    "WaitForSingleObject has timed out \n");

                WaitForClientThreadToFinish(hThreadClient);                

                CloseThreadHandle(hThreadClient);

                CloseEventHandle(hReadEvent);                
        
                /* Do some cleanup */
                DoWSATestCleanup( testSockets,
                                numSockets );

                Fail("");
            }        
        }    

        /* if it is the first receive, we expect MSG_PARTIAL
           because the buffer sent is 255 long while the receive
           buffer is 150.

           Update : MSG_PARTIAL is not tested because it never happens.
        */
        if(i==0)
        {
             /* 
               MSDN: The lpFlags parameter is both an input and an output 
               parameter, allowing applications to sense the output state 
               of the MSG_PARTIAL flag bit. However, the MSG_PARTIAL flag bit 
               is not supported by all protocols. 

               According to win32 result, MSG_PARTIAL is not set with TCP.                              

               this test is no longer valid:
               if(wsaRecvOverlapped.Internal==MSG_PARTIAL))

               Here we test if the first WSARecv has been filled completely

            */

            if(wsaRecvOverlapped.InternalHigh!=150)
            {
                Trace("Server error: "
                    "First WSARecv(...) "
                    "returned wsaRecvOverlapped.InternalHigh = %d" 
                    ", expected maximum buffer size of 150."
                    "\n", wsaRecvOverlapped.InternalHigh);

                WaitForClientThreadToFinish(hThreadClient);                

                CloseThreadHandle(hThreadClient);

                CloseEventHandle(hReadEvent);

                 /* Do some cleanup */
                DoWSATestCleanup( testSockets,
                                numSockets );

                Fail("");
           }
            /*set the recv buffer to the second half of myBuffer */
            wsaBuf.buf = myBuffer+150;
            wsaBuf.len = 150;
        }
        else /* i == 1 */
        {
           /* on the second wsarecv, it should have read the remaining data to 
              be read on the overlapped result.
           */            
            if(wsaRecvOverlapped.InternalHigh!=105)
            {
                Trace("Server error: "
                    "Second WSARecv(...) "
                    "returned wsaRecvOverlapped.InternalHigh = %d" 
                    ", expected maximum buffer size of 105."
                    "\n", wsaRecvOverlapped.InternalHigh);

                WaitForClientThreadToFinish(hThreadClient);                

                CloseThreadHandle(hThreadClient);

                CloseEventHandle(hReadEvent);

                 /* Do some cleanup */
                DoWSATestCleanup( testSockets,
                                numSockets );

                Fail("");
           }           
        }       
    } /* end of the for loop */

    if(!WaitForClientThreadToFinish(hThreadClient))
    {
        CloseThreadHandle(hThreadClient);

        CloseEventHandle(hReadEvent);

        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );

        Fail("");
    }

    if(!CloseThreadHandle(hThreadClient)||
       !CloseEventHandle(hReadEvent))
    {
        /* Do some cleanup */
        DoWSATestCleanup( testSockets,
                          numSockets );
        Fail("");
    }

    /* test the data received if it valid */
    for(i=0;i<255;i++)
    {
        if(myBuffer[i]!=i)
        {
           Trace("Server error: "
                "WSARecv(...) "
                "returned wsaRecvOverlapped.InternalHigh = %d" 
                ", expected maximum buffer size of 105."
                "\n", wsaRecvOverlapped.InternalHigh);

                /* Do some cleanup */
            DoWSATestCleanup( testSockets,
                            numSockets );

            Fail("");           
         }
    }
 
    /* Do some cleanup */
    DoWSATestCleanup( testSockets,
                      numSockets );


    PAL_Terminate();
    return PASS;
}