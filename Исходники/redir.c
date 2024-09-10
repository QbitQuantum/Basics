static void remote_send_cb(EV_P_ ev_io *w, int revents)
{
    remote_ctx_t *remote_send_ctx = (remote_ctx_t *)w;
    remote_t *remote              = remote_send_ctx->remote;
    server_t *server              = remote->server;

    if (!remote_send_ctx->connected) {
        struct sockaddr_storage addr;
        socklen_t len = sizeof addr;
        int r         = getpeername(remote->fd, (struct sockaddr *)&addr, &len);
        if (r == 0) {
            remote_send_ctx->connected = 1;
            ev_io_stop(EV_A_ & remote_send_ctx->io);
            ev_timer_stop(EV_A_ & remote_send_ctx->watcher);

            // send destaddr
            buffer_t ss_addr_to_send;
            buffer_t *abuf = &ss_addr_to_send;
            balloc(abuf, BUF_SIZE);

            if (AF_INET6 == server->destaddr.ss_family) { // IPv6
                abuf->array[abuf->len++] = 4;          // Type 4 is IPv6 address

                size_t in6_addr_len = sizeof(struct in6_addr);
                memcpy(abuf->array + abuf->len,
                       &(((struct sockaddr_in6 *)&(server->destaddr))->sin6_addr),
                       in6_addr_len);
                abuf->len += in6_addr_len;
                memcpy(abuf->array + abuf->len,
                       &(((struct sockaddr_in6 *)&(server->destaddr))->sin6_port),
                       2);
            } else {                             // IPv4
                abuf->array[abuf->len++] = 1; // Type 1 is IPv4 address

                size_t in_addr_len = sizeof(struct in_addr);
                memcpy(abuf->array + abuf->len,
                       &((struct sockaddr_in *)&(server->destaddr))->sin_addr, in_addr_len);
                abuf->len += in_addr_len;
                memcpy(abuf->array + abuf->len,
                       &((struct sockaddr_in *)&(server->destaddr))->sin_port, 2);
            }
            abuf->len += 2;

            if (auth) {
                abuf->array[0] |= ONETIMEAUTH_FLAG;
                ss_onetimeauth(abuf, server->e_ctx->evp.iv, BUF_SIZE);
            }

            int err = ss_encrypt(abuf, server->e_ctx, BUF_SIZE);
            if (err) {
                bfree(abuf);
                LOGE("invalid password or cipher");
                close_and_free_remote(EV_A_ remote);
                close_and_free_server(EV_A_ server);
                return;
            }

            int s = send(remote->fd, abuf->array, abuf->len, 0);

            bfree(abuf);

            if (s < abuf->len) {
                LOGE("failed to send addr");
                close_and_free_remote(EV_A_ remote);
                close_and_free_server(EV_A_ server);
                return;
            }

            ev_io_start(EV_A_ & server->recv_ctx->io);
            ev_io_start(EV_A_ & remote->recv_ctx->io);

            return;
        } else {
            ERROR("getpeername");
            // not connected
            close_and_free_remote(EV_A_ remote);
            close_and_free_server(EV_A_ server);
            return;
        }
    } else {
        if (remote->buf->len == 0) {
            // close and free
            close_and_free_remote(EV_A_ remote);
            close_and_free_server(EV_A_ server);
            return;
        } else {
            // has data to send
            ssize_t s = send(remote->fd, remote->buf->array + remote->buf->idx,
                             remote->buf->len, 0);
            if (s < 0) {
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    ERROR("send");
                    // close and free
                    close_and_free_remote(EV_A_ remote);
                    close_and_free_server(EV_A_ server);
                }
                return;
            } else if (s < remote->buf->len) {
                // partly sent, move memory, wait for the next time to send
                remote->buf->len -= s;
                remote->buf->idx += s;
                return;
            } else {
                // all sent out, wait for reading
                remote->buf->len = 0;
                remote->buf->idx = 0;
                ev_io_stop(EV_A_ & remote_send_ctx->io);
                ev_io_start(EV_A_ & server->recv_ctx->io);
            }
        }
    }
}