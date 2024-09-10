static ngx_int_t
ngx_event_post_one_udp_recv(ngx_listening_t *ls, ngx_udp_recv_event_t *event)
{
    int        rc;
    DWORD      flags;
    WSABUF     wsabuf;
    ngx_err_t  err;

    event->pool = ngx_create_pool(ls->pool_size, ngx_cycle->log);
    if (event->pool == NULL) {
        return NGX_ERROR;
    }

    event->buffer = ngx_create_temp_buf(event->pool, ls->udp_recv_buffer_size);
    if (event->buffer == NULL) {
        ngx_destroy_pool(event->pool);
        return NGX_ERROR;
    }

    wsabuf.buf = (CHAR *) event->buffer->last;
    wsabuf.len = (DWORD) (event->buffer->end - event->buffer->last);

    flags = 0;

    event->socklen = NGX_SOCKADDRLEN;

    rc = WSARecvFrom(ls->connection->fd, &wsabuf, 1, NULL, &flags,
                     (struct sockaddr *) event->sockaddr,
                     (LPINT) &event->socklen,
                     (LPWSAOVERLAPPED) &event->event.ovlp, NULL);

    err = ngx_socket_errno;

    if (rc == SOCKET_ERROR && err != WSA_IO_PENDING) {
        ngx_log_error(NGX_LOG_ALERT, ngx_cycle->log, err,
                      "WSARecvFrom() failed");
        return NGX_ERROR;
    }

    return NGX_OK;
}