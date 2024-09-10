int
main (
	int		argc,
	char*		argv[]
	)
{
	pgm_error_t* pgm_err = NULL;

	setlocale (LC_ALL, "");

#ifndef _WIN32
	puts ("プリン プリン");
#else
	_putws (L"プリン プリン");
#endif

	if (!pgm_init (&pgm_err)) {
		fprintf (stderr, "Unable to start PGM engine: %s\n", pgm_err->message);
		pgm_error_free (pgm_err);
		return EXIT_FAILURE;
	}

/* parse program arguments */
	const char* binary_name = strrchr (argv[0], '/');
	int c;
	while ((c = getopt (argc, argv, "s:n:p:f:K:N:lih")) != -1)
	{
		switch (c) {
		case 'n':	network = optarg; break;
		case 's':	port = atoi (optarg); break;
		case 'p':	udp_encap_port = atoi (optarg); break;
		case 'f':	use_fec = TRUE; break;
		case 'K':	rs_k = atoi (optarg); break;
		case 'N':	rs_n = atoi (optarg); break;
		case 'l':	use_multicast_loop = TRUE; break;

		case 'i':
			pgm_if_print_all();
			return EXIT_SUCCESS;

		case 'h':
		case '?': usage (binary_name);
		}
	}

	if (use_fec && ( !rs_n || !rs_k )) {
		fprintf (stderr, "Invalid Reed-Solomon parameters RS(%d,%d).\n", rs_n, rs_k);
		usage (binary_name);
	}

/* setup signal handlers */
#ifdef SIGHUP
	signal (SIGHUP,  SIG_IGN);
#endif
#ifndef _WIN32
	int e = pipe (terminate_pipe);
	assert (0 == e);
	signal (SIGINT,  on_signal);
	signal (SIGTERM, on_signal);
#else
	terminate_event = CreateEvent (NULL, TRUE, FALSE, TEXT("TerminateEvent"));
	SetConsoleCtrlHandler ((PHANDLER_ROUTINE)on_console_ctrl, TRUE);
#endif /* !_WIN32 */

	if (!on_startup()) {
		fprintf (stderr, "Startup failed\n");
		return EXIT_FAILURE;
	}

/* dispatch loop */
#ifndef _WIN32
	int fds;
	fd_set readfds;
#else
	int n_handles = 3, recv_sock, pending_sock;
	HANDLE waitHandles[ 3 ];
	DWORD dwTimeout, dwEvents;
	WSAEVENT recvEvent, pendingEvent;

	recvEvent = WSACreateEvent ();
	pgm_getsockopt (sock, PGM_RECV_SOCK, &recv_sock, sizeof(recv_sock));
	WSAEventSelect (recv_sock, recvEvent, FD_READ);
	pendingEvent = WSACreateEvent ();
	pgm_getsockopt (sock, PGM_PENDING_SOCK, &pending_sock, sizeof(pending_sock));
	WSAEventSelect (pending_sock, pendingEvent, FD_READ);

	waitHandles[0] = terminate_event;
	waitHandles[1] = recvEvent;
	waitHandles[2] = pendingEvent;
#endif /* !_WIN32 */
	puts ("Entering PGM message loop ... ");
	do {
		struct timeval tv;
		char buffer[4096];
		size_t len;
		pgm_tsi_t from;
		const int status = pgm_recvfrom (sock,
					         buffer,
					         sizeof(buffer),
					         0,
					         &len,
					         &from,
					         &pgm_err);
		switch (status) {
		case PGM_IO_STATUS_NORMAL:
			on_data (buffer, len, &from);
			break;
		case PGM_IO_STATUS_TIMER_PENDING:
			pgm_getsockopt (sock, PGM_TIME_REMAIN, &tv, sizeof(tv));
			goto block;
		case PGM_IO_STATUS_RATE_LIMITED:
			pgm_getsockopt (sock, PGM_RATE_REMAIN, &tv, sizeof(tv));
		case PGM_IO_STATUS_WOULD_BLOCK:
/* select for next event */
block:
#ifndef _WIN32
			fds = terminate_pipe[0] + 1;
			FD_ZERO(&readfds);
			FD_SET(terminate_pipe[0], &readfds);
			pgm_select_info (sock, &readfds, NULL, &fds);
			fds = select (fds, &readfds, NULL, NULL, PGM_IO_STATUS_WOULD_BLOCK == status ? NULL : &tv);
#else
			dwTimeout = PGM_IO_STATUS_WOULD_BLOCK == status ? INFINITE : (DWORD)((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
			dwEvents = WaitForMultipleObjects (n_handles, waitHandles, FALSE, dwTimeout);
			switch (dwEvents) {
			case WAIT_OBJECT_0+1: WSAResetEvent (recvEvent); break;
			case WAIT_OBJECT_0+2: WSAResetEvent (pendingEvent); break;
			default: break;
			}
#endif /* !_WIN32 */
			break;

		default:
			if (pgm_err) {
				fprintf (stderr, "%s\n", pgm_err->message);
				pgm_error_free (pgm_err);
				pgm_err = NULL;
			}
			if (PGM_IO_STATUS_ERROR == status)
				break;
		}
	} while (!is_terminated);

	puts ("Message loop terminated, cleaning up.");

/* cleanup */
#ifndef _WIN32
	close (terminate_pipe[0]);
	close (terminate_pipe[1]);
#else
	WSACloseEvent (recvEvent);
	WSACloseEvent (pendingEvent);
	CloseHandle (terminate_event);
#endif /* !_WIN32 */

	if (sock) {
		puts ("Destroying PGM socket.");
		pgm_close (sock, TRUE);
		sock = NULL;
	}

	puts ("PGM engine shutdown.");
	pgm_shutdown ();
	puts ("finished.");
	return EXIT_SUCCESS;
}