int tcp_socket_open (int family,void *adr,size_t adrlen,unsigned short port,
		     char *tmp,char *hst)
{
  int sock;
  size_t len;
  char *s;
  struct protoent *pt = getprotobyname ("tcp");
  struct sockaddr *sadr = ip_sockaddr (family,adr,adrlen,port,&len);
  sprintf (tmp,"Trying IP address [%s]",ip_sockaddrtostring (sadr));
  mm_log (tmp,NIL);
				/* get a TCP stream */
  if ((sock = socket (sadr->sa_family,SOCK_STREAM,pt ? pt->p_proto : 0)) ==
      INVALID_SOCKET)
    sprintf (tmp,"Unable to create TCP socket (%d)",WSAGetLastError ());
  else {
    wsa_sock_open++;		/* count this socket as open */
				/* open connection */
    if (connect (sock,sadr,len) == SOCKET_ERROR) {
      switch (WSAGetLastError ()) {
      case WSAECONNREFUSED:
	s = "Refused";
	break;
      case WSAENOBUFS:
	s = "Insufficient system resources";
	break;
      case WSAETIMEDOUT:
	s = "Timed out";
	break;
      case WSAEHOSTUNREACH:
	s = "Host unreachable";
	break;
      default:
	s = "Unknown error";
	break;
      }
      sprintf (tmp,"Can't connect to %.80s,%ld: %s (%d)",hst,port,s,
	       WSAGetLastError ());
      tcp_abort (&sock);	/* flush socket */
      sock = INVALID_SOCKET;
    }
  }
  fs_give ((void **) &sadr);
  return sock;			/* return the socket */
}