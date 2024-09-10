TCPSTREAM *tcp_open (char *host,char *service,unsigned long port)
{
  TCPSTREAM *stream = NIL;
  int i;
  int sock = -1;
  int ctr = 0;
  int silent = (port & NET_SILENT) ? T : NIL;
  int *ctrp = (port & NET_NOOPENTIMEOUT) ? NIL : &ctr;
  char *s;
  struct sockaddr_in sin;
  struct hostent *he;
  char hostname[MAILTMPLEN];
  char tmp[MAILTMPLEN];
  struct servent *sv = NIL;
  blocknotify_t bn = (blocknotify_t) mail_parameters (NIL,GET_BLOCKNOTIFY,NIL);
  void *data;
  port &= 0xffff;		/* erase flags */
				/* lookup service */
  if (service && (sv = getservbyname (service,"tcp")))
    port = ntohs (sin.sin_port = sv->s_port);
 				/* copy port number in network format */
  else sin.sin_port = htons (port);
  /* The domain literal form is used (rather than simply the dotted decimal
     as with other Amiga programs) because it has to be a valid "host name"
     in mailsystem terminology. */
				/* look like domain literal? */
  if (host[0] == '[' && host[(strlen (host))-1] == ']') {
    strcpy (hostname,host+1);	/* yes, copy number part */
    hostname[(strlen (hostname))-1] = '\0';
    if ((sin.sin_addr.s_addr = inet_addr (hostname)) == -1)
      sprintf (tmp,"Bad format domain-literal: %.80s",host);
    else {
      sin.sin_family = AF_INET;	/* family is always Internet */
      strcpy (hostname,host);	/* hostname is user's argument */
      (*bn) (BLOCK_TCPOPEN,NIL);
				/* get an open socket for this system */
      sock = tcp_socket_open (&sin,tmp,ctrp,hostname,port);
      (*bn) (BLOCK_NONE,NIL);
    }
  }

  else {			/* lookup host name */
    if (tcpdebug) {
      sprintf (tmp,"DNS resolution %.80s",host);
      mm_log (tmp,TCPDEBUG);
    }
    (*bn) (BLOCK_DNSLOOKUP,NIL);/* quell alarms */
    data = (*bn) (BLOCK_SENSITIVE,NIL);
    if (!(he = gethostbyname (lcase (strcpy (hostname,host)))))
      sprintf (tmp,"No such host as %.80s",host);
    (*bn) (BLOCK_NONSENSITIVE,data);
    (*bn) (BLOCK_NONE,NIL);
    if (he) {			/* DNS resolution won? */
      if (tcpdebug) mm_log ("DNS resolution done",TCPDEBUG);
				/* copy address type */
      sin.sin_family = he->h_addrtype;
				/* copy host name */
      strcpy (hostname,he->h_name);
#ifdef HOST_NOT_FOUND		/* muliple addresses only on DNS systems */
      for (sock = -1,i = 0; (sock < 0) && (s = he->h_addr_list[i]); i++) {
	if (i && !silent) mm_log (tmp,WARN);
	memcpy (&sin.sin_addr,s,he->h_length);
	(*bn) (BLOCK_TCPOPEN,NIL);
	sock = tcp_socket_open (&sin,tmp,ctrp,hostname,port);
	(*bn) (BLOCK_NONE,NIL);
      }
#else				/* the one true address then */
      memcpy (&sin.sin_addr,he->h_addr,he->h_length);
      (*bn) (BLOCK_TCPOPEN,NIL);
      sock = tcp_socket_open (&sin,tmp,ctrp,hostname,port);
      (*bn) (BLOCK_NONE,NIL);
#endif
    }
  }
  if (sock >= 0)  {		/* won */
    stream = (TCPSTREAM *) memset (fs_get (sizeof (TCPSTREAM)),0,
				   sizeof (TCPSTREAM));
    stream->port = port;	/* port number */
				/* init sockets */
    stream->tcpsi = stream->tcpso = sock;
				/* stash in the snuck-in byte */
    if (stream->ictr = ctr) *(stream->iptr = stream->ibuf) = tmp[0];
				/* copy official host name */
    stream->host = cpystr (hostname);
    if (tcpdebug) mm_log ("Stream open and ready for read",TCPDEBUG);
  }
  else if (!silent) mm_log (tmp,ERROR);
  return stream;		/* return success */
}