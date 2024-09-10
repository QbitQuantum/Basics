int
main(int argc, char **argv)
{
  int verbose;
  int ca_racket;
  int showtime;
  int setclock;
  const char *host;
  const char *port;
  const char *protocol;
  const char *ca_cert_container;
  int timewarp;
  int leap;
  const char *proxy;

  host = DEFAULT_HOST;
  port = DEFAULT_PORT;
  protocol = DEFAULT_PROTOCOL;
  ca_cert_container = DEFAULT_CERTFILE;
  verbose = 0;
  ca_racket = 1;
  showtime = 0;
  setclock = 1;
  timewarp = 0;
  leap = 0;
  proxy = NULL;

  while (1) {
    int option_index = 0;
    int c;

    static struct option long_options[] =
      {
        {"verbose", 0, 0, 'v'},
        {"showtime", 2, 0, 'V'},
        {"skip-verification", 0, 0, 's'},
        {"help", 0, 0, 'h'},
        {"host", 0, 0, 'H'},
        {"port", 0, 0, 'p'},
        {"protocol", 0, 0, 'P'},
        {"dont-set-clock", 0, 0, 'n'},
        {"certcontainer", 0, 0, 'C'},
        {"timewarp", 0, 0, 't'},
        {"leap", 0, 0, 'l'},
        {"proxy", 0, 0, 'x'},
        {0, 0, 0, 0}
      };

    c = getopt_long(argc, argv, "vV::shH:p:P:nC:tlx:",
                    long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
      case 'v': verbose = 1; break;
      case 'V': showtime = (optarg && 0 == strcmp("raw", optarg) ? 2:1); break;
      case 's': ca_racket = 0; break;
      case 'h': usage(); exit(1); break;
      case 'H': host = optarg; break;
      case 'p': port = optarg; break;
      case 'P': protocol = optarg; break;
      case 'n': setclock = 0; break;
      case 'C': ca_cert_container = optarg; break;
      case 't': timewarp = 1; break;
      case 'l': leap = 1; break;
      case 'x': proxy = optarg; break;
      case '?': break;
      default : fprintf(stderr, "Unknown option!\n"); usage(); exit(1);
    }
  }

  if (verbose) {
    fprintf(stderr,
      "V: tlsdate version %s\n"
            "V: We were called with the following arguments:\n"
            "V: %s host = %s:%s\n",
            PACKAGE_VERSION,
      ca_racket ? "validate SSL certificates" : "disable SSL certificate check",
            host, port);
    if (0 == ca_racket)
      fprintf(stderr, "WARNING: Skipping certificate verification!\n");
  }

  execlp (TLSDATE_HELPER,
    "tlsdate",
    host,
    port,
    protocol,
    (ca_racket ? "racket" : "unchecked"),
    (verbose ? "verbose" : "quiet"),
    ca_cert_container,
    (setclock ? "setclock" : "dont-set-clock"),
    (showtime ? (showtime == 2 ? "showtime=raw" : "showtime") : "no-showtime"),
    (timewarp ? "timewarp" : "no-fun"),
    (leap ? "leapaway" : "holdfast"),
    (proxy ? proxy : "none"),
    NULL);
  perror("Failed to run tlsdate-helper");
  return 1;
}