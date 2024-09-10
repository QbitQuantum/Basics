/*!
** @brief Get the full DAG of the local socket.
**
** @param sockfd An Xsocket of type SOCK_STREAM
** @param dag A sockaddr to hold the returned DAG.
** @param len On input contans the size of the sockaddr,
**  on output contains sizeof(sockaddr_x).
**
** @returns 0 on success
** @returns -1 on failure with errno set
** @returns errno = EFAULT if dag is NULL
** @returns errno = EOPNOTSUPP if sockfd is not of type XSSOCK_STREAM
** @returns errno = ENOTCONN if sockfd is not in a connected state
**
*/
int Xgetsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int rc;
	int flags;
	char buf[MAXBUFLEN];

	if (!addr || !addrlen) {
		LOG("pointer is null!\n");
		errno = EFAULT;
		return -1;
	}

	if (*addrlen < sizeof(sockaddr_x)) {
		errno = EINVAL;
		return -1;
	}

	if (validateSocket(sockfd, XSOCK_STREAM, EOPNOTSUPP) < 0) {
		LOG("Xgetsockname is only valid with stream sockets.");
		return -1;
	}

	if (connState(sockfd) != CONNECTED) {
		LOGF("Socket %d is not connected", sockfd);
		errno = ENOTCONN;
		return -1;
	}

	xia::XSocketMsg xsm;
	xsm.set_type(xia::XGETSOCKNAME);

	flags = Xfcntl(sockfd, F_GETFL);
	fcntl(sockfd, F_SETFL, flags & ~O_NONBLOCK);

	// send the protobuf containing the user data to click
    if ((rc = click_send(sockfd, &xsm)) < 0) {
		LOGF("Error talking to Click: %s", strerror(errno));
		fcntl(sockfd, F_SETFL, flags);
		return -1;
	}

	// get the dag
	// FIXME: loop here till done or error
	if ((rc = click_reply(sockfd, xia::XGETSOCKNAME, buf, sizeof(buf))) < 0) {
		LOGF("Error retrieving status from Click: %s", strerror(errno));
		fcntl(sockfd, F_SETFL, flags);
		return -1;
	}

	fcntl(sockfd, F_SETFL, flags);

	xsm.Clear();
	xsm.ParseFromString(buf);

	if (xsm.type() != xia::XGETSOCKNAME) {
		LOGF("error: expected %d, got %d\n", xia::XGETPEERNAME, xsm.type());
		return -1;
	}

	xia::X_GetSockname_Msg *msg = xsm.mutable_x_getsockname();

	Graph g(msg->dag().c_str());

	g.fill_sockaddr((sockaddr_x*)addr);
	*addrlen = sizeof(sockaddr_x);

	return 0;
}