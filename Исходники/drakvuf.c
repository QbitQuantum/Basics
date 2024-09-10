int main(int argc, char** argv) {

    int c, i;
    char *inject_cmd = NULL;
    char *domain = NULL;
    char *rekall_profile = NULL;
    char *dump_folder = NULL;
    vmi_pid_t injection_pid = -1;
    struct sigaction act;
    int timeout = 0;
    GThread *timeout_thread = NULL;
    output_format_t output = OUTPUT_DEFAULT;

    fprintf(stderr, "%s v%s\n", PACKAGE_NAME, PACKAGE_VERSION);

    if ( __DRAKVUF_PLUGIN_LIST_MAX == 0 ) {
        fprintf(stderr, "No plugins have been enabled, nothing to do!\n");
        return 1;
    }

    if (argc < 4) {
        fprintf(stderr, "Required input:\n"
               "\t -r <rekall profile>       The Rekall profile of the Windows kernel\n"
               "\t -d <domain ID or name>    The domain's ID or name\n"
               "Optional inputs:\n"
               "\t -i <injection pid>        The PID of the process to hijack for injection\n"
               "\t -e <inject_exe>           The executable to start with injection\n"
               "\t -t <timeout>              Timeout (in seconds)\n"
               "\t -D <file dump folder>     Folder where extracted files should be stored at\n"
               "\t -o <format>               Output format (default or csv)\n"
               "\t -v                        Turn on verbose (debug) output\n"
        );
        return 1;
    }

    while ((c = getopt (argc, argv, "r:d:i:e:t:D:o:v")) != -1)
    switch (c)
    {
    case 'r':
        rekall_profile = optarg;
        break;
    case 'd':
        domain = optarg;
        break;
    case 'i':
        injection_pid = atoi(optarg);
        break;
    case 'e':
        inject_cmd = optarg;
        break;
    case 't':
        timeout = atoi(optarg);
        break;
    case 'D':
        dump_folder = optarg;
        break;
    case 'o':
        if(!strncmp(optarg,"csv",3))
            output = OUTPUT_CSV;
        break;
    case 'v':
//        verbose = 1;
        break;
    default:
        fprintf(stderr, "Unrecognized option: %c\n", c);
        return 1;
    }

    interrupted = 0;

    if (!drakvuf_init(&drakvuf, domain, rekall_profile))
        return 1;

    if(output != OUTPUT_DEFAULT)
        drakvuf_set_output_format(drakvuf, output);

    if(timeout > 0) {
        timeout_thread = g_thread_new(NULL, timer, &timeout);
    }

    drakvuf_pause(drakvuf);

    if (injection_pid > 0 && inject_cmd) {
        int rc = drakvuf_inject_cmd(drakvuf, injection_pid, inject_cmd);

        if (!rc) {
            fprintf(stderr, "Process startup failed\n");
            goto exit;
        }
    }

    /*
     * Pass the configuration input to the plugins.
     * Default config is only the rekall profile but plugins
     * can define additional options which need to be passed
     * through their own config structure.
     */
    for(i=0;i<__DRAKVUF_PLUGIN_LIST_MAX;i++) {
        switch (i) {
        case PLUGIN_FILEDELETE:
        {
            struct filedelete_config c = {
                .rekall_profile = rekall_profile,
                .dump_folder = dump_folder
            };

            if ( !drakvuf_plugin_init(drakvuf, i, &c) )
                goto exit;
            break;
        }
        default:
            if ( !drakvuf_plugin_init(drakvuf, i, rekall_profile) )
                goto exit;
            break;
        };
    }

    /* for a clean exit */
    act.sa_handler = close_handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGHUP, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGALRM, &act, NULL);

    if ( drakvuf_plugins_start(drakvuf) )
        drakvuf_loop(drakvuf);

exit:
    drakvuf_pause(drakvuf);
    drakvuf_plugins_close(drakvuf);
    drakvuf_close(drakvuf);

    if(timeout_thread)
        g_thread_join(timeout_thread);

    return 0;
}