int
MAIN(int argc, TSK_TCHAR ** argv)
{
    TSK_TCHAR *imgtype = NULL;
    TSK_TCHAR *fstype = NULL;
    TSK_FS_INFO *fs;
    TSK_IMG_INFO *img;
    int ch;
    TSK_TCHAR *cp;
    extern int optind;
    DADDR_T block = 0;          /* the block to find */
    INUM_T parinode = 0;
    TSK_TCHAR *path = NULL;
    SSIZE_T imgoff = 0;

    progname = argv[0];
    setlocale(LC_ALL, "");

    localflags = 0;

    while ((ch = getopt(argc, argv, _TSK_T("ad:f:i:ln:o:p:vVz:"))) > 0) {
        switch (ch) {
        case _TSK_T('a'):
            localflags |= TSK_FS_IFIND_ALL;
            break;
        case _TSK_T('d'):
            if (localflags & (TSK_FS_IFIND_PAR | TSK_FS_IFIND_PATH)) {
                tsk_fprintf(stderr,
                    "error: only one address type can be given\n");
                usage();
            }
            localflags |= TSK_FS_IFIND_DATA;
            block = TSTRTOULL(optarg, &cp, 0);
            if (*cp || *cp == *optarg) {
                TFPRINTF(stderr, _TSK_T("Invalid block address: %s\n"),
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
        case _TSK_T('l'):
            localflags |= TSK_FS_IFIND_PAR_LONG;
            break;
        case _TSK_T('n'):
            {
                size_t len;
                if (localflags & (TSK_FS_IFIND_PAR | TSK_FS_IFIND_DATA)) {
                    tsk_fprintf(stderr,
                        "error: only one address type can be given\n");
                    usage();
                }
                localflags |= TSK_FS_IFIND_PATH;
                len = (TSTRLEN(optarg) + 1) * sizeof(TSK_TCHAR);
                if ((path = (TSK_TCHAR *) tsk_malloc(len)) == NULL) {
                    tsk_error_print(stderr);
                    exit(1);
                }
                TSTRNCPY(path, optarg, TSTRLEN(optarg) + 1);
                break;
            }
        case 'o':
            if ((imgoff = tsk_parse_offset(optarg)) == -1) {
                tsk_error_print(stderr);
                exit(1);
            }
            break;
        case 'p':
            if (localflags & (TSK_FS_IFIND_PATH | TSK_FS_IFIND_DATA)) {
                tsk_fprintf(stderr,
                    "error: only one address type can be given\n");
                usage();
            }
            localflags |= TSK_FS_IFIND_PAR;
            if (tsk_parse_inum(optarg, &parinode, NULL, NULL, NULL)) {
                TFPRINTF(stderr, _TSK_T("Invalid inode address: %s\n"),
                    optarg);
                usage();
            }
            break;
        case 'v':
            tsk_verbose++;
            break;
        case 'V':
            tsk_print_version(stdout);
            exit(0);
        case 'z':
            {
                TSK_TCHAR envstr[32];
                TSNPRINTF(envstr, 32, _TSK_T("TZ=%s"), optarg);
                if (0 != PUTENV(envstr)) {
                    tsk_fprintf(stderr, "error setting environment");
                    exit(1);
                }

                /* we should be checking this somehow */
                TZSET();
                break;
            }
        case '?':
        default:
            tsk_fprintf(stderr, "Invalid argument: %s\n", argv[optind]);
            usage();
        }
    }

    /* We need at least one more argument */
    if (optind >= argc) {
        tsk_fprintf(stderr, "Missing image name\n");
        if (path)
            free(path);
        usage();
    }

    if (0 ==
        (localflags & (TSK_FS_IFIND_PATH | TSK_FS_IFIND_DATA |
                TSK_FS_IFIND_PAR))) {
        tsk_fprintf(stderr, "-d, -n, or -p must be given\n");
        usage();
    }


    if ((img =
            tsk_img_open(imgtype, argc - optind,
                (const TSK_TCHAR **) &argv[optind])) == NULL) {
        tsk_error_print(stderr);
        if (path)
            free(path);
        exit(1);
    }

    if ((fs = tsk_fs_open(img, imgoff, fstype)) == NULL) {
        tsk_error_print(stderr);
        if (tsk_errno == TSK_ERR_FS_UNSUPTYPE)
            tsk_fs_print_types(stderr);
        img->close(img);
        if (path)
            free(path);
        exit(1);
    }

    if (localflags & TSK_FS_IFIND_DATA) {
        if (block > fs->last_block) {
            tsk_fprintf(stderr,
                "Block %" PRIuDADDR
                " is larger than last block in image (%" PRIuDADDR
                ")\n", block, fs->last_block);
            fs->close(fs);
            img->close(img);
            exit(1);
        }
        else if (block == 0) {
            tsk_printf("Inode not found\n");
            fs->close(fs);
            img->close(img);
            exit(1);
        }
        if (tsk_fs_ifind_data(fs, localflags, block)) {
            tsk_error_print(stderr);
            fs->close(fs);
            img->close(img);
            exit(1);
        }
    }

    else if (localflags & TSK_FS_IFIND_PAR) {
        if ((fs->ftype & TSK_FS_INFO_TYPE_FS_MASK) !=
            TSK_FS_INFO_TYPE_NTFS_TYPE) {
            tsk_fprintf(stderr, "-p works only with NTFS file systems\n");
            fs->close(fs);
            img->close(img);
            exit(1);
        }
        else if (parinode > fs->last_inum) {
            tsk_fprintf(stderr,
                "Meta data %" PRIuINUM
                " is larger than last MFT entry in image (%" PRIuINUM
                ")\n", parinode, fs->last_inum);
            fs->close(fs);
            img->close(img);
            exit(1);
        }
        if (tsk_fs_ifind_par(fs, localflags, parinode)) {
            tsk_error_print(stderr);
            fs->close(fs);
            img->close(img);
            exit(1);
        }
    }

    else if (localflags & TSK_FS_IFIND_PATH) {
        int retval;
        INUM_T inum;

        if (-1 == (retval =
                tsk_fs_ifind_path(fs, localflags, path, &inum))) {
            tsk_error_print(stderr);
            fs->close(fs);
            img->close(img);
            free(path);
            exit(1);
        }
        free(path);
        if (retval == 1)
            tsk_printf("File not found\n");
        else
            tsk_printf("%" PRIuINUM "\n", inum);
    }
    fs->close(fs);
    img->close(img);

    exit(0);
}