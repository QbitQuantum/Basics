int
mls_elope_rpc(struct mls_net_ud_cln *cln,
    struct mls_elope_packet *req, struct mls_elope_packet *res, int reslen)
{
    int ret = 0;
    int sock = cln->sock;
    struct sockaddr_storage from;
    socklen_t fromlen;
    ssize_t len;

    fd_set mask;
    int width;
    int i, retry = 2, wait_sec = 2;

    FD_ZERO(&mask);
    FD_SET(sock, &mask);
    width = sock + 1;

    for (i = 0; i < retry; i++) {
        fd_set ready;
        struct timeval timeout;

        /* request */
        if ((len = SENDTO(sock, req, mls_elope_packet_get_length(req),
                          0, (struct sockaddr *)&(cln->to), cln->tolen)) == -1)
        {
            ret = -errno;
            LOG_ERR(MLS_LOG_DEFAULT_MODULE,
                    "sendto(%d): %s.\n", errno, strerror(errno));
            goto out;
        }

        ready = mask;
        timeout.tv_sec = wait_sec;
        timeout.tv_usec = 0;

        switch (select(width, (fd_set*)&ready, NULL, NULL, &timeout)) {
        case -1:
            ret = -errno;
            LOG_ERR(MLS_LOG_DEFAULT_MODULE,
                "select(%d,%s)\n", errno, strerror(errno));
            goto out;
        case 0:
            /* timeout, retry */
            break;

        default:
            if (FD_ISSET(sock, &ready)) {
                ssize_t len;

                /* response */
                fromlen = sizeof(from);
                if ((len = RECVFROM(sock, (char*)res, reslen, 
                                    0, (struct sockaddr*)&from, &fromlen)) == -1)
                {
                    ret = -errno;
                    LOG_ERR(MLS_LOG_DEFAULT_MODULE,
                            "recvfrom(%d): %s.\n", errno, strerror(errno));
                    goto out;
                }

                /* OK, response packet */
                ret = len;
                LOG_INFO(MLS_LOG_DEFAULT_MODULE,
                    "message rpc, ok(%d,%d)\n", i, ret);
                goto out;
            }
            break;
        }
    }

    /* retry over */
    ret = -1;
    LOG_ERR(MLS_LOG_DEFAULT_MODULE, "message rpc, retry over(%d,%d)\n", i, ret);

out:
    return ret;
}