/*
 * request - send a configuration request to the server, wait for a response
 */
static int
request(
	struct conf_peer *conf
	)
{
	struct sock_timeval tvout;
	struct req_pkt reqpkt;
	size_t	req_len;
	size_t	total_len;	/* req_len plus keyid & digest */
	fd_set	fdset;
	l_fp	ts;
	char *	pch;
	char *	pchEnd;
	l_fp *	pts;
	keyid_t *pkeyid;
	int n;
#ifdef SYS_WINNT
	HANDLE	hReadWriteEvent = NULL;
	BOOL	ret;
	DWORD	NumberOfBytesWritten, NumberOfBytesRead, dwWait;
	OVERLAPPED overlap;
#endif /* SYS_WINNT */

	checkparent();		/* make sure our guy is still running */

	if (sockfd == INVALID_SOCKET)
		openntp();
	
#ifdef SYS_WINNT
	hReadWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
#endif /* SYS_WINNT */

	/*
	 * Try to clear out any previously received traffic so it
	 * doesn't fool us.  Note the socket is nonblocking.
	 */
	tvout.tv_sec =  0;
	tvout.tv_usec = 0;
	FD_ZERO(&fdset);
	FD_SET(sockfd, &fdset);
	while (select(sockfd + 1, &fdset, (fd_set *)0, (fd_set *)0, &tvout) >
	       0) {
		recv(sockfd, (char *)&reqpkt, sizeof(reqpkt), 0);
		FD_ZERO(&fdset);
		FD_SET(sockfd, &fdset);
	}

	/*
	 * Make up a request packet with the configuration info
	 */
	memset(&reqpkt, 0, sizeof(reqpkt));

	reqpkt.rm_vn_mode = RM_VN_MODE(0, 0, 0);
	reqpkt.auth_seq = AUTH_SEQ(1, 0);	/* authenticated, no seq */
	reqpkt.implementation = IMPL_XNTPD;	/* local implementation */
	reqpkt.request = REQ_CONFIG;		/* configure a new peer */
	reqpkt.err_nitems = ERR_NITEMS(0, 1);	/* one item */
	reqpkt.mbz_itemsize = MBZ_ITEMSIZE(sizeof(*conf));
	/* Make sure mbz_itemsize <= sizeof reqpkt.data */
	if (sizeof(*conf) > sizeof(reqpkt.data)) {
		msyslog(LOG_ERR,
			"Bletch: conf_peer is too big for reqpkt.data!");
		resolver_exit(1);
	}
	memcpy(reqpkt.data, conf, sizeof(*conf));

	if (sys_authenticate && req_hashlen > 16) {
		pch = reqpkt.data; 
		/* 32-bit alignment */
		pch += (sizeof(*conf) + 3) & ~3;
		pts = (void *)pch;
		pkeyid = (void *)(pts + 1);
		pchEnd = (void *)pkeyid;
		req_len = pchEnd - (char *)&reqpkt;
		pchEnd = (void *)(pkeyid + 1);
		pchEnd += req_hashlen;
		total_len = pchEnd - (char *)&reqpkt;
		if (total_len > sizeof(reqpkt)) {
			msyslog(LOG_ERR,
				"intres total_len %u limit is %u (%u octet digest)\n",
				total_len, sizeof(reqpkt),
				req_hashlen);
			resolver_exit(1);
		}
	} else {
		pts = &reqpkt.tstamp;
		pkeyid = &reqpkt.keyid;
		req_len = REQ_LEN_NOMAC;
	}

	*pkeyid = htonl(req_keyid);
	get_systime(&ts);
	L_ADDUF(&ts, SKEWTIME);
	HTONL_FP(&ts, pts);
	if (sys_authenticate) {
		n = authencrypt(req_keyid, (void *)&reqpkt, req_len);
		if ((size_t)n != req_hashlen + sizeof(reqpkt.keyid)) {
			msyslog(LOG_ERR,
				"intres maclen %d expected %u\n",
				n, req_hashlen + sizeof(reqpkt.keyid));
			resolver_exit(1);
		}
		req_len += n;
	}

	/*
	 * Done.  Send it.
	 */
#ifndef SYS_WINNT
	n = send(sockfd, (char *)&reqpkt, req_len, 0);
	if (n < 0) {
		msyslog(LOG_ERR, "send to NTP server failed: %m");
		return 0;	/* maybe should exit */
	}
#else
	/* In the NT world, documentation seems to indicate that there
	 * exist _write and _read routines that can be used to do blocking
	 * I/O on sockets. Problem is these routines require a socket
	 * handle obtained through the _open_osf_handle C run-time API
	 * of which there is no explanation in the documentation. We need
	 * nonblocking write's and read's anyway for our purpose here.
	 * We're therefore forced to deviate a little bit from the Unix
	 * model here and use the ReadFile and WriteFile Win32 I/O API's
	 * on the socket
	 */
	overlap.Offset = overlap.OffsetHigh = (DWORD)0;
	overlap.hEvent = hReadWriteEvent;
	ret = WriteFile((HANDLE)sockfd, (char *)&reqpkt, req_len,
			NULL, (LPOVERLAPPED)&overlap);
	if ((ret == FALSE) && (GetLastError() != ERROR_IO_PENDING)) {
		msyslog(LOG_ERR, "send to NTP server failed: %m");
		return 0;
	}
	dwWait = WaitForSingleObject(hReadWriteEvent, (DWORD) TIMEOUT_SEC * 1000);
	if ((dwWait == WAIT_FAILED) || (dwWait == WAIT_TIMEOUT)) {
		if (dwWait == WAIT_FAILED)
		    msyslog(LOG_ERR, "WaitForSingleObject failed: %m");
		return 0;
	}
	if (!GetOverlappedResult((HANDLE)sockfd, (LPOVERLAPPED)&overlap,
				(LPDWORD)&NumberOfBytesWritten, FALSE)) {
		msyslog(LOG_ERR, "GetOverlappedResult for WriteFile fails: %m");
		return 0;
	}
#endif /* SYS_WINNT */


	/*
	 * Wait for a response.  A weakness of the mode 7 protocol used
	 * is that there is no way to associate a response with a
	 * particular request, i.e. the response to this configuration
	 * request is indistinguishable from that to any other.  I should
	 * fix this some day.  In any event, the time out is fairly
	 * pessimistic to make sure that if an answer is coming back
	 * at all, we get it.
	 */
	for (;;) {
		FD_ZERO(&fdset);
		FD_SET(sockfd, &fdset);
		tvout.tv_sec = TIMEOUT_SEC;
		tvout.tv_usec = TIMEOUT_USEC;

		n = select(sockfd + 1, &fdset, (fd_set *)0,
			   (fd_set *)0, &tvout);

		if (n < 0) {
			if (errno != EINTR)
				msyslog(LOG_ERR, "select() fails: %m");
			return 0;
		} else if (n == 0) {
#ifdef DEBUG
			if (debug)
				msyslog(LOG_INFO, "ntp_intres select() returned 0.");
#endif
			return 0;
		}

#ifndef SYS_WINNT
		n = recv(sockfd, (char *)&reqpkt, sizeof(reqpkt), 0);
		if (n <= 0) {
			if (n < 0) {
				msyslog(LOG_ERR, "recv() fails: %m");
				return 0;
			}
			continue;
		}
#else /* Overlapped I/O used on non-blocking sockets on Windows NT */
		ret = ReadFile((HANDLE)sockfd, (char *)&reqpkt, sizeof(reqpkt),
			       NULL, (LPOVERLAPPED)&overlap);
		if ((ret == FALSE) && (GetLastError() != ERROR_IO_PENDING)) {
			msyslog(LOG_ERR, "ReadFile() fails: %m");
			return 0;
		}
		dwWait = WaitForSingleObject(hReadWriteEvent, (DWORD) TIMEOUT_SEC * 1000);
		if ((dwWait == WAIT_FAILED) || (dwWait == WAIT_TIMEOUT)) {
			if (dwWait == WAIT_FAILED) {
				msyslog(LOG_ERR, "WaitForSingleObject for ReadFile fails: %m");
				return 0;
			}
			continue;
		}
		if (!GetOverlappedResult((HANDLE)sockfd, (LPOVERLAPPED)&overlap,
					(LPDWORD)&NumberOfBytesRead, FALSE)) {
			msyslog(LOG_ERR, "GetOverlappedResult fails: %m");
			return 0;
		}
		n = NumberOfBytesRead;
#endif /* SYS_WINNT */

		/*
		 * Got one.  Check through to make sure it is what
		 * we expect.
		 */
		if (n < RESP_HEADER_SIZE) {
			msyslog(LOG_ERR, "received runt response (%d octets)",
				n);
			continue;
		}

		if (!ISRESPONSE(reqpkt.rm_vn_mode)) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO, "received non-response packet");
#endif
			continue;
		}

		if (ISMORE(reqpkt.rm_vn_mode)) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO, "received fragmented packet");
#endif
			continue;
		}

		if ( ( (INFO_VERSION(reqpkt.rm_vn_mode) < 2)
		       || (INFO_VERSION(reqpkt.rm_vn_mode) > NTP_VERSION))
		     || INFO_MODE(reqpkt.rm_vn_mode) != MODE_PRIVATE) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO,
				    "version (%d/%d) or mode (%d/%d) incorrect",
				    INFO_VERSION(reqpkt.rm_vn_mode),
				    NTP_VERSION,
				    INFO_MODE(reqpkt.rm_vn_mode),
				    MODE_PRIVATE);
#endif
			continue;
		}

		if (INFO_SEQ(reqpkt.auth_seq) != 0) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO,
				    "nonzero sequence number (%d)",
				    INFO_SEQ(reqpkt.auth_seq));
#endif
			continue;
		}

		if (reqpkt.implementation != IMPL_XNTPD ||
		    reqpkt.request != REQ_CONFIG) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO,
				    "implementation (%d) or request (%d) incorrect",
				    reqpkt.implementation, reqpkt.request);
#endif
			continue;
		}

		if (INFO_NITEMS(reqpkt.err_nitems) != 0 ||
		    INFO_MBZ(reqpkt.mbz_itemsize) != 0 ||
		    INFO_ITEMSIZE(reqpkt.mbz_itemsize) != 0) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO,
				    "nitems (%d) mbz (%d) or itemsize (%d) nonzero",
				    INFO_NITEMS(reqpkt.err_nitems),
				    INFO_MBZ(reqpkt.mbz_itemsize),
				    INFO_ITEMSIZE(reqpkt.mbz_itemsize));
#endif
			continue;
		}

		n = INFO_ERR(reqpkt.err_nitems);
		switch (n) {
		    case INFO_OKAY:
			/* success */
			return 1;
		
		    case INFO_ERR_NODATA:
			/*
			 * newpeer() refused duplicate association, no
			 * point in retrying so call it success.
			 */
			return 1;
		
		    case INFO_ERR_IMPL:
			msyslog(LOG_ERR,
				"ntp_intres.request: implementation mismatch");
			return 0;
		
		    case INFO_ERR_REQ:
			msyslog(LOG_ERR,
				"ntp_intres.request: request unknown");
			return 0;
		
		    case INFO_ERR_FMT:
			msyslog(LOG_ERR,
				"ntp_intres.request: format error");
			return 0;

		    case INFO_ERR_AUTH:
			msyslog(LOG_ERR,
				"ntp_intres.request: permission denied");
			return 0;

		    default:
			msyslog(LOG_ERR,
				"ntp_intres.request: unknown error code %d", n);
			return 0;
		}
	}
}