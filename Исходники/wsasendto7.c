/* DWORD  PALAPI Thread_Client(LPVOID lpParam)  
   This is a client thread started by the main process.
   It simulate a client connecting to a remote server.   
*/
void  PALAPI Thread_Client(LPVOID lpParam)
{     
    int     i;
    int     err;
    struct  sockaddr_in mySockaddr;    

    /* Sockets descriptor */
    const int numSockets = 1;    /* number of sockets used in this test */

    SOCKET testSockets[1];
    
    /* Variables for WSASend */

    WSABUF wsaSendBuf;
    DWORD  dwNbrOfByteSent;
    DWORD  dwNbrOfBuf  = 1;
    DWORD  dwSendFlags = 0;
    
    unsigned char   sendBuffer[255];

    int byteCounter;

    WSAOVERLAPPED wsaOverlapped;

    /* variable for iocltsocket */
    u_long argp;

    /* Variables needed for select */
    struct timeval waitTime;
    fd_set writeFds;    
    int    socketFds;        

    HANDLE  hWriteEvent;
    DWORD   waitResult;

    threadExitCode=THREAD_UNDEFINED;

    /* Sockets initialization to INVALID_SOCKET */
    for( i = 0; i < numSockets; i++ )
    {
        testSockets[i] = INVALID_SOCKET;
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
        Trace("Client error: Unexpected failure: "
              "WSASocketA"
              "(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED) "
              " returned %u\n",
              GetLastError());

        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }

    /* enable non blocking socket */
    argp=1;
    err = ioctlsocket(testSockets[0], FIONBIO, (u_long FAR *)&argp);

    if (err==SOCKET_ERROR )
    {
        Trace("ERROR: Unexpected failure: "
              "ioctlsocket(.., FIONBIO, ..) "
              "returned %u\n",
              GetLastError() );

        /* Do some cleanup */
        CloseSocket( testSockets, numSockets );
       
        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }
    
    /* prepare the sockaddr_in structure */
    mySockaddr.sin_family           = AF_INET;
    mySockaddr.sin_port             = getRotorTestPort();
    mySockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    memset( &(mySockaddr.sin_zero), 0, 8);

    /* wait for the server to be prepared */
    Sleep(1000);

    /* connect to a server */
    err = connect( testSockets[0], 
                   (struct sockaddr *)&mySockaddr,
                   sizeof(struct sockaddr));

    if( err == SOCKET_ERROR )    
    {
        err = GetLastError();
        if ( err != WSAEWOULDBLOCK )
        {
            Trace("ERROR: Unexpected failure: "
              "connect() socket with local server "
              "returned %u, expected WSAEWOULDBLOCK\n",
              GetLastError());

            /* Do some cleanup */
            CloseSocket( testSockets, numSockets );
            
            threadExitCode=THREAD_FAIL;

            ExitThread(0);
        }     

          /* set the server waiting time as 10 seconds */
        waitTime.tv_sec = 10L;
        waitTime.tv_usec = 0L;

        /* initialize the except socket set  */
        FD_ZERO( &writeFds );

        /* add socket to readable socket set */
        FD_SET( testSockets[0], 
                &writeFds );

        /* monitor the readable socket set to determine the
        completion of the connection request.
        */
        socketFds = select( 0,                        
                            NULL,
                            &writeFds,
                            NULL,
                            &waitTime);

        if( socketFds == SOCKET_ERROR )
        {
            Trace("ERROR: Unexpected failure "
                "with select\n");

            /* Do some cleanup */
            CloseSocket( testSockets, numSockets );
            
            threadExitCode=THREAD_FAIL;

            ExitThread(0);
        }

        if( socketFds == 0 )
        {
            Trace("ERROR: Unexpected select "
                "timed out\n");

            /* Do some cleanup */
            CloseSocket( testSockets, numSockets );
            
            threadExitCode=THREAD_FAIL;

            ExitThread(0);
        }        
    }  
   
    /* create events */
    hWriteEvent = CreateEvent( NULL, /* no security   */
                             FALSE,    /* reset type    */
                             FALSE,    /* initial state */
                             NULL );   /* object name   */
            
    if( hWriteEvent == NULL )
    {
        Trace("Client error: Unexpected failure: "
              "CreateEvent() "
              "returned %u\n",
              GetLastError());

        /* Do some cleanup */
        CloseSocket( testSockets, numSockets );

        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }   

    /* fill the sent buffer with value */
    for (i=0;i<255;i++)
    {
        sendBuffer[i]= i;
    }

    /* Set the WSABUF structure */
    wsaSendBuf.len = 255;        
    wsaSendBuf.buf = sendBuffer;

    byteCounter = 0;   

    /*  This loop send a 400 buffer to the server.
        It then shutdown the connection.
    */
    for(i=0;i<500;i++)
    {
        /* Initialize the WSAOVERLAPPED to 0 */
        memset(&wsaOverlapped, 0, sizeof(WSAOVERLAPPED));  
        wsaOverlapped.hEvent = hWriteEvent;

        /* Send some data */
        err = WSASendTo( testSockets[0],
                    &wsaSendBuf,
                    dwNbrOfBuf,
                    &dwNbrOfByteSent,
                    dwSendFlags,
                    (struct sockaddr*)NULL, /* ignored in TCP */
                    (int)NULL, /* ignored in TCP */
                    &wsaOverlapped,
                    0 );


        if(err == SOCKET_ERROR )
        {
             /* The server shutdown its socket after 400 wsarecv, it is 
               impossible to have 401 or more successfull send operation */
            err=GetLastError();
            if(err==WSAECONNABORTED
               ||err==WSAESHUTDOWN
               ||err==WSAECONNRESET)
            {
                if (i<400)
                {
                    if(err==WSAESHUTDOWN)
                    {
                        Trace("Unexpected WSAESHUTDOWN at send %d",i);
                    }
                    else if(err==WSAECONNABORTED)
                    {
                        Trace("Unexpected WSAECONNABORTED at send %d",i);
                    }
                    else if(err==WSAECONNRESET)
                    {
                        Trace("Unexpected WSAECONNRESET at send %d",i);
                    }

                    CloseEventHandle(hWriteEvent);

                    /* Do some cleanup */
                    CloseSocket( testSockets, numSockets );

                    threadExitCode=THREAD_FAIL;

                    ExitThread(0);
                }
                else
                {
                    break;
                }
            }

            /* Handle the overlapped operation */
            if(err!=WSA_IO_PENDING)
            {
                Trace("Client error: Unexpected failure: "
                    "WSASend() "
                    "returned %u\n",
                    err);
                     
                CloseEventHandle(hWriteEvent);

                /* Do some cleanup */
                CloseSocket( testSockets, numSockets );

                threadExitCode=THREAD_FAIL;

                ExitThread(0);
            }

            /* Wait 10 seconds for hWriteEvent to be signaled 
            for pending operation
            */
            waitResult = WaitForSingleObject( hWriteEvent, 
                                              10000 );            

            if (waitResult!=WAIT_OBJECT_0)
            {  
                Trace("Client Error: Unexpected failure: "
                    "WaitForSingleObject has timed out \n");

                CloseEventHandle(hWriteEvent);
        
                /* Do some cleanup */
                CloseSocket( testSockets, numSockets );       

                threadExitCode=THREAD_FAIL;
                ExitThread(0);
            }
            
            /* The server shutdown its socket after 400 wsarecv, it is 
               impossible to have 401 or more successfull send operation */
            if(wsaOverlapped.Internal==WSAECONNABORTED||
               wsaOverlapped.Internal==WSAESHUTDOWN||
               wsaOverlapped.Internal==WSAECONNRESET)
            {
                if (i<400)
                {
                    if(err==WSAESHUTDOWN)
                    {
                        Trace("Unexpected WSAESHUTDOWN at send %d",i);
                    }
                    else if(err==WSAECONNABORTED)
                    {
                        Trace("Unexpected WSAECONNABORTED at send %d",i);
                    }
                    else if(err==WSAECONNRESET)
                    {
                        Trace("Unexpected WSAECONNRESET at send %d",i);
                    }

                    CloseEventHandle(hWriteEvent);

                    /* Do some cleanup */
                    CloseSocket( testSockets, numSockets );

                    threadExitCode=THREAD_FAIL;

                    ExitThread(0);
                }
                else
                {
                    break;
                }
            }

        }
        else
        {
            /* Reset Event */
            ResetEvent(hWriteEvent);
        }

        /* if wsaOverlapped.InternalHigh is 0, it means 
           that connection has been closed
        */
        if(wsaOverlapped.InternalHigh==0&&wsaOverlapped.Internal==0)
        {
            /* The server shutdown the receiving socket 
               after 400 successfull receive.
            */
            if (i<400)
            {
                Trace("Unexpected wsaOverlapped.InternalHigh = 0 " 
                     "at WSASend attempt #%d", i);

                CloseEventHandle(hWriteEvent);
    
                /* Do some cleanup */
                CloseSocket( testSockets, numSockets ); 

                threadExitCode=THREAD_FAIL;
                ExitThread(0);
            }
            /* the server shutdown the socket as expected */
            break;
        }

        /* keep track of the number of bytes sent */
        byteCounter += wsaOverlapped.InternalHigh;

        /* Verify that the number of bytes sent are the number of byte
           specified in the wsaBuf structure 
        */
        if(wsaSendBuf.len!=wsaOverlapped.InternalHigh)
        {            
            Trace("Server error: Array out of bound "
                "while writing buffer received in myData.\n");

            CloseEventHandle(hWriteEvent);
    
            /* Do some cleanup */
            CloseSocket( testSockets, numSockets );   

            threadExitCode=THREAD_FAIL;
            ExitThread(0);
        }
    }/* end of for loop */

    /* close the handle to hWriteEvent 
       Do some cleanup 
    */
    
    if(!CloseEventHandle(hWriteEvent)||
       !CloseSocket( testSockets, numSockets ))
    {
        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }

    threadExitCode=THREAD_SUCCESS;

    ExitThread(0);    
} 