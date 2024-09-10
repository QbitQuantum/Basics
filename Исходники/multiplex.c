static void mplex() {
	struct timeval timeout = {
		.tv_sec = 1,
		.tv_usec = 0,
	};
	int i;
	int maxfd = 0;
	fd_set rok, wok, xok;
	FD_ZERO(&rok);
	FD_ZERO(&wok);
	FD_ZERO(&xok);
	if (io_stop == 1) {
		io_stop = 2;
		q_puts(&sockets->net[0].sendq, "X\n");
	}
	for(i=0; i < sockets->count; i++) {
		struct sockifo* ifo = &sockets->net[i];
		if (ifo->death_time && ifo->death_time < now) {
			esock(ifo, "Ping Timeout");
		}
		if (ifo->fd < 0) {
			if (ifo->state.mplex_dropped) {
				delnet_real(ifo);
				i--;
			}
			continue;
		}
		if (ifo->fd > maxfd)
			maxfd = ifo->fd;

		int need_read, need_write;
		switch (ifo->state.poll) {
		case POLL_NORMAL:
			writable(ifo);
			need_read = 1;
			need_write = (ifo->sendq.start != ifo->sendq.end);
			break;
		case POLL_FORCE_ROK:
			writable(ifo);
			need_read = 1;
			need_write = 0;
			break;
		case POLL_FORCE_WOK:
			need_read = 0;
			need_write = 1;
			break;
		case POLL_HANG:
		default:
			need_read = 0;
			need_write = 0;
		}
		if (ifo->fd < 0)
			continue;
		if (need_read)
			FD_SET(ifo->fd, &rok);
		if (need_write)
			FD_SET(ifo->fd, &wok);
		FD_SET(ifo->fd, &xok);
		if (io_stop == 2)
			break;
	}
	int ready = select(maxfd + 1, &rok, &wok, &xok, &timeout);
	time_t new_ts = time(NULL);
	if (now != new_ts && io_stop != 2) {
		now = new_ts;
		qprintf(&sockets->net[0].sendq, "T %d\n", now);
	}
	if (ready <= 0)
		return;
	for(i=0; i < sockets->count; i++) {
		struct sockifo* ifo = &sockets->net[i];
		if (ifo->fd < 0)
			continue;
		if (FD_ISSET(ifo->fd, &xok)) {
			esock(ifo, "Exception on socket");
			continue;
		}
		if (FD_ISSET(ifo->fd, &wok)) {
			writable(ifo);
			if (ifo->fd < 0)
				continue;
		}
		if (FD_ISSET(ifo->fd, &rok)) {
			readable(ifo);
		}
		if (io_stop == 2)
			return;
	}
	if (ready > 1 || !FD_ISSET(sockets->net[0].fd, &rok))
		q_puts(&sockets->net[0].sendq, "Q\n");
}

static void sig2child(int sig) {
	kill(worker_pid, sig);
}