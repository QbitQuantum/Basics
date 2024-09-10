int ncat_connect(void)
{
    nsock_pool mypool;
    int rc;

    /* Unless explicitely asked not to do so, ncat uses the
     * fallback nsock engine to maximize compatibility between
     * operating systems and the different use cases.
     */
    if (!o.nsock_engine)
        nsock_set_default_engine("select");

    /* Create an nsock pool */
    if ((mypool = nsp_new(NULL)) == NULL)
        bye("Failed to create nsock_pool.");

    if (o.debug >= 6)
        nsock_set_loglevel(mypool, NSOCK_LOG_DBG_ALL);
    else if (o.debug >= 3)
        nsock_set_loglevel(mypool, NSOCK_LOG_DBG);
    else if (o.debug >= 1)
        nsock_set_loglevel(mypool, NSOCK_LOG_INFO);
    else
        nsock_set_loglevel(mypool, NSOCK_LOG_ERROR);

    /* Allow connections to broadcast addresses. */
    nsp_setbroadcast(mypool, 1);

#ifdef HAVE_OPENSSL
    set_ssl_ctx_options((SSL_CTX *) nsp_ssl_init(mypool));
#endif

    if (httpconnect.storage.ss_family == AF_UNSPEC
             && socksconnect.storage.ss_family == AF_UNSPEC) {
        /* A non-proxy connection. Create an iod for a new socket. */
        cs.sock_nsi = nsi_new(mypool, NULL);
        if (cs.sock_nsi == NULL)
            bye("Failed to create nsock_iod.");

        if (nsi_set_hostname(cs.sock_nsi, o.target) == -1)
            bye("Failed to set hostname on iod.");

#if HAVE_SYS_UN_H
        /* For DGRAM UNIX socket we have to use source socket */
        if (o.af == AF_UNIX && o.proto == IPPROTO_UDP)
        {
            if (srcaddr.storage.ss_family != AF_UNIX) {
                char *tmp_name = NULL;
                /* If no source socket was specified, we have to create temporary one. */
                if ((tmp_name = tempnam(NULL, "ncat.")) == NULL)
                    bye("Failed to create name for temporary DGRAM source Unix domain socket (tempnam).");

                srcaddr.un.sun_family = AF_UNIX;
                strncpy(srcaddr.un.sun_path, tmp_name, sizeof(srcaddr.un.sun_path));
                free (tmp_name);
            }
            nsi_set_localaddr(cs.sock_nsi, &srcaddr.storage, SUN_LEN((struct sockaddr_un *)&srcaddr.storage));

            if (o.verbose)
                loguser("[%s] used as source DGRAM Unix domain socket.\n", srcaddr.un.sun_path);
        }
        else
#endif
        if (srcaddr.storage.ss_family != AF_UNSPEC)
            nsi_set_localaddr(cs.sock_nsi, &srcaddr.storage, sizeof(srcaddr.storage));

        if (o.numsrcrtes) {
            unsigned char *ipopts = NULL;
            size_t ipoptslen = 0;

            if (o.af != AF_INET)
                bye("Sorry, -g can only currently be used with IPv4.");
            ipopts = buildsrcrte(targetss.in.sin_addr, o.srcrtes, o.numsrcrtes, o.srcrteptr, &ipoptslen);

            nsi_set_ipoptions(cs.sock_nsi, ipopts, ipoptslen);
            free(ipopts); /* Nsock has its own copy */
        }

#if HAVE_SYS_UN_H
        if (o.af == AF_UNIX) {
            if (o.proto == IPPROTO_UDP) {
                nsock_connect_unixsock_datagram(mypool, cs.sock_nsi, connect_handler, NULL,
                                                &targetss.sockaddr,
                                                SUN_LEN((struct sockaddr_un *)&targetss.sockaddr));
            } else {
                nsock_connect_unixsock_stream(mypool, cs.sock_nsi, connect_handler, o.conntimeout,
                                              NULL, &targetss.sockaddr,
                                              SUN_LEN((struct sockaddr_un *)&targetss.sockaddr));
            }
        } else
#endif
        if (o.proto == IPPROTO_UDP) {
            nsock_connect_udp(mypool, cs.sock_nsi, connect_handler,
                              NULL, &targetss.sockaddr, targetsslen,
                              inet_port(&targetss));
        }
#ifdef HAVE_OPENSSL
        else if (o.proto == IPPROTO_SCTP && o.ssl) {
            nsock_connect_ssl(mypool, cs.sock_nsi, connect_handler,
                              o.conntimeout, NULL,
                              &targetss.sockaddr, targetsslen,
                              IPPROTO_SCTP, inet_port(&targetss),
                              NULL);
        }
#endif
        else if (o.proto == IPPROTO_SCTP) {
            nsock_connect_sctp(mypool, cs.sock_nsi, connect_handler,
                              o.conntimeout, NULL,
                              &targetss.sockaddr, targetsslen,
                              inet_port(&targetss));
        }
#ifdef HAVE_OPENSSL
        else if (o.ssl) {
            nsock_connect_ssl(mypool, cs.sock_nsi, connect_handler,
                              o.conntimeout, NULL,
                              &targetss.sockaddr, targetsslen,
                              IPPROTO_TCP, inet_port(&targetss),
                              NULL);
        }
#endif
        else {
            nsock_connect_tcp(mypool, cs.sock_nsi, connect_handler,
                              o.conntimeout, NULL,
                              &targetss.sockaddr, targetsslen,
                              inet_port(&targetss));
        }
    } else {
        /* A proxy connection. */
        static int connect_socket;
        int len;
        char *line;
        size_t n;

        if (httpconnect.storage.ss_family != AF_UNSPEC) {
            connect_socket = do_proxy_http();
            if (connect_socket == -1)
                return 1;
        } else if (socksconnect.storage.ss_family != AF_UNSPEC) {
            struct socket_buffer stateful_buf;
            struct socks4_data socks4msg;
            char socksbuf[8];

            connect_socket = do_connect(SOCK_STREAM);
            if (connect_socket == -1) {
                loguser("Proxy connection failed: %s.\n", socket_strerror(socket_errno()));
                return 1;
            }

            socket_buffer_init(&stateful_buf, connect_socket);

            if (o.verbose) {
                loguser("Connected to proxy %s:%hu\n", inet_socktop(&targetss),
                    inet_port(&targetss));
            }

            /* Fill the socks4_data struct */
            zmem(&socks4msg, sizeof(socks4msg));
            socks4msg.version = SOCKS4_VERSION;
            socks4msg.type = SOCKS_CONNECT;
            socks4msg.port = socksconnect.in.sin_port;
            socks4msg.address = socksconnect.in.sin_addr.s_addr;
            if (o.proxy_auth)
                Strncpy(socks4msg.username, (char *) o.proxy_auth, sizeof(socks4msg.username));

            len = 8 + strlen(socks4msg.username) + 1;

            if (send(connect_socket, (char *) &socks4msg, len, 0) < 0) {
                loguser("Error sending proxy request: %s.\n", socket_strerror(socket_errno()));
                return 1;
            }
            /* The size of the socks4 response is 8 bytes. So read exactly
               8 bytes from the buffer */
            if (socket_buffer_readcount(&stateful_buf, socksbuf, 8) < 0) {
                loguser("Error: short reponse from proxy.\n");
                return 1;
            }
            if (socksbuf[1] != 90) {
                loguser("Proxy connection failed.\n");
                return 1;
            }

            /* Clear out whatever is left in the socket buffer which may be
               already sent by proxy server along with http response headers. */
            line = socket_buffer_remainder(&stateful_buf, &n);
            /* Write the leftover data to stdout. */
            Write(STDOUT_FILENO, line, n);
        }

        /* Once the proxy negotiation is done, Nsock takes control of the
           socket. */
        cs.sock_nsi = nsi_new2(mypool, connect_socket, NULL);

        /* Create IOD for nsp->stdin */
        if ((cs.stdin_nsi = nsi_new2(mypool, 0, NULL)) == NULL)
            bye("Failed to create stdin nsiod.");

        post_connect(mypool, cs.sock_nsi);
    }

    /* connect */
    rc = nsock_loop(mypool, -1);

    if (o.verbose) {
        struct timeval end_time;
        double time;
        gettimeofday(&end_time, NULL);
        time = TIMEVAL_MSEC_SUBTRACT(end_time, start_time) / 1000.0;
        loguser("%lu bytes sent, %lu bytes received in %.2f seconds.\n",
            nsi_get_write_count(cs.sock_nsi),
            nsi_get_read_count(cs.sock_nsi), time);
    }

#if HAVE_SYS_UN_H
    if (o.af == AF_UNIX && o.proto == IPPROTO_UDP) {
        if (o.verbose)
            loguser("Deleting source DGRAM Unix domain socket. [%s]\n", srcaddr.un.sun_path);
        unlink(srcaddr.un.sun_path);
    }
#endif

    nsp_delete(mypool);

    return rc == NSOCK_LOOP_ERROR ? 1 : 0;
}