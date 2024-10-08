int mcpOpen(char *name)
{
  char host[MAXHOSTNAMELEN], service[MAXHOSTNAMELEN];

  char buf[1024];

  char *cptr;
  int count, status;

  int sock_fd;
  struct hostent *hp;
  struct servent *sp;
  struct in_addr tmpaddr;
  int optval;

  struct sockaddr_in	inet_a;  // inet_addr is a function name

#ifndef _WIN32
  char path[MAXPATHLEN];
  struct sockaddr_un	unix_addr;
  size_t		unix_addr_len;

#endif //WIN32

#ifdef _WIN32
  // make sure we are initialized
  extern struct { int initialized; } initializer;
  if (initializer.initialized == 0)
	  return -1;
#endif //WIN32

  /*
   * Parse the name string.
   *
   *  A. If there is a ':' then it is an internet socket connection.
   *	1. Parse the name into <host>:<service> format.
   *	  a. If host is empty, use "localhost".
   *	  b. Lookup service with getservbyname().  If found, use
   *	     that port value.  If not found, attempt to convert
   *	     it to an integer and use that port value.
   *	2. Connect to <host>:<port>.  If the connection fails,
   *	   attempt to connect to <host>:tcpmux then request <service>
   *	   from tcpmux.
   *  B. Else the name is a unix domain socket name.
   *    1. If the first character is not '/', prepend '/tmp/' to the
   *	   name string.
   *	2. Connect to the socket name.
   */

  cptr = strchr(name, ':');

  if (cptr)
  {
    /* Copy the host name */
    if (cptr == name)
    {
      strcpy(host, "localhost");
    }
    else
    {
      strncpy(host, name, (cptr - name));
      host[cptr-name] = '\0';
    }

    /* Copy the service name */
    strcpy(service, cptr + 1);

    /* Initialize the inet_a struct */
    bzero((char *) &inet_a, sizeof(inet_a));
    inet_a.sin_family = AF_INET;

    /* Attempt to convert the host address as a dotted decimal number */
#ifdef _WIN32
    tmpaddr.s_addr = inet_addr(host);
    status = (tmpaddr.s_addr != INADDR_NONE) ? 1 : 0;
#else
    status = inet_aton(host, &tmpaddr);
#endif //WIN32
    if (status == 1)
    {
      bcopy((char *) &tmpaddr, (char *) &inet_a.sin_addr, sizeof(tmpaddr));
    }
    else
    {
      /* Now find the host */
      hp = gethostbyname(host);

      if (!hp)
      {
	/* We could not find the host */
	errno = ENOENT;
	return -1;
      }

      bcopy(hp->h_addr, (char *) &inet_a.sin_addr, hp->h_length);
    }

    /* Attempt to decode the service parameter */
    sp = getservbyname(service, "tcp");

    if (sp)
    {
      inet_a.sin_port = sp->s_port;
    }
    else
    {
      /* Attempt to convert the service name as an integer */
      inet_a.sin_port = htons((unsigned short)atoi(service));
    }

    /* Create the socket */
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
      return -1;
    }

    status = connect(sock_fd, (struct sockaddr *) &inet_a,
                     sizeof(inet_a));

    if (status < 0)
    {
      int status2;
      /*
       * The connection failed, try connecting to the tcpmux service.
       * tcpmux is at the well known port 1 so I just hardcoded it.
       */
      inet_a.sin_port = htons(1);

      status = errno;
      status2 = connect(sock_fd, (struct sockaddr *) &inet_a,
                        sizeof(inet_a));
      if (status2 < 0)
      {
		closefd(sock_fd);
		errno = status;
		return -1;
      }

      /*
       * We connected to tcpmux, now send the service name and see if
       * tcpmux can give it to us.  The tcpmux protocol works as follows:
       *
       *  1 Connect to the tcpmux port
       *  2 write the name of the service that you want followed by <CRLF>.
       *  3 read back the response terminated by <CRLF>
       *    a If the first character is a '+' then we are connected.
       *    b if the first character is a '-' then we are not connected.
       */
      sprintf(buf, "%s\r\n", service);
      status = mcpWrite(sock_fd, buf, (unsigned int) strlen(buf));
      if (status != (int)strlen(buf))
      {
		status = errno;
		closefd(sock_fd);
		errno = status;
		return -1;
      }

      /* Read up through the <CRLF> pair */
      /* There will be at least 3 characters coming back */
      cptr = buf;
      count = 3;
      while (1)
      {
		status = mcpRead(sock_fd, cptr, count);
		if (status <= 0)
		{
		  status = errno;
		  closefd(sock_fd);
		  errno = status;
		  return -1;
		}

		cptr += status;
		if (cptr[-1] == '\n')
		{
		  break;
		}
		else if (cptr[-1] == '\r')
		{
		  count = 1;
		}
		else
		{
		  count = 2;
		}
      }

      if (buf[0] != '+')
      {
		closefd(sock_fd);
#ifdef _WIN32
		errno = WSAECONNREFUSED;
		WSASetLastError (WSAECONNREFUSED);
#else
		errno = ECONNREFUSED;
#endif //WIN32
		return -1;
	  }
    }

    /*
     * We did it!  We actually succeeded in connecting to the name
     * via internet sockets.  Now make sure that we can send small
     * packets without delay.
     */
    optval = 1;
    status = setsockopt(sock_fd, IPPROTO_TCP, TCP_NODELAY, (void *)&optval,
			sizeof(optval));
  }
  else /* This must be a unix domain socket name */
  {
#ifndef _WIN32 // {
    /* Initialize the unix_addr struct */
    bzero((char *) &unix_addr, sizeof(unix_addr));
    unix_addr.sun_family = AF_UNIX;

    /*
     * If there is a leading '/' in the name name, it is an
     * absolute path name, otherwise, it is relative to /tmp.
     */
    if (name[0] == '/')
    {
      strcpy(path, name);
    }
    else
    {
      sprintf(path, "/tmp/%s", name);
    }

    strcpy(unix_addr.sun_path, path);
    unix_addr_len = sizeof(unix_addr.sun_len) + sizeof(unix_addr.sun_family) + strlen(path);

    /* Create the socket */
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
      return -1;
    }

    /* Connect to the name */
    status = connect(sock_fd, (struct sockaddr *) &unix_addr, unix_addr_len);
    if (status < 0)
    {
      closefd(sock_fd);
      return -1;
    }

    /*
     * We did it!  We actually succeeded in connecting to the name
     * via unix sockets.
     */
#else // } {
	HANDLE h;
	void* pmem;
	DWORD *mask, bit;
	struct sockmap* map;
	int i;
	
	h = CreateFileMapping(INVALID_HANDLE_VALUE, 0, 
		PAGE_READWRITE,
		0, MAYA_UNIX_SOCKET_SHARE_SIZE,
		MAYA_UNIX_SOCKET_SHARE_NAME);
	if (!h)
		return -1;
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		/* no "unix" handles exist */
		CloseHandle(h);
		return -1;
	}
	
	pmem = MapViewOfFile(h, FILE_MAP_WRITE,	0, 0, 0);
	if (!pmem)
	{
		CloseHandle(h);
		return -1;
	}
	mask = (DWORD*)pmem;
	map = (struct sockmap*)((char*)pmem+sizeof(DWORD));

	/* check if name is already here */
	sock_fd = -1;
	for (bit = 1, i = 0; i < 32; ++i)
	{
		if (*mask & bit)
		{
			if (strcmp(map[i].unix_path, name) == 0)
				break; /* found */
		}
		bit = bit << 1;
	}
	
	/* found */
	if (i < 32)
	{
		/* Initialize the inet_a struct */
		bzero((char *) &inet_a, sizeof(inet_a));
		inet_a.sin_family = AF_INET;

		/* Now find the host */
		hp = gethostbyname("localhost");
		if (!hp)
			errno = ENOENT;
		else
		{
			bcopy(hp->h_addr, (char *) &inet_a.sin_addr, hp->h_length);
			inet_a.sin_port = map[i].port;

			/* Create the socket */
			sock_fd = socket(AF_INET, SOCK_STREAM, 0);
			if (sock_fd >= 0)
			{
				status = connect(sock_fd, (struct sockaddr*)&inet_a, sizeof(inet_a));
				if (status < 0)
				{
					closefd(sock_fd);
					sock_fd = -1;
					errno = status;
				}
				else
				{
					optval = 1;
					status = setsockopt(sock_fd, IPPROTO_TCP, TCP_NODELAY,
						(char*)&optval, sizeof(optval));
				}
			}
		}
	}

	UnmapViewOfFile(pmem);
	CloseHandle(h);

#endif //WIN32 }
  }

  /* Ok, we are connected.  Return the socket descriptor */
  return sock_fd;
}