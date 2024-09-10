static void
manage_client_event (struct item_s *it, uint32_t evt)
{
    ssize_t rc;

    if (evt & EPOLLIN) {
        rc = splice (it->fd, NULL, it->pfd[1], NULL, PIPE_SIZE,
            SPLICE_F_MOVE | SPLICE_F_MORE | SPLICE_F_NONBLOCK);
        if (rc > 0) {
            it->loaded += rc;
            evt |= EPOLLOUT;
        }
        else if (rc == 0)
            evt |= EPOLLHUP;
        else {
            if (errno != EINTR && errno != EAGAIN)
                evt |= EPOLLERR;
        }
    }
    if (evt & EPOLLOUT) {
        if (it->loaded > 0) {
            rc = splice (it->pfd[0], NULL, it->fd, NULL, it->loaded,
                SPLICE_F_MOVE | SPLICE_F_MORE | SPLICE_F_NONBLOCK);
            if (rc > 0)
                it->loaded -= rc;
            else if (rc < 0) {
                if (errno != EINTR && errno != EAGAIN)
                    evt |= EPOLLERR;
            }
        }
    }
    if ((evt & EPOLLHUP) && !(evt & EPOLLERR)) {
        shutdown (it->fd, SHUT_WR);
        it->shut = 1;
        evt |= EPOLLERR;
    }
    if (evt & EPOLLERR) {
retry_del:
        rc = epoll_ctl (fd_epoll, EPOLL_CTL_DEL, it->fd, NULL);
        if (rc < 0) {
            if (errno == EINTR)
                goto retry_del;
            if (errno != ENOENT) {
                ASSERT (rc == 0);
            }
        }

        return item_free (it);
    }
    else {
        uint32_t e = ((it->loaded > 0) ? EPOLLOUT : 0)
            | ((it->loaded < PIPE_SIZE) ? EPOLLIN : 0);

        if (e != it->events) {
            struct epoll_event epevt;

retry_mod:
            epevt.data.ptr = it;
            epevt.events = e;
            it->events = e;
            rc = epoll_ctl (fd_epoll, EPOLL_CTL_MOD, it->fd, &epevt);
            if (rc < 0) {
                if (errno == EINTR)
                    goto retry_mod;
                ASSERT (rc == 0);
            }
        }
    }
}