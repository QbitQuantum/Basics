static int parse_params(int argc, char *argv[])
{
    int c;
    while ((c = getopt(argc, argv, "BUCo:w:d:v:V:p:")) != -1) {
        switch (c) {
            case 'U':
                do_unpack = 0;
                break;
            case 'B':
                do_build = 0;
                break;
            case 'C':
                do_gencontrol = 0;
                break;
            case 'o':
                out_dir = optarg;
                break;
            case 'w':
                if ((work_dir = realpath(optarg, NULL)) == NULL) {
                    fprintf(stderr, "realpath(%s) failed: %s\n", optarg,
                            strerror(errno));
                    return -1;
                }
                break;
            case 'd':
                if ((dist_dir = realpath(optarg, NULL)) == NULL) {
                    fprintf(stderr, "realpath(%s) failed: %s\n", optarg,
                            strerror(errno));
                    return -1;
                }
                break;
            case 'p':
                if ((pkg_dir = realpath(optarg, NULL)) == NULL) {
                    fprintf(stderr, "realpath(%s) failed: %s\n", optarg,
                            strerror(errno));
                    return -1;
                }
                break;
            case 'v':
                ver_mode = VERSION_OVERRIDE;
                ver_param = optarg;
                break;
            case 'V':
                ver_mode = VERSION_APPEND;
                ver_param = optarg;
                break;
            case '?':
                fprintf(stderr, "Unknown option: %c\n", optopt);
                return -1;

            default:
                fprintf(stderr, "Unexpected option: %c\n", c);
                abort();
        }
    }

    if (work_dir == NULL) {
        fprintf(stderr, "A working directory must be set\n");
        return -1;
    }

    if (optind + 1 != argc)
        return -1;

    if ((control_path = realpath(argv[optind], NULL)) == NULL) {
        fprintf(stderr, "realpath(%s) failed: %s\n", argv[optind],
                strerror(errno));
        return -1;
    }
    return 0;
}