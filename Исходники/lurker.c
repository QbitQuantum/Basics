int main(int argc, char **argv)
{
    int r;
    int option;
    struct option getopt_options[] =
    {
        {"help", 0, 0, 'h'},
        {"input", 1, 0, 'i'},
        {"output", 1, 0, 'o'},
        {"append", 1, 0, 'a'},
        {"threshold", 1, 0, 't'},
        {"runlength", 1, 0, 'r'},
        {"filter", 1, 0, 'f'},
        {"start", 1, 0, 's'},
        {"divisor", 1, 0, 'd'},
        {NULL, 0, 0, 0}
    };

    /* defaults */
    input = NULL; /* stdin */
    output = "clip_%F_%H:%M:%S.wav";
    /* use .wav to be nice to people who like to listen while recording */
    recording_append = ".recording.wav";
    threshold = 0.1;
    runlength = 4;
    short_filter = 0; /* dont filter */
    time_start = 0; /* 0 = use system time */
    slice_divisor = 60;

    /* shameless plug */
    printf("lurker 0.4, (C)2004 Mattias Wadman <*****@*****.**>\n");

    while(1)
    {
        option = getopt_long(argc, argv, "hi:o:a:t:r:f:s:d:", getopt_options, NULL);

        if(option == -1)
            break;
        else if(option == 'h')
        {
            printf("Usage: %s [OPTION]...\n"
                   "    -i, --input PATH       Input file (stdin)\n"
                   "    -o, --output PATH      Output path, strftime formated (%s)\n"
                   "    -a, --append STRING    Append to filename while recording (%s)\n"
                   "    -t, --threshold NUMBER Sound level threshold to trigger (%g)\n"
                   "    -r, --runlength NUMBER Seconds of silence to untrigger (%g)\n"
                   "    -f, --filter NUMBER    Remove clip if length is less then NUMBER seconds (%g)\n"
                   "    -s, --start DATETIME   Use a given start time and offset with audio time\n"
                   "                           Eg: \"2000-01-02 03:04:05\"\n"
                   "                           Eg: now (use system clock as start)\n"
                   "    -d, --divisor NUMBER   Slice sample rate into NUMBER parts internally (%g)\n"
                   "",
                   argv[0], output, recording_append, threshold, runlength,
                   short_filter, slice_divisor
                   );

            return EXIT_SUCCESS;
        }
        else if(option == 'i')
            input = optarg;
        else if(option == 'o')
            output = optarg;
        else if(option == 'a')
            recording_append = optarg;
        else if(option == 't')
            threshold = atof(optarg);
        else if(option == 'r')
            runlength = atof(optarg);
        else if(option == 'f')
            short_filter = atof(optarg);
        else if(option == 's')
        {
            struct tm t;
            char *s;

            if(strcmp(optarg, "now") == 0)
                time_start = time(NULL);
            else
            {
                s = strptime(optarg, "%Y-%m-%d %H:%M:%S", &t);
                if(s == NULL || *s != '\0')
                {
                    fprintf(stderr, "Invalid time format\n");

                    return EXIT_FAILURE;
                }
                
                time_start = mktime(&t);
            }
        }
        else if(option == 'd')
            slice_divisor = atof(optarg);
        else
        {
            fprintf(stderr, "Error in argument: %c\n", option);

            return EXIT_FAILURE;
        }
    }
   
    /* string used to clear current line */
    clear_line = generate_clear_line_string();
    if(clear_line == NULL)
    {
        fprintf(stderr, "generate_clear_line_string failed, fallback to \"\\r\"\n");
        clear_line = strdup("\r");
    }
   
    /* get current working path and make sure it end with a slash */
    current_dir = get_current_dir_name();
    if(current_dir == NULL)
    {
        fprintf(stderr, "get_current_dir_name failed\n");

        return EXIT_FAILURE;
    }
    /* it is possible that it already ends with a slash, see man page about $PWD */
    else if(current_dir[strlen(current_dir) - 1] != '/')
    {
        char *t;

        if(asprintf(&t, "%s/", current_dir) == -1)
        {
            fprintf(stderr, "asprintf failed\n");

            return EXIT_FAILURE;
        }

        free(current_dir);
        current_dir = t;
    }

    r = lurk();
    free(current_dir);
    free(clear_line);

    return (r == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}