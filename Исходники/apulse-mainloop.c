APULSE_EXPORT
int
pa_mainloop_prepare(pa_mainloop *m, int timeout)
{
    trace_info("P %s m=%p, timeout=%d\n", __func__, m, timeout);

    m->timeout = timeout;
    if (m->recreate_fds) {
        GList *keys = g_hash_table_get_keys(m->events_ht);
        GList *it;
        struct pollfd *tmp;

        m->nfds = g_list_length(keys) + 1;
        tmp = realloc(m->fds, m->nfds * sizeof(*m->fds));
        if (!tmp)
            return -1;
        m->fds = tmp;

        m->fds[0].fd = m->wakeup_pipe[0];
        m->fds[0].events = POLLIN;
        m->fds[0].revents = 0;

        /* special case for alsa pollfds */
        int k = 1;
        m->alsa_special_cnt = 0;
        it = keys;
        while (it) {
            struct pa_io_event *ioe = it->data;
            if (ioe->events & 0x80000000u) {
                m->fds[k].fd = ioe->fd;
                m->fds[k].events = ioe->events & (~0x80000000u);
                m->fds[k].revents = 0;
                ioe->pollfd = &m->fds[k];
                k ++;
                m->alsa_special_cnt ++;
            }
            it = g_list_next(it);
        }

        /* normal file descriptors */
        it = keys;
        while (it) {
            struct pa_io_event *ioe = it->data;
            if ((ioe->events & 0x80000000u) == 0) {
                m->fds[k].fd = ioe->fd;
                m->fds[k].events = from_pa_io_event_flags(ioe->events);
                m->fds[k].revents = 0;
                ioe->pollfd = &m->fds[k];
                k ++;
            }
            it = g_list_next(it);
        }

        m->nfds = k;

        g_list_free(keys);
        m->recreate_fds = 0;
    }

    return 0;
}