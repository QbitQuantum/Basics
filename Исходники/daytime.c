unsigned
__stdcall
#endif
nak_routine (
	void*		arg
	)
{
/* dispatch loop */
	pgm_sock_t* nak_sock = (pgm_sock_t*)arg;
#ifndef _WIN32
	int fds;
	fd_set readfds;
#else
	SOCKET recv_sock, repair_sock, pending_sock;
	DWORD cEvents = PGM_SEND_SOCKET_READ_COUNT + 1;
	WSAEVENT waitEvents[ PGM_SEND_SOCKET_READ_COUNT + 1 ];
	DWORD dwTimeout, dwEvents;
	socklen_t socklen = sizeof (SOCKET);

	waitEvents[0] = terminateEvent;
	waitEvents[1] = WSACreateEvent();
	waitEvents[2] = WSACreateEvent();
	waitEvents[3] = WSACreateEvent();
	assert (3 == PGM_SEND_SOCKET_READ_COUNT);
	pgm_getsockopt (nak_sock, IPPROTO_PGM, PGM_RECV_SOCK, &recv_sock, &socklen);
	WSAEventSelect (recv_sock, waitEvents[1], FD_READ);
	pgm_getsockopt (nak_sock, IPPROTO_PGM, PGM_REPAIR_SOCK, &repair_sock, &socklen);
	WSAEventSelect (repair_sock, waitEvents[2], FD_READ);
	pgm_getsockopt (nak_sock, IPPROTO_PGM, PGM_PENDING_SOCK, &pending_sock, &socklen);
	WSAEventSelect (pending_sock, waitEvents[3], FD_READ);
#endif /* !_WIN32 */
	do {
		struct timeval tv;
		char buf[4064];
		pgm_error_t* pgm_err = NULL;
		const int status = pgm_recv (nak_sock, buf, sizeof(buf), 0, NULL, &pgm_err);
		switch (status) {
		case PGM_IO_STATUS_TIMER_PENDING:
			{
				socklen_t optlen = sizeof (tv);
				pgm_getsockopt (sock, IPPROTO_PGM, PGM_TIME_REMAIN, &tv, &optlen);
			}
			goto block;
		case PGM_IO_STATUS_RATE_LIMITED:
			{
				socklen_t optlen = sizeof (tv);
				pgm_getsockopt (sock, IPPROTO_PGM, PGM_RATE_REMAIN, &tv, &optlen);
			}
		case PGM_IO_STATUS_WOULD_BLOCK:
block:
#ifndef _WIN32
			fds = terminate_pipe[0] + 1;
			FD_ZERO(&readfds);
			FD_SET(terminate_pipe[0], &readfds);
			pgm_select_info (nak_sock, &readfds, NULL, &fds);
			fds = select (fds, &readfds, NULL, NULL, PGM_IO_STATUS_WOULD_BLOCK == status ? NULL : &tv);
#else
			dwTimeout = PGM_IO_STATUS_WOULD_BLOCK == status ? WSA_INFINITE : (DWORD)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
			dwEvents = WSAWaitForMultipleEvents (cEvents, waitEvents, FALSE, dwTimeout, FALSE);
			switch (dwEvents) {
			case WSA_WAIT_EVENT_0+1: WSAResetEvent (waitEvents[1]); break;
			case WSA_WAIT_EVENT_0+2: WSAResetEvent (waitEvents[2]); break;
			case WSA_WAIT_EVENT_0+3: WSAResetEvent (waitEvents[3]); break;
			default: break;
			}
#endif /* !_WIN32 */
			break;

		default:
			if (pgm_err) {
				fprintf (stderr, "%s\n", pgm_err->message ? pgm_err->message : "(null)");
				pgm_error_free (pgm_err);
				pgm_err = NULL;
			}
			if (PGM_IO_STATUS_ERROR == status)
				break;
		}
	} while (!is_terminated);
#ifndef _WIN32
	return NULL;
#else
	WSACloseEvent (waitEvents[1]);
	WSACloseEvent (waitEvents[2]);
	WSACloseEvent (waitEvents[3]);
	_endthread();
	return 0;
#endif
}