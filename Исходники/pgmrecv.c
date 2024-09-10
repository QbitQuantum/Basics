static
gpointer
receiver_thread (
	gpointer	data
	)
{
	pgm_sock_t* rx_sock = (pgm_sock_t*)data;
	const long iov_len = 20;
	const long ev_len  = 1;
	struct pgm_msgv_t msgv[iov_len];

#ifdef CONFIG_HAVE_EPOLL
	struct epoll_event events[ev_len];	/* wait for maximum 1 event */
	const int efd = epoll_create (IP_MAX_MEMBERSHIPS);
	if (efd < 0) {
		g_error ("epoll_create failed errno %i: \"%s\"", errno, strerror(errno));
		g_main_loop_quit (g_loop);
		return NULL;
	}

	if (pgm_epoll_ctl (rx_sock, efd, EPOLL_CTL_ADD, EPOLLIN) < 0)
	{
		g_error ("pgm_epoll_ctl failed errno %i: \"%s\"", errno, strerror(errno));
		g_main_loop_quit (g_loop);
		return NULL;
	}
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = g_quit_pipe[0];
	if (epoll_ctl (efd, EPOLL_CTL_ADD, g_quit_pipe[0], &event) < 0)
	{
		g_error ("epoll_ctl failed errno %i: \"%s\"", errno, strerror(errno));
		g_main_loop_quit (g_loop);
		return NULL;
	}
#elif defined(CONFIG_HAVE_POLL)
	int n_fds = 2;
	struct pollfd fds[ 1 + n_fds ];
#elif defined(G_OS_UNIX) /* HAVE_SELECT */
	int n_fds;
	fd_set readfds;
#else /* G_OS_WIN32 */
	SOCKET recv_sock, pending_sock;
	DWORD cEvents = PGM_RECV_SOCKET_READ_COUNT + 1;
	WSAEVENT waitEvents[ PGM_RECV_SOCKET_READ_COUNT + 1 ];
	socklen_t socklen = sizeof (SOCKET);

	waitEvents[0] = g_quit_event;
	waitEvents[1] = WSACreateEvent ();
	pgm_getsockopt (rx_sock, IPPROTO_PGM, PGM_RECV_SOCK, &recv_sock, &socklen);
	WSAEventSelect (recv_sock, waitEvents[1], FD_READ);
	waitEvents[2] = WSACreateEvent ();
	pgm_getsockopt (rx_sock, IPPROTO_PGM, PGM_PENDING_SOCK, &pending_sock, &socklen);
	WSAEventSelect (pending_sock, waitEvents[2], FD_READ);
#endif /* !CONFIG_HAVE_EPOLL */

	do {
		struct timeval tv;
#ifndef _WIN32
		int timeout;
#else
		DWORD dwTimeout, dwEvents;
#endif
		size_t len;
		pgm_error_t* pgm_err = NULL;
		const int status = pgm_recvmsgv (rx_sock,
					         msgv,
					         G_N_ELEMENTS(msgv),
					         0,
					         &len,
					         &pgm_err);
		switch (status) {
		case PGM_IO_STATUS_NORMAL:
			on_msgv (msgv, len);
			break;
		case PGM_IO_STATUS_TIMER_PENDING:
			{
				socklen_t optlen = sizeof (tv);
				pgm_getsockopt (rx_sock, IPPROTO_PGM, PGM_TIME_REMAIN, &tv, &optlen);
			}
			goto block;
		case PGM_IO_STATUS_RATE_LIMITED:
			{
				socklen_t optlen = sizeof (tv);
				pgm_getsockopt (rx_sock, IPPROTO_PGM, PGM_RATE_REMAIN, &tv, &optlen);
			}
/* fall through */
		case PGM_IO_STATUS_WOULD_BLOCK:
block:
#ifdef CONFIG_HAVE_EPOLL
			timeout = PGM_IO_STATUS_WOULD_BLOCK == status ? -1 : ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
			epoll_wait (efd, events, G_N_ELEMENTS(events), timeout /* ms */);
#elif defined(CONFIG_HAVE_POLL)
			timeout = PGM_IO_STATUS_WOULD_BLOCK == status ? -1 : ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
			memset (fds, 0, sizeof(fds));
			fds[0].fd = g_quit_pipe[0];
			fds[0].events = POLLIN;
			pgm_poll_info (rx_sock, &fds[1], &n_fds, POLLIN);
			poll (fds, 1 + n_fds, timeout /* ms */);
#elif defined(G_OS_UNIX) /* HAVE_SELECT */
			FD_ZERO(&readfds);
			FD_SET(g_quit_pipe[0], &readfds);
			n_fds = g_quit_pipe[0] + 1;
			pgm_select_info (rx_sock, &readfds, NULL, &n_fds);
			select (n_fds, &readfds, NULL, NULL, PGM_IO_STATUS_RATE_LIMITED == status ? &tv : NULL);
#else /* G_OS_WIN32 */
			dwTimeout = PGM_IO_STATUS_WOULD_BLOCK == status ? WSA_INFINITE : ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
			dwEvents = WSAWaitForMultipleEvents (cEvents, waitEvents, FALSE, dwTimeout, FALSE);
			switch (dwEvents) {
			case WSA_WAIT_EVENT_0+1: WSAResetEvent (waitEvents[1]); break;
			case WSA_WAIT_EVENT_0+2: WSAResetEvent (waitEvents[2]); break;
			default: break;
			}
#endif /* !CONFIG_HAVE_EPOLL */
			break;

		default:
			if (pgm_err) {
				g_warning ("%s", pgm_err->message);
				pgm_error_free (pgm_err);
				pgm_err = NULL;
			}
			if (PGM_IO_STATUS_ERROR == status)
				break;
		}
	} while (!g_quit);

#ifdef CONFIG_HAVE_EPOLL
	close (efd);
#elif defined(G_OS_WIN32)
	WSACloseEvent (waitEvents[1]);
	WSACloseEvent (waitEvents[2]);
#  if (__STDC_VERSION__ < 199901L)
	g_free (waitHandles);
#  endif
#endif
	return NULL;
}