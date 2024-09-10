/* =========================== */
int main(int argc,char *argv[])
{
   unsigned short       port;
   int                  result;
   int                  err;
   SOCKET               masterSock;
   SOCKET               clientSock;
   em_workspace_t       *wrk;
   struct sockaddr_in   servAddr;
   int                  i;
   WORD                 wVersionRequested;
   WSADATA              wsaData;
   int                  clientAddrLen;
   struct sockaddr      clientAddr;

   fprintf(stdout,"Embedded Web Server - Windows 95 : %s\n",__TIMESTAMP__);
   fprintf(stdout,"Copyright (c) 1995-1996 David M. Howard\n");

   port = w95t_server_port;

   /* initialize printf */
   printf_init();

   /* =============================================== */
   /* initialize winsock library                      */
   /* =============================================== */

   wVersionRequested = MAKEWORD(1, 1);

   err = WSAStartup(wVersionRequested, &wsaData);
   if (err != 0) {
      fprintf(stderr,"Can't initialize winsock lib\n");
      exit(1);
   }

   /* Confirm that the Windows Sockets DLL supports 1.1.*/
   /* Note that if the DLL supports versions greater */
   /* than 1.1 in addition to 1.1, it will still return */
   /* 1.1 in wVersion since that is the version we */
   /* requested. */

   if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
      /* Tell the user that we couldn't find a useable */
      /* winsock.dll. */
      WSACleanup();
      fprintf(stderr,"Winsock doesn't support version 1.1\n");
      exit(1);
   }

   ews_printf("Winsock Initialized OK\n");

   /* =============================================== */
   /* The Windows Sockets DLL is acceptable. Proceed. */
   /* =============================================== */

   /* Create a socket and bind address, listen for incoming connections */
   masterSock = socket( PF_INET, SOCK_STREAM, 0 );
   if ( masterSock == INVALID_SOCKET ) {
      ews_printf("socket(..) failed\n");
      exit(1);
   }

   /*lint -e740 unusual pointer cast */
   memset((char *) &servAddr, 0, sizeof servAddr );
   servAddr.sin_family      = AF_INET;
   servAddr.sin_addr.s_addr = htonl( INADDR_ANY );
   servAddr.sin_port        = htons( port );
   result = bind( masterSock, ( struct sockaddr * ) &servAddr, sizeof servAddr );
   if ( result == -1 ) {
      ews_printf("bind(..) failed\n");
      exit(1);
   }

   /*lint _e740 */

   result = listen( masterSock, 3 );
   if ( result == -1 ) {
      ews_printf("listen(..) failed\n");
      exit(1);
   }

   ews_printf("masterSock listening on port %hu\n",port);

   /* ================================== */
   /* create the client connection queue */
   /* ================================== */
   thread_sockq = socket_qinit(NUMBER_OF_SERVER_TASKS);

   /* for each vrtx connection thread */
   for(i=0;i<NUMBER_OF_SERVER_TASKS;i++) {
      /* initialize a workspace  */
      wrk = &w95t_workspace[i];

      /* clear it to all 0's to start */
      memset(wrk,0,sizeof(em_workspace_t));

      /* SOCKET IO FUNCTIONS */
      wrk->system.p           = &w95t_dresp[i];
      wrk->system.read        = w95t_Read;
      wrk->system.write       = w95t_Write;
      wrk->system.open        = w95t_Open;
      wrk->system.close       = w95t_Close;
      wrk->system.exit        = w95t_Exit;
      wrk->system.gmt         = w95t_GMT;
      wrk->system.pagebin     = app_binurl;

      /* spawn the thread and pass it the workspace pointer */
      _beginthread(w95t_server_thread,0,wrk);
   }

   /* all threads are spawned */
   /* loop, waiting for connections */
   /* when a connection is received, enqueue it for the server threads */
   for(;;) {
      /* specify the max length of the address structure and accept the
      next connection.  clientAddrLen is passed as a pointer as it is
      updated by the accept call.
      retry accept until it works
      */
      ews_printf("Accept : masterSock = %ld\n",masterSock);

      clientAddrLen = sizeof (clientAddr);
      clientSock = accept( masterSock, &clientAddr, &clientAddrLen );


      /* if accept call fails */
      if ( clientSock == INVALID_SOCKET ) {
         /* get winsock error */
         err = WSAGetLastError();

         /* print it to error output */
         ews_printf("Accept failed : %d\n",err);

         /* quit */
         break;
      }

      ews_printf("Connect : clientSock = %ld\n",clientSock);

      /* client socket is accepted  */
      /* enqueue it for the servers */
      /* return (long)clientSock;   */
      socket_qsend(thread_sockq,clientSock);
   }

   return 0;
}