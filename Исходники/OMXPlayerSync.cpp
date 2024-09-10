int OMXPlayerSync::setUpConnection ()
{
   int i;
   
   if ( syncType == SYNC_SERVER )
   {
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if (-1 == sockfd) {
         perror("0:socket");
         return 1;
      }
      
      if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &forceRebind, sizeof(int))) {
         perror("0:setsockopt");
         return 1;
      }
      
      memset((void *) &server, 0, sizeof(struct sockaddr_in));
      server.sin_family = AF_INET;
      server.sin_port = htons( port );
      server.sin_addr.s_addr = INADDR_ANY;
      
      if (-1 == bind(sockfd, (const struct sockaddr *) &server,
            sizeof(struct sockaddr_in))) {
         perror("0:bind");
         return 1;
      }
      
      if (-1 == listen(sockfd, 0)) {
         perror("0:listen");
         return 1;
      }
      
      // Set up the client sockets
      for ( i = 0; i < numNodes && i < MAX_NUM_CLIENT_SOCKETS; i++)
      {
         clientSocket [ i ] = accept(sockfd, (struct sockaddr *) &client, &clientaddrlen);
         if (-1 == clientSocket [ i ]) {
            perror("0:accept");
            return 1;
         }
      }
      
      return 0;
   }
   else
   {
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if (-1 == sockfd) {
         perror("1:socket");
         return 1;
      }
      
      if (0 != getaddrinfo(serverAddress.c_str (), NULL, NULL, &serverinfo)) {
         perror("getaddrinfo");
         return 1;
      }
      
      /*Copy size of sockaddr_in b/c res->ai_addr to big for this example*/
      memcpy(&server, serverinfo->ai_addr, sizeof(struct sockaddr_in));
      server.sin_family = AF_INET;
      server.sin_port = htons( port );
      freeaddrinfo(serverinfo);
      
#ifdef LOOP_UNTIL_CONNECT
      while ( true )
      {
         if (-1 != connect(sockfd, (const struct sockaddr *) &server,
               sizeof(struct sockaddr_in))) {
            break;
         }
         usleep ( CONNECT_SLEEP_PERIOD );
      }
#else
      if (-1 == connect(sockfd, (const struct sockaddr *) &server,
            sizeof(struct sockaddr_in))) {
         perror("1:connect");
         return 1;
      }
#endif // LOOP_UNTIL_CONNECT
      
      return 0;
   }
}