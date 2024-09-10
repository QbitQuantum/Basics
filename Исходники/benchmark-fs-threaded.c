static int parse_args(int argc, char * argv[])
{
    int i, c;
    long n;

    while ((c = getopt_long(argc, argv, 
                    opt_string, long_options, &i)) != -1) {
        switch (c) {
        case 'v':
            verbose = 1;
            break;
        case 'p':
            report_progress = 1;
            break;
        case 'h':
            help = 1;
            break;
        case 'f':
            if (strlen(optarg) == 0) {
                printf("invalid root directory\n");
                return 1;
            }
            benchmark_root_dir = optarg;
            break;
        case 'c':
            n = atol(optarg);
            if (n <= 32) {
                printf("cachesize shouldn't be less than 32mb\n");
                return 1;
            }
            cachesize = n * 1024 * 1024L;
            break;
        case 'n':
            n = atol(optarg);
            if (n <= 0) {
                printf("need to operate on at least one file\n");
                return 1;
            }
            num_files = n;
            break;
        case 'd':
            n = atol(optarg);
            if (n <= 0) {
                printf("need at least one file per directory\n");
                return 1;
            }
            directory_max_children = n;
            break;
        case 'm':
            n = atol(optarg);
            if (n <= 0) {
                printf("need to use at least one thread\n");
                return 1;
            }
            num_threads = n;
            break;
        case 'b':
            n = atol(optarg);
            if (n <= 0) {
                printf("io size needs to be > 0\n");
                return 1;
            }
            iosize = n;
            break;
        case 'x':
            n = atol(optarg);
            if (n < 0) {
                printf("number of operations needs to be >= 0.\n"
                       "0 means only open and close files\n");
                return 1;
            }
            num_operations = n;
            break;
        case 0:
            break;
        case '?':
            printf("?\n");
        default:
            return 1;
        }
    }

    return 0;
}