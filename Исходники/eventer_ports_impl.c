static void alter_fd_associate(eventer_t e, int mask, struct ports_spec *spec) {
    int events = 0, s_errno = 0, ret;
    if(mask & EVENTER_READ) events |= POLLIN;
    if(mask & EVENTER_WRITE) events |= POLLOUT;
    if(mask & EVENTER_EXCEPTION) events |= POLLERR;
    errno = 0;
    ret = port_associate(spec->port_fd, PORT_SOURCE_FD, e->fd, events, (void *)(vpsized_int)e->fd);
    s_errno = errno;
    if (ret == -1) {
        mtevFatal(mtev_error,
                  "eventer port_associate failed(%d-%d): %d/%s\n", e->fd, spec->port_fd, s_errno, strerror(s_errno));
    }
}