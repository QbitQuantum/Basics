/*
 * chat [-esSvV] [-f chat-file] [-r report-file] [-t timeout]
 *      [-T phone-number] [-U phone-number2] [chat-script]
 * where chat-script has the form:
 *	[...[[expect[-send[-expect...]] send expect[-send[-expect]] ...]]]
 *
 * Perform a UUCP-dialer-like chat script on stdin and stdout.
 */
int
main(int argc, char *argv[])
{
    int option;

    tzset();

    while ((option = getopt(argc, argv, "ef:r:sSt:T:U:vV")) != -1) {
	switch (option) {
	case 'e':
	    ++echo;
	    break;

	case 'f':
	    if (chat_file != NULL)
		free(chat_file);
	    chat_file = copy_of(optarg);
	    break;

	case 'r':
	    if (report_fp != NULL)
		fclose(report_fp);
	    if (report_file != NULL)
		free(report_file);
	    report_file = copy_of(optarg);
	    report_fp = fopen(report_file, "a");
	    if (report_fp != NULL) {
		if (verbose)
		    fprintf(report_fp, "Opening \"%s\"...\n", report_file);
	    } else
		fatal(2, "cannot open \"%s\" for appending", report_file);
	    break;

	case 's':
	    ++to_stderr;
	    break;

	case 'S':
	    to_log = 0;
	    break;

	case 't':
	    timeout = atoi(optarg);
	    break;

	case 'T':
	    if (phone_num != NULL)
		free(phone_num);
	    phone_num = copy_of(optarg);
	    break;

	case 'U':
	    if (phone_num2 != NULL)
		free(phone_num2);
	    phone_num2 = copy_of(optarg);
	    break;

	case 'v':
	    ++verbose;
	    break;

	case 'V':
	    ++Verbose;
	    break;

	default:
	    usage();
	    break;
	}
    }

    argc -= optind;
    argv += optind;

/*
 * Default the report file to the stderr location
 */
    if (report_fp == NULL)
	report_fp = stderr;

    if (to_log) {
	openlog("chat", LOG_PID | LOG_NDELAY, LOG_LOCAL2);

	if (verbose)
	    setlogmask(LOG_UPTO(LOG_INFO));
	else
	    setlogmask(LOG_UPTO(LOG_WARNING));
    }

    if (chat_file != NULL) {
	if (*argv != NULL)
	    usage();
	else {
            init();
	    do_file(chat_file);
	}
    } else {
	init();
	while (*argv != NULL && argc > 0) {
	    chat_expect(*argv);
	    argv++;
	    argc--;

	    if (*argv != NULL && argc > 0) {
		chat_send(*argv);
		argv++;
		argc--;
	    }
	}
    }

    terminate(0);
    return 0;
}