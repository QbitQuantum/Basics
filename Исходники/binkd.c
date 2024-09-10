int main (int argc, char *argv[])
#endif
{
  char tmp[128];
#if defined(HAVE_FORK)
  char **saved_argv;

  mypid = getpid();
  /* save argv as setproctitle() under some systems will change it */
  saved_argv = mkargv (argc, argv);

  configpath = parseargs(argc, saved_argv);
#else
  configpath = parseargs(argc, argv);
#endif

  saved_envp = mkargv (-1, environ);

#ifdef WIN32
  if (service_flag==w32_installservice && !configpath)
    Log (0, "%s: invalid command line: config name must be specified", extract_filename(argv[0]));
  w32Init();
#ifdef BINKD9X
  {
    int win9x_rc;

    win9x_rc = win9x_process(argc, argv);
    if (win9x_rc != -1)
      return win9x_rc;
  }
#endif
#endif

  tzset();

  if (poll_flag && server_flag)
    Log (0, "-p and -s cannot be used together");

#if defined(WIN32) && !defined(BINKD9X)
  if (service_flag!=w32_noservice)
    if (service(argc, argv, environ) && service_flag!=w32_run_as_service) {
      Log(0, "Windows NT service error");
    }
  if (tray_flag)
     do_tray_flag();
  else
  {
    atexit(UnloadBinkdIcon);
    LoadBinkdIcon();
  }
#endif

  /* No command line options: run both client and server */
  if (!client_flag && !server_flag)
    client_flag = server_flag = 1;

  InitSem (&hostsem);
  InitSem (&resolvsem);
  InitSem (&lsem);
  InitSem (&blsem);
  InitSem (&varsem);
  InitSem (&config_sem);
  InitEventSem (&eothread);
  InitEventSem (&wakecmgr);
#ifdef OS2
  InitSem (&fhsem);
#endif

  /* Init for ftnnode.c */
  nodes_init ();

  if (configpath)
  {
    current_config = readcfg (configpath);
    if (!current_config)
      Log (0, "error in configuration, aborting");
    if (dumpcfg_flag)
    {
      debug_readcfg ();
      exit(0);
    }
    InitLog(current_config->loglevel, current_config->conlog,
            current_config->logpath, current_config->nolog.first);
  }
  else if (verbose_flag)
  {
#if defined(WIN32) && defined(BINKD9X)
    AllocTempConsole();
#endif

    printf ("Binkd " MYVER " (" __DATE__ " " __TIME__ "%s)\n", get_os_string ());
    if (verbose_flag>1)
    {
      printf ("Compilation flags: " _DBNKD ".\n");
      printf ("Facilities: "
#ifndef srv_getaddrinfo
              "fsp1035 "
#endif
#ifndef HAVE_GETADDRINFO
              "rfc2553emu "
#else
              "ipv6 "
#endif
              "\n");
    }
    exit (0);
  }
  else if (argc > 1)
    Log (0, "%s: invalid command line: config name must be specified", extract_filename(argv[0]));
  else
    usage ();

  print_args (tmp, sizeof (tmp), argv + 1);
#ifdef WIN32
  if (service_flag==w32_run_as_service)
    Log (4, "BEGIN service '%s', " MYNAME "/" MYVER "%s%s", service_name, get_os_string(), tmp);
  else
    Log (4, "BEGIN standalone, " MYNAME "/" MYVER "%s%s", get_os_string(), tmp);
#else
  Log (4, "BEGIN, " MYNAME "/" MYVER "%s%s", get_os_string(), tmp);
#endif
  if (sock_init ())
    Log (0, "sock_init: %s", TCPERR ());

  bsy_init ();
  rnd ();
  initsetproctitle (argc, argv, environ);
#ifdef WIN32
  SetFileApisToOEM();
#endif

  /* Set up break handler, set up exit list if needed */
  if (!set_break_handlers ())
    Log (0, "cannot install break handlers");

#if defined(SIGPIPE)
  signal(SIGPIPE, SIG_IGN);
#endif

#if defined(WITH_ZLIB) && defined(ZLIBDL)
  if (current_config->zlib_dll[0]) {
    if (!zlib_init(current_config->zlib_dll))
      Log (2, "cannot load %s, GZ compression disabled", current_config->zlib_dll);
    else
      Log (6, "%s loaded successfully", current_config->zlib_dll);
  } else
    Log (current_config->zrules.first ? 3 : 5, "zlib-dll not defined, GZ compression disabled");
#endif
#if defined(WITH_BZLIB2) && defined(ZLIBDL)
  if (current_config->bzlib2_dll[0]) {
    if (!bzlib2_init(current_config->bzlib2_dll))
      Log (2, "cannot load %s, BZ2 compression disabled", current_config->bzlib2_dll);
    else
      Log (6, "%s loaded successfully", current_config->bzlib2_dll);
  } else
    Log (current_config->zrules.first
#ifdef WITH_ZLIB
         && !zlib_loaded
#endif
         ? 3 : 5, "bzlib2-dll not defined, BZ2 compression disabled");
#endif

#ifdef WITH_PERL
  if (current_config->perl_script[0]) {
    if (!perl_init(current_config->perl_script, current_config)) {
      if (current_config->perl_strict)
        Log (0, "error parsing Perl script %s", current_config->perl_script);
    } else {
      perl_on_start(current_config);
      perl_config_loaded(current_config);
    }
  }
#endif

#ifdef HAVE_FORK
  signal (SIGCHLD, sighandler);
#endif

  { /* Create polls and release polls list */
    struct maskchain *psP;
    for (psP = psPolls.first; psP; psP = psP->next)
      poll_node (psP->mask, current_config);
    simplelist_free(&psPolls.linkpoint, destroy_maskchain);
  }

  if (no_flag)
    Log (0, "Exit on option '-n'");

  if (inetd_flag)
  {
    FTN_ADDR ftn_addr, *pftn_addr;
    int tempfd;

    pftn_addr = NULL;
    if (remote_node)
    {
      if (parse_ftnaddress (remote_node, &ftn_addr, current_config->pDomains.first))
      {
        char szFTNAddr[FTN_ADDR_SZ + 1];

        exp_ftnaddress (&ftn_addr, current_config->pAddr, current_config->nAddr, current_config->pDomains.first);
        pftn_addr = &ftn_addr;
        ftnaddress_to_str (szFTNAddr, pftn_addr);
        Log (3, "Session with %s", szFTNAddr);
      }
      else
        Log (1, "`%s' cannot be parsed as a Fido-style address", remote_node);
    }
    if (!remote_addr)
    {
      char *p = getenv("SSH_CONNECTION");

      if (p)
      {
	remote_addr = strdup(p);
	p = strchr(remote_addr, ' ');
	if (p) *p = '\0';
      }
    }
    /* not using stdin/stdout itself to avoid possible collisions */
    if (inetd_socket_in == -1)
      inetd_socket_in = dup(fileno(stdin));
    if (inetd_socket_out == -1)
      inetd_socket_out = dup(fileno(stdout));
#ifdef UNIX
    tempfd = open("/dev/null", O_RDWR);
#else
    tempfd = open("nul", O_RDWR);
#endif
    if (tempfd != -1)
    {
      dup2(tempfd, fileno(stdin));
      dup2(tempfd, fileno(stdout));
      close(tempfd);
    }
    protocol (inetd_socket_in, inetd_socket_out, NULL, pftn_addr, remote_addr, current_config);
    soclose (inetd_socket_out);
    exit (0);
  }

#ifdef BINKD_DAEMONIZE
  if (daemon_flag)
  {
    if (binkd_daemonize(1) < 0)
      Log (0, "Cannot daemonize");
    else
      mypid = getpid();
  }
#endif

#if defined(HAVE_FORK)
  signal (SIGHUP, sighandler);
#endif

  if (client_flag && !server_flag)
  {
    clientmgr (0);
    exit (0);
  }

  pidsmgr = (int) getpid ();
  if (client_flag && (pidcmgr = branch (clientmgr, 0, 0)) < 0)
  {
    Log (0, "cannot branch out");
  }

  if (*current_config->pid_file)
  {
    if ( unlink (current_config->pid_file) == 0 ) /* successfully unlinked, i.e.
	                                            an old pid_file was found */
	Log (1, "unexpected pid_file: %s: unlinked", current_config->pid_file);
    else
    {
	int current_log_level = 1;
	switch ( errno )
	{
	   case ENOENT :	/* file not found or null pathname */
		current_log_level = 8; /* it's ok */
		break;
	   default :
		break;
	}
	Log (current_log_level, "unlink_pid_file: %s: %s", current_config->pid_file, strerror (errno));
    }
    create_sem_file (current_config->pid_file, 1);
  }

  servmgr ();

  return 0;
}