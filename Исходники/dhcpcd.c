int main(int argc, char **argv)
{
  options_t options;
  int doversion = 0;
  int dohelp = 0;
  int userclasses = 0;
  int ch;
  int option_index = 0;
  char prefix[IF_NAMESIZE + 3];
  pid_t pid;

  const struct option longopts[] =
    {
	{"arp", no_argument, NULL, 'a'},
	{"script",required_argument, NULL, 'c'},
	{"debug", no_argument, NULL, 'd'},
	{"hostname", required_argument, NULL, 'h'},
	{"classid", required_argument, NULL, 'i'},
	{"release", no_argument, NULL, 'k'},
	{"leasetime", required_argument, NULL, 'l'},
	{"metric", required_argument, NULL, 'm'},
	{"renew", no_argument, NULL, 'n'},
	{"persistent", no_argument, NULL, 'p'},
	{"request", required_argument, NULL, 's'},
	{"timeout", required_argument, NULL, 't'},
	{"userclass", required_argument, NULL, 'u'},
	{"fqdn", optional_argument, NULL, 'F'},
	{"nogateway", no_argument, NULL, 'G'},
	{"sethostname", no_argument, NULL, 'H'},
	{"clientid", required_argument, NULL, 'I'},
	{"nontp", no_argument, NULL, 'N'},
	{"nodns", no_argument, NULL, 'R'},
	{"nonis", no_argument, NULL, 'Y'},
	{"help", no_argument, &dohelp, 1},
	{"version", no_argument, &doversion, 1},
	{NULL, 0, NULL, 0}
    };

  /* Sanitize our fd's */
  int zero;
  if ((zero = open (_PATH_DEVNULL, O_RDWR, 0)) >= 0)
    {
      while (zero < 3)
	zero = dup (zero);
      close(zero);
    }

  openlog (PACKAGE, LOG_PID, LOG_LOCAL0);

  memset (&options, 0, sizeof (options_t));
  options.script = (char *) DEFAULT_SCRIPT;
  snprintf (options.classid, CLASS_ID_MAX_LEN, "%s %s", PACKAGE, VERSION); 

  options.doarp = false;
  options.dodns = true;
  options.donis = true;
  options.dontp = true;
  options.dogateway = true;
  gethostname (options.hostname, sizeof (options.hostname));
  if (strcmp (options.hostname, "(none)") == 0 ||
      strcmp (options.hostname, "localhost") == 0)
    memset (options.hostname, 0, sizeof (options.hostname));
  options.timeout = DEFAULT_TIMEOUT;

  while ((ch = getopt_long(argc, argv, "ac:dh:i:kl:m:nps:t:u:F:GHI:NRY", longopts,
			   &option_index)) != -1)
    switch (ch)
      {
      case 0:
	if (longopts[option_index].flag)
	  break;
	logger (LOG_ERR, "option `%s' should set a flag",
		longopts[option_index].name);
	exit (EXIT_FAILURE);
	break;

      case 'a':
	options.doarp = true;
	break;
      case 'c':
	options.script = optarg;
	break;
      case 'd':
	setloglevel(LOG_DEBUG);
	break;
      case 'h':
	if (strlen (optarg) > HOSTNAME_MAX_LEN)
	  {
	    logger(LOG_ERR, "`%s' too long for HostName string, max is %d",
		   optarg, HOSTNAME_MAX_LEN);
	    exit (EXIT_FAILURE);
	  }
	else
	  strcpy (options.hostname, optarg);
	break;
      case 'i':
	if (strlen(optarg) > CLASS_ID_MAX_LEN)
	  {
	    logger (LOG_ERR, "`%s' too long for ClassID string, max is %d",
		    optarg, CLASS_ID_MAX_LEN);
	    exit (EXIT_FAILURE);
	  }
	else
	  sprintf(options.classid, "%s", optarg);
	break;
      case 'k':
	options.signal = SIGHUP;
	break;
      case 'l':
	STRINGINT (optarg, options.leasetime);
	if (options.leasetime <= 0)
	  {
	    logger (LOG_ERR, "leasetime must be a positive value");
	    exit (EXIT_FAILURE);
	  }
	break;
      case 'm':
	STRINGINT(optarg, options.metric);
	break;
      case 'n':
	options.signal = SIGALRM;
	break;
      case 'p':
	options.persistent = true;
	break;
      case 's':
	if (! inet_aton (optarg, &options.requestaddress))
	  {
	    logger (LOG_ERR, "`%s' is not a valid IP address", optarg);
	    exit (EXIT_FAILURE);
	  }
	break;
      case 't':
	STRINGINT (optarg, options.timeout);
	if (options.timeout < 0)
	  {
	    logger (LOG_ERR, "timeout must be a positive value");
	    exit (EXIT_FAILURE);
	  }
	break;
      case 'u':
	  {
	    int i;
	    int offset = 0;
	    for (i = 0; i < userclasses; i++)
	      offset += (int) options.userclass[offset] + 1;
	    if (offset + 1 + strlen (optarg) > USERCLASS_MAX_LEN)
	      {
		logger (LOG_ERR, "userclass overrun, max is %d",
			USERCLASS_MAX_LEN);
		exit (EXIT_FAILURE);
	      }
	    userclasses++;
	    memcpy (options.userclass + offset + 1 , optarg, strlen (optarg));
	    options.userclass[offset] = strlen (optarg);
	    options.userclass_len += (strlen (optarg)) + 1;
	  }
	break;
      case 'F':
	if (strcmp (optarg, "none") == 0)
	  options.fqdn = FQDN_NONE;
	else if (strcmp (optarg, "ptr") == 0)
	  options.fqdn = FQDN_PTR;
	else if (strcmp (optarg, "both") == 0)
	  options.fqdn = FQDN_BOTH;
	else
	  {
	    logger (LOG_ERR, "invalid value `%s' for FQDN", optarg);
	    exit (EXIT_FAILURE);
	  }
	break;
      case 'G':
	options.dogateway = false;
	break;
      case 'H':
	options.dohostname = true;
	break;
      case 'I':
	if (strlen (optarg) > CLIENT_ID_MAX_LEN)
	  {
	    logger (LOG_ERR, "`%s' is too long for ClientID, max is %d",
		    optarg, CLIENT_ID_MAX_LEN);
	    exit (EXIT_FAILURE);
	  }
	else
	  sprintf(options.clientid, "%s", optarg);
	break;
      case 'N':
	options.dontp = false;
	break;
      case 'R':
	options.dodns = false;
	break;
      case 'Y':
	options.donis = false;
	break;
      case '?':
	usage ();
	exit (EXIT_FAILURE);
      default:
	usage ();
	exit (EXIT_FAILURE);
      }

  if (doversion)
    printf (""PACKAGE" "VERSION"\n");

  if (dohelp)
    usage ();

  if (optind < argc)
    {
      if (strlen (argv[optind]) > IF_NAMESIZE)
	{
	  logger (LOG_ERR, "`%s' is too long for an interface name (max=%d)",
		  argv[optind], IF_NAMESIZE);
	  exit (EXIT_FAILURE);
	}
      strcpy (options.interface, argv[optind]);
    }
  else
    {
      /* If only version was requested then exit now */
      if (doversion || dohelp)
	exit (EXIT_SUCCESS);

      logger (LOG_ERR, "no interface specified", options.interface);
      exit (EXIT_FAILURE);
    }

  if (geteuid ())
    {
      logger (LOG_ERR, "you need to be root to run "PACKAGE);
      exit (EXIT_FAILURE);
    }

  snprintf (prefix, IF_NAMESIZE, "%s: ", options.interface);
  setlogprefix (prefix);
  snprintf (options.pidfile, sizeof (options.pidfile), PIDFILE,
	    options.interface);

  if (options.signal != 0)
    {
      int killed = -1;
      pid = read_pid (options.pidfile);
      if (pid != 0)
        logger (LOG_INFO, "sending signal %d to pid %d", options.signal, pid);

      if (! pid || (killed = kill (pid, options.signal)))
	logger (options.signal == SIGALRM ? LOG_INFO : LOG_ERR, ""PACKAGE" not running");

      if (pid != 0 && (options.signal != SIGALRM || killed != 0))
	unlink (options.pidfile);

      if (killed == 0)
	exit (EXIT_SUCCESS);

      if (options.signal != SIGALRM)
	exit (EXIT_FAILURE);
    }

  umask (022);

  if (mkdir (CONFIGDIR, S_IRUSR |S_IWUSR |S_IXUSR | S_IRGRP | S_IXGRP
	     | S_IROTH | S_IXOTH) && errno != EEXIST )
    {
      logger (LOG_ERR, "mkdir(\"%s\",0): %s\n", CONFIGDIR, strerror (errno));
      exit (EXIT_FAILURE);
    }

  if (mkdir (ETCDIR, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP
	     | S_IROTH | S_IXOTH) && errno != EEXIST )
    {
      logger (LOG_ERR, "mkdir(\"%s\",0): %s\n", ETCDIR, strerror (errno));
      exit (EXIT_FAILURE);
    }

  if ((pid = read_pid (options.pidfile)) > 0 && kill (pid, 0) == 0)
    {
      logger (LOG_ERR, ""PACKAGE" already running (%s)", options.pidfile);
      exit (EXIT_FAILURE);
    }

  make_pid (options.pidfile);

  logger (LOG_INFO, PACKAGE " " VERSION " starting");
  if (dhcp_run (&options))
    {
      unlink (options.pidfile);
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
}