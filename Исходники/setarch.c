int main(int argc, char *argv[])
{
  const char *p;
  unsigned long options = 0;
  int verbose = 0;
  int c;

  /* Options --3gb and --4gb are for compatibitity with an old Debian setarch
     implementation. */
  static const struct option longopts[] =
  {
      { "help",               0, 0, 'h' },
      { "version",            0, 0, 'V' },
      { "verbose",            0, 0, 'v' },
      { "addr-no-randomize",  0, 0, 'R' },
      { "fdpic-funcptrs",     0, 0, 'F' },
      { "mmap-page-zero",     0, 0, 'Z' },
      { "addr-compat-layout", 0, 0, 'L' },
      { "read-implies-exec",  0, 0, 'X' },
      { "32bit",              0, 0, 'B' },
      { "short-inode",        0, 0, 'I' },
      { "whole-seconds",      0, 0, 'S' },
      { "sticky-timeouts",    0, 0, 'T' },
      { "3gb",                0, 0, '3' },
      { "4gb",                0, 0, OPT_4GB },
      { "uname-2.6",          0, 0, OPT_UNAME26 },
      { NULL,                 0, 0, 0 }
  };

  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, LOCALEDIR);
  textdomain(PACKAGE);
  atexit(close_stdout);

  if (argc < 1)
    show_usage(_("Not enough arguments"));

  p = program_invocation_short_name;
  if (!strcmp(p, "setarch")) {
    argc--;
    if (argc < 1)
      show_usage(_("Not enough arguments"));
    p = argv[1];
    argv[1] = argv[0];		/* for getopt_long() to get the program name */
    argv++;
    if (!strcmp(p, "-h") || !strcmp(p, "--help"))
      show_help();
    else if (!strcmp(p, "-V") || !strcmp(p, "--version"))
      show_version();
    else if (!strcmp(p, "--list")) {
      set_arch(argv[0], 0L, 1);
      return EXIT_SUCCESS;
    }
  }
  #if defined(__sparc64__) || defined(__sparc__)
   if (!strcmp(p, "sparc32bash")) {
       if (set_arch(p, 0L, 0))
           err(EXIT_FAILURE, _("Failed to set personality to %s"), p);
       execl("/bin/bash", NULL);
       err(EXIT_FAILURE, _("failed to execute %s"), "/bin/bash");
   }
  #endif

  while ((c = getopt_long(argc, argv, "+hVv3BFILRSTXZ", longopts, NULL)) != -1) {
    switch (c) {
    case 'h':
      show_help();
      break;
    case 'V':
      show_version();
      break;
    case 'v':
      verbose = 1;
      break;
    case 'R':
	turn_on(ADDR_NO_RANDOMIZE, options);
	break;
    case 'F':
	turn_on(FDPIC_FUNCPTRS, options);
	break;
    case 'Z':
	turn_on(MMAP_PAGE_ZERO, options);
	break;
    case 'L':
	turn_on(ADDR_COMPAT_LAYOUT, options);
	break;
    case 'X':
	turn_on(READ_IMPLIES_EXEC, options);
	break;
    case 'B':
	turn_on(ADDR_LIMIT_32BIT, options);
	break;
    case 'I':
	turn_on(SHORT_INODE, options);
	break;
    case 'S':
	turn_on(WHOLE_SECONDS, options);
	break;
    case 'T':
	turn_on(STICKY_TIMEOUTS, options);
	break;
    case '3':
	turn_on(ADDR_LIMIT_3GB, options);
	break;
    case OPT_4GB:          /* just ignore this one */
      break;
    case OPT_UNAME26:
	turn_on(UNAME26, options);
	break;
    default:
        show_usage(NULL);
    }
  }

  argc -= optind;
  argv += optind;

  if (set_arch(p, options, 0))
    err(EXIT_FAILURE, _("Failed to set personality to %s"), p);

  /* flush all output streams before exec */
  fflush(NULL);

  if (!argc) {
    execl("/bin/sh", "-sh", NULL);
    err(EXIT_FAILURE, _("failed to execute %s"), "/bin/sh");
  }

  execvp(argv[0], argv);
  err(EXIT_FAILURE, "%s", argv[0]);
  return EXIT_FAILURE;
}