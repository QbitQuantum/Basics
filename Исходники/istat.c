int
MAIN(int argc, TSK_TCHAR ** argv)
{
    TSK_TCHAR *imgtype = NULL;
    TSK_TCHAR *fstype = NULL;
    TSK_IMG_INFO *img;
    TSK_FS_INFO *fs;
    INUM_T inum;
    int ch;
    TSK_TCHAR *cp;
    int32_t sec_skew = 0;
    SSIZE_T imgoff = 0;

    /* When > 0 this is the number of blocks to print, used for -b arg */
    DADDR_T numblock = 0;

    progname = argv[0];
    setlocale(LC_ALL, "");

    while ((ch = getopt(argc, argv, _TSK_T("b:f:i:o:s:vVz:"))) > 0) {
        switch (ch) {
        case _TSK_T('?'):
        default:
            TFPRINTF(stderr, _TSK_T("Invalid argument: %s\n"),
                argv[optind]);
            usage();
        case _TSK_T('b'):
            numblock = TSTRTOULL(optarg, &cp, 0);
            if (*cp || *cp == *optarg || numblock < 1) {
                TFPRINTF(stderr,
                    _TSK_T
                    ("invalid argument: block count must be positive: %s\n"),
                    optarg);
                usage();
            }
            break;
        case _TSK_T('f'):
            fstype = optarg;
            if (TSTRCMP(fstype, _TSK_T("list")) == 0) {
                tsk_fs_print_types(stderr);
                exit(1);
            }
            break;
        case _TSK_T('i'):
            imgtype = optarg;
            if (TSTRCMP(imgtype, _TSK_T("list")) == 0) {
                tsk_img_print_types(stderr);
                exit(1);
            }
            break;
        case _TSK_T('o'):
            if ((imgoff = tsk_parse_offset(optarg)) == -1) {
                tsk_error_print(stderr);
                exit(1);
            }
            break;
        case _TSK_T('s'):
            sec_skew = TATOI(optarg);
            break;
        case _TSK_T('v'):
            tsk_verbose++;
            break;
        case _TSK_T('V'):
            tsk_print_version(stdout);
            exit(0);
        case _TSK_T('z'):
            {
                TSK_TCHAR envstr[32];
                TSNPRINTF(envstr, 32, _TSK_T("TZ=%s"), optarg);
                if (0 != PUTENV(envstr)) {
                    tsk_fprintf(stderr, "error setting environment");
                    exit(1);
                }
                TZSET();
            }
            break;
        }
    }

    /* We need at least two more argument */
    if (optind + 1 >= argc) {
        tsk_fprintf(stderr, "Missing image name and/or address\n");
        usage();
    }

    /* if we are given the inode in the inode-type-id form, then ignore
     * the other stuff w/out giving an error 
     *
     * This will make scripting easier
     */
    if (tsk_parse_inum(argv[argc - 1], &inum, NULL, NULL, NULL)) {
        TFPRINTF(stderr, _TSK_T("Invalid inode number: %s"),
            argv[argc - 1]);
        usage();
    }

    /*
     * Open the file system.
     */
    if ((img =
            tsk_img_open(imgtype, argc - optind - 1,
                (const TSK_TCHAR **) &argv[optind])) == NULL) {
        tsk_error_print(stderr);
        exit(1);
    }

    if ((fs = tsk_fs_open(img, imgoff, fstype)) == NULL) {
        tsk_error_print(stderr);
        if (tsk_errno == TSK_ERR_FS_UNSUPTYPE)
            tsk_fs_print_types(stderr);
        img->close(img);
        exit(1);
    }

    if (inum > fs->last_inum) {
        tsk_fprintf(stderr,
            "Metadata address is too large for image (%" PRIuINUM ")\n",
            fs->last_inum);
        fs->close(fs);
        img->close(img);
        exit(1);
    }

    if (inum < fs->first_inum) {
        tsk_fprintf(stderr,
            "Metadata address is too small for image (%" PRIuINUM ")\n",
            fs->first_inum);
        fs->close(fs);
        img->close(img);
        exit(1);
    }

    if (fs->istat(fs, stdout, inum, numblock, sec_skew)) {
        tsk_error_print(stderr);
        fs->close(fs);
        img->close(img);
        exit(1);
    }

    fs->close(fs);
    img->close(img);
    exit(0);
}