static
ssize_t
Nsendto(int fd, const void* buf, size_t len, int flags, const struct sockaddr* addr, int alen)
{
    ssize_t r;
    int res;
    WSABUF wbuf;

    wbuf.len = (u_long)len;
    wbuf.buf = (char FAR*)buf;

    if (addr != NULL)
        res = WSASendTo(fhand[fd].sock, &wbuf, 1, &r, flags,
                        addr, alen, NULL, NULL);
    else
        res = WSASend(fhand[fd].sock, &wbuf, 1, &r, flags, NULL, NULL);

    if (res == SOCKET_ERROR) {
        int err = WSAGetLastError();
        return (-1);
    }
    else {
        return (r);
    }
}