int
main(int argc, char **argv)
{
    struct sockaddr_in6 sin6;
    int rc, fd, i, opt;
    time_t expiry_time, source_expiry_time, kernel_dump_time;
    const char **config_files = NULL;
    int num_config_files = 0;
    void *vrc;
    unsigned int seed;
    struct interface *ifp;

    gettime(&now);

    rc = read_random_bytes(&seed, sizeof(seed));
    if(rc < 0) {
        perror("read(random)");
        seed = 42;
    }

    seed ^= (now.tv_sec ^ now.tv_usec);
    srandom(seed);

    parse_address("ff02:0:0:0:0:0:1:6", protocol_group, NULL);
    protocol_port = 6696;
    change_smoothing_half_life(4);

    while(1) {
        opt = getopt(argc, argv, "m:p:h:H:i:k:A:sruS:d:g:lwz:M:t:T:c:C:DL:I:");
        if(opt < 0)
            break;

        switch(opt) {
        case 'm':
            rc = parse_address(optarg, protocol_group, NULL);
            if(rc < 0)
                goto usage;
            if(protocol_group[0] != 0xff) {
                fprintf(stderr,
                        "%s is not a multicast address\n", optarg);
                goto usage;
            }
            if(protocol_group[1] != 2) {
                fprintf(stderr,
                        "Warning: %s is not a link-local multicast address\n",
                        optarg);
            }
            break;
        case 'p':
            protocol_port = parse_nat(optarg);
            if(protocol_port <= 0 || protocol_port > 0xFFFF)
                goto usage;
            break;
        case 'h':
            default_wireless_hello_interval = parse_thousands(optarg);
            if(default_wireless_hello_interval <= 0 ||
               default_wireless_hello_interval > 0xFFFF * 10)
                goto usage;
            break;
        case 'H':
            default_wired_hello_interval = parse_thousands(optarg);
            if(default_wired_hello_interval <= 0 ||
               default_wired_hello_interval > 0xFFFF * 10)
                goto usage;
            break;
        case 'k':
            kernel_metric = parse_nat(optarg);
            if(kernel_metric < 0 || kernel_metric > 0xFFFF)
                goto usage;
            break;
        case 'A':
            allow_duplicates = parse_nat(optarg);
            if(allow_duplicates < 0 || allow_duplicates > 0xFFFF)
                goto usage;
            break;
        case 's':
            split_horizon = 0;
            break;
        case 'r':
            random_id = 1;
            break;
        case 'u':
            keep_unfeasible = 1;
            break;
        case 'S':
            state_file = optarg;
            break;
        case 'd':
            debug = parse_nat(optarg);
            if(debug < 0)
                goto usage;
            break;
        case 'g':
#ifdef NO_LOCAL_INTERFACE
            fprintf(stderr, "Warning: no local interface in this version.\n");
#else
            local_server_port = parse_nat(optarg);
            if(local_server_port <= 0 || local_server_port > 0xFFFF)
                goto usage;
#endif
            break;
        case 'l':
            link_detect = 1;
            break;
        case 'w':
            all_wireless = 1;
            break;
        case 'z':
            {
                char *comma;
                diversity_kind = (int)strtol(optarg, &comma, 0);
                if(*comma == '\0')
                    diversity_factor = 128;
                else if(*comma == ',')
                    diversity_factor = parse_nat(comma + 1);
                else
                    goto usage;
                if(diversity_factor <= 0 || diversity_factor > 256)
                    goto usage;
            }
            break;
        case 'M': {
            int l = parse_nat(optarg);
            if(l < 0 || l > 3600)
                goto usage;
            change_smoothing_half_life(l);
            break;
        }
        case 't':
            export_table = parse_nat(optarg);
            if(export_table < 0 || export_table > 0xFFFF)
                goto usage;
            break;
        case 'T':
            if(add_import_table(parse_nat(optarg)))
                goto usage;
            break;
        case 'c':
            config_files = realloc(config_files,
                                   (num_config_files + 1) * sizeof(char*));
            if(config_files == NULL) {
                fprintf(stderr, "Couldn't allocate config file.\n");
                exit(1);
            }
            config_files[num_config_files++] = optarg;
            break;
        case 'C':
            rc = parse_config_from_string(optarg);
            if(rc < 0) {
                fprintf(stderr,
                        "Couldn't parse configuration from command line.\n");
                exit(1);
            }
            break;
        case 'D':
            do_daemonise = 1;
            break;
        case 'L':
            logfile = optarg;
            break;
        case 'I':
            pidfile = optarg;
            break;
        default:
            goto usage;
        }
    }

    if(num_config_files == 0) {
        if(access("/etc/babeld.conf", F_OK) >= 0) {
            config_files = malloc(sizeof(char*));
            if(config_files == NULL) {
                fprintf(stderr, "Couldn't allocate config file.\n");
                exit(1);
            }
            config_files[num_config_files++] = "/etc/babeld.conf";
        }
    }

    for(i = 0; i < num_config_files; i++) {
        int line;
        rc = parse_config_from_file(config_files[i], &line);
        if(rc < 0) {
            fprintf(stderr,
                    "Couldn't parse configuration from file %s "
                    "(error at line %d).\n",
                    config_files[i], line);
            exit(1);
        }
    }

    free(config_files);

    if(default_wireless_hello_interval <= 0)
        default_wireless_hello_interval = 4000;
    default_wireless_hello_interval = MAX(default_wireless_hello_interval, 5);

    if(default_wired_hello_interval <= 0)
        default_wired_hello_interval = 4000;
    default_wired_hello_interval = MAX(default_wired_hello_interval, 5);

    resend_delay = 2000;
    resend_delay = MIN(resend_delay, default_wireless_hello_interval / 2);
    resend_delay = MIN(resend_delay, default_wired_hello_interval / 2);
    resend_delay = MAX(resend_delay, 20);

    if(do_daemonise) {
        if(logfile == NULL)
            logfile = "/var/log/babeld.log";
    }

    rc = reopen_logfile();
    if(rc < 0) {
        perror("reopen_logfile()");
        exit(1);
    }

    fd = open("/dev/null", O_RDONLY);
    if(fd < 0) {
        perror("open(null)");
        exit(1);
    }

    rc = dup2(fd, 0);
    if(rc < 0) {
        perror("dup2(null, 0)");
        exit(1);
    }

    close(fd);

    if(do_daemonise) {
        rc = daemonise();
        if(rc < 0) {
            perror("daemonise");
            exit(1);
        }
    }

    if(pidfile && pidfile[0] != '\0') {
        int pfd, len;
        char buf[100];

        len = snprintf(buf, 100, "%lu", (unsigned long)getpid());
        if(len < 0 || len >= 100) {
            perror("snprintf(getpid)");
            exit(1);
        }

        pfd = open(pidfile, O_WRONLY | O_CREAT | O_EXCL, 0644);
        if(pfd < 0) {
            char buf[40];
            snprintf(buf, 40, "creat(%s)", pidfile);
            buf[39] = '\0';
            perror(buf);
            exit(1);
        }

        rc = write(pfd, buf, len);
        if(rc < len) {
            perror("write(pidfile)");
            goto fail_pid;
        }

        close(pfd);
    }

    rc = kernel_setup(1);
    if(rc < 0) {
        fprintf(stderr, "kernel_setup failed.\n");
        goto fail_pid;
    }

    rc = kernel_setup_socket(1);
    if(rc < 0) {
        fprintf(stderr, "kernel_setup_socket failed.\n");
        kernel_setup(0);
        goto fail_pid;
    }

    rc = finalise_config();
    if(rc < 0) {
        fprintf(stderr, "Couldn't finalise configuration.\n");
        goto fail;
    }

    for(i = optind; i < argc; i++) {
        vrc = add_interface(argv[i], NULL);
        if(vrc == NULL)
            goto fail;
    }

    if(interfaces == NULL) {
        fprintf(stderr, "Eek... asked to run on no interfaces!\n");
        goto fail;
    }

    if(random_id)
        goto random_id;

    FOR_ALL_INTERFACES(ifp) {
        /* ifp->ifindex is not necessarily valid at this point */
        int ifindex = if_nametoindex(ifp->name);
        if(ifindex > 0) {
            unsigned char eui[8];
            rc = if_eui64(ifp->name, ifindex, eui);
            if(rc < 0)
                continue;
            memcpy(myid, eui, 8);
            goto have_id;
        }
    }

    /* We failed to get a global EUI64 from the interfaces we were given.
       Let's try to find an interface with a MAC address. */
    for(i = 1; i < 256; i++) {
        char buf[IF_NAMESIZE], *ifname;
        unsigned char eui[8];
        ifname = if_indextoname(i, buf);
        if(ifname == NULL)
            continue;
        rc = if_eui64(ifname, i, eui);
        if(rc < 0)
            continue;
        memcpy(myid, eui, 8);
        goto have_id;
    }

    fprintf(stderr,
            "Warning: couldn't find router id -- using random value.\n");

 random_id:
    rc = read_random_bytes(myid, 8);
    if(rc < 0) {
        perror("read(random)");
        goto fail;
    }
    /* Clear group and global bits */
    myid[0] &= ~3;

 have_id:
    myseqno = (random() & 0xFFFF);

    fd = open(state_file, O_RDONLY);
    if(fd < 0 && errno != ENOENT)
        perror("open(babel-state)");
    rc = unlink(state_file);
    if(fd >= 0 && rc < 0) {
        perror("unlink(babel-state)");
        /* If we couldn't unlink it, it's probably stale. */
        close(fd);
        fd = -1;
    }
    if(fd >= 0) {
        char buf[100];
        char buf2[100];
        int s;
        long t;
        rc = read(fd, buf, 99);
        if(rc < 0) {
            perror("read(babel-state)");
        } else {
            buf[rc] = '\0';
            rc = sscanf(buf, "%99s %d %ld\n", buf2, &s, &t);
            if(rc == 3 && s >= 0 && s <= 0xFFFF) {
                unsigned char sid[8];
                rc = parse_eui64(buf2, sid);
                if(rc < 0) {
                    fprintf(stderr, "Couldn't parse babel-state.\n");
                } else {
                    struct timeval realnow;
                    debugf("Got %s %d %ld from babel-state.\n",
                           format_eui64(sid), s, t);
                    gettimeofday(&realnow, NULL);
                    if(memcmp(sid, myid, 8) == 0)
                        myseqno = seqno_plus(s, 1);
                    else if(!random_id)
                        fprintf(stderr, "ID mismatch in babel-state.\n");
                }
            } else {
                fprintf(stderr, "Couldn't parse babel-state.\n");
            }
        }
        close(fd);
        fd = -1;
    }

    protocol_socket = babel_socket(protocol_port);
    if(protocol_socket < 0) {
        perror("Couldn't create link local socket");
        goto fail;
    }

#ifndef NO_LOCAL_INTERFACE
    if(local_server_port >= 0) {
        local_server_socket = tcp_server_socket(local_server_port, 1);
        if(local_server_socket < 0) {
            perror("local_server_socket");
            goto fail;
        }
    }
#endif

    init_signals();
    rc = resize_receive_buffer(1500);
    if(rc < 0)
        goto fail;
    if(receive_buffer == NULL)
        goto fail;

    check_interfaces();

    rc = check_xroutes(0);
    if(rc < 0)
        fprintf(stderr, "Warning: couldn't check exported routes.\n");

    kernel_routes_changed = 0;
    kernel_link_changed = 0;
    kernel_addr_changed = 0;
    kernel_dump_time = now.tv_sec + roughly(30);
    schedule_neighbours_check(5000, 1);
    schedule_interfaces_check(30000, 1);
    expiry_time = now.tv_sec + roughly(30);
    source_expiry_time = now.tv_sec + roughly(300);

    /* Make some noise so that others notice us, and send retractions in
       case we were restarted recently */
    FOR_ALL_INTERFACES(ifp) {
        if(!if_up(ifp))
            continue;
        /* Apply jitter before we send the first message. */
        usleep(roughly(10000));
        gettime(&now);
        send_hello(ifp);
        send_wildcard_retraction(ifp);
    }

    FOR_ALL_INTERFACES(ifp) {
        if(!if_up(ifp))
            continue;
        usleep(roughly(10000));
        gettime(&now);
        send_hello(ifp);
        send_wildcard_retraction(ifp);
        send_self_update(ifp);
        send_request(ifp, NULL, 0);
        flushupdates(ifp);
        flushbuf(ifp);
    }

    debugf("Entering main loop.\n");

    while(1) {
        struct timeval tv;
        fd_set readfds;

        gettime(&now);

        tv = check_neighbours_timeout;
        timeval_min(&tv, &check_interfaces_timeout);
        timeval_min_sec(&tv, expiry_time);
        timeval_min_sec(&tv, source_expiry_time);
        timeval_min_sec(&tv, kernel_dump_time);
        timeval_min(&tv, &resend_time);
        FOR_ALL_INTERFACES(ifp) {
            if(!if_up(ifp))
                continue;
            timeval_min(&tv, &ifp->flush_timeout);
            timeval_min(&tv, &ifp->hello_timeout);
            timeval_min(&tv, &ifp->update_timeout);
            timeval_min(&tv, &ifp->update_flush_timeout);
        }
        timeval_min(&tv, &unicast_flush_timeout);
        FD_ZERO(&readfds);
        if(timeval_compare(&tv, &now) > 0) {
            int maxfd = 0;
            timeval_minus(&tv, &tv, &now);
            FD_SET(protocol_socket, &readfds);
            maxfd = MAX(maxfd, protocol_socket);
            if(kernel_socket < 0) kernel_setup_socket(1);
            if(kernel_socket >= 0) {
                FD_SET(kernel_socket, &readfds);
                maxfd = MAX(maxfd, kernel_socket);
            }
#ifndef NO_LOCAL_INTERFACE
            if(local_server_socket >= 0 &&
               num_local_sockets < MAX_LOCAL_SOCKETS) {
                FD_SET(local_server_socket, &readfds);
                maxfd = MAX(maxfd, local_server_socket);
            }
            for(i = 0; i < num_local_sockets; i++) {
                FD_SET(local_sockets[i], &readfds);
                maxfd = MAX(maxfd, local_sockets[i]);
            }
#endif
            rc = select(maxfd + 1, &readfds, NULL, NULL, &tv);
            if(rc < 0) {
                if(errno != EINTR) {
                    perror("select");
                    sleep(1);
                }
                rc = 0;
                FD_ZERO(&readfds);
            }
        }

        gettime(&now);

        if(exiting)
            break;

        if(kernel_socket >= 0 && FD_ISSET(kernel_socket, &readfds))
            kernel_callback(kernel_routes_callback, NULL);

        if(FD_ISSET(protocol_socket, &readfds)) {
            rc = babel_recv(protocol_socket,
                            receive_buffer, receive_buffer_size,
                            (struct sockaddr*)&sin6, sizeof(sin6));
            if(rc < 0) {
                if(errno != EAGAIN && errno != EINTR) {
                    perror("recv");
                    sleep(1);
                }
            } else {
                FOR_ALL_INTERFACES(ifp) {
                    if(!if_up(ifp))
                        continue;
                    if(ifp->ifindex == sin6.sin6_scope_id) {
                        parse_packet((unsigned char*)&sin6.sin6_addr, ifp,
                                     receive_buffer, rc);
                        VALGRIND_MAKE_MEM_UNDEFINED(receive_buffer,
                                                    receive_buffer_size);
                        break;
                    }
                }
            }
        }

#ifndef NO_LOCAL_INTERFACE
        accept_local_connections(&readfds);

        i = 0;
        while(i < num_local_sockets) {
            if(FD_ISSET(local_sockets[i], &readfds)) {
                rc = local_read(local_sockets[i]);
                if(rc <= 0) {
                    if(rc < 0) {
                        if(errno == EINTR)
                            continue;
                        perror("read(local_socket)");
                    }
                    close(local_sockets[i]);
                    local_sockets[i] = local_sockets[--num_local_sockets];
                    continue;
                }
            }
            i++;
        }
#endif

        if(reopening) {
            kernel_dump_time = now.tv_sec;
            check_neighbours_timeout = now;
            expiry_time = now.tv_sec;
            rc = reopen_logfile();
            if(rc < 0) {
                perror("reopen_logfile");
                break;
            }
            reopening = 0;
        }

        if(kernel_link_changed || kernel_addr_changed) {
            check_interfaces();
            kernel_link_changed = 0;
        }

        if(kernel_routes_changed || kernel_addr_changed ||
           now.tv_sec >= kernel_dump_time) {
            rc = check_xroutes(1);
            if(rc < 0)
                fprintf(stderr, "Warning: couldn't check exported routes.\n");
            kernel_routes_changed = kernel_addr_changed = 0;
            if(kernel_socket >= 0)
                kernel_dump_time = now.tv_sec + roughly(300);
            else
                kernel_dump_time = now.tv_sec + roughly(30);
        }

        if(timeval_compare(&check_neighbours_timeout, &now) < 0) {
            int msecs;
            msecs = check_neighbours();
            /* Multiply by 3/2 to allow neighbours to expire. */
            msecs = MAX(3 * msecs / 2, 10);
            schedule_neighbours_check(msecs, 1);
        }

        if(timeval_compare(&check_interfaces_timeout, &now) < 0) {
            check_interfaces();
            schedule_interfaces_check(30000, 1);
        }

        if(now.tv_sec >= expiry_time) {
            expire_routes();
            expire_resend();
            expiry_time = now.tv_sec + roughly(30);
        }

        if(now.tv_sec >= source_expiry_time) {
            expire_sources();
            source_expiry_time = now.tv_sec + roughly(300);
        }

        FOR_ALL_INTERFACES(ifp) {
            if(!if_up(ifp))
                continue;
            if(timeval_compare(&now, &ifp->hello_timeout) >= 0)
                send_hello(ifp);
            if(timeval_compare(&now, &ifp->update_timeout) >= 0)
                send_update(ifp, 0, NULL, 0);
            if(timeval_compare(&now, &ifp->update_flush_timeout) >= 0)
                flushupdates(ifp);
        }

        if(resend_time.tv_sec != 0) {
            if(timeval_compare(&now, &resend_time) >= 0)
                do_resend();
        }

        if(unicast_flush_timeout.tv_sec != 0) {
            if(timeval_compare(&now, &unicast_flush_timeout) >= 0)
                flush_unicast(1);
        }

        FOR_ALL_INTERFACES(ifp) {
            if(!if_up(ifp))
                continue;
            if(ifp->flush_timeout.tv_sec != 0) {
                if(timeval_compare(&now, &ifp->flush_timeout) >= 0)
                    flushbuf(ifp);
            }
        }

        if(UNLIKELY(debug || dumping)) {
            dump_tables(stdout);
            dumping = 0;
        }
    }