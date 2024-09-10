int comms_connect(HWND hWnd, struct th_data *data) {
	struct tray_status *status = &data->status;
	struct tcp_keepalive ka_get;
	struct tcp_keepalive ka_set = {
		.onoff = 1,
		.keepalivetime = 5000, /* 5 seconds */
		.keepaliveinterval = 5000 /* 5 seconds */
	};
	int timeout = 5000; /* 5 seconds */
	INT ret;
	DWORD retd;
	DWORD err;

	odprintf("comms[connect]");

	if (!data->running)
		return 0;

	if (data->s != INVALID_SOCKET)
		return 0;

	status->conn = NOT_CONNECTED;
	tray_update(hWnd, data);

#if HAVE_GETADDRINFO
	if (data->addrs_cur == NULL && data->addrs_res != NULL) {
		freeaddrinfo(data->addrs_res);
		data->addrs_res = NULL;
	}

	if (data->addrs_res == NULL) {
		SetLastError(0);
		ret = getaddrinfo(data->node, data->service, &data->hints, &data->addrs_res);
		err = GetLastError();
		odprintf("getaddrinfo: %d (%ld)", ret, err);
		if (ret != 0) {
			ret = snprintf(status->msg, sizeof(status->msg), "Unable to resolve node \"%s\" service \"%s\" (%d)", data->node, data->service, ret);
			if (ret < 0)
				status->msg[0] = 0;
			tray_update(hWnd, data);

			return 1;
		}

		if (data->addrs_res == NULL) {
			odprintf("no results");
			ret = snprintf(status->msg, sizeof(status->msg), "No results resolving node \"%s\" service \"%s\"", data->node, data->service);
			if (ret < 0)
				status->msg[0] = 0;
			tray_update(hWnd, data);

			return 1;
		}

		data->addrs_cur = data->addrs_res;
	}

	SetLastError(0);
	ret = getnameinfo(data->addrs_cur->ai_addr, data->addrs_cur->ai_addrlen, data->hbuf, sizeof(data->hbuf), data->sbuf, sizeof(data->sbuf), NI_NUMERICHOST|NI_NUMERICSERV);
	err = GetLastError();
	odprintf("getnameinfo: %d (%ld)", ret, err);
	if (ret == 0) {
		odprintf("trying to connect to node \"%s\" service \"%s\"", data->hbuf, data->sbuf);
	} else {
		data->hbuf[0] = 0;
		data->sbuf[0] = 0;
	}
#else
	odprintf("trying to connect to node \"%s\" service \"%s\"", data->node, data->service);
#endif

	SetLastError(0);
#if HAVE_GETADDRINFO
	data->s = socket(data->addrs_cur->ai_family, SOCK_STREAM, IPPROTO_TCP);
#else
	data->s = socket(data->family, SOCK_STREAM, IPPROTO_TCP);
#endif
	err = GetLastError();
	odprintf("socket: %d (%ld)", data->s, err);

	if (data->s == INVALID_SOCKET) {
		ret = snprintf(status->msg, sizeof(status->msg), "Unable to create socket (%ld)", err);
		if (ret < 0)
			status->msg[0] = 0;
		tray_update(hWnd, data);

#if HAVE_GETADDRINFO
		data->addrs_cur = data->addrs_cur->ai_next;
#endif
		return 1;
	}

	SetLastError(0);
	ret = setsockopt(data->s, SOL_SOCKET, SO_RCVTIMEO, (void*)&timeout, sizeof(timeout));
	err = GetLastError();
	odprintf("setsockopt: %d (%ld)", ret, err);
	if (ret != 0) {
		ret = snprintf(status->msg, sizeof(status->msg), "Unable to set socket timeout (%ld)", err);
		if (ret < 0)
			status->msg[0] = 0;
		tray_update(hWnd, data);

		SetLastError(0);
		ret = closesocket(data->s);
		err = GetLastError();
		odprintf("closesocket: %d (%ld)", ret, err);
		data->s = INVALID_SOCKET;

#if HAVE_GETADDRINFO
		data->addrs_cur = data->addrs_cur->ai_next;
#endif
		return 1;
	}

	SetLastError(0);
	ret = WSAIoctl(data->s, SIO_KEEPALIVE_VALS, (void*)&ka_set, sizeof(ka_set), (void*)&ka_get, sizeof(ka_get), &retd, NULL, NULL);
	err = GetLastError();
	odprintf("WSAIoctl: %d, %d (%ld)", ret, retd, err);
	if (ret != 0) {
		ret = snprintf(status->msg, sizeof(status->msg), "Unable to set socket keepalive options (%ld)", err);
		if (ret < 0)
			status->msg[0] = 0;
		tray_update(hWnd, data);

		SetLastError(0);
		ret = closesocket(data->s);
		err = GetLastError();
		odprintf("closesocket: %d (%ld)", ret, err);
		data->s = INVALID_SOCKET;

#if HAVE_GETADDRINFO
		data->addrs_cur = data->addrs_cur->ai_next;
#endif
		return 1;
	}

	SetLastError(0);
	ret = WSAAsyncSelect(data->s, hWnd, WM_APP_SOCK, FD_CONNECT|FD_READ|FD_CLOSE);
	err = GetLastError();
	odprintf("WSAAsyncSelect: %d (%ld)", ret, err);
	if (ret != 0) {
		ret = snprintf(status->msg, sizeof(status->msg), "Unable to async select on socket (%ld)", err);
		if (ret < 0)
			status->msg[0] = 0;
		tray_update(hWnd, data);

		SetLastError(0);
		ret = closesocket(data->s);
		err = GetLastError();
		odprintf("closesocket: %d (%ld)", ret, err);
		data->s = INVALID_SOCKET;

#if HAVE_GETADDRINFO
		data->addrs_cur = data->addrs_cur->ai_next;
#endif
		return 1;
	}

	status->conn = CONNECTING;
#if HAVE_GETADDRINFO
	if (data->hbuf[0] != 0 && data->sbuf[0] != 0) {
		ret = snprintf(status->msg, sizeof(status->msg), "node \"%s\" service \"%s\" (%ld)", data->hbuf, data->sbuf, err);
	} else {
#endif
		ret = snprintf(status->msg, sizeof(status->msg), "node \"%s\" service \"%s\" (%ld)", data->node, data->service, err);
#if HAVE_GETADDRINFO
	}
#endif
	if (ret < 0)
		status->msg[0] = 0;
	tray_update(hWnd, data);

	SetLastError(0);
#if HAVE_GETADDRINFO
	ret = connect(data->s, data->addrs_cur->ai_addr, data->addrs_cur->ai_addrlen);
#else
	ret = connect(data->s, data->sa, data->sa_len);
#endif
	err = GetLastError();
	odprintf("connect: %d (%ld)", ret, err);
	if (ret == 0 || err == WSAEWOULDBLOCK) {
		return 0;
	} else {
		status->conn = NOT_CONNECTED;
#if HAVE_GETADDRINFO
		if (data->hbuf[0] != 0 && data->sbuf[0] != 0) {
			ret = snprintf(status->msg, sizeof(status->msg), "Error connecting to node \"%s\" service \"%s\"", data->hbuf, data->sbuf);
		} else {
#endif
			ret = snprintf(status->msg, sizeof(status->msg), "Error connecting to node \"%s\" service \"%s\"", data->node, data->service);
#if HAVE_GETADDRINFO
		}
#endif
		if (ret < 0)
			status->msg[0] = 0;
		tray_update(hWnd, data);

		SetLastError(0);
		ret = closesocket(data->s);
		err = GetLastError();
		odprintf("closesocket: %d (%ld)", ret, err);
		data->s = INVALID_SOCKET;

#if HAVE_GETADDRINFO
		data->addrs_cur = data->addrs_cur->ai_next;
#endif
		return 1;
	}
}

int comms_activity(HWND hWnd, struct th_data *data, SOCKET s, WORD sEvent, WORD sError) {
	struct tray_status *status = &data->status;
	INT ret;
	DWORD err;

	odprintf("comms[activity]: s=%p sEvent=%d sError=%d", s, sEvent, sError);

	if (!data->running)
		return 0;

	if (data->s != s)
		return 0;

	switch (sEvent) {
	case FD_CONNECT:
		odprintf("FD_CONNECT %s", status->conn == CONNECTING ? "OK" : "?");
		if (status->conn != CONNECTING)
			return 0;

		if (sError == 0) {
			status->conn = CONNECTED;
			status->msg[0] = 0;
			status->temperature_celsius = NAN;
			status->relative_humidity = NAN;
			status->dew_point = NAN;
			tray_update(hWnd, data);

#if HAVE_GETADDRINFO
			freeaddrinfo(data->addrs_res);
			data->addrs_res = NULL;
#endif
			data->parse_pos = 0;
			data->def_sensor = 0;
			return 0;
		} else {
			status->conn = NOT_CONNECTED;
#if HAVE_GETADDRINFO
			if (data->hbuf[0] != 0 && data->sbuf[0] != 0) {
				ret = snprintf(status->msg, sizeof(status->msg), "Error connecting to node \"%s\" service \"%s\" (%d)", data->hbuf, data->sbuf, sError);
			} else {
#endif
				ret = snprintf(status->msg, sizeof(status->msg), "Error connecting to node \"%s\" service \"%s\" (%d)", data->node, data->service, sError);
#if HAVE_GETADDRINFO
			}
#endif
			if (ret < 0)
				status->msg[0] = 0;
			tray_update(hWnd, data);

			SetLastError(0);
			ret = closesocket(data->s);
			err = GetLastError();
			odprintf("closesocket: %d (%ld)", ret, err);

			data->s = INVALID_SOCKET;
#if HAVE_GETADDRINFO
			data->addrs_cur = data->addrs_cur->ai_next;
#endif
			return 1;
		}

	case FD_READ:
		odprintf("FD_READ %s", status->conn == CONNECTED ? "OK" : "?");
		if (status->conn != CONNECTED)
			return 0;

		if (sError == 0) {
			char recv_buf[128];

			SetLastError(0);
			ret = recv(data->s, recv_buf, sizeof(recv_buf), 0);
			err = GetLastError();
			odprintf("recv: %d (%ld)", ret, err);
			if (ret <= 0) {
				status->conn = NOT_CONNECTED;
#if HAVE_GETADDRINFO
				if (data->hbuf[0] != 0 && data->sbuf[0] != 0) {
					ret = snprintf(status->msg, sizeof(status->msg), "Error reading from node \"%s\" service \"%s\" (%ld)", data->hbuf, data->sbuf, err);
				} else {
#endif
					ret = snprintf(status->msg, sizeof(status->msg), "Error reading from node \"%s\" service \"%s\" (%ld)", data->node, data->service, err);
#if HAVE_GETADDRINFO
				}
#endif
				if (ret < 0)
					status->msg[0] = 0;
				tray_update(hWnd, data);

				SetLastError(0);
				ret = closesocket(data->s);
				err = GetLastError();
				odprintf("closesocket: %d (%ld)", ret, err);

				data->s = INVALID_SOCKET;
				return 1;
			} else if (err == WSAEWOULDBLOCK) {
				return 0;
			} else {
				int size, i;

				size = ret;
				for (i = 0; i < size; i++) {
					/* find a newline and parse the buffer */
					if (recv_buf[i] == '\n') {
						comms_parse(hWnd, data);

						/* clear buffer */
						data->parse_pos = 0;

					/* buffer overflow */
					} else if (data->parse_pos == sizeof(data->parse_buf)/sizeof(char) - 1) {
						odprintf("parse: sender overflowed buffer waiting for '\\n'");
						data->parse_buf[0] = 0;
						data->parse_pos++;

					/* ignore */
					} else if (data->parse_pos > sizeof(data->parse_buf)/sizeof(char) - 1) {

					/* append to buffer */
					} else {
						data->parse_buf[data->parse_pos++] = recv_buf[i];
						data->parse_buf[data->parse_pos] = 0;
					}
				}
				return 0;
			}
		} else {
			status->conn = NOT_CONNECTED;
#if HAVE_GETADDRINFO
			if (data->hbuf[0] != 0 && data->sbuf[0] != 0) {
				ret = snprintf(status->msg, sizeof(status->msg), "Error reading from node \"%s\" service \"%s\" (%d)", data->hbuf, data->sbuf, sError);
			} else {
#endif
				ret = snprintf(status->msg, sizeof(status->msg), "Error reading from node \"%s\" service \"%s\" (%d)", data->node, data->service, sError);
#if HAVE_GETADDRINFO
			}
#endif
			if (ret < 0)
				status->msg[0] = 0;
			tray_update(hWnd, data);

			SetLastError(0);
			ret = closesocket(data->s);
			err = GetLastError();
			odprintf("closesocket: %d (%ld)", ret, err);

			data->s = INVALID_SOCKET;
			return 1;
		}

	case FD_CLOSE:
		odprintf("FD_CLOSE %s", status->conn == CONNECTED ? "OK" : "?");
		if (status->conn != CONNECTED)
			return 0;

		status->conn = NOT_CONNECTED;
#if HAVE_GETADDRINFO
		if (data->hbuf[0] != 0 && data->sbuf[0] != 0) {
			ret = snprintf(status->msg, sizeof(status->msg), "Lost connection to node \"%s\" service \"%s\" (%d)", data->hbuf, data->sbuf, sError);
		} else {
#endif
			ret = snprintf(status->msg, sizeof(status->msg), "Lost connection to node \"%s\" service \"%s\" (%d)", data->node, data->service, sError);
#if HAVE_GETADDRINFO
		}
#endif
		if (ret < 0)
			status->msg[0] = 0;
		tray_update(hWnd, data);

		SetLastError(0);
		ret = closesocket(data->s);
		err = GetLastError();
		odprintf("closesocket: %d (%ld)", ret, err);

		data->s = INVALID_SOCKET;
		return 1;

	default:
		return 0;
	}
}

void comms_parse(HWND hWnd, struct th_data *data) {
	struct tray_status *status = &data->status;
	char msg_type[16];

	if (sscanf(data->parse_buf, "%16s", msg_type) == 1) {
		odprintf("msg_type: %s", msg_type);
		if (!strcmp(msg_type, "SENSD")) {
			data->def_sensor = 1;
		} else if (!strcmp(msg_type, "SENSR")) {
			data->def_sensor = 0;
		} else if (data->def_sensor) {
			if (!strcmp(msg_type, "TEMPC")) {
				if (sscanf(data->parse_buf, "%*s %lf", &status->temperature_celsius) != 1)
					status->temperature_celsius = NAN;
			} else if (!strcmp(msg_type, "RHUM%")) {
				if (sscanf(data->parse_buf, "%*s %lf", &status->relative_humidity) != 1)
					status->relative_humidity = NAN;
			} else if (!strcmp(msg_type, "DEWPC")) {
				if (sscanf(data->parse_buf, "%*s %lf", &status->dew_point) != 1)
					status->dew_point = NAN;
			} else if (!strcmp(msg_type, "SENSF")) {
				tray_update(hWnd, data);
			}
		}
	}
}