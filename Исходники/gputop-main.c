int
main (int argc, char **argv)
{
    int opt;

#define LIB_GL_OPT	(CHAR_MAX + 1)
#define LIB_EGL_OPT	(CHAR_MAX + 2)
#define DEBUG_CTX_OPT	(CHAR_MAX + 3)
#define REMOTE_OPT	(CHAR_MAX + 4)

    /* The initial '+' means that getopt will stop looking for
     * options after the first non-option argument. */
    const char *short_options="+h";
    const struct option long_options[] = {
	{"help",	    no_argument,	0, 'h'},
#ifdef SUPPORT_GL
	{"libgl",	    optional_argument,	0, LIB_GL_OPT},
	{"libegl",	    optional_argument,	0, LIB_EGL_OPT},
	{"debug-context",   no_argument,	0, DEBUG_CTX_OPT},
#endif
#ifdef SUPPORT_WEBUI
	{"remote",	    no_argument,	0, REMOTE_OPT},
#endif
	{0, 0, 0, 0}
    };
    const char *prev_ld_library_path;
    char *ld_library_path;
    char *gputop_system_args[] = {
	"gputop-system",
	NULL
    };
    char **args = argv;
    int err;
    int i;


    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL))
	   != -1)
    {
	switch (opt) {
	    case 'h':
		usage();
		return 0;
	    case LIB_GL_OPT:
		setenv("GPUTOP_GL_LIBRARY", optarg, true);
		break;
	    case LIB_EGL_OPT:
		setenv("GPUTOP_EGL_LIBRARY", optarg, true);
		break;
	    case DEBUG_CTX_OPT:
		setenv("GPUTOP_FORCE_DEBUG_CONTEXT", "1", true);
		break;
	    case REMOTE_OPT:
		setenv("GPUTOP_MODE", "remote", true);
		break;
	    default:
		fprintf (stderr, "Internal error: "
			 "unexpected getopt value: %d\n", opt);
		exit (1);
	}
    }

    if (optind >= argc) {
	/* If no program is given then launch a dummy "test
	 * application" so gputop can also be used for analysing
	 * system wide metrics. */
	args = gputop_system_args;
	optind = 0;
    }

    if (!getenv("GPUTOP_GL_LIBRARY"))
        resolve_lib_path_for_env("libGL.so.1", "glClear", "GPUTOP_GL_LIBRARY");

    if (!getenv("GPUTOP_EGL_LIBRARY"))
        resolve_lib_path_for_env("libEGL.so.1", "eglGetDisplay", "GPUTOP_EGL_LIBRARY");

    prev_ld_library_path = getenv("LD_LIBRARY_PATH");
    if (!prev_ld_library_path)
	prev_ld_library_path = "";

    asprintf(&ld_library_path, "%s:%s", GPUTOP_WRAPPER_DIR, prev_ld_library_path);
    setenv("LD_LIBRARY_PATH", ld_library_path, true);
    free(ld_library_path);

    execvp(args[optind], &args[optind]);
    err = errno;

    fprintf(stderr, "gputop: Failed to run GL application: \n\n"
	    "  ");
    for (i = optind; i < argc; i++)
	fprintf(stderr, "%s ", args[i]);
    fprintf(stderr, "\n\n%s\n", strerror(err));

    return 0;
}