void run(EpmdVars *g)
{
  int listensock;
  int i;
  int opt;
  struct EPMD_SOCKADDR_IN iserv_addr;

  node_init(g);
  g->conn = conn_init(g);

  dbg_printf(g,2,"try to initiate listening port %d", g->port);
  
  if ((listensock = socket(FAMILY,SOCK_STREAM,0)) < 0) {
    dbg_perror(g,"error opening stream socket");
    epmd_cleanup_exit(g,1);
  }
  g->listenfd = listensock;

  /*
   * Initialize number of active file descriptors.
   * Stdin, stdout, and stderr are still open.
   * One for the listen socket.
   */
  g->active_conn = 3+1;
  
  /*
   * Note that we must not enable the SO_REUSEADDR on Windows,
   * because addresses will be reused even if they are still in use.
   */
  
#if (!defined(__WIN32__) && !defined(_OSE_))
  /* We ignore the SIGPIPE signal that is raised when we call write
     twice on a socket closed by the other end. */
  signal(SIGPIPE, SIG_IGN);

  opt = 1;			/* Set this option */
  if (setsockopt(listensock,SOL_SOCKET,SO_REUSEADDR,(char* ) &opt,
		 sizeof(opt)) <0) {
    dbg_perror(g,"can't set sockopt");
    epmd_cleanup_exit(g,1);
  }
#endif
  
  /* In rare cases select returns because there is someone
     to accept but the request is withdrawn before the
     accept function is called. We set the listen socket
     to be non blocking to prevent us from being hanging
     in accept() waiting for the next request. */
#ifdef _OSE_  
  opt = 1;
  if (ioctl(listensock, FIONBIO, (char*)&opt) != 0)
#else
#if (defined(__WIN32__) || defined(NO_FCNTL))
  opt = 1;
  if (ioctl(listensock, FIONBIO, &opt) != 0) /* Gives warning in VxWorks */
#else
  opt = fcntl(listensock, F_GETFL, 0);
  if (fcntl(listensock, F_SETFL, opt | O_NONBLOCK) == -1)
#endif /* __WIN32__ || VXWORKS */
#endif /* _OSE_ */
    dbg_perror(g,"failed to set non-blocking mode of listening socket %d",
	       listensock);

  { /* store port number in unsigned short */
    unsigned short sport = g->port;
    SET_ADDR_ANY(iserv_addr, FAMILY, sport);
  }
  
#ifdef _OSE_
  {
    int optlen = sizeof(opt);
    opt = 1;
    if(getsockopt(listensock, SOL_SOCKET, SO_REUSEADDR,
		  (void*)&opt, &optlen) < 0)
      fprintf(stderr, "\n\nGETSOCKOPT FAILS! %d\n\n", errno);
    else if(opt == 1)
      fprintf(stderr, "SO_REUSEADDR is set!\n");
  }
#endif

  if(bind(listensock,(struct sockaddr*) &iserv_addr, sizeof(iserv_addr)) < 0 )
    {
      if (errno == EADDRINUSE)
	{
	  dbg_tty_printf(g,1,"there is already a epmd running at port %d",
			 g->port);
	  epmd_cleanup_exit(g,0);
	}
      else
	{
	  dbg_perror(g,"failed to bind socket");
	  epmd_cleanup_exit(g,1);
	}
    }

  dbg_printf(g,2,"starting");

  listen(listensock, SOMAXCONN);


  FD_ZERO(&g->orig_read_mask);
  FD_SET(listensock,&g->orig_read_mask);

  dbg_tty_printf(g,2,"entering the main select() loop");

 select_again:
  while(1)
    {	
      fd_set read_mask = g->orig_read_mask;
      struct timeval timeout;
      int ret;

      /* If we are idle we time out now and then to enable the code
	 below to close connections that are old and probably
	 hanging. Make sure that select will return often enough. */

      timeout.tv_sec = (g->packet_timeout < IDLE_TIMEOUT) ? 1 : IDLE_TIMEOUT;
      timeout.tv_usec = 0;

      if ((ret = select(g->max_conn,&read_mask,(fd_set *)0,(fd_set *)0,&timeout)) < 0)
	dbg_perror(g,"error in select ");
      else {
	time_t now;
	if (ret == 0) {
	  FD_ZERO(&read_mask);
	}
	if (g->delay_accept) {		/* Test of busy server */
	  sleep(g->delay_accept);
	}

	if (FD_ISSET(listensock,&read_mask)) {
	  if (do_accept(g, listensock) && g->active_conn < g->max_conn) {
	    /*
	     * The accept() succeeded, and we have at least one file
	     * descriptor still free, which means that another accept()
	     * could succeed. Go do do another select(), in case there
	     * are more incoming connections waiting to be accepted.
	     */
	    goto select_again;
	  }
	}
	  
	/* Check all open streams marked by select for data or a
	   close.  We also close all open sockets except ALIVE
	   with no activity for a long period */

	now = current_time(g);
	for (i = 0; i < g->max_conn; i++) {
	  if (g->conn[i].open == EPMD_TRUE) {
	    if (FD_ISSET(g->conn[i].fd,&read_mask))
	      do_read(g,&g->conn[i]);
	    else if ((g->conn[i].keep == EPMD_FALSE) &&
		     ((g->conn[i].mod_time + g->packet_timeout) < now)) {
	      dbg_tty_printf(g,1,"closing because timed out on receive");
	      epmd_conn_close(g,&g->conn[i]);
	    }
	  }
	}
      }
    }
}