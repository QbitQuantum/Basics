int main(int argc, char **argv)
{
  struct hostent *  host                = NULL;
  int               net_preopen_result;
#ifdef ENABLE_IPV6
  struct addrinfo       hints, *res;
  int                   error;
  struct hostent        trhost;
  char *                alptr[2];
  struct sockaddr_in *  sa4;
  struct sockaddr_in6 * sa6;
#endif

  /*  Get the raw sockets first thing, so we can drop to user euid immediately  */

  if ( ( net_preopen_result = net_preopen () ) ) {
    fprintf( stderr, "mtr: unable to get raw sockets.\n" );
    exit( EXIT_FAILURE );
  }

  /*  Now drop to user permissions  */
  if (setgid(getgid()) || setuid(getuid())) {
    fprintf (stderr, "mtr: Unable to drop permissions.\n");
    exit(1);
  }

  /*  Double check, just in case  */
  if ((geteuid() != getuid()) || (getegid() != getgid())) {
    fprintf (stderr, "mtr: Unable to drop permissions.\n");
    exit(1);
  }

  /* reset the random seed */
  srand (getpid());

  display_detect(&argc, &argv);
  display_mode = 0;

  /* The field options are now in a static array all together,
     but that requires a run-time initialization. */
  init_fld_options ();

  parse_mtr_options (getenv ("MTR_OPTIONS"));

  parse_arg (argc, argv);

  while (optind < argc) {
    char* name = argv[optind++];
    append_to_names(argv[0], name);
  }

  /* Now that we know mtrtype we can select which socket to use */
  if (net_selectsocket() != 0) {
    fprintf( stderr, "mtr: Couldn't determine raw socket type.\n" );
    exit( EXIT_FAILURE );
  }

  if (PrintVersion) {
    printf ("mtr " MTR_VERSION "\n");
    exit(0);
  }

  if (PrintHelp) {
       printf("usage: %s [--help] [--version] [-4|-6] [-F FILENAME]\n"
              "\t\t[--report] [--report-wide] [--displaymode MODE]\n"
              "\t\t[--xml] [--gtk] [--curses] [--raw] [--csv] [--split]\n"
              "\t\t[--no-dns] [--show-ips] [-o FIELDS] [-y IPINFO] [--aslookup]\n"
              "\t\t[-i INTERVAL] [-c COUNT] [-s PACKETSIZE] [-B BITPATTERN]\n"
              "\t\t[-Q TOS] [--mpls]\n"
              "\t\t[-a ADDRESS] [-f FIRST-TTL] [-m MAX-TTL] [-U MAX_UNKNOWN]\n"
              "\t\t[--udp] [--tcp] [--sctp] [-P PORT] [-L LOCALPORT] [-Z TIMEOUT]\n"
              "\t\t[-G GRACEPERIOD] [-M MARK] HOSTNAME\n", argv[0]);
       printf("See the man page for details.\n");
    exit(0);
  }

  time_t now = time(NULL);

  if (!names) append_to_names (argv[0], "localhost"); // default: localhost. 

  names_t* head = names;
  while (names != NULL) {

    Hostname = names->name;
    //  if (Hostname == NULL) Hostname = "localhost"; // no longer necessary.
    if (gethostname(LocalHostname, sizeof(LocalHostname))) {
      strcpy(LocalHostname, "UNKNOWNHOST");
    }

    if (net_preopen_result != 0) {
      fprintf(stderr, "mtr: Unable to get raw socket.  (Executable not suid?)\n");
      if ( DisplayMode != DisplayCSV ) exit(EXIT_FAILURE);
      else {
        names = names->next;
        continue;
      }
    }

#ifdef ENABLE_IPV6
    /* gethostbyname2() is deprecated so we'll use getaddrinfo() instead. */
    bzero( &hints, sizeof hints );
    hints.ai_family = af;
    hints.ai_socktype = SOCK_DGRAM;
    error = getaddrinfo( Hostname, NULL, &hints, &res );
    if ( error ) {
      if (error == EAI_SYSTEM)
         perror ("Failed to resolve host");
      else
         fprintf (stderr, "Failed to resolve host: %s\n", gai_strerror(error));

      if ( DisplayMode != DisplayCSV ) exit(EXIT_FAILURE);
      else {
        names = names->next;
        continue;
      }
    }
    /* Convert the first addrinfo into a hostent. */
    host = &trhost;
    bzero( host, sizeof trhost );
    host->h_name = res->ai_canonname;
    host->h_aliases = NULL;
    host->h_addrtype = res->ai_family;
    af = res->ai_family;
    host->h_length = res->ai_addrlen;
    host->h_addr_list = alptr;
    switch ( af ) {
    case AF_INET:
      sa4 = (struct sockaddr_in *) res->ai_addr;
      alptr[0] = (void *) &(sa4->sin_addr);
      break;
    case AF_INET6:
      sa6 = (struct sockaddr_in6 *) res->ai_addr;
      alptr[0] = (void *) &(sa6->sin6_addr);
      break;
    default:
      fprintf( stderr, "mtr unknown address type\n" );
      if ( DisplayMode != DisplayCSV ) exit(EXIT_FAILURE);
      else {
        names = names->next;
        continue;
      }
    }
    alptr[1] = NULL;
#else
      host = gethostbyname(Hostname);
    if (host == NULL) {
      herror("mtr gethostbyname");
      if ( DisplayMode != DisplayCSV ) exit(EXIT_FAILURE);
      else {
        names = names->next;
        continue;
      }
    }
    af = host->h_addrtype;
#endif

    if (net_open(host) != 0) {
      fprintf(stderr, "mtr: Unable to start net module.\n");
      if ( DisplayMode != DisplayCSV ) exit(EXIT_FAILURE);
      else {
        names = names->next;
        continue;
      }
    }

    if (net_set_interfaceaddress (InterfaceAddress) != 0) {
      fprintf( stderr, "mtr: Couldn't set interface address.\n" );
      if ( DisplayMode != DisplayCSV ) exit(EXIT_FAILURE);
      else {
        names = names->next;
        continue;
      }
    }


    lock(argv[0], stdout);
      display_open();
      dns_open();

      display_loop();

      net_end_transit();
      display_close(now);
    unlock(argv[0], stdout);

    if ( DisplayMode != DisplayCSV ) break;
    else names = names->next;

  }

  net_close();

  while (head != NULL) {
    names_t* item = head;
    free(item->name); item->name = NULL;
    head = head->next;
    free(item); item = NULL;
  }
  head=NULL;

  return 0;
}