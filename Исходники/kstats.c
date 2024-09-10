int main(int argc, char** argv) {
    bool cpu_stats = false;
    bool mem_stats = false;
    zx_duration_t delay = ZX_SEC(1);
    int num_loops = -1;
    bool timestamp = false;

    int c;
    while ((c = getopt(argc, argv, "cd:n:hmt")) > 0) {
        switch (c) {
            case 'c':
                cpu_stats = true;
                break;
            case 'd':
                delay = ZX_SEC(atoi(optarg));
                if (delay == 0) {
                    fprintf(stderr, "Bad -d value '%s'\n", optarg);
                    print_help(stderr);
                    return 1;
                }
                break;
            case 'n':
                num_loops = atoi(optarg);
                if (num_loops == 0) {
                    fprintf(stderr, "Bad -n value '%s'\n", optarg);
                    print_help(stderr);
                    return 1;
                }
                break;
            case 'h':
                print_help(stdout);
                return 0;
            case 'm':
                mem_stats = true;
                break;
            case 't':
                timestamp = true;
                break;
            default:
                fprintf(stderr, "Unknown option\n");
                print_help(stderr);
                return 1;
        }
    }

    if (!cpu_stats && !mem_stats) {
        fprintf(stderr, "No statistics selected\n");
        print_help(stderr);
        return 1;
    }

    zx_handle_t root_resource;
    zx_status_t ret = get_root_resource(&root_resource);
    if (ret != ZX_OK) {
        return ret;
    }

    // set stdin to non blocking so we can intercept ctrl-c.
    // TODO: remove once ctrl-c works in the shell
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    for (;;) {
        zx_time_t next_deadline = zx_deadline_after(delay);

        // Print the current UTC time with milliseconds as
        // an ISO 8601 string.
        if (timestamp) {
            struct timespec now;
            timespec_get(&now, TIME_UTC);
            struct tm nowtm;
            gmtime_r(&now.tv_sec, &nowtm);
            char tbuf[40];
            strftime(tbuf, sizeof(tbuf), "%FT%T", &nowtm);
            printf("\n--- %s.%03ldZ ---\n", tbuf, now.tv_nsec / (1000 * 1000));
        }

        if (cpu_stats) {
            ret |= cpustats(root_resource, delay);
        }
        if (mem_stats) {
            ret |= memstats(root_resource);
        }

        if (ret != ZX_OK)
            break;

        if (num_loops > 0) {
            if (--num_loops == 0) {
                break;
            }
        } else {
            // TODO: replace once ctrl-c works in the shell
            char c;
            int err;
            while ((err = read(STDIN_FILENO, &c, 1)) > 0) {
                if (c == 0x3)
                    return 0;
            }
        }

        zx_nanosleep(next_deadline);
    }

    zx_handle_close(root_resource);

    return ret;
}