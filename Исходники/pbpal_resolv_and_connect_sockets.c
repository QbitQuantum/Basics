enum pbpal_resolv_n_connect_result pbpal_resolv_and_connect(pubnub_t *pb)
{
    int error;
    char const* origin = PUBNUB_ORIGIN_SETTABLE ? pb->origin : PUBNUB_ORIGIN;

    PUBNUB_ASSERT(pb_valid_ctx_ptr(pb));
    PUBNUB_ASSERT_OPT((pb->state == PBS_READY) || (pb->state == PBS_WAIT_DNS_SEND)  || (pb->state == PBS_WAIT_DNS_RCV));

    if (PUBNUB_USE_ADNS) {
        struct sockaddr_in dest;
        int skt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (SOCKET_INVALID == skt) {
            return pbpal_resolv_resource_failure;
        }
        pb->options.use_blocking_io = false;
        pbpal_set_blocking_io(pb);
        dest.sin_family = AF_INET;
        dest.sin_port = htons(DNS_PORT);
        inet_pton(AF_INET, "8.8.8.8", &dest.sin_addr.s_addr);
        error = send_dns_query(skt, (struct sockaddr*)&dest, (unsigned char*)origin);
        if (error < 0) {
            socket_close(skt);
            return pbpal_resolv_failed_send;
        }
        else if (error > 0) {
            return pbpal_resolv_send_wouldblock;
        }
        pb->pal.socket = skt;
        return pbpal_resolv_sent;
    }
    else {
        struct addrinfo *result;
        struct addrinfo *it;
        struct addrinfo hint;

        hint.ai_socktype = SOCK_STREAM;
        hint.ai_family = AF_UNSPEC;
        hint.ai_protocol = hint.ai_flags = hint.ai_addrlen = 0;
        hint.ai_addr = NULL;
        hint.ai_canonname = NULL;
        hint.ai_next = NULL;
        error = getaddrinfo(origin, HTTP_PORT_STRING, &hint, &result);
        if (error != 0) {
            return pbpal_resolv_failed_processing;
        }

        for (it = result; it != NULL; it = it->ai_next) {
            pb->pal.socket = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
            if (pb->pal.socket == SOCKET_INVALID) {
                continue;
            }
            pbpal_set_blocking_io(pb);
            if (connect(pb->pal.socket, it->ai_addr, it->ai_addrlen) == SOCKET_ERROR) {
                if (socket_would_block()) {
                    error = 1;
                    break;
                }
                else {
                    PUBNUB_LOG_WARNING("socket connect() failed, will try another IP address, if available\n");
                    socket_close(pb->pal.socket);
                    pb->pal.socket = SOCKET_INVALID;
                    continue;
                }
            }
            break;
        }
        freeaddrinfo(result);

        if (NULL == it) {
            return pbpal_connect_failed;
        }

        socket_set_rcv_timeout(pb->pal.socket, pb->transaction_timeout_ms);

        return error ? pbpal_connect_wouldblock : pbpal_connect_success;
    }
}