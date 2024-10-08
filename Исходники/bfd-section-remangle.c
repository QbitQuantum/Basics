int main(int argc, char * argv[])
{
        bfd *                bfd_in;
        bfd *                bfd_out;
        char *               filename_in;
        char *               filename_out;

        log_init(PROGRAM_NAME, LOG_MESSAGE);
        atexit(log_fini);

        filename_in  = NULL;
        filename_out = NULL;

        int c;
        // int digit_optind = 0;
        while (1) {
                // int this_option_optind = optind ? optind : 1;
                int option_index       = 0;

                static struct option long_options[] = {
                        { "input",        1, 0, 'i' },
                        { "output",       1, 0, 'o' },

                        { "debug",        0, 0, 'd' },
                        { "verbose",      0, 0, 'v' },
                        { "version",      0, 0, 'V' },
                        { "help",         0, 0, 'h' },
                        { 0,              0, 0, 0   }
                };
                c = getopt_long(argc, argv, "i:o:dvVh",
                                long_options, &option_index);
                if (c == -1) {
                        break;
                }

                debug("Handling option character '%c'\n", c);

                switch (c) {
                        case 'i':
                                filename_in = optarg;
                                break;
                        case 'o':
                                filename_out = optarg;
                                break;
                        case 'd':
                                log_level(LOG_DEBUG);
                                break;
                        case 'v':
                                log_level(LOG_VERBOSE);
                                break;
                        case 'V':
                                version(PROGRAM_NAME);
                                return 0;
                        case 'h':
                                help();
                                return 0;
                        case '?':
                                hint(PROGRAM_NAME, "Unrecognized option");
                                return 1;
                        default:
                                BUG();
                                return 1;
                }
        }

        if (!filename_in) {
                fatal("Missing input filename\n");
                exit(EXIT_FAILURE);
        }
        if (!filename_out) {
                fatal("Missing output filename\n");
                exit(EXIT_FAILURE);
        }
        /* XXX FIXME: Use stat instead of strcmp */
        if (!strcmp(filename_in, filename_out)) {
                fatal("Input and output are the same file\n");
                exit(EXIT_FAILURE);
        }

        bfd_init();

        debug("Reading input file %s\n", filename_in);
        bfd_in = bfd_openr(filename_in, NULL);
        if (!bfd_in) {
                fatal("Cannot open input file %s (%s)\n",
                      filename_in, BFD_strerror());
                exit(EXIT_FAILURE);
        }
        if (!bfd_check_format(bfd_in, bfd_object)) {
                fatal("Wrong input file format (not an object)\n");
                exit(EXIT_FAILURE);
        }

        bfd_out = bfd_openw(filename_out, NULL);
        if (!bfd_out) {
                fatal("Cannot open output file %s (%s)\n",
                      filename_out, BFD_strerror());
                exit(EXIT_FAILURE);
        }

        debug("Generating output file %s\n", filename_out);
        bfd_set_format(bfd_out, bfd_get_format(bfd_in));

        if (bfd_copy_private_bfd_data(bfd_in, bfd_out) == FALSE) {
                fatal("Cannot copy private bfd data (%s)\n",
                      BFD_strerror());
                exit(EXIT_FAILURE);
        }
        if (bfd_copy_private_header_data(bfd_in, bfd_out) == FALSE) {
                fatal("Cannot copy private header data (%s)\n",
                      BFD_strerror());
                exit(EXIT_FAILURE);
        }

        bfd_close(bfd_in);
        bfd_close(bfd_out);

        exit(EXIT_SUCCESS);
}