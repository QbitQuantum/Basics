int main(int argc, char** argv) {
#ifdef _MSC_VER
    _set_error_mode(_OUT_TO_STDERR);
    _set_abort_behavior( 0, _WRITE_ABORT_MSG);
#endif
#ifdef _WIN32
    get_argv_utf8(&argc, &argv);
#endif
    char *outfile = 0;
    int from_stdin = 0;
    bool generate_source_map = false;
    struct Sass_Options* options = sass_make_options();
    sass_option_set_output_style(options, SASS_STYLE_NESTED);
    sass_option_set_precision(options, 5);

    int c;
    size_t i;
    int long_index = 0;
    static struct option long_options[] =
    {
        { "stdin",              no_argument,       0, 's' },
        { "load-path",          required_argument, 0, 'I' },
        { "plugin-path",        required_argument, 0, 'P' },
        { "style",              required_argument, 0, 't' },
        { "line-numbers",       no_argument,       0, 'l' },
        { "line-comments",      no_argument,       0, 'l' },
        { "sourcemap",          no_argument,       0, 'm' },
        { "omit-map-comment",   no_argument,       0, 'M' },
        { "precision",          required_argument, 0, 'p' },
        { "version",            no_argument,       0, 'v' },
        { "help",               no_argument,       0, 'h' },
        { NULL,                 0,                 NULL, 0}
    };
    while ((c = getopt_long(argc, argv, "vhslmMp:t:I:P:", long_options, &long_index)) != -1) {
        switch (c) {
        case 's':
            from_stdin = 1;
            break;
        case 'I':
            sass_option_push_include_path(options, strdup(optarg));
            break;
        case 'P':
            sass_option_push_plugin_path(options, strdup(optarg));
            break;
        case 't':
            for(i = 0; i < NUM_STYLE_OPTION_STRINGS; ++i) {
                if(strcmp(optarg, style_option_strings[i].style_string) == 0) {
                    sass_option_set_output_style(options, style_option_strings[i].output_style);
                    break;
                }
            }
            if(i == NUM_STYLE_OPTION_STRINGS) {
                fprintf(stderr, "Invalid argument for -t flag: '%s'. Allowed arguments are:", optarg);
                for(i = 0; i < NUM_STYLE_OPTION_STRINGS; ++i) {
                    fprintf(stderr, " %s", style_option_strings[i].style_string);
                }
                fprintf(stderr, "\n");
                invalid_usage(argv[0]);
            }
            break;
        case 'l':
            sass_option_set_source_comments(options, true);
            break;
        case 'm':
            generate_source_map = true;
            break;
        case 'M':
            sass_option_set_omit_source_map_url(options, true);
            break;
        case 'p':
            sass_option_set_precision(options, atoi(optarg)); // TODO: make this more robust
            if (sass_option_get_precision(options) < 0) sass_option_set_precision(options, 5);
            break;
        case 'v':
            print_version();
            return 0;
        case 'h':
            print_usage(argv[0]);
            return 0;
        case '?':
            /* Unrecognized flag or missing an expected value */
            /* getopt should produce it's own error message for this case */
            invalid_usage(argv[0]);
        default:
            fprintf(stderr, "Unknown error while processing arguments\n");
            return 2;
        }
    }

    if(optind < argc - 2) {
        fprintf(stderr, "Error: Too many arguments.\n");
        invalid_usage(argv[0]);
    }

    int result;
    if(optind < argc && strcmp(argv[optind], "-") != 0 && !from_stdin) {
        if (optind + 1 < argc) {
            outfile = argv[optind + 1];
        }
        if (generate_source_map && outfile) {
            const char* extension = ".map";
            char* source_map_file  = calloc(strlen(outfile) + strlen(extension) + 1, sizeof(char));
            strcpy(source_map_file, outfile);
            strcat(source_map_file, extension);
            sass_option_set_source_map_file(options, source_map_file);
        }
        result = compile_file(options, argv[optind], outfile);
    } else {
        if (optind < argc) {
            outfile = argv[optind];
        }
        result = compile_stdin(options, outfile);
    }

    return result;
}