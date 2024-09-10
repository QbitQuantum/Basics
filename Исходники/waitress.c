/*	Receive data from host and call *callback ()
 *	@param waitress handle
 *	@return WaitressReturn_t
 */
WaitressReturn_t WaitressFetchCall (WaitressHandle_t *waith) {
	struct addrinfo hints, *res;
	int sockfd;
	char recvBuf[WAITRESS_RECV_BUFFER];
	char writeBuf[2*1024];
	ssize_t recvSize = 0;
	WaitressReturn_t wRet = WAITRESS_RET_OK;
	struct pollfd sockpoll;
	int pollres;
	/* header parser vars */
	char *nextLine = NULL, *thisLine = NULL;
	enum {HDRM_HEAD, HDRM_LINES, HDRM_FINISHED} hdrParseMode = HDRM_HEAD;
	char statusCode[3], val[256];
	unsigned int bufFilled = 0;

	/* initialize */
	waith->contentLength = 0;
	waith->contentReceived = 0;
	memset (&hints, 0, sizeof hints);

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	/* Use proxy? */
	if (WaitressProxyEnabled (waith)) {
		if (getaddrinfo (waith->proxyHost, waith->proxyPort, &hints, &res) != 0) {
			return WAITRESS_RET_GETADDR_ERR;
		}
	} else {
		if (getaddrinfo (waith->host, waith->port, &hints, &res) != 0) {
			return WAITRESS_RET_GETADDR_ERR;
		}
	}

	if ((sockfd = socket (res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
		freeaddrinfo (res);
		return WAITRESS_RET_SOCK_ERR;
	}
	sockpoll.fd = sockfd;

	fcntl (sockfd, F_SETFL, O_NONBLOCK);
	/* increase socket receive buffer */
	const int sockopt = 256*1024;
	setsockopt (sockfd, SOL_SOCKET, SO_RCVBUF, &sockopt, sizeof (sockopt));

	/* non-blocking connect will return immediately */
	connect (sockfd, res->ai_addr, res->ai_addrlen);

	sockpoll.events = POLLOUT;
	pollres = poll (&sockpoll, 1, waith->socktimeout);
	freeaddrinfo (res);
	if (pollres == 0) {
		return WAITRESS_RET_TIMEOUT;
	} else if (pollres == -1) {
		return WAITRESS_RET_ERR;
	}
	/* check connect () return value */
	socklen_t pollresSize = sizeof (pollres);
	getsockopt (sockfd, SOL_SOCKET, SO_ERROR, &pollres, &pollresSize);
	if (pollres != 0) {
		return WAITRESS_RET_CONNECT_REFUSED;
	}

	/* send request */
	if (WaitressProxyEnabled (waith)) {
		snprintf (writeBuf, sizeof (writeBuf),
			"%s http://%s:%s%s HTTP/1.0\r\n",
			(waith->method == WAITRESS_METHOD_GET ? "GET" : "POST"),
			waith->host, waith->port, waith->path);
	} else {
		snprintf (writeBuf, sizeof (writeBuf),
			"%s %s HTTP/1.0\r\n",
			(waith->method == WAITRESS_METHOD_GET ? "GET" : "POST"),
			waith->path);
	}
	WRITE_RET (writeBuf, strlen (writeBuf));

	snprintf (writeBuf, sizeof (writeBuf),
			"Host: %s\r\nUser-Agent: " PACKAGE "\r\n", waith->host);
	WRITE_RET (writeBuf, strlen (writeBuf));

	if (waith->method == WAITRESS_METHOD_POST && waith->postData != NULL) {
		snprintf (writeBuf, sizeof (writeBuf), "Content-Length: %zu\r\n",
				strlen (waith->postData));
		WRITE_RET (writeBuf, strlen (writeBuf));
	}
	
	if (waith->extraHeaders != NULL) {
		WRITE_RET (waith->extraHeaders, strlen (waith->extraHeaders));
	}
	
	WRITE_RET ("\r\n", 2);

	if (waith->method == WAITRESS_METHOD_POST && waith->postData != NULL) {
		WRITE_RET (waith->postData, strlen (waith->postData));
	}

	/* receive answer */
	nextLine = recvBuf;
	while (hdrParseMode != HDRM_FINISHED) {
		READ_RET (recvBuf+bufFilled, sizeof (recvBuf)-1 - bufFilled, &recvSize);
		if (recvSize == 0) {
			/* connection closed too early */
			CLOSE_RET (WAITRESS_RET_CONNECTION_CLOSED);
		}
		bufFilled += recvSize;
		memset (recvBuf+bufFilled, 0, sizeof (recvBuf) - bufFilled);
		thisLine = recvBuf;

		/* split */
		while ((nextLine = strchr (thisLine, '\n')) != NULL &&
				hdrParseMode != HDRM_FINISHED) {
			/* make lines parseable by string routines */
			*nextLine = '\0';
			if (*(nextLine-1) == '\r') {
				*(nextLine-1) = '\0';
			}
			/* skip \0 */
			++nextLine;

			switch (hdrParseMode) {
				/* Status code */
				case HDRM_HEAD:
					if (sscanf (thisLine, "HTTP/1.%*1[0-9] %3[0-9] ",
							statusCode) == 1) {
						if (memcmp (statusCode, "200", 3) == 0 ||
								memcmp (statusCode, "206", 3) == 0) {
							/* everything's fine... */
						} else if (memcmp (statusCode, "403", 3) == 0) {
							CLOSE_RET (WAITRESS_RET_FORBIDDEN);
						} else if (memcmp (statusCode, "404", 3) == 0) {
							CLOSE_RET (WAITRESS_RET_NOTFOUND);
						} else {
							CLOSE_RET (WAITRESS_RET_STATUS_UNKNOWN);
						}
						hdrParseMode = HDRM_LINES;
					} /* endif */
					break;

				/* Everything else, except status code */
				case HDRM_LINES:
					/* empty line => content starts here */
					if (*thisLine == '\0') {
						hdrParseMode = HDRM_FINISHED;
					} else {
						memset (val, 0, sizeof (val));
						if (sscanf (thisLine, "Content-Length: %255c", val) == 1) {
							waith->contentLength = atol (val);
						}
					}
					break;

				default:
					break;
			} /* end switch */
			thisLine = nextLine;
		} /* end while strchr */
		memmove (recvBuf, thisLine, thisLine-recvBuf);
		bufFilled -= (thisLine-recvBuf);
	} /* end while hdrParseMode */

	/* push remaining bytes */
	if (bufFilled > 0) {
		waith->contentReceived += bufFilled;
		if (waith->callback (thisLine, bufFilled, waith->data) ==
				WAITRESS_CB_RET_ERR) {
			CLOSE_RET (WAITRESS_RET_CB_ABORT);
		}
	}

	/* receive content */
	do {
		READ_RET (recvBuf, sizeof (recvBuf), &recvSize);
		if (recvSize > 0) {
			waith->contentReceived += recvSize;
			if (waith->callback (recvBuf, recvSize, waith->data) ==
					WAITRESS_CB_RET_ERR) {
				wRet = WAITRESS_RET_CB_ABORT;
				break;
			}
		}
	} while (recvSize > 0);

	close (sockfd);

	if (wRet == WAITRESS_RET_OK && waith->contentReceived < waith->contentLength) {
		return WAITRESS_RET_PARTIAL_FILE;
	}
	return wRet;
}