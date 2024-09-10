static BOOL send_ssl_chunk(netconn_t *conn, const void *msg, size_t size)
{
    SecBuffer bufs[4] = {
        {conn->ssl_sizes.cbHeader, SECBUFFER_STREAM_HEADER, conn->ssl_buf},
        {size,  SECBUFFER_DATA, conn->ssl_buf+conn->ssl_sizes.cbHeader},
        {conn->ssl_sizes.cbTrailer, SECBUFFER_STREAM_TRAILER, conn->ssl_buf+conn->ssl_sizes.cbHeader+size},
        {0, SECBUFFER_EMPTY, NULL}
    };
    SecBufferDesc buf_desc = {SECBUFFER_VERSION, sizeof(bufs)/sizeof(*bufs), bufs};
    SECURITY_STATUS res;

    memcpy(bufs[1].pvBuffer, msg, size);
    res = EncryptMessage(&conn->ssl_ctx, 0, &buf_desc, 0);
    if(res != SEC_E_OK) {
        WARN("EncryptMessage failed\n");
        return FALSE;
    }

    if(sock_send(conn->socket, conn->ssl_buf, bufs[0].cbBuffer+bufs[1].cbBuffer+bufs[2].cbBuffer, 0) < 1) {
        WARN("send failed\n");
        return FALSE;
    }

    return TRUE;
}