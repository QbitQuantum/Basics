int					/* O - Exit code */
main(int  argc,				/* I - Number of command-line args */
     char *argv[])			/* I - Command-line arguments */
{
    int		i;			/* Looping var */
    int		request_id;		/* Request ID */
    int		timeout;		/* Timeout in seconds */
    const char	*server_bin;		/* CUPS_SERVERBIN environment variable */
    char		filename[1024];		/* Backend directory filename */
    cups_dir_t	*dir;			/* Directory pointer */
    cups_dentry_t *dent;			/* Directory entry */
    double	current_time,		/* Current time */
            end_time;		/* Ending time */
    int		num_options;		/* Number of options */
    cups_option_t	*options;		/* Options */
    cups_array_t	*requested,		/* requested-attributes values */
                    *exclude,		/* exclude-schemes values */
                    *include;		/* include-schemes values */
#if defined(HAVE_SIGACTION) && !defined(HAVE_SIGSET)
    struct sigaction action;		/* Actions for POSIX signals */
#endif /* HAVE_SIGACTION && !HAVE_SIGSET */


    setbuf(stderr, NULL);

    /*
     * Check the command-line...
     */

    if (argc != 6)
    {
        fputs("Usage: cups-deviced request-id limit timeout user-id options\n", stderr);

        return (1);
    }

    request_id = atoi(argv[1]);
    if (request_id < 1)
    {
        fprintf(stderr, "ERROR: [cups-deviced] Bad request ID %d!\n", request_id);

        return (1);
    }

    device_limit = atoi(argv[2]);
    if (device_limit < 0)
    {
        fprintf(stderr, "ERROR: [cups-deviced] Bad limit %d!\n", device_limit);

        return (1);
    }

    timeout = atoi(argv[3]);
    if (timeout < 1)
    {
        fprintf(stderr, "ERROR: [cups-deviced] Bad timeout %d!\n", timeout);

        return (1);
    }

    normal_user = (uid_t)atoi(argv[4]);
    if (normal_user <= 0)
    {
        fprintf(stderr, "ERROR: [cups-deviced] Bad user %d!\n", normal_user);

        return (1);
    }

    num_options = cupsParseOptions(argv[5], 0, &options);
    requested   = cupsdCreateStringsArray(cupsGetOption("requested-attributes",
                                          num_options, options));
    exclude     = cupsdCreateStringsArray(cupsGetOption("exclude-schemes",
                                          num_options, options));
    include     = cupsdCreateStringsArray(cupsGetOption("include-schemes",
                                          num_options, options));

    if (!requested || cupsArrayFind(requested, "all") != NULL)
    {
        send_class = send_info = send_make_and_model = send_uri = send_id =
                                     send_location = 1;
    }
    else
    {
        send_class          = cupsArrayFind(requested, "device-class") != NULL;
        send_info           = cupsArrayFind(requested, "device-info") != NULL;
        send_make_and_model = cupsArrayFind(requested, "device-make-and-model") != NULL;
        send_uri            = cupsArrayFind(requested, "device-uri") != NULL;
        send_id             = cupsArrayFind(requested, "device-id") != NULL;
        send_location       = cupsArrayFind(requested, "device-location") != NULL;
    }

    /*
     * Listen to child signals...
     */

#ifdef HAVE_SIGSET /* Use System V signals over POSIX to avoid bugs */
    sigset(SIGCHLD, sigchld_handler);
#elif defined(HAVE_SIGACTION)
    memset(&action, 0, sizeof(action));

    sigemptyset(&action.sa_mask);
    sigaddset(&action.sa_mask, SIGCHLD);
    action.sa_handler = sigchld_handler;
    sigaction(SIGCHLD, &action, NULL);
#else
    signal(SIGCLD, sigchld_handler);	/* No, SIGCLD isn't a typo... */
#endif /* HAVE_SIGSET */

    /*
     * Try opening the backend directory...
     */

    if ((server_bin = getenv("CUPS_SERVERBIN")) == NULL)
        server_bin = CUPS_SERVERBIN;

    snprintf(filename, sizeof(filename), "%s/backend", server_bin);

    if ((dir = cupsDirOpen(filename)) == NULL)
    {
        fprintf(stderr, "ERROR: [cups-deviced] Unable to open backend directory "
                "\"%s\": %s", filename, strerror(errno));

        return (1);
    }

    /*
     * Setup the devices array...
     */

    devices = cupsArrayNew((cups_array_func_t)compare_devices, NULL);

    /*
     * Loop through all of the device backends...
     */

    while ((dent = cupsDirRead(dir)) != NULL)
    {
        /*
         * Skip entries that are not executable files...
         */

        if (!S_ISREG(dent->fileinfo.st_mode) ||
                !isalnum(dent->filename[0] & 255) ||
                (dent->fileinfo.st_mode & (S_IRUSR | S_IXUSR)) != (S_IRUSR | S_IXUSR))
            continue;

        /*
         * Skip excluded or not included backends...
         */

        if (cupsArrayFind(exclude, dent->filename) ||
                (include && !cupsArrayFind(include, dent->filename)))
            continue;

        /*
         * Backends without permissions for normal users run as root,
         * all others run as the unprivileged user...
         */

        start_backend(dent->filename, !(dent->fileinfo.st_mode & (S_IWGRP | S_IRWXO)));
    }

    cupsDirClose(dir);

    /*
     * Collect devices...
     */

    if (getenv("SOFTWARE"))
        puts("Content-Type: application/ipp\n");

    cupsdSendIPPHeader(IPP_OK, request_id);
    cupsdSendIPPGroup(IPP_TAG_OPERATION);
    cupsdSendIPPString(IPP_TAG_CHARSET, "attributes-charset", "utf-8");
    cupsdSendIPPString(IPP_TAG_LANGUAGE, "attributes-natural-language", "en-US");

    end_time = get_current_time() + timeout;

    while (active_backends > 0 && (current_time = get_current_time()) < end_time)
    {
        /*
         * Collect the output from the backends...
         */

        timeout = (int)(1000 * (end_time - current_time));

        if (poll(backend_fds, (nfds_t)num_backends, timeout) > 0)
        {
            for (i = 0; i < num_backends; i ++)
                if (backend_fds[i].revents && backends[i].pipe)
                {
                    cups_file_t *bpipe = backends[i].pipe;
                    /* Copy of pipe for backend... */

                    do
                    {
                        if (get_device(backends + i))
                        {
                            backend_fds[i].fd     = 0;
                            backend_fds[i].events = 0;
                            break;
                        }
                    }
                    while (bpipe->ptr && memchr(bpipe->ptr, '\n', (size_t)(bpipe->end - bpipe->ptr)));
                }
        }

        /*
         * Get exit status from children...
         */

        if (dead_children)
            process_children();
    }

    cupsdSendIPPTrailer();

    /*
     * Terminate any remaining backends and exit...
     */

    if (active_backends > 0)
    {
        for (i = 0; i < num_backends; i ++)
            if (backends[i].pid)
                kill(backends[i].pid, SIGTERM);
    }

    return (0);
}