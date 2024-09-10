int main( int argc, char *argv[]) {
    int c = 0;
    int ret_val = 0;
    int port = 0;
    char network[128];
    char *file = NULL;
    char *iface = NULL;
    char *mcast_addr = NULL;
    int bfd = 0;
    network[0] = '\0';

#ifdef UDPTEST
    int sockfd = 0;
#else
    pgm_error_t* pgm_err = NULL;
    pgm_sock_t *pgm_sock;
    pthread_t nak_thread;
#endif

    while((c = getopt(argc, argv, ":hm:i:p:f:")) != -1) {
        switch (c) {
        case 'm':
            mcast_addr = optarg;
            break;
        case 'i':
            iface = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case 'h':
        case '?':
            print_usage();
            break;
        default:
            print_usage();
            break;
        }
    }

    if(optind != argc-1) {
        PRINT_ERR("Please provide the path to a file you want to send!");
        ret_val = -1;
        goto ret_error;
    } else {
        file = argv[optind];
    }

    if (iface) {
        char *ifaddr = pftp_inet_iftoa(iface);
        if (strlen(ifaddr) > 0) {
            strncat(network, ifaddr, 128);
            strncat(network, ";", 128);
        }
    }

    if (mcast_addr) {
        strncat(network, mcast_addr, 128);
    } else {
        strncat(network, PFTP_DEFAULT_MCAST_ADDR, 128);
    }

#ifdef UDPTEST
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(PFTP_DEFAULT_MCAST_ADDR);
    servaddr.sin_port = port ? htons(port) : htons(PFTP_UDP_PORT);
#else

    if (0 != pftp_create(1, network, port, &pgm_sock)) {
        ret_val = -1;
        goto ret_error;
    }

    int pgm_status;

    /* Start NAK receiver thread */
    m_run_receiver = 1;
    pthread_create(&nak_thread, NULL, nak_routine, (void*)pgm_sock);
#endif

    char buf[PGMBUF_SIZE];
    buf[0] = '\0';

    struct stat fstat;
    if (-1 == stat(file, &fstat)) {
        PRINT_ERR("Couldn't stat file: %s", strerror(errno));
        ret_val = -1;
        goto ret_error;
    }

    char *fname = strrchr(file, '/');
    if (!fname) {
        fname = file;
    } else {
        fname = fname+1;
    }

    memset(buf, 0, PGMBUF_SIZE);
    snprintf(buf, PGMBUF_SIZE, CMD_SEND_FILE" %ld %s", fstat.st_size, fname);
    PRINT_DBG("Sending file with command: %s", buf);

    size_t bytes_written;
    int bytes_read;

#ifdef UDPTEST
    bytes_written = sendto(sockfd, buf, strlen(buf)+1, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if (bytes_written != strlen(buf)+1) {
        PRINT_ERR("Couldn't send file transfer command! %s", strerror(errno));
        ret_val = -1;
        goto ret_error;
    }
#else
    pgm_status = pgm_status = pgm_send(pgm_sock, buf, strlen(buf)+1, &bytes_written);
    if (pgm_status != PGM_IO_STATUS_NORMAL) {
        PRINT_ERR("Couldn't send file transfer command!");
        ret_val = -1;
        goto ret_error;
    }
#endif

    bfd = open(file, O_RDONLY);
    if (bfd < 0) {
        PRINT_ERR("Couldn't open file for reading! %s", strerror(errno));
        ret_val = -1;
        goto ret_error;
    }

    int fds = 0;
    fd_set writefds;
    fd_set readfds;

    bytes_read = read(bfd, buf, PGMBUF_SIZE);
    while (bytes_read > 0) {

#ifdef UDPTEST

        bytes_written = sendto(sockfd, buf, bytes_read, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

#else
        struct timeval tv;
        pgm_status = pgm_send(pgm_sock, buf, bytes_read, &bytes_written);

        //PRINT_DBG("pgm_status: %d", pgm_status);

        switch (pgm_status) {

        case PGM_IO_STATUS_NORMAL :
        {
#endif
            if (bytes_written != bytes_read) {
                PRINT_ERR("Error sending file!");
                ret_val = -1;
                goto ret_error;
            }
            bytes_read = read(bfd, buf, PGMBUF_SIZE);

#ifdef UDPTEST
            struct timespec ts = {0, 35000};
            nanosleep(&ts, NULL);
#else
        } break;
        case PGM_IO_STATUS_TIMER_PENDING:
        {
            socklen_t optlen = sizeof(tv);
            pgm_getsockopt (pgm_sock, IPPROTO_PGM, PGM_TIME_REMAIN, &tv, &optlen);
            if (0 == (tv.tv_sec * 1000) + ((tv.tv_usec + 500) / 1000))
                break;
            goto block;
        }
        case PGM_IO_STATUS_RATE_LIMITED :
        {
            socklen_t optlen = sizeof(tv);
            pgm_getsockopt (pgm_sock, IPPROTO_PGM, PGM_RATE_REMAIN, &tv, &optlen);
            if (0 == (tv.tv_sec * 1000) + ((tv.tv_usec + 500) / 1000))
                break;
            /* No accidental fallthrough! */
        }
        case PGM_IO_STATUS_CONGESTION :
        case PGM_IO_STATUS_WOULD_BLOCK :
block:
        {
            FD_ZERO(&writefds);
            pgm_select_info(pgm_sock, NULL, &writefds, &fds);
            fds = select(fds, NULL, &writefds, NULL, pgm_status == PGM_IO_STATUS_WOULD_BLOCK ? NULL : &tv);
        } break;
        default:
            PRINT_ERR("Send error!");
            ret_val = -1;
            goto ret_error;
            break;
        }
#endif
    }

#ifndef UDPTEST
    pthread_mutex_lock(&m_pftp_mutex);
    m_run_receiver = 0;
    pthread_mutex_unlock(&m_pftp_mutex);
    pthread_join(nak_thread, NULL);
    pthread_mutex_destroy(&m_pftp_mutex);
#endif

    goto ret_good;

ret_error:
    PRINT_DBG("Exit error");
    goto ret;
ret_good:
    PRINT_DBG("Exit good");
ret:
    if (bfd > 0)
        close(bfd);
#ifdef UDPTEST
    if (sockfd > 0)
        close(sockfd);
#else
    if (pgm_sock) {
        pftp_stop(pgm_sock);
    }
#endif
    return ret_val;
}