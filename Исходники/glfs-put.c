void
parse_options (int argc, char *argv[])
{
        uint16_t port = GLUSTER_DEFAULT_PORT;
        int ret = -1;
        int opt = 0;
        int option_index = 0;
        struct xlator_option *option;

        while (true) {
                opt = getopt_long (argc, argv, "adfo:p:r", long_options,
                                   &option_index);

                if (opt == -1) {
                        break;
                }

                switch (opt) {
                        case 'a':
                                state->append = true;
                                break;
                        case 'd':
                                state->debug = true;
                                break;
                        case 'f':
                                state->overwrite = true;
                                break;
                        case 'o':
                                option = parse_xlator_option (optarg);
                                if (option == NULL) {
                                        error (0, errno, "%s", optarg);
                                        goto err;
                                }

                                if (append_xlator_option (&state->xlator_options, option) == -1) {
                                        error (EXIT_FAILURE, errno, "append_xlator_option: %s", optarg);
                                }

                                break;
                        case 'p':
                                port = strtoport (optarg);
                                if (port == 0) {
                                        exit (EXIT_FAILURE);
                                }

                                break;
                        case 'r':
                                state->parents = true;
                                break;
                        case 'v':
                                printf ("%s (%s) %s\n%s\n%s\n%s\n",
                                        program_invocation_name,
                                        PACKAGE_NAME,
                                        PACKAGE_VERSION,
                                        COPYRIGHT,
                                        LICENSE,
                                        AUTHORS);
                                exit (EXIT_SUCCESS);
                        case 'x':
                                usage (EXIT_SUCCESS);
                        default:
                                goto err;
                }
        }

        if ((argc - option_index) < 2) {
                error (0, 0, "missing operand");
                goto err;
        } else {
                state->url = strdup (argv[argc - 1]);
                if (state->url == NULL) {
                        error (0, errno, "strdup");
                        goto out;
                }

                ret = gluster_parse_url (argv[argc - 1], &(state->gluster_url));
                if (ret == -1) {
                        error (0, EINVAL, "%s", state->url);
                        goto err;
                }

                state->gluster_url->port = port;
        }

        goto out;

err:
        error (EXIT_FAILURE, 0, "Try --help for more information.");
out:
        return;
}