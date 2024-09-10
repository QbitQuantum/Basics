/* DWORD  PALAPI Thread_Client(LPVOID lpParam)  
*  This is a client thread started by the main process.
*  It simulate a client connecting to a remote server.   
*
*  As soon as the client thread is started it calls WaitForSingleObject
*  and wait for the server to be ready to receive data. 
*
*  If the client fail somewhere it will set a global variable accordingly
*  and will call ExitThread. The main thread (server) will then continue 
*  its execution normally and handle the client error.
*
*    
*
*/
void  PALAPI Thread_Client(LPVOID lpParam)
{     
    int     i;
    int     err;
    struct  sockaddr_in mySockaddr;    

    int byteCounter;

    /* Sockets descriptor */
    const int numSockets = 1;    /* number of sockets used in this test */

    SOCKET testSockets[1];    
    
    
    /* Variables for WSASend */

    WSABUF wsaSendBuf;
    DWORD  dwNbrOfByteSent;
    DWORD  dwNbrOfBuf  = 1;
    DWORD  dwSendFlags = 0;
    
    unsigned char   sendBuffer[255];
    

    WSAOVERLAPPED wsaOverlapped;    

    HANDLE  hWriteEvent;
    DWORD   waitResult;
    
    /* Thread Event handle */
    HANDLE hThreadEvent;

    threadExitCode=THREAD_UNDEFINED;

    /* Create the EventClientServer controled by the server  */     
    hThreadEvent = (HANDLE)CreateEvent( NULL,
        TRUE,                /* ignored */
        FALSE,                /* ignored */
        (LPCSTR)"EventClientServer");  /* name of Event */

    if (hThreadEvent == NULL) 
    {        
        /* Check for error. */
        Trace( "Server Error: Unexpected failure: "
              "CreateEvent() "
              "returned NULL\n");

        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }
    
    /* Wait 10 seconds for EventClientServer to be signaled 
       from the server. It will mean that the server is ready
       to receive data or connection.
    */
    waitResult = WaitForSingleObject( hThreadEvent,
                                      10000 );
            
    if (waitResult!=WAIT_OBJECT_0)
    {
        Trace("Client error: Unexpected failure: "
              "WaitForSingleObject has timed out while "
              "waiting for EventClientServer.\n");

        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }    
    
    /* Destroy the Event Handle, we don't need it anymore */
    if(!CloseEventHandle(hThreadEvent))
    {       
        /* Trace is done in CloseEventHandle */

        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }


    /* Sockets initialization to INVALID_SOCKET */
    for( i = 0; i < numSockets; i++ )
    {
        testSockets[i] = INVALID_SOCKET;
    }


    /* create an overlapped stream socket in AF_INET domain */

    testSockets[0] = WSASocketA( AF_INET, 
                                 SOCK_DGRAM, 
                                 IPPROTO_UDP,
                                 NULL, 
                                 0, 
                                 WSA_FLAG_OVERLAPPED ); 


    if( testSockets[0] == INVALID_SOCKET )

    {
        Trace("Client error: Unexpected failure: "
              "WSASocketA"
              "(AF_INET,SOCK_DGRAM,IPPROTO_UDP,NULL,0,WSA_FLAG_OVERLAPPED)) "
              " returned %d\n",
              GetLastError());        

        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }
    
    /* prepare the sockaddr_in structure */
    mySockaddr.sin_family           = AF_INET;
    mySockaddr.sin_port             = getRotorTestPort();
    mySockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    memset( &(mySockaddr.sin_zero), 0, 8);

    /* fill the sent buffer with value */
    for (i=0;i<255;i++)
    {
        sendBuffer[i]= i;
    }

    /* prepare data for the send operation */    

    /* create events */
    hWriteEvent = CreateEvent( NULL, /* no security   */
                             FALSE,    /* reset type    */
                             FALSE,    /* initial state */
                             NULL );   /* object name   */
            
    if( hWriteEvent == NULL )
    {            
        Trace("Client error: Unexpected failure: "
              "CreateEvent() "
              "returned %d\n",
              GetLastError());

        /* Do some cleanup */
        CloseSocket( testSockets, numSockets );

        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }    
    
    /* Set the WSABUF structure */
    wsaSendBuf.len = 255;        
    wsaSendBuf.buf = sendBuffer;
    
    byteCounter = 0;

    /*
        That loop will wsasend a 500 buffer of data with UDP datagram to
        the server thread.
    */
    for(i=0;i<500;i++)
    {        
        /* Initialize the WSAOVERLAPPED for every send operation */
        memset(&wsaOverlapped, 0, sizeof(WSAOVERLAPPED));
        wsaOverlapped.hEvent = hWriteEvent;

        /* Send some data */
        err = WSASendTo( testSockets[0],
                       &(wsaSendBuf),
                       dwNbrOfBuf,
                       &dwNbrOfByteSent,
                       dwSendFlags,
                       (struct sockaddr FAR *)&mySockaddr,
                       sizeof(mySockaddr),
                       &wsaOverlapped,
                       0 );


        if(err == SOCKET_ERROR )
        {
            if(GetLastError()!=WSA_IO_PENDING)
            {
                Trace("Client error: Unexpected failure: "
                      "WSASend() "
                      "returned %d\n",
                      GetLastError());                

                /* Do some cleanup */
                CloseEventHandle(hWriteEvent);

                CloseSocket( testSockets, numSockets );

                threadExitCode=THREAD_FAIL;

                ExitThread(0);
            }

            /* Wait 10 seconds for WriteEvent to be signaled 
               for pending operation
            */
            waitResult = WaitForSingleObject( hWriteEvent, 
                                              10000 );            
 
            if (waitResult!=WAIT_OBJECT_0)
            {                   
                Trace("Client Error: Unexpected failure: "
                      "WaitForSingleObject has timed out \n");

                /* Do some cleanup */

                CloseEventHandle(hWriteEvent);                        
                
                CloseSocket( testSockets, numSockets );

                threadExitCode=THREAD_FAIL;

                ExitThread(0);
            }            
        }
        else
        {
            /* WSASend returned immediately 
               dwNbrOfByteSent should be 255
            */
            if(dwNbrOfByteSent!=255)
            {
                Trace("Client error, Unexpected failure: "
                      "number of byte sent by WSASend to is %d"
                      ", expected 255.\n",dwNbrOfByteSent);

                /* Do some cleanup */

                CloseEventHandle(hWriteEvent);
                
                CloseSocket( testSockets, numSockets );

                threadExitCode=THREAD_FAIL;

                ExitThread(0);
            }
            /* Reset the event */
            ResetEvent(hWriteEvent);
        }
        
        /* test if number of byte sent is different from 0
           in that case it means that the connection was closed
        */
        if(wsaOverlapped.InternalHigh==0)
        {
            Trace("Client Error: Unexpected failure: "
                  "WSASend overlapped operation sent 0 byte. "
                  "wsaOverlapped.Internal "
                  "= %d\n",wsaOverlapped.InternalHigh);
            
            /* Do some cleanup */

            CloseEventHandle(hWriteEvent);
            
            CloseSocket( testSockets, numSockets );                

            threadExitCode=THREAD_FAIL;

            ExitThread(0);            
        }

        /* keep track of the number of bytes sent */
        byteCounter += wsaOverlapped.InternalHigh;
 
        /* Verify that the number of bytes sent are the number of byte
           specified in the wsaBuf structure 
        */
        if(wsaSendBuf.len!=wsaOverlapped.InternalHigh)
        {   
            Trace("Client WSASend has not send the number of byte requested "
                  "wsaSendBuf.len = %d while "
                  "wsaOverlapped.InternalHigh = % d",
                  wsaSendBuf.len, wsaOverlapped.InternalHigh);

            /* Do some cleanup */
            CloseSocket( testSockets, numSockets );

            CloseEventHandle(hWriteEvent);

            threadExitCode=THREAD_FAIL;

            ExitThread(0);
        }        
    }   
    
    
    if(!CloseEventHandle(hWriteEvent))
    {
        /* Do some cleanup */
        CloseSocket( testSockets, numSockets );

        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }


    /* Expected number of bytes sent is 127500 */
    if(byteCounter!=127500)
    {
        Trace("Client error: Invalid number of byte sent to the server: %d"
               "\n",byteCounter);

        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }    

    /* Do some cleanup */
    if(!CloseSocket( testSockets, numSockets ))
    {
        threadExitCode=THREAD_FAIL;

        ExitThread(0);
    }

    threadExitCode=THREAD_SUCCESS;

    ExitThread(0);    
} 