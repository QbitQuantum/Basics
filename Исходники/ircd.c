int
main (int argc, char *argv[])
{
  /* Check to see if the user is running
   * us as root, which is a nono
   */
  if (geteuid () == 0)
    {
      fprintf (stderr, "Don't run ircd as root!!!\n");
      return (-1);
    }

  /* save server boot time right away, so getrusage works correctly */
  set_time ();

  /* Setup corefile size immediately after boot -kre */
  setup_corefile ();

  /* set initialVMTop before we allocate any memory */
  initialVMTop = get_vm_top ();

  ServerRunning = 0;

  /* It ain't random, but it ought to be a little harder to guess */
  srand (SystemTime.tv_sec ^ (SystemTime.tv_usec | (getpid () << 20)));
  memset (&me, 0, sizeof (me));
  memset (&meLocalUser, 0, sizeof (meLocalUser));
  me.localClient = &meLocalUser;
  dlinkAdd (&me, &me.node, &global_client_list);	/* Pointer to beginning
							   of Client list */

  memset (&ServerInfo, 0, sizeof (ServerInfo));

  /* Initialise the channel capability usage counts... */
  init_chcap_usage_counts ();

  ConfigFileEntry.dpath = DPATH;
  ConfigFileEntry.configfile = CPATH;	/* Server configuration file */
  ConfigFileEntry.klinefile = KPATH;	/* Server kline file         */
  ConfigFileEntry.xlinefile = XPATH;	/* Server xline file         */
  ConfigFileEntry.dlinefile = DLPATH;	/* dline file                */
  ConfigFileEntry.cresvfile = CRESVPATH;	/* channel resv file      */
  ConfigFileEntry.nresvfile = NRESVPATH;	/* nick resv file         */
  myargv = argv;
  umask (077);			/* better safe than sorry --SRB */

  parseargs (&argc, &argv, myopts);

  build_version ();

  if (printVersion)
    {
      printf ("ircd: version %s\n", ircd_version);
      exit (EXIT_SUCCESS);
    }

  if (chdir (ConfigFileEntry.dpath))
    {
      perror ("chdir");
      exit (EXIT_FAILURE);
    }

  if (!server_state.foreground)
    make_daemon ();
  else
    print_startup (getpid ());

#ifdef HAVE_LIBCRYPTO
  dh_init();
  fprintf(stderr, "SSL: Initialize\n");

  SSL_load_error_strings();
  SSLeay_add_ssl_algorithms();
  ServerInfo.ctx = SSL_CTX_new(SSLv23_server_method());

  if (!ServerInfo.ctx) {
       ERR_print_errors_fp(stderr);
       return 0;
  }

  fprintf(stderr, "SSL: Client based SSL connections are enabled.\n");
#endif

  setup_signals ();
  /* We need this to initialise the fd array before anything else */
  fdlist_init ();

  if (!server_state.foreground)
    close_all_connections ();	/* this needs to be before init_netio()! */
  else
    check_can_use_v6 ();	/* Done in close_all_connections normally */

  init_log (logFileName);
  init_netio ();		/* This needs to be setup early ! -- adrian */
  /* Check if there is pidfile and daemon already running */
  check_pidfile (pidFileName);
  /* Init the event subsystem */
  eventInit ();
  init_sys ();

#ifndef NOBALLOC
  initBlockHeap ();
#endif
  init_dlink_nodes ();
  init_slink_nodes ();
  initialize_message_files ();
  dbuf_init ();
  init_hash ();
  init_ip_hash_table ();	/* client host ip hash table */
  init_host_hash ();		/* Host-hashtable. */
  clear_hash_parse ();
  init_client ();
  init_user ();
  init_channels ();
  init_class ();
  init_whowas ();
  init_stats ();
  init_hooks ();
  read_conf_files (1);		/* cold start init conf files */
  initServerMask ();
  init_uid ();
  init_auth ();			/* Initialise the auth code */
  init_resolver ();		/* Needs to be setup before the io loop */
  init_reject ();               /* Set up the reject code. */
  init_umodes ();               /* Set up the usermode system. */

  initialize_foundation_signals(); /* register things that modules need */

#ifdef HAVE_LIBCRYPTO
  bio_spare_fd = save_spare_fd ("SSL private key validation");
#endif /* HAVE_LIBCRYPTO */

  initialize_server_capabs ();	/* Set up default_server_capabs */
  initialize_global_set_options ();

  if (ServerInfo.name == NULL)
    {
      fprintf (stderr,
	       "ERROR: No server name specified in serverinfo block.\n");
      ilog (L_CRIT, "No server name specified in serverinfo block.");
      exit (EXIT_FAILURE);
    }
  strlcpy (me.name, ServerInfo.name, sizeof (me.name));

  /* serverinfo{} description must exist.  If not, error out. */
  if (ServerInfo.description == NULL)
    {
      fprintf (stderr,
	       "ERROR: No server description specified in serverinfo block.\n");
      ilog (L_CRIT,
	    "ERROR: No server description specified in serverinfo block.");
      exit (EXIT_FAILURE);
    }
  strlcpy (me.info, ServerInfo.description, sizeof (me.info));

  me.from = &me;
  me.servptr = &me;

  SetMe (&me);
  make_server (&me);

  strlcpy (me.serv->up, me.name, sizeof (me.serv->up));
  me.lasttime = me.since = me.firsttime = CurrentTime;
  hash_add_client (&me);

  /* add ourselves to global_serv_list */
  dlinkAdd (&me, make_dlink_node (), &global_serv_list);

  check_class ();

#ifndef STATIC_MODULES
  if (chdir (MODPATH))
    {
      ilog (L_CRIT, "Could not load core modules. Terminating!");
      exit (EXIT_FAILURE);
    }
  mod_set_base ();
  load_all_modules (1);
  load_core_modules (1);
  /* Go back to DPATH after checking to see if we can chdir to MODPATH */
  chdir (ConfigFileEntry.dpath);
#else
  load_all_modules (1);
#endif

  write_pidfile (pidFileName);

  ilog (L_NOTICE, "Server Ready");

  eventAddIsh ("cleanup_tklines", cleanup_tklines, NULL,
	       CLEANUP_TKLINES_TIME);

  /* We want try_connections to be called as soon as possible now! -- adrian */
  /* No, 'cause after a restart it would cause all sorts of nick collides */
  eventAddIsh ("try_connections", try_connections, NULL,
	       STARTUP_CONNECTIONS_TIME);

  eventAddIsh ("collect_zipstats", collect_zipstats, NULL, ZIPSTATS_TIME);

  /* Setup the timeout check. I'll shift it later :)  -- adrian */
  eventAddIsh ("comm_checktimeouts", comm_checktimeouts, NULL, 1);

  if (splitmode)
    eventAddIsh ("check_splitmode", check_splitmode, NULL, 60);

  ServerRunning = 1;
  io_loop ();
  return (0);
}