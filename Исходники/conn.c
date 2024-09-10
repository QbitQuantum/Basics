_inline int PollSockets(LPCONNPOOL cp) {
	int num_fds, i;
	SOCKET fd_highest;
	LPSESS sess;

	#if defined(_USE_KQUEUE)
		num_fds = kevent(cp->smfd, NULL, 0, cp->events, cp->nconns, NULL);
		return num_fds;
		
	#elif defined(_USE_EPOLL)
		num_fds = epoll_wait(cp->smfd, cp->events, cp->nconns, -1);
		return num_fds;
		
	#elif defined(_USE_DEVPOLL)
		num_fds = ioctl(cp->smfd, DP_POLL, &pollstuff);
		return (num_fds >= 0) ? num_fds : -1;

	#elif defined(_USE_POLL)
		num_fds = poll(cp->fds, cp->nconns, -1);
		return num_fds;
		
	#elif defined(_USE_WSAPOLL)
		num_fds = WSAPoll(cp->fdarray, cp->nconns, -1);
		return num_fds;
		
	#elif defined(_USE_WSAEVENTS)
		num_fds = WSAWaitForMultipleEvents(cp->nconns, cp->events, FALSE, WSA_INFINITE, TRUE);
		if (num_fds == WSA_WAIT_FAILED)
			return -1;
		WSAResetEvent(cp->events[num_fds - WSA_WAIT_EVENT_0]);
		return num_fds;

	#elif defined(_USE_SELECT)
		FD_ZERO(&cp->rdfds);
		fd_highest = 0;
		for (i = 0; i != cp->nconns; i++) {
			sess = cp->sessions[i];
			FD_SET(sess->sck, &cp->rdfds);
			if (sess->sck > fd_highest)
				fd_highest = sess->sck;
		}
		//printf("#before select(): nfds %d\n", cp->rdfds.fd_count);
		num_fds = select(fd_highest + 1, &cp->rdfds, NULL, NULL, NULL);
		//printf("#after select(): nfds %d\n", cp->rdfds.fd_count);
		/*if (!num_fds) {
			printf("WARNING: fd_count being manually set!\n");
			cp->rdfds.fd_count = cp->nconns - cp->n_connupdates;
			return 0;
		}*/
		//return num_fds;
		return (num_fds != -1) ? cp->nconns : -1;
	#endif
}