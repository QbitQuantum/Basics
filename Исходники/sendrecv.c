APR_DECLARE(apr_status_t) apr_socket_send(apr_socket_t *sock, const char *buf,
                                          apr_size_t *len)
{
    apr_ssize_t rv;
    WSABUF wsaData;
    int lasterror;
    DWORD dwBytes = 0;

    wsaData.len = (u_long)*len;
    wsaData.buf = (char*) buf;

#ifndef _WIN32_WCE
    rv = WSASend(sock->socketdes, &wsaData, 1, &dwBytes, 0, NULL, NULL);
#else
    rv = send(sock->socketdes, wsaData.buf, wsaData.len, 0);
    dwBytes = rv;
#endif
    if (rv == SOCKET_ERROR) {
        lasterror = apr_get_netos_error();
        *len = 0;
        return lasterror;
    }

    *len = dwBytes;

    return APR_SUCCESS;
}