int
main(int argc, char *argv[])
{
	fd_set              rfds, wfds;
	struct cn_strct    *tp, *to;
	int                 rnum, wnum, readsocks;
	int                 i;
	struct    tm       *tm_struct;

	/* initialize the masterdate we update only every second */
	_Last_loop = time(NULL);
	tm_struct  = gmtime(&_Last_loop);
	strftime( _Master_date, 32, "%a, %d %b %Y %H:%M:%S %Z", tm_struct);
#if DEBUG_VERBOSE == 2
	_Conn_count=0;
#endif
#if DEBUG_VERBOSE == 1
	printf("STARTED AT: %s\n", _Master_date);
#endif

	signal(SIGQUIT, die);
	signal(SIGTERM, die);
	signal(SIGPIPE, check_sockets);
	signal(SIGINT,  clean_on_quit);

	/* Fill up the initial connection lists; _Free_conns is just a LIFO stack,
	 * there shall never be a performance issues -> single linked only */
	_Free_count=0;
	for (i = 0; i < INITIAL_CONNS; i++) {
		tp = _Free_conns;
		_Free_conns = (struct cn_strct *) calloc(1, sizeof(struct cn_strct));
		_Free_conns->data_buf_head =
			(char *) calloc (RECV_BUFF_LENGTH, sizeof (char));
		_Free_conns->c_next = tp;
		_Free_conns->c_prev = NULL;
		_Free_conns->q_prev = NULL;
		_Free_conns->identifier = _Conn_count++;
		_Free_count++;
	}

	/* create the master listener */
	if ((_Master_sock = create_listener(HTTP_PORT)) == -1) {
		fprintf(stderr, "ERR: Couldn't bind to port %d\n",
				HTTP_PORT);
		exit(1);
	}

	/* set up LIFO queue */
	_Queue_tail = _Queue_head = NULL;
	_Queue_count = 0;

	/* create workers for application */
	for(i = 0; i < WORKER_THREADS; i++) {
		pthread_create(&_Workers[i], NULL, &run_app_thread, (void *) &i);
	}
	sleep(1);
	for(i = 0; i < WORKER_THREADS; i++) {
		pthread_detach( _Workers[i] );
	}

#if DEBUG_VERBOSE == 1
	printf("%s: listening on port %d (http)\n",
			_Server_version, HTTP_PORT);
#endif

	/* main loop */
	while (1) {
		// clean socket lists
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		wnum = -1;

		// Add master listener to reading sockets
		FD_SET(_Master_sock, &rfds);
		rnum = _Master_sock;

		// Add the established sockets
		tp = _Busy_conns;

		/* Adding connection to the SocketSets based on state */
		while (tp != NULL) {
			if (REQSTATE_READ_HEAD == tp->req_state) {
				FD_SET(tp->net_socket, &rfds);
				rnum = (tp->net_socket > rnum) ? tp->net_socket : rnum;
			}
			if (REQSTATE_SEND_FILE == tp->req_state) {
				FD_SET(tp->net_socket, &wfds);
				wnum = (tp->net_socket > wnum) ? tp->net_socket : wnum;
			}
			tp = tp->c_next;
		}

		readsocks = select(
			(wnum > rnum) ? wnum+1 : rnum+1,
			(-1 != rnum)  ? &rfds : NULL,
			(-1 != wnum)  ? &wfds : NULL,
			(fd_set *) 0,
			NULL
		);

		// is the main listener in the read set? -> New connection
		if (FD_ISSET(_Master_sock, &rfds)) {
			handle_new_conn(_Master_sock);
			readsocks--;
		}

		// Handle the established sockets
		tp = _Busy_conns;

		while (readsocks > 0 && tp != NULL) {
			to = tp;
			tp = tp->c_next;

			if (REQSTATE_READ_HEAD == to->req_state &&
			  FD_ISSET(to->net_socket, &rfds)) {
				readsocks--;
#if DEBUG_VERBOSE == 1
				printf("WANNA RECV HEAD\n");
#endif
				read_request(to);
			}
			if (REQSTATE_SEND_FILE == to->req_state &&
			  FD_ISSET(to->net_socket, &wfds)) {
				readsocks--;
#if DEBUG_VERBOSE == 1
				printf("WANNA SEND FILE\n");
#endif
				send_file(to);
			}
		}
	}
	return 0;
}