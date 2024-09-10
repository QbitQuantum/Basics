static int
win32thr_del (struct win32thr *wth, struct event *ev)
{
    int i, n = --wth->n;

    if (ev->tq) timeout_del(ev);

    ev->wth = NULL;
    wth->evq->nevents--;

    i = ev->w.index;
    if (ev->flags & EVENT_SOCKET) {
	HANDLE hEvent = wth->handles[i];
	WSAEventSelect((int) ev->fd, hEvent, 0);
	CloseHandle(hEvent);
    }
    if (i < n) {
	ev = wth->events[n];
	ev->w.index = i;
	wth->events[i] = ev;
	wth->handles[i] = wth->handles[n];
    }
    wth->handles[n] = wth->signal;  /* lower signal event */

    if (ev->flags & EVENT_DIRWATCH)
	return !FindCloseChangeNotification(ev->fd);

    return 0;
}