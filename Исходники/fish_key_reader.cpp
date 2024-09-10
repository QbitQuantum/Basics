int main(int argc, char **argv) {
    program_name = L"fish_key_reader";
    bool continuous_mode = false;
    const char *short_opts = "+cd:D:";
    const struct option long_opts[] = {{"continuous", no_argument, NULL, 'c'},
                                       {"debug-level", required_argument, NULL, 'd'},
                                       {"debug-stack-frames", required_argument, NULL, 'D'},
                                       {NULL, 0, NULL, 0}};
    int opt;
    while ((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
        switch (opt) {
            case 0: {
                fprintf(stderr, "getopt_long() unexpectedly returned zero\n");
                exit(1);
            }
            case 'c': {
                continuous_mode = true;
                break;
            }
            case 'd': {
                char *end;
                long tmp;

                errno = 0;
                tmp = strtol(optarg, &end, 10);

                if (tmp >= 0 && tmp <= 10 && !*end && !errno) {
                    debug_level = (int)tmp;
                } else {
                    fwprintf(stderr, _(L"Invalid value '%s' for debug-level flag"), optarg);
                    exit(1);
                }
                break;
            }
            case 'D': {
                char *end;
                long tmp;

                errno = 0;
                tmp = strtol(optarg, &end, 10);

                if (tmp > 0 && tmp <= 128 && !*end && !errno) {
                    debug_stack_frames = (int)tmp;
                } else {
                    fwprintf(stderr, _(L"Invalid value '%s' for debug-stack-frames flag"), optarg);
                    exit(1);
                }
                break;
            }
            default: {
                // We assume getopt_long() has already emitted a diagnostic msg.
                exit(1);
            }
        }
    }

    argc -= optind;
    if (argc != 0) {
        fprintf(stderr, "Expected no arguments, got %d\n", argc);
        return 1;
    }

    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)) {
        fprintf(stderr, "Stdin and stdout must be attached to a tty, redirection not allowed.\n");
        return 1;
    }

    setup_and_process_keys(continuous_mode);
    return 0;
}