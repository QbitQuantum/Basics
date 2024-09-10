int do_eventsel_loop(HANDLE other_event)
{
	int n, nhandles, nallhandles, netindex, otherindex;
	long next, ticks;
	HANDLE *handles;
	SOCKET *sklist;
	int skcount;
	long now = GETTICKCOUNT();
	static int timeoutCount = 0;

	if (sk_isClosed()) {
		return -1;
	}

	if (run_timers(now, &next)) {
		ticks = next - GETTICKCOUNT();
		if (ticks < 0) ticks = 0;  /* just in case */
	} else {
		ticks = INFINITE;
	}

	if (ticks < 0 || ticks > 100) ticks = 100;

	handles = handle_get_events(&nhandles);
	handles = sresize(handles, nhandles+2, HANDLE);
	nallhandles = nhandles;

	if (netevent != INVALID_HANDLE_VALUE)
		handles[netindex = nallhandles++] = netevent;
	else
		netindex = -1;
	if (other_event != INVALID_HANDLE_VALUE)
		handles[otherindex = nallhandles++] = other_event;
	else
		otherindex = -1;

	n = WaitForMultipleObjects(nallhandles, handles, FALSE, ticks);

	if (STATUS_TIMEOUT == n) {
		sfree(handles);
		++timeoutCount;
		return timeoutCount > 50 ? -1 : 0;
	}
	timeoutCount = 0;

	if ((unsigned)(n - WAIT_OBJECT_0) < (unsigned)nhandles) {
		handle_got_event(handles[n - WAIT_OBJECT_0]);
	} else if (netindex >= 0 && n == WAIT_OBJECT_0 + netindex) {
		WSANETWORKEVENTS things;
		SOCKET socket;
		extern SOCKET first_socket(int *), next_socket(int *);
		extern int select_result(WPARAM, LPARAM);
		int i, socketstate;

		/*
		* We must not call select_result() for any socket
		* until we have finished enumerating within the
		* tree. This is because select_result() may close
		* the socket and modify the tree.
		*/
		/* Count the active sockets. */
		i = 0;		
		for (socket = first_socket(&socketstate);
			socket != INVALID_SOCKET;
			socket = next_socket(&socketstate)) i++;

		/* Expand the buffer if necessary. */
		sklist = snewn(i, SOCKET);

		/* Retrieve the sockets into sklist. */
		skcount = 0;
		for (socket = first_socket(&socketstate);
			socket != INVALID_SOCKET;
			socket = next_socket(&socketstate)) {
				sklist[skcount++] = socket;
		}

		/* Now we're done enumerating; go through the list. */
		for (i = 0; i < skcount; i++) {
			WPARAM wp;
			socket = sklist[i];
			wp = (WPARAM) socket;
			if (!p_WSAEnumNetworkEvents(socket, NULL, &things)) {
				static const struct { int bit, mask; } eventtypes[] = {
					{FD_CONNECT_BIT, FD_CONNECT},
					{FD_READ_BIT, FD_READ},
					{FD_CLOSE_BIT, FD_CLOSE},
					{FD_OOB_BIT, FD_OOB},
					{FD_WRITE_BIT, FD_WRITE},
					{FD_ACCEPT_BIT, FD_ACCEPT},
				};
				int e;

				noise_ultralight(socket);
				noise_ultralight(things.lNetworkEvents);

				for (e = 0; e < lenof(eventtypes); e++)
					if (things.lNetworkEvents & eventtypes[e].mask) {
						LPARAM lp;
						int err = things.iErrorCode[eventtypes[e].bit];
						lp = WSAMAKESELECTREPLY(eventtypes[e].mask, err);
						select_result(wp, lp);
					}
			}
		}

		sfree(sklist);
	}

	sfree(handles);

	if (n == WAIT_TIMEOUT) {
		now = next;
	} else {
		now = GETTICKCOUNT();
	}

	if (otherindex >= 0 && n == WAIT_OBJECT_0 + otherindex)
		return 1;

	return 0;
}