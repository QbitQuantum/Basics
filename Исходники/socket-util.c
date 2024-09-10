int
check_connection_completion(int fd)
{
    static struct vlog_rate_limit rl = VLOG_RATE_LIMIT_INIT(5, 10);
    struct pollfd pfd;
    int retval;

    pfd.fd = fd;
    pfd.events = POLLOUT;

#ifndef _WIN32
    do {
        retval = poll(&pfd, 1, 0);
    } while (retval < 0 && errno == EINTR);
#else
    retval = WSAPoll(&pfd, 1, 0);
#endif
    if (retval == 1) {
        if (pfd.revents & POLLERR) {
            ssize_t n = send(fd, "", 1, 0);
            if (n < 0) {
                return sock_errno();
            } else {
                VLOG_ERR_RL(&rl, "poll return POLLERR but send succeeded");
                return EPROTO;
            }
        }
        return 0;
    } else if (retval < 0) {
        VLOG_ERR_RL(&rl, "poll: %s", sock_strerror(sock_errno()));
        return errno;
    } else {
        return EAGAIN;
    }
}