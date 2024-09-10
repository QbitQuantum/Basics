int main(int argc, char **argv)
{
    int err;
    int hasSetLogFormat = 0;
    int clearLog = 0;
    int getLogSize = 0;
    int mode = O_RDONLY;
    const char *forceFilters = NULL;
    log_device_t* devices = NULL;
    log_device_t* dev;
    bool needBinary = false;

    g_logformat = android_log_format_new();

    if (argc == 2 && 0 == strcmp(argv[1], "--test")) {
        logprint_run_tests();
        exit(0);
    }

    if (argc == 2 && 0 == strcmp(argv[1], "--help")) {
        android::show_help(argv[0]);
        exit(0);
    }

    for (;;) {
        int ret;

        ret = getopt(argc, argv, "cdt:gsQf:r::n:v:b:B");

        if (ret < 0) {
            break;
        }

        switch(ret) {
            case 's': 
                // default to all silent
                android_log_addFilterRule(g_logformat, "*:s");
            break;

            case 'c':
                clearLog = 1;
                mode = O_WRONLY;
            break;

            case 'd':
                g_nonblock = true;
            break;

            case 't':
                g_nonblock = true;
                g_tail_lines = atoi(optarg);
            break;

            case 'g':
                getLogSize = 1;
            break;

            case 'b': {
                char* buf = (char*) malloc(strlen(LOG_FILE_DIR) + strlen(optarg) + 1);
                strcpy(buf, LOG_FILE_DIR);
                strcat(buf, optarg);

                bool binary = strcmp(optarg, "events") == 0;
                if (binary) {
                    needBinary = true;
                }

                if (devices) {
                    dev = devices;
                    while (dev->next) {
                        dev = dev->next;
                    }
                    dev->next = new log_device_t(buf, binary, optarg[0]);
                } else {
                    devices = new log_device_t(buf, binary, optarg[0]);
                }
                android::g_devCount++;
            }
            break;

            case 'B':
                android::g_printBinary = 1;
            break;

            case 'f':
                // redirect output to a file

                android::g_outputFileName = optarg;

            break;

            case 'r':
                if (optarg == NULL) {                
                    android::g_logRotateSizeKBytes 
                                = DEFAULT_LOG_ROTATE_SIZE_KBYTES;
                } else {
                    long logRotateSize;
                    char *lastDigit;

                    if (!isdigit(optarg[0])) {
                        fprintf(stderr,"Invalid parameter to -r\n");
                        android::show_help(argv[0]);
                        exit(-1);
                    }
                    android::g_logRotateSizeKBytes = atoi(optarg);
                }
            break;

            case 'n':
                if (!isdigit(optarg[0])) {
                    fprintf(stderr,"Invalid parameter to -r\n");
                    android::show_help(argv[0]);
                    exit(-1);
                }

                android::g_maxRotatedLogs = atoi(optarg);
            break;

            case 'v':
                err = setLogFormat (optarg);
                if (err < 0) {
                    fprintf(stderr,"Invalid parameter to -v\n");
                    android::show_help(argv[0]);
                    exit(-1);
                }

                hasSetLogFormat = 1;
            break;

            case 'Q':
                /* this is a *hidden* option used to start a version of logcat                 */
                /* in an emulated device only. it basically looks for androidboot.logcat=      */
                /* on the kernel command line. If something is found, it extracts a log filter */
                /* and uses it to run the program. If nothing is found, the program should     */
                /* quit immediately                                                            */
#define  KERNEL_OPTION  "androidboot.logcat="
#define  CONSOLE_OPTION "androidboot.console="
                {
                    int          fd;
                    char*        logcat;
                    char*        console;
                    int          force_exit = 1;
                    static char  cmdline[1024];

                    fd = open("/proc/cmdline", O_RDONLY);
                    if (fd >= 0) {
                        int  n = read(fd, cmdline, sizeof(cmdline)-1 );
                        if (n < 0) n = 0;
                        cmdline[n] = 0;
                        close(fd);
                    } else {
                        cmdline[0] = 0;
                    }

                    logcat  = strstr( cmdline, KERNEL_OPTION );
                    console = strstr( cmdline, CONSOLE_OPTION );
                    if (logcat != NULL) {
                        char*  p = logcat + sizeof(KERNEL_OPTION)-1;;
                        char*  q = strpbrk( p, " \t\n\r" );;

                        if (q != NULL)
                            *q = 0;

                        forceFilters = p;
                        force_exit   = 0;
                    }
                    /* if nothing found or invalid filters, exit quietly */
                    if (force_exit)
                        exit(0);

                    /* redirect our output to the emulator console */
                    if (console) {
                        char*  p = console + sizeof(CONSOLE_OPTION)-1;
                        char*  q = strpbrk( p, " \t\n\r" );
                        char   devname[64];
                        int    len;

                        if (q != NULL) {
                            len = q - p;
                        } else
                            len = strlen(p);

                        len = snprintf( devname, sizeof(devname), "/dev/%.*s", len, p );
                        fprintf(stderr, "logcat using %s (%d)\n", devname, len);
                        if (len < (int)sizeof(devname)) {
                            fd = open( devname, O_WRONLY );
                            if (fd >= 0) {
                                dup2(fd, 1);
                                dup2(fd, 2);
                                close(fd);
                            }
                        }
                    }
                }
                break;

            default:
                fprintf(stderr,"Unrecognized Option\n");
                android::show_help(argv[0]);
                exit(-1);
            break;
        }
    }

    if (!devices) {
        devices = new log_device_t(strdup("/dev/"LOGGER_LOG_MAIN), false, 'm');
        android::g_devCount = 1;
        int accessmode =
                  (mode & O_RDONLY) ? R_OK : 0
                | (mode & O_WRONLY) ? W_OK : 0;
        // only add this if it's available
        if (0 == access("/dev/"LOGGER_LOG_SYSTEM, accessmode)) {
            devices->next = new log_device_t(strdup("/dev/"LOGGER_LOG_SYSTEM), false, 's');
            android::g_devCount++;
        }
    }

    if (android::g_logRotateSizeKBytes != 0 
        && android::g_outputFileName == NULL
    ) {
        fprintf(stderr,"-r requires -f as well\n");
        android::show_help(argv[0]);
        exit(-1);
    }

    android::setupOutput();

    if (hasSetLogFormat == 0) {
        const char* logFormat = getenv("ANDROID_PRINTF_LOG");

        if (logFormat != NULL) {
            err = setLogFormat(logFormat);

            if (err < 0) {
                fprintf(stderr, "invalid format in ANDROID_PRINTF_LOG '%s'\n", 
                                    logFormat);
            }
        }
    }

    if (forceFilters) {
        err = android_log_addFilterString(g_logformat, forceFilters);
        if (err < 0) {
            fprintf (stderr, "Invalid filter expression in -logcat option\n");
            exit(0);
        }
    } else if (argc == optind) {
        // Add from environment variable
        char *env_tags_orig = getenv("ANDROID_LOG_TAGS");

        if (env_tags_orig != NULL) {
            err = android_log_addFilterString(g_logformat, env_tags_orig);

            if (err < 0) { 
                fprintf(stderr, "Invalid filter expression in" 
                                    " ANDROID_LOG_TAGS\n");
                android::show_help(argv[0]);
                exit(-1);
            }
        }
    } else {
        // Add from commandline
        for (int i = optind ; i < argc ; i++) {
            err = android_log_addFilterString(g_logformat, argv[i]);

            if (err < 0) { 
                fprintf (stderr, "Invalid filter expression '%s'\n", argv[i]);
                android::show_help(argv[0]);
                exit(-1);
            }
        }
    }

    dev = devices;
    while (dev) {
        dev->fd = open(dev->device, mode);
        if (dev->fd < 0) {
            fprintf(stderr, "Unable to open log device '%s': %s\n",
                dev->device, strerror(errno));
            exit(EXIT_FAILURE);
        }

        if (clearLog) {
            int ret;
            ret = android::clearLog(dev->fd);
            if (ret) {
                perror("ioctl");
                exit(EXIT_FAILURE);
            }
        }

        if (getLogSize) {
            int size, readable;

            size = android::getLogSize(dev->fd);
            if (size < 0) {
                perror("ioctl");
                exit(EXIT_FAILURE);
            }

            readable = android::getLogReadableSize(dev->fd);
            if (readable < 0) {
                perror("ioctl");
                exit(EXIT_FAILURE);
            }

            printf("%s: ring buffer is %dKb (%dKb consumed), "
                   "max entry is %db, max payload is %db\n", dev->device,
                   size / 1024, readable / 1024,
                   (int) LOGGER_ENTRY_MAX_LEN, (int) LOGGER_ENTRY_MAX_PAYLOAD);
        }

        dev = dev->next;
    }

    if (getLogSize) {
        return 0;
    }
    if (clearLog) {
        return 0;
    }

    //LOG_EVENT_INT(10, 12345);
    //LOG_EVENT_LONG(11, 0x1122334455667788LL);
    //LOG_EVENT_STRING(0, "whassup, doc?");

    if (needBinary)
        android::g_eventTagMap = android_openEventTagMap(EVENT_TAG_MAP_FILE);

    android::readLogLines(devices);

    return 0;
}