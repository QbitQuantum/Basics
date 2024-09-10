int WINAPI new_WSAConnect(SOCKET s,
			  const struct sockaddr *name,
			  int namelen,
			  LPWSABUF lpCallerData,
			  LPWSABUF lpCalleeData,
			  LPQOS lpSQOS, LPQOS lpGQOS) {
    int rc, err;
    struct sockaddr_in in_addr;
    struct sockaddr_in out_addr;
    char buf[256];
    fd_set set;

    DEBUG_ENTER;

    memcpy(&in_addr, name, sizeof(in_addr));

    /* change non-local */
    if (in_addr.sin_addr.s_addr != inet_addr("127.0.0.1")) {
	DEBUG;
	out_addr.sin_family = AF_INET;
	out_addr.sin_port = htons(1080);
	out_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    }

    DEBUG;

    /* connect */
    _unhook(2);
    rc = WSAConnect(s, (struct sockaddr *) (&out_addr),
		    sizeof(struct sockaddr_in), lpCallerData,
		    lpCalleeData, lpSQOS, lpGQOS);
    err = WSAGetLastError();
#if defined(_DEBUG) || defined(_DEBUG_)
    TRACE_NO("connect (rc:%i err:%i pid:%i): %s\n", rc, err,
	     GetCurrentProcessId(), socketError());
#endif
    _hook(2);
    if (rc != 0 && err != WSAEWOULDBLOCK) {
	closesocket(s);
	DEBUG_LEAVE;
	return rc;
    }

    /* pass through local */
    if (in_addr.sin_addr.s_addr == inet_addr("127.0.0.1")) {
	DEBUG_LEAVE;
	return rc;
    }

    /* fd_set */
    FD_ZERO(&set);
    FD_SET(s, &set);
    /* sock5 handshake */
    select(s + 1, NULL, &set, NULL, 0);
    rc = send(s, "\x05\x01\x00", 3, 0);
#if defined(_DEBUG) || defined(_DEBUG_)
    TRACE_VERBOSE("send (rc:%i err:%i pid:%i): %s\n", rc,
		  WSAGetLastError(), GetCurrentProcessId(), socketError());
#endif
    if (rc != 3) {
	closesocket(s);
	DEBUG_LEAVE;
	return SOCKET_ERROR;
    }

    /* socks5 ack */
    select(s + 1, &set, NULL, NULL, 0);
    rc = recv(s, buf, 256, 0);
#if defined(_DEBUG) || defined(_DEBUG_)
    TRACE_VERBOSE("recv (rc:%i err:%i pid:%i): %s\n", rc,
		  WSAGetLastError(), GetCurrentProcessId(), socketError());
    DUMP(buf, rc);
#endif
    if (rc != 2) {
	closesocket(s);
	DEBUG_LEAVE;
	return SOCKET_ERROR;
    }

    /* socks5 request */
    memcpy(buf, "\x05\x01\x00\x01", 4);
    memcpy(buf + 4, &in_addr.sin_addr.s_addr, 4);
    memcpy(buf + 8, &in_addr.sin_port, 2);
    select(s + 1, NULL, &set, NULL, 0);
    rc = send(s, buf, 10, 0);
#if defined(_DEBUG) || defined(_DEBUG_)
    TRACE_VERBOSE("send (rc:%i err:%i pid:%i): %s\n", rc,
		  WSAGetLastError(), GetCurrentProcessId(), socketError());
#endif
    if (rc != 10) {
	closesocket(s);
	DEBUG_LEAVE;
	return SOCKET_ERROR;
    }

    /* socks5 ack */
    select(s + 1, &set, NULL, NULL, 0);
    rc = recv(s, buf, 256, 0);
#if defined(_DEBUG) || defined(_DEBUG_)
    TRACE_VERBOSE("recv (rc:%i err:%i pid:%i): %s\n", rc,
		  WSAGetLastError(), GetCurrentProcessId(), socketError());
    DUMP(buf, rc);
#endif
    if (rc != 10) {
	closesocket(s);
	DEBUG_LEAVE;
	return SOCKET_ERROR;
    }

    DEBUG_LEAVE;
    return 0;
}