/*
 * FtpConnect - connect to remote server
 *
 * return 1 if connected, 0 if not
 */
GLOBALDEF int FtpConnect(const char *host, netbuf **nControl)
{
    int sControl, stat, flags, oldflags;
    struct sockaddr_in sin;
    struct hostent *phe;
    struct servent *pse;
    int on=1;
    netbuf *ctrl;
    char *lhost;
    char *pnum;
    struct timeval tv;
    fd_set wr;

    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    lhost = strdup(host);
    pnum = strchr(lhost,':');
    if (pnum == NULL)
      {
#if defined(VMS) || defined(ANDROID)
          sin.sin_port = htons(21);
#else
          if ((pse = getservbyname("ftp","tcp")) == NULL)
            {
                perror("getservbyname");
                return 0;
            }
          sin.sin_port = pse->s_port;
#endif
      }
    else
      {
          *pnum++ = '\0';
          if (isdigit(*pnum))
              sin.sin_port = htons(atoi(pnum));
          else
            {
                pse = getservbyname(pnum,"tcp");
                sin.sin_port = pse->s_port;
            }
      }
    if ((sin.sin_addr.s_addr = inet_addr(lhost)) == -1)
      {
          if ((phe = gethostbyname(lhost)) == NULL)
            {
                perror("gethostbyname");
                return 0;
            }

          memcpy((char *)&sin.sin_addr, phe->h_addr, phe->h_length);

      }
    free(lhost);

    sControl = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sControl == -1)
      {
          perror("socket");
          return 0;
      }

    if ( setsockopt(sControl,SOL_SOCKET,SO_REUSEADDR,
                   SETSOCKOPT_OPTVAL_TYPE &on, sizeof(on)) == -1)
      {
          perror("setsockopt");
          net_close(sControl);
          return 0;
      }

#if defined(_WIN32)
	if (connect(sControl, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		perror("connect");
		net_close(sControl);
		return 0;
	}
#else
     //set nonblocking for connection timeout
    flags = fcntl( sControl, F_GETFL,0);
    oldflags=flags;
    fcntl( sControl, F_SETFL, O_NONBLOCK|flags);

    stat=connect( sControl, (struct sockaddr *)&sin, sizeof(sin));
    if (stat < 0) 
      { 
          if (errno != EWOULDBLOCK && errno != EINPROGRESS) 
            { 
                perror("connect");
                net_close(sControl);
                return 0;
            } 
      } 

    FD_ZERO(&wr); 
    FD_SET( sControl, &wr); 

    tv.tv_sec = ACCEPT_TIMEOUT;
    tv.tv_usec = 0; 

    stat = select(sControl+1, 0, &wr, 0, &tv);

    if (stat < 1)
      { 
            // time out has expired, 
            // or an error has ocurred
          perror("timeout");
          net_close(sControl);
          return 0;
      } 

    if (ftplib_debug > 1)
        printf("connected\n");

      //set original flags
    fcntl( sControl, F_SETFL, oldflags);
#endif

    ctrl = calloc(1,sizeof(netbuf));
    if (ctrl == NULL)
      {
          perror("calloc");
          net_close(sControl);
          return 0;
      }
    ctrl->buf = malloc(FTPLIB_BUFSIZ);
    if (ctrl->buf == NULL)
      {
          perror("calloc");
          net_close(sControl);
          free(ctrl);
          return 0;
      }
    ctrl->handle = sControl;
    ctrl->dir = FTPLIB_CONTROL;
    ctrl->ctrl = NULL;
    ctrl->cmode = FTPLIB_DEFMODE;
    ctrl->idlecb = NULL;
    ctrl->writercb = NULL;
    ctrl->idletime.tv_sec = ctrl->idletime.tv_usec = 0;
    ctrl->idlearg = NULL;
    ctrl->writerarg = NULL;
    ctrl->xfered = 0;
    ctrl->xfered1 = 0;
    ctrl->cbbytes = 0;
    if (readresp('2', ctrl) == 0)
      {
          net_close(sControl);
          free(ctrl->buf);
          free(ctrl);
          return 0;
      }
    *nControl = ctrl;
    return 1;
}