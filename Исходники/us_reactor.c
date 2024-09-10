bool us_reactor_poll(us_reactor_t *self, int timeout) {
    bool r = false;
    us_reactor_collect_finished(self);
    us_reactor_fill_poll(self);
    if (self->m_num_handlers > 0) {
        int n;
#ifdef WIN32
        n = WSAPoll(self->m_poll_handlers, self->m_num_handlers, timeout);
#else
        n = poll(self->m_poll_handlers, self->m_num_handlers, timeout);
#endif
        if (n < 0 && errno != EINTR) {
            /* error doing poll, stop loop */
            us_reactor_log_debug("error doing poll, errno=%d", errno);
            r = false;
        }
        if (n > 0) {
            /* some handlers to be handled */
            us_reactor_handler_t *item = self->m_handlers;
            int n;
            int num = self->m_num_handlers;
            for (n = 0; n < num; ++n, item = item->m_next) {
                struct pollfd *p = &self->m_poll_handlers[n];
                if (p->fd != item->m_fd) {
                    us_reactor_log_error("item %p fd %d != p->fd", (void *)item, item->m_fd, p->fd);
                    abort();
                }
                if (item->m_wake_on_readable && (p->revents & POLLIN)) {
                    us_reactor_log_debug("item %p fd %d is readable", item, item->m_fd);
                    item->readable(item);
                }
                if (item->m_wake_on_writable && (p->revents & POLLOUT)) {
                    us_reactor_log_debug("item %p fd %d is writable", item, item->m_fd);
                    item->writable(item);
                }
                if ((p->revents & POLLHUP)) {
                    us_reactor_log_debug("poll item %p fd %d got HUP: %d", (void *)item, item->m_fd, p->revents);
                    us_reactor_handler_finish(item);
                }
                if ((p->revents & POLLERR)) {
                    us_reactor_log_debug("poll item %p fd %d got ERR: %d", (void *)item, item->m_fd, p->revents);
                    us_reactor_handler_finish(item);
                }
                if ((p->revents & POLLNVAL)) {
                    us_reactor_log_error("poll item %p fd %d got NVAL: %d", (void *)item, item->m_fd, p->revents);
                    us_reactor_handler_finish(item);
                }
            }
            r = true;
        }
        if (n == 0) {
            /* there are handlers, nothing to do, timeout occurred */
            r = true;
        }
    }
    us_reactor_collect_finished(self);
    return r;
}