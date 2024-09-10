/* Connect to SERVER at PORT and return a file descriptor or -1 on
   error. */
static int
connect_server (const char *server, unsigned short port)
{
  int sock = -1;

#ifdef _WIN32
  struct hostent *hp;
  struct sockaddr_in addr;
  unsigned long l;

  init_sockets ();

  memset (&addr, 0, sizeof addr);
  addr.sin_family = AF_INET;
  addr.sin_port = htons (port);

  /* Win32 gethostbyname doesn't handle IP addresses internally, so we
     try inet_addr first on that platform only. */
  if ((l = inet_addr (server)) != INADDR_NONE) 
    memcpy (&addr.sin_addr, &l, sizeof l);
  else if ((hp = gethostbyname (server))) 
    {
      if (hp->h_addrtype != AF_INET)
        {
          fprintf (console, "gpgkeys: unknown address family for `%s'\n",
                   server);
          return -1;
        }
      if (hp->h_length != 4)
        {
          fprintf (console, "gpgkeys: illegal address length for `%s'\n",
                   server);
          return -1;
        }
      memcpy (&addr.sin_addr, hp->h_addr, hp->h_length);
    }
  else
    {
      fprintf (console, "gpgkeys: host `%s' not found: ec=%d\n",
               server, (int)WSAGetLastError ());
      return -1;
    }

  sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock == INVALID_SOCKET)
    {
      fprintf (console, "gpgkeys: error creating socket: ec=%d\n", 
               (int)WSAGetLastError ());
      return -1;
    }

  if (connect (sock, (struct sockaddr *)&addr, sizeof addr))
    {
      fprintf (console, "gpgkeys: error connecting `%s': ec=%d\n", 
               server, (int)WSAGetLastError ());
      sock_close (sock);
      return -1;
    }

#else

  struct sockaddr_in addr;
  struct hostent *host;

  addr.sin_family = AF_INET;
  addr.sin_port = htons (port);
  host = gethostbyname ((char*)server);
  if (!host)
    {
      fprintf (console, "gpgkeys: host `%s' not found: %s\n",
               server, strerror (errno));
      return -1;
    }
  
  addr.sin_addr = *(struct in_addr*)host->h_addr;

  sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    {
      fprintf (console, "gpgkeys: error creating socket: %s\n", 
               strerror (errno));
      return -1;
    }
  
  if (connect (sock, (struct sockaddr *)&addr, sizeof addr) == -1)
    {
      fprintf (console, "gpgkeys: error connecting `%s': %s\n", 
               server, strerror (errno));
      close (sock);
      return -1;
    }
#endif
    
  return sock;
}