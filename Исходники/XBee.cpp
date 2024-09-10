int main(int argc, char * const *argv) {

    int opt = 0;

    //  getopt treats argv interstingly
    while ((opt = getopt(argc, argv, "b:p:")) != -1) {
        switch (opt) {
        case 'b':
            baud = optarg;
            break;
        case 'p':
            port = optarg;
            break;
        default:
            usage();
            break;
        }
    }

    int baudi = atoi(baud);
    int bval = lookup_baud(baudi);
    if (bval <= 0) {
        fprintf(stderr, "Not a recognized baud rate: %s\n", baud);
        exit(EXIT_FAILURE);
    }

    if (optind >= argc) {
        usage();
    }
    command = argv[optind++];
    if (optind < argc) {
        filename = argv[optind++];
    }
    if (optind < argc) {
        usage();
    }

    openport(bval);

    if (!strcmp(command, "dump")) {
        do_dump();
    }
    else if (!strcmp(command, "load")) {
        do_load();
    }
    else {
        fprintf(stderr, "unknown command '%s'\n", command);
        usage();
    }

    return EXIT_SUCCESS;
}