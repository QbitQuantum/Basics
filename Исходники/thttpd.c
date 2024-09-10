int
main( int argc, char** argv )
    {
    char* cp;
    struct passwd* pwd;
    uid_t uid;
    gid_t gid;
    char cwd[MAXPATHLEN];
    FILE* logfp;
    int num_ready;
    int cnum, ridx;
    connecttab* c;
    httpd_conn* hc;
    httpd_sockaddr sa4;
    httpd_sockaddr sa6;
    int gotv4, gotv6;
    struct timeval tv;

    argv0 = argv[0];

    cp = strrchr( argv0, '/' );
    if ( cp != (char*) 0 )
	++cp;
    else
	cp = argv0;
    openlog( cp, LOG_NDELAY|LOG_PID, LOG_FACILITY );

    /* Handle command-line arguments. */
    parse_args( argc, argv );

    /* Check port number. */
    if ( port <= 0 )
	{
	syslog( LOG_CRIT, "illegal port number" );
	(void) fprintf( stderr, "%s: illegal port number\n", argv0 );
	exit( 1 );
	}

    /* Read zone info now, in case we chroot(). */
    tzset();

    /* Look up hostname now, in case we chroot(). */
    lookup_hostname( &sa4, sizeof(sa4), &gotv4, &sa6, sizeof(sa6), &gotv6 );
    if ( ! ( gotv4 || gotv6 ) )
	{
	syslog( LOG_ERR, "can't find any valid address" );
	(void) fprintf( stderr, "%s: can't find any valid address\n", argv0 );
	exit( 1 );
	}

    /* Throttle file. */
    numthrottles = 0;
    maxthrottles = 0;
    throttles = (throttletab*) 0;
    if ( throttlefile != (char*) 0 )
	read_throttlefile( throttlefile );

    /* Log file. */
    if ( logfile != (char*) 0 )
	{
	if ( strcmp( logfile, "/dev/null" ) == 0 )
	    {
	    no_log = 1;
	    logfp = (FILE*) 0;
	    }
	else
	    {
	    logfp = fopen( logfile, "a" );
	    if ( logfp == (FILE*) 0 )
		{
		syslog( LOG_CRIT, "%.80s - %m", logfile );
		perror( logfile );
		exit( 1 );
		}
	    (void) fcntl( fileno( logfp ), F_SETFD, 1 );
	    }
	}
    else
	logfp = (FILE*) 0;

    /* Figure out uid/gid from user. */
    pwd = getpwnam( user );
    if ( pwd == (struct passwd*) 0 )
	{
	syslog( LOG_CRIT, "unknown user - '%.80s'", user );
	(void) fprintf( stderr, "%s: unknown user - '%s'\n", argv0, user );
	exit( 1 );
	}
    uid = pwd->pw_uid;
    gid = pwd->pw_gid;

    /* Switch directories if requested. */
    if ( dir != (char*) 0 )
	{
	if ( chdir( dir ) < 0 )
	    {
	    syslog( LOG_CRIT, "chdir - %m" );
	    perror( "chdir" );
	    exit( 1 );
	    }
	}
#ifdef USE_USER_DIR
    else if ( getuid() == 0 )
	{
	/* No explicit directory was specified, we're root, and the
	** USE_USER_DIR option is set - switch to the specified user's
	** home dir.
	*/
	if ( chdir( pwd->pw_dir ) < 0 )
	    {
	    syslog( LOG_CRIT, "chdir - %m" );
	    perror( "chdir" );
	    exit( 1 );
	    }
	}
#endif /* USE_USER_DIR */

    /* Get current directory. */
    (void) getcwd( cwd, sizeof(cwd) - 1 );
    if ( cwd[strlen( cwd ) - 1] != '/' )
	(void) strcat( cwd, "/" );

    if ( ! debug )
	{
	/* We're not going to use stdin stdout or stderr from here on, so close
	** them to save file descriptors.
	*/
	(void) fclose( stdin );
	(void) fclose( stdout );
	(void) fclose( stderr );

	/* Daemonize - make ourselves a subprocess. */
#ifdef HAVE_DAEMON
	if ( daemon( 1, 1 ) < 0 )
	    {
	    syslog( LOG_CRIT, "daemon - %m" );
	    exit( 1 );
	    }
#else /* HAVE_DAEMON */
	switch ( fork() )
	    {
	    case 0:
	    break;
	    case -1:
	    syslog( LOG_CRIT, "fork - %m" );
	    exit( 1 );
	    default:
	    exit( 0 );
	    }
#ifdef HAVE_SETSID
        (void) setsid();
#endif /* HAVE_SETSID */
#endif /* HAVE_DAEMON */
	}
    else
	{
	/* Even if we don't daemonize, we still want to disown our parent
	** process.
	*/
#ifdef HAVE_SETSID
        (void) setsid();
#endif /* HAVE_SETSID */
	}

    if ( pidfile != (char*) 0 )
	{
	/* Write the PID file. */
	FILE* pidfp = fopen( pidfile, "w" );
	if ( pidfp == (FILE*) 0 )
	    {
	    syslog( LOG_CRIT, "%.80s - %m", pidfile );
	    exit( 1 );
	    }
	(void) fprintf( pidfp, "%d\n", (int) getpid() );
	(void) fclose( pidfp );
	}

    /* Chroot if requested. */
    if ( do_chroot )
	{
	if ( chroot( cwd ) < 0 )
	    {
	    syslog( LOG_CRIT, "chroot - %m" );
	    perror( "chroot" );
	    exit( 1 );
	    }
	(void) strcpy( cwd, "/" );
	/* Always chdir to / after a chroot. */
	if ( chdir( cwd ) < 0 )
	    {
	    syslog( LOG_CRIT, "chroot chdir - %m" );
	    perror( "chroot chdir" );
	    exit( 1 );
	    }
	}

    /* Set up to catch signals. */
    (void) signal( SIGTERM, handle_term );
    (void) signal( SIGINT, handle_term );
    (void) signal( SIGPIPE, SIG_IGN );          /* get EPIPE instead */
    (void) signal( SIGHUP, handle_hup );
    got_usr1 = 0;
    (void) signal( SIGUSR1, handle_usr1 );
    (void) signal( SIGUSR2, handle_usr2 );

    /* Initialize the timer package. */
    tmr_init();

    /* Initialize the HTTP layer.  Got to do this before giving up root,
    ** so that we can bind to a privileged port.
    */
    hs = httpd_initialize(
	hostname,
	gotv4 ? &sa4 : (httpd_sockaddr*) 0, gotv6 ? &sa6 : (httpd_sockaddr*) 0,
	port, cgi_pattern, charset, cwd, no_log, logfp, no_symlink, do_vhost,
	do_global_passwd, url_pattern, local_pattern, no_empty_referers );
    if ( hs == (httpd_server*) 0 )
	exit( 1 );

    /* Set up the occasional timer. */
    if ( tmr_create( (struct timeval*) 0, occasional, JunkClientData, OCCASIONAL_TIME * 1000L, 1 ) == (Timer*) 0 )
	{
	syslog( LOG_CRIT, "tmr_create(occasional) failed" );
	exit( 1 );
	}
    if ( numthrottles > 0 )
	{
	/* Set up the throttles timer. */
	if ( tmr_create( (struct timeval*) 0, update_throttles, JunkClientData, THROTTLE_TIME * 1000L, 1 ) == (Timer*) 0 )
	    {
	    syslog( LOG_CRIT, "tmr_create(update_throttles) failed" );
	    exit( 1 );
	    }
	}
#ifdef STATS_TIME
    /* Set up the stats timer. */
    if ( tmr_create( (struct timeval*) 0, show_stats, JunkClientData, STATS_TIME * 1000L, 1 ) == (Timer*) 0 )
	{
	syslog( LOG_CRIT, "tmr_create(show_stats) failed" );
	exit( 1 );
	}
#endif /* STATS_TIME */
    start_time = stats_time = time( (time_t*) 0 );
    stats_connections = stats_bytes = 0L;
    stats_simultaneous = 0;

    /* If we're root, try to become someone else. */
    if ( getuid() == 0 )
	{
	/* Set aux groups to null. */
	if ( setgroups( 0, (const gid_t*) 0 ) < 0 )
	    {
	    syslog( LOG_CRIT, "setgroups - %m" );
	    exit( 1 );
	    }
	/* Set primary group. */
	if ( setgid( gid ) < 0 )
	    {
	    syslog( LOG_CRIT, "setgid - %m" );
	    exit( 1 );
	    }
	/* Try setting aux groups correctly - not critical if this fails. */
	if ( initgroups( user, gid ) < 0 )
	    syslog( LOG_WARNING, "initgroups - %m" );
#ifdef HAVE_SETLOGIN
	/* Set login name. */
        (void) setlogin( user );
#endif /* HAVE_SETLOGIN */
	/* Set uid. */
	if ( setuid( uid ) < 0 )
	    {
	    syslog( LOG_CRIT, "setuid - %m" );
	    exit( 1 );
	    }
	/* Check for unnecessary security exposure. */
	if ( ! do_chroot )
	    syslog(
		LOG_CRIT,
		"started as root without requesting chroot(), warning only" );
	}

    /* Initialize our connections table. */
    maxconnects = fdwatch_get_nfiles();
    if ( maxconnects < 0 )
	{
	syslog( LOG_CRIT, "fdwatch initialization failure" );
	exit( 1 );
	}
    maxconnects -= SPARE_FDS;
    connects = NEW( connecttab, maxconnects );
    if ( connects == (connecttab*) 0 )
	{
	syslog( LOG_CRIT, "out of memory allocating a connecttab" );
	exit( 1 );
	}
    for ( cnum = 0; cnum < maxconnects; ++cnum )
	{
	connects[cnum].conn_state = CNST_FREE;
	connects[cnum].hc = (httpd_conn*) 0;
	}
    numconnects = 0;
    httpd_conn_count = 0;

    if ( hs != (httpd_server*) 0 )
	{
	if ( hs->listen4_fd != -1 )
	    fdwatch_add_fd( hs->listen4_fd, (void*) 0, FDW_READ );
	if ( hs->listen6_fd != -1 )
	    fdwatch_add_fd( hs->listen6_fd, (void*) 0, FDW_READ );
	}

    /* Main loop. */
    (void) gettimeofday( &tv, (struct timezone*) 0 );
    while ( ( ! terminate ) || numconnects > 0 )
	{
	/* Do the fd watch. */
	num_ready = fdwatch( tmr_mstimeout( &tv ) );
	if ( num_ready < 0 )
	    {
	    if ( errno == EINTR )
		continue;       /* try again */
	    syslog( LOG_ERR, "fdwatch - %m" );
	    exit( 1 );
	    }
	(void) gettimeofday( &tv, (struct timezone*) 0 );
	if ( num_ready == 0 )
	    {
	    /* No fd's are ready - run the timers. */
	    tmr_run( &tv );
	    continue;
	    }

	/* Is it a new connection? */
	if ( hs != (httpd_server*) 0 && hs->listen6_fd != -1 && 
	     fdwatch_check_fd( hs->listen6_fd ) )
	    {
	    if ( handle_newconnect( &tv, hs->listen6_fd ) )
		/* Go around the loop and do another fdwatch, rather than
		** dropping through and processing existing connections.
		** New connections always get priority.
		*/
		continue;
	    }
	if ( hs != (httpd_server*) 0 && hs->listen4_fd != -1 && 
	     fdwatch_check_fd( hs->listen4_fd ) )
	    {
	    if ( handle_newconnect( &tv, hs->listen4_fd ) )
		/* Go around the loop and do another fdwatch, rather than
		** dropping through and processing existing connections.
		** New connections always get priority.
		*/
		continue;
	    }

	/* Find the connections that need servicing. */
	for ( ridx = 0; ridx < num_ready; ++ridx )
	    {
	    c = (connecttab*) fdwatch_get_client_data( ridx );
	    if ( c == (connecttab*) 0 )
		continue;
	    hc = c->hc;
	    if ( c->conn_state == CNST_READING &&
		 fdwatch_check_fd( hc->conn_fd ) )
		handle_read( c, &tv );
	    else if ( c->conn_state == CNST_SENDING &&
		 fdwatch_check_fd( hc->conn_fd ) )
		handle_send( c, &tv );
	    else if ( c->conn_state == CNST_LINGERING &&
		 fdwatch_check_fd( hc->conn_fd ) )
		handle_linger( c, &tv );
	    }
	tmr_run( &tv );

	if ( got_usr1 && ! terminate )
	    {
	    terminate = 1;
	    if ( hs != (httpd_server*) 0 )
		{
		httpd_terminate( hs );
		hs = (httpd_server*) 0;
		}
	    }
	}

    /* The main loop terminated. */
    shut_down();
    syslog( LOG_NOTICE, "exiting" );
    closelog();
    exit( 0 );
    }