int 
eval_options (int argc, char **argv, struct target_opts* defaults, 
              const char** exe_opts)
{
    const char opt_timeout[]  = "-t";
    const char opt_data_dir[] = "-d";
    const char opt_t_flags[]  = "-x";
    const char opt_compat[]   = "--compat";
    const char opt_exit[]     = "--exit";
    const char opt_help[]     = "--help";
    const char opt_ignore[]   = "--ignore";
    const char opt_nocompat[] = "--nocompat";
    const char opt_signal[]   = "--signal";
    const char opt_sleep[]    = "--sleep";
    const char opt_ulimit[]   = "--ulimit";
    const char opt_verbose[]  = "--verbose";
    const char opt_warn[]     = "--warn";

    int i;

    assert (0 != argv);
    assert (0 != defaults);

    memset (defaults, 0, sizeof (target_opts));

    /* The chain of preprocesor logic below initializes the defaults->c_warn 
       and defaults->l_warn values.
    */
#ifdef __GNUG__
    parse_warn_opts ("Gcc", defaults);
#elif defined (__HP_aCC)
    parse_warn_opts ("Acc", defaults);
#elif defined (__IBMCPP__)
    parse_warn_opts ("Xlc", defaults);
#elif defined (__SUNPRO_CC)
    parse_warn_opts ("Sunpro", defaults);
#elif defined (SNI)
    parse_warn_opts ("Cds", defaults);
#elif defined (__APOGEE__) /* EDG variant that doesn't define __EDG__. */
    parse_warn_opts ("Como", defaults);

/* The following are EDG variants, that define __EDG__ */
#elif defined (__DECCXX)
    parse_warn_opts ("Cxx", defaults);
#elif defined (_SGI_COMPILER_VERSION)
    parse_warn_opts ("Mipspro", defaults);
#elif defined (__INTEL_COMPILER)
    parse_warn_opts ("Icc", defaults);

/* So we need to check for __EDG__ after we check for them. */
#elif defined (__EDG__)
    parse_warn_opts ("Eccp", defaults);
#endif

    if (1 == argc || '-' != argv [1][0])
        return 1;

    for (i = 1; i < argc && '-' == argv [i][0]; ++i) {

        /* the name of the option being processed */
        const char* optname = argv [i];

        /* the option's argument, if any */
        const char* optarg  = 0;

        char* end = 0;

        switch (argv [i][1]) {
        case '?':   /* display help and exit with status of 0 */
        case 'h':
            show_usage (0);

        case 'r':
            ++i; /* Ignore -r option (makefile compat) */
            break;

        case 't':   /* executable timeout in seconds */
            optname = opt_timeout;
            optarg  = get_short_val (argv, &i);
            if (optarg) {
                if (!isdigit (*optarg))
                    bad_value (optname, optarg);

                errno = 0;
                defaults->timeout = unsigned (strtol (optarg, &end, 10));
                if (*end || errno)
                    bad_value (optname, optarg);
            }
            else
                missing_value (optname);

            break;

        case 'd':   /* directory containing example reference files */
            optname = opt_data_dir;
            defaults->data_dir = get_short_val (argv, &i);
            if (!defaults->data_dir)
                missing_value (optname);
            break;

        case 'v':   /* enable verbose mode */
            optname = opt_verbose;
            ++defaults->verbose;
            break;

        case 'x':   /* command line options to pass to targets */
            optname  = opt_t_flags;
            *exe_opts = get_short_val (argv, &i);
            if (!*exe_opts)
                missing_value (optname);
            break;

        case '-':   /* long options */
        {
            const size_t arglen = strlen (argv [i]);

            /* abort processing on --, eat token */
            if ('\0' == argv [i][2])
                return i+1;

            if (   sizeof opt_compat - 1 == arglen
                && !memcmp (opt_compat, argv [i], sizeof opt_compat)) {
                /* enter compatibility mode */
                defaults->compat = 1;
                break;
            }
            else if (   sizeof opt_nocompat - 1 == arglen
                     && !memcmp (opt_nocompat, argv [i], sizeof opt_nocompat)) {
                /* exit compatibility mode */
                defaults->compat = 0;
                break;
            }
            else if (   sizeof opt_exit - 1 <= arglen
                     && !memcmp (opt_exit, argv [i], sizeof opt_exit - 1)) {
                /* exit immediately with the specified status */
                optname = opt_exit;
                optarg  = get_long_val (argv, &i, sizeof opt_exit - 1);
                if (optarg && *optarg) {
                    if (!isdigit (*optarg))
                        bad_value (optname, optarg);

                    errno = 0;
                    const long code = strtol (optarg, &end, 10);
                    if ('\0' == *end && !errno)
                        exit (int (code));
                }
            }
            else if (   sizeof opt_help - 1 == arglen
                     && !memcmp (opt_help, argv [i], sizeof opt_help - 1)) {
                /* display help and exit with status of 0 */
                optname = opt_help;
                show_usage (0);
                break;
            }
            else if (   sizeof opt_sleep - 1 <= arglen
                     && !memcmp (opt_sleep, argv [i], sizeof opt_sleep - 1)) {
                /* sleep for the specified number of seconds */ 
                optname = opt_sleep;
                optarg  = get_long_val (argv, &i, sizeof opt_sleep - 1);
                if (optarg && *optarg) {
                    if (!isdigit (*optarg))
                        bad_value (optname, optarg);

                    errno = 0;
                    const long nsec = strtol (optarg, &end, 10);
                    if ('\0' == *end && 0 <= nsec && !errno) {
                        rw_sleep (int (nsec));
                        break;
                    }
                }
            }
            else if (   sizeof opt_signal - 1 <= arglen
                     && !memcmp (opt_signal, argv [i], sizeof opt_signal - 1)) {
                /* send ourselves the specified signal */
                optname = opt_signal;
                optarg  = get_long_val (argv, &i, sizeof opt_signal - 1);
                if (optarg && *optarg) {
                    const int signo = get_signo (optarg);
                    if (0 <= signo) {
                        if (0 > raise (signo))
                            terminate (1, "raise(%s) failed: %s\n",
                                       get_signame (signo), strerror (errno));
                        break;
                    }
                }
            }
            else if (   sizeof opt_ignore - 1 <= arglen
                     && !memcmp (opt_ignore, argv [i], sizeof opt_ignore - 1)) {
                /* ignore the specified signal */
                optname = opt_ignore;
                optarg  = get_long_val (argv, &i, sizeof opt_ignore - 1);
                if (optarg && *optarg) {
                    const int signo = get_signo (optarg);
                    if (0 <= signo) {
                        if (rw_signal (signo, 0 /* SIG_IGN */))
                            terminate (1, "rw_signal(%s, ...) failed: %s\n",
                                       get_signame (signo), strerror (errno));
                        break;
                    }
                }
            }
            else if (   sizeof opt_ulimit - 1 <= arglen
                     && !memcmp (opt_ulimit, argv [i], sizeof opt_ulimit - 1)) {
                /* set child process resource utilization limits */
                optname = opt_ulimit;
                optarg  = get_long_val (argv, &i, sizeof opt_ulimit - 1);
                if (optarg && *optarg) {
                    if (!parse_limit_opts (optarg, defaults)) {
                        break;
                    }
                }
            }
            else if (   sizeof opt_warn - 1 <= arglen
                     && !memcmp (opt_warn, argv [i], sizeof opt_warn - 1)) {
                /* set compiler warning mode */
                optname = opt_warn;
                optarg  = get_long_val (argv, &i, sizeof opt_warn - 1);
                if (optarg && *optarg) {
                    if (!parse_warn_opts (optarg, defaults)) {
                        break;
                    }
                }
            }
            /* fall through */
        }
        default:
            if (optarg) {
                if (*optarg)
                    bad_value (optname, optarg);
                else
                    missing_value (optname);
            }

            if (argv [i])
                bad_option (argv [i]);
            else
                missing_value (optname);
        }
    }

    return i;
}