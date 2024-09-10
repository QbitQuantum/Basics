static int
do_poll(struct pollfd *fds, int nfds, int timeout)
{
    int retval;
#ifndef _WIN32
    do {
        retval = poll(fds, nfds, timeout);
    } while (retval < 0 && errno == EINTR);
#else
    retval = WSAPoll(fds, nfds, timeout);
#endif
    return retval;
}