int main(int argc, char *argv[]) {

    size_t num_files = 0;

    char **files = (char **) calloc(MAX_FILE_SUPPORT, MAX_FILE_SUPPORT * sizeof(char *));

    if (0 > init_log_config(&logconf, argc, argv)) {
        exit(EXIT_FAILURE);
    }
    if (!SSTRISEMPTY(logconf.target) && !SSTRISEMPTY(logconf.interface)) {
        LOGGER_ERROR("%s", "cannot write to target and interface together. please choose one");
        exit(EXIT_FAILURE);
    }
        

    char *f = logconf.watch_files;
    if (!SSTRISEMPTY(f)) {
        while (f != NULL) {
            char *fprime = strsep(&f, ",");
            if (fprime != NULL) {
                files[num_files] = strdup(fprime);
                ++num_files;
            }
        }
    } else {
        LOGGER_ERROR("%s", "no files..no watch!");
        exit(EXIT_FAILURE);
    }

    if (0 > epoll_worker_init()) {
        LOGGER_ERROR("%s", "epoll_worker_init");
        exit(EXIT_FAILURE);
    }

    ribs_timer(60*1000, dump_stats);

    tab_event_fds = thashtable_create();
    delta_push    = thashtable_create();
    vmbuf_init(&write_buffer, 4096);
    vmbuf_init(&mb, 4096);


    if (SSTRISEMPTY(logconf.interface) && !SSTRISEMPTY(logconf.target)) {
        file_writer_make(&fw);

        if (0 > file_writer_init(&fw, logconf.target)) {
            LOGGER_ERROR("%s", "flie_writer");
            exit(EXIT_FAILURE);
        }
        write_to_file = true;
    } else if (!SSTRISEMPTY(logconf.interface)) {

        if (0 > http_client_pool_init(&client_pool, 20, 20)) {
            LOGGER_ERROR("http_client_pool_init");
            exit(EXIT_FAILURE);
        }

        memset(&eserv, 0, sizeof(eserv));

        vmbuf_reset(&write_buffer);
        _replace(logconf.interface, &write_buffer, "http://www.", "");
        _replace(logconf.interface, &write_buffer, "http://", "");

        char *interface = vmbuf_data(&write_buffer);
        eserv.context = ribs_strdup(strstr(interface, "/"));
        
        char *ln = strchr(interface, '/');
        ln = ribs_malloc_sprintf("%.*s", ((int)strlen(interface) - (int)strlen(ln)), interface);

        if (0 > parse_host_to_inet(ln, eserv.hostname, &eserv.server, &eserv.port)) {
            LOGGER_ERROR("%s", "server details invalid. cannot parse server");
            exit(EXIT_FAILURE);
        }
    } else {
        LOGGER_ERROR("%s", "no target defined. please use target or interface");
        exit(EXIT_FAILURE);
    }


    char _hostname[1024];
    gethostname(_hostname, 1024);
    hostname = ribs_strdup(_hostname);

    int wd = inotify_init1(IN_NONBLOCK);
    if (0 >= wd) {
        LOGGER_ERROR("%s", "failed to init inotify. cannot proceed. make sure you've inotify and is accessible to this user.");
        exit(EXIT_FAILURE);
    }

    if (!recursive_flush_events(wd, files, num_files)) {
        LOGGER_ERROR("%s", "collection failed");
        abort();
    }

    return 0;
}