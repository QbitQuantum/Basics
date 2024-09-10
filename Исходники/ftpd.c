int
main (int argc, char *argv[], char **envp)
{
  int index;

  set_program_name (argv[0]);

#ifdef HAVE_TZSET
  tzset ();			/* In case no timezone database in ~ftp.  */
#endif

#ifdef HAVE_INITSETPROCTITLE
  /* Save start and extent of argv for setproctitle.  */
  initsetproctitle (argc, argv, envp);
#endif /* HAVE_INITSETPROCTITLE */

  /* Parse the command line */
  iu_argp_init ("ftpd", default_program_authors);
  argp_parse (&argp, argc, argv, 0, &index, NULL);
  
  /* Bail out, wrong usage */
  argc -= index;
  if (argc != 0)
    error (1, 0, "surplus arguments; try `%s --help' for more info",
	   program_name);

  /* LOG_NDELAY sets up the logging connection immediately,
     necessary for anonymous ftp's that chroot and can't do it later.  */
  openlog ("ftpd", LOG_PID | LOG_NDELAY, LOG_FTP);
  freopen (PATH_DEVNULL, "w", stderr);

  /* If not running via inetd, we detach and dup(fd, 0), dup(fd, 1) the
     fd = accept(). tcpd is check if compile with the support  */
  if (daemon_mode)
    {
      if (server_mode (pid_file, &his_addr) < 0)
	exit (1);
    }
  else
    {
      socklen_t addrlen = sizeof (his_addr);
      if (getpeername (STDIN_FILENO, (struct sockaddr *) &his_addr,
		       &addrlen) < 0)
	{
	  syslog (LOG_ERR, "getpeername (%s): %m", program_name);
	  exit (1);
	}
    }

  signal (SIGHUP, sigquit);
  signal (SIGINT, sigquit);
  signal (SIGQUIT, sigquit);
  signal (SIGTERM, sigquit);
  signal (SIGPIPE, lostconn);
  signal (SIGCHLD, SIG_IGN);
  if (signal (SIGURG, myoob) == SIG_ERR)
    syslog (LOG_ERR, "signal: %m");

  /* Get info on the ctrl connection.  */
  {
    socklen_t addrlen = sizeof (ctrl_addr);
    if (getsockname (STDIN_FILENO, (struct sockaddr *) &ctrl_addr,
		     &addrlen) < 0)
      {
	syslog (LOG_ERR, "getsockname (%s): %m", program_name);
	exit (1);
      }
  }

#if defined (IP_TOS) && defined (IPTOS_LOWDELAY) && defined (IPPROTO_IP)
  /* To  minimize delays for interactive traffic.  */
  {
    int tos = IPTOS_LOWDELAY;
    if (setsockopt (STDIN_FILENO, IPPROTO_IP, IP_TOS,
		    (char *) &tos, sizeof (int)) < 0)
      syslog (LOG_WARNING, "setsockopt (IP_TOS): %m");
  }
#endif

#ifdef SO_OOBINLINE
  /* Try to handle urgent data inline.  */
  {
    int on = 1;
    if (setsockopt (STDIN_FILENO, SOL_SOCKET, SO_OOBINLINE,
		    (char *) &on, sizeof (on)) < 0)
      syslog (LOG_ERR, "setsockopt: %m");
  }
#endif

#ifdef SO_KEEPALIVE
  /* Set keepalives on the socket to detect dropped connections.  */
  {
    int keepalive = 1;
    if (setsockopt (STDIN_FILENO, SOL_SOCKET, SO_KEEPALIVE,
		    (char *) &keepalive, sizeof (keepalive)) < 0)
      syslog (LOG_WARNING, "setsockopt (SO_KEEPALIVE): %m");
  }
#endif

#ifdef	F_SETOWN
  if (fcntl (STDIN_FILENO, F_SETOWN, getpid ()) == -1)
    syslog (LOG_ERR, "fcntl F_SETOWN: %m");
#endif

  dolog (&his_addr, &cred);

  /* Deal with login disable.  */
  if (display_file (PATH_NOLOGIN, 530) == 0)
    {
      reply (530, "System not available.");
      exit (0);
    }

  /* Display a Welcome message if exists,
     N.B. reply(220,) must follow.  */
  display_file (PATH_FTPWELCOME, 220);

  hostname = localhost ();
  if (!hostname)
    perror_reply (550, "Local resource failure: malloc");

  /* Tell them we're ready to roll.  */
  if (!no_version)
    reply (220, "%s FTP server (%s %s) ready.",
	   hostname, PACKAGE_NAME, PACKAGE_VERSION);
  else
    reply (220, "%s FTP server ready.", hostname);

  /* Set the jump, if we have an error parsing,
     come here and start fresh.  */
  setjmp (errcatch);

  /* Roll.  */
  for (;;)
    yyparse ();
}