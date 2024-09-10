int main(int argc, const char *argv[]) {
   const char **arg1, *a;
   char *mainwaitstring;
   char buff[10];
   double rto;
   int i, argc0, result;
   struct utsname ubuf;
   int lockrc;

   if (mainwaitstring = getenv("SOCAT_MAIN_WAIT")) {
       sleep(atoi(mainwaitstring));
   }
   diag_set('p', strchr(argv[0], '/') ? strrchr(argv[0], '/')+1 : argv[0]);

   /* we must init before applying options because env settings have lower
      priority and are to be overridden by options */
   if (xioinitialize(XIO_MAYALL) != 0) {
      Exit(1);
   }

   xiosetopt('p', "%");
   xiosetopt('o', ":");

   argc0 = argc;	/* save for later use */
   arg1 = argv+1;  --argc;
   while (arg1[0] && (arg1[0][0] == '-')) {
      switch (arg1[0][1]) {
      case 'V': socat_version(stdout); Exit(0);
#if WITH_HELP
      case '?':
      case 'h':
	 socat_usage(stdout);
	 xioopenhelp(stdout, (arg1[0][2]=='?'||arg1[0][2]=='h') ? (arg1[0][3]=='?'||arg1[0][3]=='h') ? 2 : 1 : 0);
	 Exit(0);
#endif /* WITH_HELP */
      case 'd': diag_set('d', NULL); break;
#if WITH_FILAN
      case 'D': xioparams->debug = true; break;
#endif
      case 'l':
	 switch (arg1[0][2]) {
	 case 'm': /* mixed mode: stderr, then switch to syslog; + facility */
	    diag_set('s', NULL);
	    xiosetopt('l', "m");
	    xioparams->logopt = arg1[0][2];
	    xiosetopt('y', &arg1[0][3]);
	    break;
	 case 'y': /* syslog + facility */
	    diag_set(arg1[0][2], &arg1[0][3]);
	    break;
	 case 'f': /* to file, +filename */
	 case 'p': /* artificial program name */
	    if (arg1[0][3]) {
	       diag_set(arg1[0][2], &arg1[0][3]);
	    } else if (arg1[1]) {
	       diag_set(arg1[0][2], arg1[1]);
	       ++arg1, --argc;
	    } else {
	       Error1("option -l%c requires an argument; use option \"-h\" for help", arg1[0][2]);
	    }
	    break;
	 case 's': /* stderr */
	    diag_set(arg1[0][2], NULL);
	    break;
	 case 'u':
	    diag_set('u', NULL);
	    break;
	 case 'h':
	    diag_set_int('h', true);
	    break;
	 default:
	    Error1("unknown log option \"%s\"; use option \"-h\" for help", arg1[0]);
	    break;
	 }
	 break;
      case 'v': xioparams->verbose = true; break;
      case 'x': xioparams->verbhex = true; break;
      case 'b': if (arg1[0][2]) {
	    a = *arg1+2;
	 } else {
	    ++arg1, --argc;
	    if ((a = *arg1) == NULL) {
	       Error("option -b requires an argument; use option \"-h\" for help");
	       Exit(1);
	    }
	 }
	 xioparams->bufsiz = strtoul(a, (char **)&a, 0);
	 break;
      case 's':
	 diag_set_int('e', E_FATAL); break;
      case 't': if (arg1[0][2]) {
	    a = *arg1+2;
	 } else {
	    ++arg1, --argc;
	    if ((a = *arg1) == NULL) {
	       Error("option -t requires an argument; use option \"-h\" for help");
	       Exit(1);
	    }
	 }
	 rto = strtod(a, (char **)&a);
	 xioparams->closwait.tv_sec = rto;
	 xioparams->closwait.tv_usec =
	    (rto-xioparams->closwait.tv_sec) * 1000000; 
	 break;
      case 'T':  if (arg1[0][2]) {
	    a = *arg1+2;
	 } else {
	    ++arg1, --argc;
	    if ((a = *arg1) == NULL) {
	       Error("option -T requires an argument; use option \"-h\" for help");
	       Exit(1);
	    }
	 }
	 rto = strtod(a, (char **)&a);
	 xioparams->total_timeout.tv_sec = rto;
	 xioparams->total_timeout.tv_usec =
	    (rto-xioparams->total_timeout.tv_sec) * 1000000; 
	 break;
      case 'u': xioparams->lefttoright = true; break;
      case 'U': xioparams->righttoleft = true; break;
      case 'g': xioopts_ignoregroups = true; break;
      case 'L': if (socat_opts.lock.lockfile)
	     Error("only one -L and -W option allowed");
	 if (arg1[0][2]) {
	    socat_opts.lock.lockfile = *arg1+2;
	 } else {
	    ++arg1, --argc;
	    if ((socat_opts.lock.lockfile = *arg1) == NULL) {
	       Error("option -L requires an argument; use option \"-h\" for help");
	       Exit(1);
	    }
	 }
	 break;
      case 'W': if (socat_opts.lock.lockfile)
	    Error("only one -L and -W option allowed");
	 if (arg1[0][2]) {
	    socat_opts.lock.lockfile = *arg1+2;
	 } else {
	    ++arg1, --argc;
	    if ((socat_opts.lock.lockfile = *arg1) == NULL) {
	       Error("option -W requires an argument; use option \"-h\" for help");
	       Exit(1);
	    }
	 }
	 socat_opts.lock.waitlock = true;
	 socat_opts.lock.intervall.tv_sec  = 1;
	 socat_opts.lock.intervall.tv_nsec = 0;
	 break;
#if WITH_IP4 || WITH_IP6
#if WITH_IP4
      case '4':
#endif
#if WITH_IP6
      case '6':
#endif
	 xioopts.default_ip = arg1[0][1];
	 xioopts.preferred_ip = arg1[0][1];
	 break;
#endif /* WITH_IP4 || WITH_IP6 */
      case 'c':
	 switch (arg1[0][2]) {
	 case 'S': xioparams->pipetype = XIOCOMM_SOCKETPAIRS; break;
	 case 'P':
	 case 'p': xioparams->pipetype = XIOCOMM_PIPES;       break;
	 case 's': xioparams->pipetype = XIOCOMM_SOCKETPAIR;  break;
	 case 'Y': xioparams->pipetype = XIOCOMM_PTYS;        break;
	 case 'y': xioparams->pipetype = XIOCOMM_PTY;         break;
	 case 't': xioparams->pipetype = XIOCOMM_TCP;         break;
	 case '0': case '1': case '2': case '3': case '4':
	 case '5': case '6': case '7': case '8': case '9':
	    xioparams->pipetype = atoi(&arg1[0][2]); break;
	 default: Error1("bad chain communication type \"%s\"", &arg1[0][2]);
	 }
	 break;
      case '\0':
      case '-':	/*! this is hardcoded "--" */
      case ',':
      case ':': break;	/* this "-" is a variation of STDIO or -- */
      default:
	 xioinqopt('p', buff, sizeof(buff));
	 if (arg1[0][1] == buff[0]) {
	    break;
	 }
	 Error1("unknown option \"%s\"; use option \"-h\" for help", arg1[0]);
	 Exit(1);
      }
      /* the leading "-" might be a form of the first address */
      xioinqopt('p', buff, sizeof(buff));
      if (arg1[0][0] == '-' &&
	  (arg1[0][1] == '\0' || arg1[0][1] == ':' ||
	   arg1[0][1] == ',' || arg1[0][1] == '-'/*!*/ ||
	   arg1[0][1] == buff[0]))
	 break;
      ++arg1; --argc;
   }
#if 0
   Info1("%d address arguments", argc);
#else
   if (argc != 2) {
      Error1("exactly 2 addresses required (there are %d); use option \"-h\" for help", argc);
      Exit(1);
   }
#endif
   if (xioparams->lefttoright && xioparams->righttoleft) {
      Error("-U and -u must not be combined");
   }

   xioinitialize2();
   Info(copyright_socat);
#if WITH_OPENSSL
   Info(copyright_openssl);
   Info(copyright_ssleay);
#endif
   Debug2("socat version %s on %s", socatversion, timestamp);
   xiosetenv("VERSION", socatversion, 1);	/* SOCAT_VERSION */
   uname(&ubuf);	/* ! here we circumvent internal tracing (Uname) */
   Debug4("running on %s version %s, release %s, machine %s\n",
	   ubuf.sysname, ubuf.version, ubuf.release, ubuf.machine);

#if WITH_MSGLEVEL <= E_DEBUG
   for (i = 0; i < argc0; ++i) {
      Debug2("argv[%d]: \"%s\"", i, argv[i]);
   }
#endif /* WITH_MSGLEVEL <= E_DEBUG */

   /* not sure what signal should print a message */
   Signal(SIGHUP, socat_signal);
   Signal(SIGINT, socat_signal);
   Signal(SIGQUIT, socat_signal);
   Signal(SIGILL, socat_signal);
   /* SIGABRT for assert; catching caused endless recursion on assert in libc
      (tzfile.c:498: __tzfile_compute: Assertion 'num_types == 1' failed.) */
   /*Signal(SIGABRT, socat_signal);*/
   Signal(SIGBUS, socat_signal);
   Signal(SIGFPE, socat_signal);
   Signal(SIGSEGV, socat_signal);
   Signal(SIGTERM, socat_signal);
#if HAVE_SIGACTION
   {
      struct sigaction act;
      memset(&act, 0, sizeof(struct sigaction));
      act.sa_flags   = SA_NOCLDSTOP|SA_RESTART|SA_SIGINFO
#ifdef SA_NOMASK
	 |SA_NOMASK
#endif
	 ;
      act.sa_sigaction = xiosigaction_subaddr_ok;
      if (Sigaction(SIGUSR1, &act, NULL) < 0) {
	 /*! Linux man does not explicitely say that errno is defined */
	 Warn1("sigaction(SIGUSR1, {&xiosigaction_subaddr_ok}, NULL): %s", strerror(errno));
      }
   }
#else /* !HAVE_SIGACTION */
   if (Signal(SIGUSR1, xiosigaction_subaddr_ok) == SIG_ERR) {
      Warn1("signal(SIGCHLD, xiosigaction_subaddr_ok): %s", strerror(errno));
   }
#endif /* !HAVE_SIGACTION */

   /* set xio hooks */
   xiohook_newchild = &socat_newchild;

   if (lockrc = socat_lock()) {
      /* =0: goon; >0: locked; <0: error, printed in sub */
      if (lockrc > 0)
	 Error1("could not obtain lock \"%s\"", socat_opts.lock.lockfile);
      Exit(1);
   }

   Atexit(socat_unlock);

   result = socat(argc, arg1[0], arg1[1]);
   Notice1("exiting with status %d", result);
   Exit(result);
   return 0;	/* not reached, just for gcc -Wall */
}