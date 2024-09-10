int main(int argc, char *argv[])
{
    FILE *fd = NULL;
    Tstate prev_state;
    char filename[256];
    time_t rstart, rend, tnow;
    struct tm tm;
    char tag[32] = "default";
    char *home = getenv("HOME");

    // check for explicit tag name
    if (argc > 2 && argv[1][1] == 't') {
        strncpy(tag, argv[2], sizeof(tag));
        argc -= 2;
        argv += 2;
    }

    if (argc < 2) {
        printf("usage: %s", usage);
        exit(EXIT_SUCCESS);
    }

    snprintf(filename, sizeof(filename), "%s/.wtimed/%s", home, tag);

    if ((fd = fopen(filename, "r+")) == NULL) {
        if ((fd = fopen(filename, "w+")) == NULL) {
            fprintf(stderr, "Error while opening data file '%s'.\n", filename);
            exit(EXIT_FAILURE);
        }
    }

    if (argv[1][0] != '-') {
        fprintf(stderr, "Unknown parameter: %s\n", argv[1]);
    } else {
        if ((prev_state = cur_state(fd)) == UNKNOWN) {
            fprintf(stderr, "Corrupted data file '%s'.\n", filename);
            exit(EXIT_FAILURE);
        }
        switch (argv[1][1]) {
        case 'h':
            printf("usage: %s", usage);
            break;
        case 'a':
            if (prev_state == STARTED)
                fprintf(stderr, "We are allready counting.\n");
            else
                start_counting(fd);
            break;
        case 's':
            if (prev_state != STARTED)
                fprintf(stderr, "We are not counting.\n");
						else
                stop_counting(fd);
            break;
        case 'r':
            if (argc == 4) {    // end
                if (strptime(argv[3], "%d-%m-%Y", &tm) == NULL) {
                    fprintf(stderr, "Malformated end date\n");
                    exit(EXIT_FAILURE);
                }
                tm.tm_min = tm.tm_sec = 59;
                tm.tm_hour = 23;
                rend = mktime(&tm);
            } else {
                rend = time(NULL);
            }
            if (argc >= 3) {    // start
                if (strptime(argv[2], "%d-%m-%Y", &tm) == NULL) {
                    fprintf(stderr, "Malformated start date\n");
                    exit(EXIT_FAILURE);
                }
                tm.tm_sec = tm.tm_min = tm.tm_hour = 0;
                rstart = mktime(&tm);
            } else {            // beginning of month
                tnow = time(NULL);
                tm = *localtime(&tnow);
                tm.tm_mday = 1;
                tm.tm_sec = tm.tm_min = tm.tm_hour = 0;
                rstart = mktime(&tm);
            }
            if (rstart > rend) {
                fprintf(stderr, "Start date is further then end date.\n");
                exit(EXIT_FAILURE);
            }
            print_report(fd, rstart, rend);
            break;
        case 'c':
            if (prev_state != STARTED) {
                fprintf(stderr, "We are not counting.\n");
								exit(EXIT_FAILURE);
						} else
                print_elapsed(fd);
            break;
        default:
            fprintf(stderr, "Unknown parameter: %s\n", argv[1]);
            break;
        }
    }

    if (fd)
        fclose(fd);

    return (0);
}