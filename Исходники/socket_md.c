int
dbgsysSocketClose(int fd) {
    struct linger l;
    int len = sizeof(l);

    if (getsockopt(fd, SOL_SOCKET, SO_LINGER, (char *)&l, &len) == 0) {
        if (l.l_onoff == 0) {
            WSASendDisconnect(fd, NULL);
        }
    }
    return closesocket(fd);
}