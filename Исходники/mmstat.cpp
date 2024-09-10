int
main(int argc, char **argv1)
{
    TSK_VS_INFO *vs;
    TSK_IMG_TYPE_ENUM imgtype = TSK_IMG_TYPE_DETECT;
    TSK_VS_TYPE_ENUM vstype = TSK_VS_TYPE_DETECT;
    int ch;
    TSK_OFF_T imgaddr = 0;
    TSK_IMG_INFO *img;
    TSK_TCHAR **argv;
    unsigned int ssize = 0;
    TSK_TCHAR *cp;

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

    while ((ch = GETOPT(argc, argv, _TSK_T("b:i:o:t:vV"))) > 0) {
        switch (ch) {
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

        case _TSK_T('o'):
            if ((imgaddr = tsk_parse_offset(OPTARG)) == -1) {
                tsk_error_print(stderr);
                exit(1);
            }
            break;
        case _TSK_T('t'):
            if (TSTRCMP(OPTARG, _TSK_T("list")) == 0) {
                tsk_vs_type_print(stderr);
                exit(1);
            }
            vstype = tsk_vs_type_toid(OPTARG);
            if (vstype == TSK_VS_TYPE_UNSUPP) {
                TFPRINTF(stderr,
                    _TSK_T("Unsupported volume system type: %s\n"),
                    OPTARG);
                usage();
            }
            break;
        case 'v':
            tsk_verbose++;
            break;
        case 'V':
            tsk_version_print(stdout);
            exit(0);
        case '?':
        default:
            tsk_fprintf(stderr, "Unknown argument\n");
            usage();
        }
    }

    /* We need at least one more argument */
    if (OPTIND >= argc) {
        tsk_fprintf(stderr, "Missing image name\n");
        usage();
    }

    /* open the image */
    if ((img =
            tsk_img_open(argc - OPTIND, &argv[OPTIND], imgtype,
                ssize)) == NULL) {
        tsk_error_print(stderr);
        exit(1);
    }
    if ((imgaddr * img->sector_size) >= img->size) {
        tsk_fprintf(stderr,
            "Sector offset supplied is larger than disk image (maximum: %"
            PRIu64 ")\n", img->size / img->sector_size);
        exit(1);
    }


    /* process the partition tables */
    if ((vs = tsk_vs_open(img, imgaddr * img->sector_size, vstype)) == NULL) {
        tsk_error_print(stderr);
        if (tsk_error_get_errno() == TSK_ERR_VS_UNSUPTYPE)
            tsk_vs_type_print(stderr);

        exit(1);
    }

    print_stats(vs);

    tsk_vs_close(vs);
    tsk_img_close(img);
    exit(0);
}