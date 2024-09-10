EVQ_API int
win32iocp_set (struct event *ev, const unsigned int rw_flags)
{
    static WSABUF buf = {0, 0};

    struct event_queue *evq = ev->wth->evq;
    const sd_t sd = (sd_t) ev->fd;

    if ((rw_flags & EVENT_READ) && !ev->w.iocp.rov) {
	struct win32overlapped *ov = win32iocp_new_overlapped(evq);
	DWORD flags = 0;

	if (!ov) return -1;
	if (!WSARecv(sd, &buf, 1, NULL, &flags, (OVERLAPPED *) ov, NULL)) {
	    if (ev->flags & EVENT_AIO_SKIP) {
		win32iocp_del_overlapped(evq, ov);
		ev->flags |= EVENT_READ_RES | EVENT_ACTIVE;
		goto ready;
	    }
	} else if (WSAGetLastError() != WSA_IO_PENDING) {
	    win32iocp_del_overlapped(evq, ov);
	    return -1;
	}
	ov->ev = ev;
	ev->w.iocp.rov = ov;
	ev->flags |= EVENT_RPENDING;  /* IOCP read request is installed */
    }
    if ((rw_flags & EVENT_WRITE) && !ev->w.iocp.wov) {
	struct win32overlapped *ov = win32iocp_new_overlapped(evq);

	if (!ov) return -1;
	if (!WSASend(sd, &buf, 1, NULL, 0, (OVERLAPPED *) ov, NULL)) {
	    if (ev->flags & EVENT_AIO_SKIP) {
		win32iocp_del_overlapped(evq, ov);
		ev->flags |= EVENT_WRITE_RES | EVENT_ACTIVE;
		goto ready;
	    }
	} else if (WSAGetLastError() != WSA_IO_PENDING) {
	    win32iocp_del_overlapped(evq, ov);
	    return -1;
	}
	ov->ev = ev;
	ev->w.iocp.wov = ov;
	ev->flags |= EVENT_WPENDING;  /* IOCP write request is installed */
    }
    return 0;
 ready:
    if (ev->flags & EVENT_ONESHOT)
	evq_del(ev, 1);
    else if (ev->tq && !(ev->flags & EVENT_TIMEOUT_MANUAL))
	timeout_reset(ev, evq->now);

    ev->next_ready = evq->ev_ready;
    evq->ev_ready = ev;
    return 0;
}