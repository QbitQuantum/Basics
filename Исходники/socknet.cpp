  LIBRARY_API bool socketNet::create (struct networkStruct& socketData)
  {
    char ac[32];
    char *client_ip_address = NULL;
    HANDLE hTimer = NULL;
    LARGE_INTEGER liDueTime;
    liDueTime.QuadPart=-30000000;  //! 3 second timer for polling

    struct sockaddr_in serverAddr; //! server's socket address
    struct sockaddr_in clientAddr; //! client's socket address 
    int sockAddrSize;              //! size of socket address structure
    SOCKET newFd;                  //! socket descriptor from accept
    int ix = 0;                    //! counter for work task names
    int tcpServer_shutdown = 0;
    unsigned long l = 1;           //! to set sockets to nonblocking

    hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (NULL == hTimer)
    {
      //! Timer error
    }

    //! Set up the local address
    sockAddrSize = sizeof (struct sockaddr_in);

    WSADATA wsaData;
    int wsaret = WSAStartup(0x101, &wsaData);
    if (wsaret != 0)
      return false;
    //! Clear (zero-out) serverAddr
    memset((char *) &serverAddr, 0, sockAddrSize);
    serverAddr.sin_addr.s_addr = htons (INADDR_ANY);

    serverAddr.sin_family = AF_INET; 
    serverAddr.sin_port = htons ((u_short)socketData.sP); 

    gethostname(ac, sizeof(ac));
    struct hostent *phe = gethostbyname(ac);

    socketData.serverAddress = new char[128];//inet_ntoa (serverAddr.sin_addr);
    struct in_addr a1;//, a2, a3, a4;

    int i = 0;
    //while (phe->h_addr_list[i] != 0)
    {
      memcpy (&a1, phe->h_addr_list[i], sizeof(struct in_addr));
      sprintf (socketData.serverAddress, "%s", inet_ntoa(a1));
      ++i;
    }

    //! This allows us to have multiple clients attached to the same port
    if (!socketData.bound)
    {
      //! create a TCP-based socket
      if ((socketData.sFd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR_F)
      {
#ifdef NOISY
        perror ("socket");
#endif
        return false; 
      }

      //! bind socket to local address
      if (bind (socketData.sFd,
                (struct sockaddr *) &serverAddr,
                sockAddrSize) == ERROR_F)
      {
#ifdef NOISY
        perror ("bind");
#endif
        closesocket (socketData.sFd); 
        WSACleanup ();
        return false; 
      }
      socketData.bound = true;
    }

    //ioctlsocket (socketData.sFd, FIONBIO, &l);
    
    //! Create queue for client connection requests
    if (listen (socketData.sFd, SERVER_MAX_CONNECTIONS) == ERROR_F)
    { 
      closesocket (socketData.sFd);
      WSACleanup ();
      socketData.bound = true;
      return false;
    }
    //! Accept new connect requests and spawn tasks to process them
    //! Accept the first connection and use it...
    newFd = 0;
    do
    {
      //! If we stop the connection attempt
      bool okay;
      okay = false;
      do
      {
        if (!settings_->globalRunServer)
        {
          closesocket (socketData.sFd);
          WSACleanup();
          return false;
        }
        if ((newFd = accept (socketData.sFd,
                            (struct sockaddr*)&clientAddr,
                            &sockAddrSize)) == ERROR_F) 
        {
          printf ("%s\n", inet_ntoa (clientAddr.sin_addr));

#ifdef NOISY
          perror ("accept"); 
#endif
          int g = WSAGetLastError();
          //! We expect the error WSAEWOULDBLOCK since the socket is non-blocking
          if (g != WSAEWOULDBLOCK)
          {
            closesocket (socketData.sFd);
            WSACleanup ();
            return false; 
          }
          // Set a timer to wait for 0.1 seconds--Poll @ 10 Hz
          if (!SetWaitableTimer(hTimer, &liDueTime, 1, NULL, NULL, 0))
          {
            //! Timer error
          }

          if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0)
          {
            //! Timer error
          }
        }
        else
        {
          okay = true;
        }
      } while (!okay);

      if (newFd > 0)            
      {
        client_ip_address = inet_ntoa (clientAddr.sin_addr);
        //! JAM: A problem encountered with Windows is that it constantly
        //!      thinks a connection from 204.204.204.204:52428 is being
        //!      made
        if (strcmp("204.204.204.204", client_ip_address) != 0)
        {
          //! fill out the struct
          socketData.cFd = newFd;
          socketData.address = client_ip_address;
          socketData.cP = ntohs (clientAddr.sin_port);

          //! Disable nonblocking by default
          //unsigned long l = 0;
          //ioctlsocket (socketData.cFd, FIONBIO, &l);
          tcpServer_shutdown = 1;  //! say we are done
        }
      }
    }while (tcpServer_shutdown != 1);
    socketData.connected = true;
    settings_->connected = true;
    //l=1;
    //ioctlsocket (socketData.cFd, FIONBIO, &l);

    return true;
  } 