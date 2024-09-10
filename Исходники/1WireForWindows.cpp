SOCKET ConnectToService()
{
   // Connection
   SOCKET theSocket = INVALID_SOCKET;
   struct addrinfo *result = NULL,
      *ptr = NULL,
      hints;

   ZeroMemory(&hints,sizeof(hints));
   hints.ai_family = AF_UNSPEC;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_protocol = IPPROTO_TCP;

   // Resolve the server address and port
   int getaddrinfoRet = getaddrinfo("localhost",_1WIRE_SERVICE_PORT,&hints,&result);
   if (getaddrinfoRet != 0)
   {
      Log(LOG_ERROR,"getaddrinfo failed with error: %d\n", getaddrinfoRet);
      return INVALID_SOCKET;
   }

   // Attempt to connect to an address until one succeeds
   for(ptr=result;ptr!=NULL;ptr=ptr->ai_next)
   {
      // Create a SOCKET for connecting to server
      theSocket = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
      if (theSocket == INVALID_SOCKET)
      {
         Log(LOG_ERROR,"socket function failed with error = %d\n", WSAGetLastError());
         return INVALID_SOCKET;
      }

      // Connect to server
	  if (connect(theSocket, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen)) == SOCKET_ERROR)
      {
         Log(LOG_ERROR,"1Wire: connect function failed with error: %ld\n", WSAGetLastError());
         closesocket(theSocket);
         theSocket = INVALID_SOCKET;
         continue;
      }
      break;
   }

   freeaddrinfo(result);

   if (theSocket==INVALID_SOCKET)
   {
      return INVALID_SOCKET;
   }

   // Set receive timeout
   struct timeval tv;
   tv.tv_sec = 10*1000;  /* 10 Secs Timeout */
   if (setsockopt(theSocket,SOL_SOCKET,SO_RCVTIMEO,(char*)&tv,sizeof(struct timeval))==SOCKET_ERROR)
   {
      Log(LOG_ERROR,"setsockopt failed with error: %u\n", WSAGetLastError());
      closesocket(theSocket);
      return INVALID_SOCKET;
   }

   return theSocket;
}