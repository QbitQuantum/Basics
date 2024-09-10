int
main(int argc, char **argv)
{
    struct sockaddr_storage __ss;
    struct sockaddr *sa = (struct sockaddr *)&__ss;
    int on = 1;
    socklen_t sa_size;
    int ch;
#if	defined(IPPROTO_IP) && defined(IP_TOS)
    int tos = -1;
#endif
#ifdef ENCRYPTION
    des_check_key = 1;	/* Kludge for Mac NCSA telnet 2.6 /bg */
#endif

	pfrontp = pbackp = ptyobuf;
    netip = netibuf;
    nfrontp = nbackp = netobuf;
	    
#ifdef __SYMBIAN32__
	if( getConnectionUp() < 0) exit(1);
#endif	

    setprogname(argv[0]);

    progname = *argv;
#ifdef ENCRYPTION
    nclearto = 0;
#endif

#ifdef _CRAY
    /*
     * Get number of pty's before trying to process options,
     * which may include changing pty range.
     */
    highpty = getnpty();
#endif /* CRAY */

    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
#ifndef __SYMBIAN32__
	print_version(NULL); 
#endif //__SYMBIAN32__
	exit(0);
    }

    while ((ch = getopt(argc, argv, valid_opts)) != -1) {
	switch(ch) {

#ifdef	AUTHENTICATION
	case 'a':
	    /*
	     * Check for required authentication level
	     */
	    if (strcmp(optarg, "debug") == 0) {
		auth_debug_mode = 1;
	    } else if (strcasecmp(optarg, "none") == 0) {
		auth_level = 0;
	    } else if (strcasecmp(optarg, "otp") == 0) {
		auth_level = 0;
		require_otp = 1;
	    } else if (strcasecmp(optarg, "other") == 0) {
		auth_level = AUTH_OTHER;
	    } else if (strcasecmp(optarg, "user") == 0) {
		auth_level = AUTH_USER;
	    } else if (strcasecmp(optarg, "valid") == 0) {
		auth_level = AUTH_VALID;
	    } else if (strcasecmp(optarg, "off") == 0) {
		/*
		 * This hack turns off authentication
		 */
		auth_level = -1;
	    } else {
		fprintf(stderr,
			"telnetd: unknown authorization level for -a\n");
	    }
	    break;
#endif	/* AUTHENTICATION */

	case 'B': /* BFTP mode is not supported any more */
	    break;
	case 'd':
	    if (strcmp(optarg, "ebug") == 0) {
		debug++;
		break;
	    }
	    usage();
	    /* NOTREACHED */
	    break;

#ifdef DIAGNOSTICS
	case 'D':
	    /*
	     * Check for desired diagnostics capabilities.
	     */
	    if (!strcmp(optarg, "report")) {
		diagnostic |= TD_REPORT|TD_OPTIONS;
	    } else if (!strcmp(optarg, "exercise")) {
		diagnostic |= TD_EXERCISE;
	    } else if (!strcmp(optarg, "netdata")) {
		diagnostic |= TD_NETDATA;
	    } else if (!strcmp(optarg, "ptydata")) {
		diagnostic |= TD_PTYDATA;
	    } else if (!strcmp(optarg, "options")) {
		diagnostic |= TD_OPTIONS;
	    } else {
		usage();
		/* NOT REACHED */
	    }
	    break;
#endif /* DIAGNOSTICS */


	case 'h':
	    hostinfo = 0;
	    break;

	case 'k': /* Linemode is not supported any more */
	case 'l':
	    break;

	case 'n':
	    keepalive = 0;
	    break;

#ifdef _CRAY
	case 'r':
	    {
		char *strchr();
		char *c;

		/*
		 * Allow the specification of alterations
		 * to the pty search range.  It is legal to
		 * specify only one, and not change the
		 * other from its default.
		 */
		c = strchr(optarg, '-');
		if (c) {
		    *c++ = '\0';
		    highpty = atoi(c);
		}
		if (*optarg != '\0')
		    lowpty = atoi(optarg);
		if ((lowpty > highpty) || (lowpty < 0) ||
		    (highpty > 32767)) {
		    usage();
		    /* NOT REACHED */
		}
		break;
	    }
#endif	/* CRAY */

	case 'S':
#ifdef	HAVE_PARSETOS
	    if ((tos = parsetos(optarg, "tcp")) < 0)
		fprintf(stderr, "%s%s%s\n",
			"telnetd: Bad TOS argument '", optarg,
			"'; will try to use default TOS");
#else
	    fprintf(stderr, "%s%s\n", "TOS option unavailable; ",
		    "-S flag not supported\n");
#endif
	    break;

	case 'u': {
	    char *eptr;

	    utmp_len = strtol(optarg, &eptr, 0);
	    if (optarg == eptr)
		fprintf(stderr, "telnetd: unknown utmp len (%s)\n", optarg);
	    break;
	}

	case 'U':
	    registerd_host_only = 1;
	    break;

#ifdef	AUTHENTICATION
	case 'X':
	    /*
	     * Check for invalid authentication types
	     */
	    auth_disable_name(optarg);
	    break;
#endif
	case 'y':
	    no_warn = 1;
	    break;
#ifdef AUTHENTICATION
	case 'z':
	    log_unauth = 1;
	    break;

#endif	/* AUTHENTICATION */

	case 'L':
	    new_login = optarg;
	    break;
			
	default:
	    fprintf(stderr, "telnetd: %c: unknown option\n", ch);
	    /* FALLTHROUGH */
	case '?':
	    usage();
	    /* NOTREACHED */
	}
    }

    argc -= optind;
    argv += optind;

    if (debug) {
	int port = 0;
	struct servent *sp;

	if (argc > 1) {
	    usage ();
	} else if (argc == 1) {
	    sp = (struct servent*)roken_getservbyname (*argv, "tcp");
	    if (sp)
		port = sp->s_port;
	    else
		port = htons(atoi(*argv));
	} else {
#ifdef 	__SYMBIAN32__
		port = htons(atoi("23"));		
#else
#ifdef KRB5
	    port = krb5_getportbyname (NULL, "telnet", "tcp", 23);
#else
	    port = k_getportbyname("telnet", "tcp", htons(23));
#endif
#endif //__SYMBIAN32__
	}
	mini_inetd (port);
    } else if (argc > 0) {
	usage();
	/* NOT REACHED */
    }

#ifdef _SC_CRAY_SECURE_SYS
    secflag = sysconf(_SC_CRAY_SECURE_SYS);

    /*
     *	Get socket's security label
     */
    if (secflag)  {
	socklen_t szss = sizeof(ss);
	int sock_multi;
	socklen_t szi = sizeof(int);

	memset(&dv, 0, sizeof(dv));

	if (getsysv(&sysv, sizeof(struct sysv)) != 0) 
	    fatalperror(net, "getsysv");

	/*
	 *	Get socket security label and set device values
	 *	   {security label to be set on ttyp device}
	 */
#ifdef SO_SEC_MULTI			/* 8.0 code */
	if ((getsockopt(0, SOL_SOCKET, SO_SECURITY,
			(void *)&ss, &szss) < 0) ||
	    (getsockopt(0, SOL_SOCKET, SO_SEC_MULTI,
			(void *)&sock_multi, &szi) < 0)) 
	    fatalperror(net, "getsockopt");
	else {
	    dv.dv_actlvl = ss.ss_actlabel.lt_level;
	    dv.dv_actcmp = ss.ss_actlabel.lt_compart;
	    if (!sock_multi) {
		dv.dv_minlvl = dv.dv_maxlvl = dv.dv_actlvl;
		dv.dv_valcmp = dv.dv_actcmp;
	    } else {
		dv.dv_minlvl = ss.ss_minlabel.lt_level;
		dv.dv_maxlvl = ss.ss_maxlabel.lt_level;
		dv.dv_valcmp = ss.ss_maxlabel.lt_compart;
	    }
	    dv.dv_devflg = 0;
	}
#else /* SO_SEC_MULTI */		/* 7.0 code */
	if (getsockopt(0, SOL_SOCKET, SO_SECURITY,
		       (void *)&ss, &szss) >= 0) {
	    dv.dv_actlvl = ss.ss_slevel;
	    dv.dv_actcmp = ss.ss_compart;
	    dv.dv_minlvl = ss.ss_minlvl;
	    dv.dv_maxlvl = ss.ss_maxlvl;
	    dv.dv_valcmp = ss.ss_maxcmp;
	}
#endif /* SO_SEC_MULTI */
    }
#endif	/* _SC_CRAY_SECURE_SYS */

 
    roken_openlog("telnetd", LOG_PID | LOG_ODELAY, LOG_DAEMON);
    sa_size = sizeof (__ss);
    
    if (getpeername(STDIN_FILENO, sa, &sa_size) < 0) {
	fprintf(stderr, "%s: ", progname);
	perror("getpeername");
	_exit(1);
    }

    if (keepalive &&
	setsockopt(STDIN_FILENO, SOL_SOCKET, SO_KEEPALIVE,
		   (void *)&on, sizeof (on)) < 0) {		 
#ifndef __SYMBIAN32__		     
	syslog(LOG_WARNING, "setsockopt (SO_KEEPALIVE): %m");
#endif
	;
    }
    

#if	defined(IPPROTO_IP) && defined(IP_TOS) && defined(HAVE_SETSOCKOPT)
    {
# ifdef HAVE_GETTOSBYNAME
	struct tosent *tp;
	if (tos < 0 && (tp = gettosbyname("telnet", "tcp")))
	    tos = tp->t_tos;
# endif
	if (tos < 0)
	    tos = 020;	/* Low Delay bit */
	if (tos
	    && sa->sa_family == AF_INET
	    && (setsockopt(STDIN_FILENO, IPPROTO_IP, IP_TOS,
			   (void *)&tos, sizeof(tos)) < 0)
	    && (errno != ENOPROTOOPT) )
	    syslog(LOG_WARNING, "setsockopt (IP_TOS): %m");
    }
#endif	/* defined(IPPROTO_IP) && defined(IP_TOS) */
    net = STDIN_FILENO;
    doit(sa, sa_size);
    /* NOTREACHED */
    return 0;
}  /* end of main */