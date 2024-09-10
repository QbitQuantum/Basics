int eloop_register_read_sock(int sock, eloop_sock_handler handler,
			     void *eloop_data, void *user_data)
{
	WSAEVENT event;
	struct eloop_sock *tmp;

	if (eloop_prepare_handles())
		return -1;

	event = WSACreateEvent();
	if (event == WSA_INVALID_EVENT) {
		printf("WSACreateEvent() failed: %d\n", WSAGetLastError());
		return -1;
	}

	if (WSAEventSelect(sock, event, FD_READ)) {
		printf("WSAEventSelect() failed: %d\n", WSAGetLastError());
		WSACloseEvent(event);
		return -1;
	}
	tmp = os_realloc_array(eloop.readers, eloop.reader_count + 1,
			       sizeof(struct eloop_sock));
	if (tmp == NULL) {
		WSAEventSelect(sock, event, 0);
		WSACloseEvent(event);
		return -1;
	}

	tmp[eloop.reader_count].sock = sock;
	tmp[eloop.reader_count].eloop_data = eloop_data;
	tmp[eloop.reader_count].user_data = user_data;
	tmp[eloop.reader_count].handler = handler;
	tmp[eloop.reader_count].event = event;
	eloop.reader_count++;
	eloop.readers = tmp;
	if (sock > eloop.max_sock)
		eloop.max_sock = sock;
	eloop.reader_table_changed = 1;

	return 0;
}