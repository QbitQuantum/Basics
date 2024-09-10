int
main(int argc, char **argv1)
{
    TSK_IMG_TYPE_ENUM imgtype = TSK_IMG_TYPE_DETECT;
    int ch;
    TSK_TCHAR **argv;
    unsigned int ssize = 0;
    TSK_TCHAR *cp;
    int32_t sec_skew = 0;

#ifdef TSK_WIN32
    // On Windows, get the wide arguments (mingw doesn't support wmain)
    argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argv == NULL) {
        fprintf(stderr, "Error getting wide arguments\n");
        exit(1);
    }
#else
    argv = (TSK_TCHAR **) argv1;
#endif

    progname = argv[0];
    setlocale(LC_ALL, "");

    while ((ch = GETOPT(argc, argv, _TSK_T("b:i:s:vVz:"))) > 0) {
        switch (ch) {
        case _TSK_T('?'):
        default:
            TFPRINTF(stderr, _TSK_T("Invalid argument: %s\n"),
                     argv[OPTIND]);
            usage();


        case _TSK_T('b'):
            ssize = (unsigned int) TSTRTOUL(OPTARG, &cp, 0);
            if (*cp || *cp == *OPTARG || ssize < 1) {
                TFPRINTF(stderr,
                         _TSK_T
                         ("invalid argument: sector size must be positive: %s\n"),
                         OPTARG);
                usage();
            }
            break;



        case _TSK_T('i'):
            if (TSTRCMP(OPTARG, _TSK_T("list")) == 0) {
                tsk_img_type_print(stderr);
                exit(1);
            }
            imgtype = tsk_img_type_toid(OPTARG);
            if (imgtype == TSK_IMG_TYPE_UNSUPP) {
                TFPRINTF(stderr, _TSK_T("Unsupported image type: %s\n"),
                         OPTARG);
                usage();
            }
            break;

        case _TSK_T('s'):
            sec_skew = TATOI(OPTARG);
            break;


        case _TSK_T('v'):
            tsk_verbose++;
            break;

        case _TSK_T('V'):
            tsk_version_print(stdout);
            exit(0);

        case 'z':
        {
            TSK_TCHAR envstr[32];
            TSNPRINTF(envstr, 32, _TSK_T("TZ=%s"), OPTARG);
            if (0 != TPUTENV(envstr)) {
                tsk_fprintf(stderr, "error setting environment");
                exit(1);
            }

            /* we should be checking this somehow */
            TZSET();
        }
        break;

        }
    }

    /* We need at least one more argument */
    if (OPTIND > argc) {
        tsk_fprintf(stderr,
                    "Missing image name\n");
        usage();
    }

    TskGetTimes tskGetTimes(sec_skew);
    if (tskGetTimes.openImage(argc - OPTIND, &argv[OPTIND], imgtype,
                              ssize)) {
        tsk_error_print(stderr);
        exit(1);
    }

    if (tskGetTimes.findFilesInImg()) {
        tsk_error_print(stderr);
        exit(1);
    }

    exit(0);
}