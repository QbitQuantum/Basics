/**
 * @brief
 *      This function provides the port forwarding feature for forwarding the
 *      X data from mom to qsub and from qsub to the X server.
 *
 * @param socks[in] - Input structure which tracks the sockets that are active
 *                    and data read/written by peers.
 * @param connfunc[in] - Function pointer pointing to a function used for
 *                       either connecting the X server (if running in qsub) or
 *                       connecting qsub (if running in mom).
 * @param phost[in] - peer host that needs to be connected.
 * @param pport[in] - peer port number.
 * @param inter_read_sock[in] -  socket descriptor from where mom and qsub
 *                               readers read data.
 * @param readfunc[in] - function pointer pointing to the mom and qsub readers.
 * @param logfunc[in] - Function pointer for log function
 *
 * @return void
 */
void
port_forwarder(
	struct pfwdsock *socks,
	int (*connfunc)(char *, long),
	char *phost,
	int pport,
	int inter_read_sock,
	int (*readfunc)(int),
	void (*logfunc) (char *))
{
	fd_set rfdset, wfdset, efdset;
	int rc;
	struct sockaddr_in from;
	pbs_socklen_t fromlen;
	int n, n2, sock;
	fromlen = sizeof(from);
	char err_msg[LOG_BUF_SIZE];
	int readfunc_ret;
        /*
         * Make the sockets in the socks structure non blocking
         */
	for (n = 0; n < NUM_SOCKS; n++) {
		if (!(socks + n)->active || ((socks + n)->sock < 0))
			continue;
		if (set_nonblocking((socks + n)->sock) == -1) {
			close((socks + n)->sock);
			(socks + n)->active = 0;
			snprintf(err_msg, sizeof(err_msg),
				"set_nonblocking failed for socket=%d, errno=%d",
				(socks + n)->sock, errno);
			PF_LOGGER(logfunc, err_msg);
			continue;
		}
		if (set_nodelay((socks + n)->sock) == -1) {
			snprintf(err_msg, sizeof(err_msg),
				"set_nodelay failed for socket=%d, errno=%d",
				(socks + n)->sock, errno);
			PF_LOGGER(logfunc, err_msg);
		}
	}

	while (x11_reader_go) {
		int maxsock;

		FD_ZERO(&rfdset);
		FD_ZERO(&wfdset);
		FD_ZERO(&efdset);
		maxsock = inter_read_sock + 1;
		/*setting the sock fd in rfdset for qsub and mom readers to read data*/
		FD_SET(inter_read_sock, &rfdset);
		FD_SET(inter_read_sock, &efdset);
		for (n = 0; n < NUM_SOCKS; n++) {
			if (!(socks + n)->active || ((socks + n)->sock < 0))
				continue;

			if ((socks + n)->listening) {
				FD_SET((socks + n)->sock, &rfdset);
				maxsock = (socks + n)->sock > maxsock ?(socks + n)->sock : maxsock;
			} else{
				if ((socks + n)->bufavail < PF_BUF_SIZE) {
					FD_SET((socks + n)->sock, &rfdset);
					maxsock = (socks + n)->sock > maxsock ?(socks + n)->sock : maxsock;
				}
				if ((socks + ((socks + n)->peer))->bufavail -
					(socks + ((socks + n)->peer))->bufwritten > 0) {
					FD_SET((socks + n)->sock, &wfdset);
					maxsock = (socks + n)->sock > maxsock ?(socks + n)->sock : maxsock;
				}
			}

		}

		maxsock++;

		rc = select(maxsock, &rfdset, &wfdset, &efdset, NULL);
		if ((rc == -1) && (errno == EINTR))
			continue;
		if (rc < 0) {
			snprintf(err_msg, sizeof(err_msg),
				"port forwarding select() error");
			PF_LOGGER(logfunc, err_msg);
			return;
		}
		if (FD_ISSET(inter_read_sock, &efdset)) {
			snprintf(err_msg, sizeof(err_msg),
				"exception for socket=%d, errno=%d",
				inter_read_sock, errno);
			PF_LOGGER(logfunc, err_msg);
			close(inter_read_sock);
			return;
		}
		if (FD_ISSET(inter_read_sock, &rfdset)) {
			/*calling mom/qsub readers*/
			readfunc_ret = readfunc(inter_read_sock);
			if (readfunc_ret == -1) {
				snprintf(err_msg, sizeof(err_msg),
					"readfunc failed for socket:%d", inter_read_sock);
				PF_LOGGER(logfunc, err_msg);
			}
			if (readfunc_ret  < 0) {
				return;
			}
		}

		for (n = 0; n < NUM_SOCKS; n++) {
			if (!(socks + n)->active || ((socks + n)->sock < 0))
				continue;
			if (FD_ISSET((socks + n)->sock, &rfdset)) {
				if ((socks + n)->listening && (socks + n)->active) {
					int newsock = 0, peersock = 0;
					if ((sock = accept((socks + n)->sock, (struct sockaddr *)
						& from, &fromlen)) < 0) {
						if ((errno == EAGAIN) || (errno == EWOULDBLOCK)
							|| (errno == EINTR) || (errno == ECONNABORTED))
							continue;
						snprintf(err_msg, sizeof(err_msg),
							"closing the socket %d after accept call failure, errno=%d",
							(socks + n)->sock, errno);
						PF_LOGGER(logfunc, err_msg);
						close((socks + n)->sock);
						(socks + n)->active = 0;
						continue;
					}
                                        /*
                                         * Make the sock non blocking
                                         */
					if (set_nonblocking(sock) == -1) {
						snprintf(err_msg, sizeof(err_msg),
							"set_nonblocking failed for socket=%d, errno=%d",
							sock, errno);
						PF_LOGGER(logfunc, err_msg);
						close(sock);
						continue;
					}
					if (set_nodelay(sock) == -1) {
						snprintf(err_msg, sizeof(err_msg),
							"set_nodelay failed for socket=%d, errno=%d",
							sock, errno);
						PF_LOGGER(logfunc, err_msg);
					}

					newsock = peersock = 0;

					for (n2 = 0; n2 < NUM_SOCKS; n2++) {
						if ((socks + n2)->active || (((socks + n2)->peer != 0)
							&& (socks + ((socks + n2)->peer))->active))
							continue;
						if (newsock == 0)
							newsock = n2;
						else if (peersock == 0)
							peersock = n2;
						else
							break;
					}

					(socks + newsock)->sock = (socks + peersock)->remotesock
						= sock;
					(socks + newsock)->listening = (socks + peersock)->listening
						= 0;
					(socks + newsock)->active = (socks + peersock)->active = 1;
					(socks + peersock)->sock = connfunc(phost, pport);
                                        /*
                                         * Make sockets non-blocking
                                         */
					if (set_nonblocking((socks + peersock)->sock) == -1) {
						snprintf(err_msg, sizeof(err_msg),
							"set_nonblocking failed for socket=%d, errno=%d",
							(socks + peersock)->sock, errno);
						PF_LOGGER(logfunc, err_msg);
						close((socks + peersock)->sock);
						(socks + peersock)->active = 0;
						continue;
					}
					if (set_nodelay((socks + peersock)->sock) == -1) {
						snprintf(err_msg, sizeof(err_msg),
							"set_nodelay failed for socket=%d, errno=%d",
							(socks + peersock)->sock, errno);
						PF_LOGGER(logfunc, err_msg);
					}
					(socks + newsock)->bufwritten = (socks + peersock)->bufwritten = 0;
					(socks + newsock)->bufavail = (socks + peersock)->bufavail = 0;
					(socks + newsock)->buff[0] = (socks + peersock)->buff[0] = '\0';
					(socks + newsock)->peer = peersock;
					(socks + peersock)->peer = newsock;
				} else{
					/* non-listening socket to be read */
					rc = read(
						(socks + n)->sock,
						(socks + n)->buff + (socks + n)->bufavail,
						PF_BUF_SIZE - (socks + n)->bufavail);
					if (rc == -1) {
						if ((errno == EWOULDBLOCK) || (errno == EAGAIN) || (errno == EINTR) || (errno == EINPROGRESS)) {
							continue;
						}
						shutdown((socks + n)->sock, SHUT_RDWR);
						close((socks + n)->sock);
						(socks + n)->active = 0;
						snprintf(err_msg, sizeof(err_msg),
							"closing the socket %d after read failure, errno=%d",
							(socks + n)->sock, errno);
						PF_LOGGER(logfunc, err_msg);
					} else if (rc == 0) {
						shutdown((socks + n)->sock, SHUT_RDWR);
						close((socks + n)->sock);
						(socks + n)->active = 0;
					} else{
						(socks + n)->bufavail += rc;
					}
				}
			} /* END if rfdset */
			if (FD_ISSET((socks + n)->sock, &wfdset)) {
				int peer = (socks + n)->peer;

				rc = write(
					(socks + n)->sock,
					(socks + peer)->buff + (socks + peer)->bufwritten,
					(socks + peer)->bufavail - (socks + peer)->bufwritten);

				if (rc == -1) {
					if ((errno == EWOULDBLOCK) || (errno == EAGAIN) || (errno == EINTR) || (errno == EINPROGRESS)) {
						continue;
					}
					shutdown((socks + n)->sock, SHUT_RDWR);
					close((socks + n)->sock);
					(socks + n)->active = 0;
					snprintf(err_msg, sizeof(err_msg),
						"closing the socket %d after write failure, errno=%d",
						(socks + n)->sock, errno);
					PF_LOGGER(logfunc, err_msg);
				} else if (rc == 0) {
					shutdown((socks + n)->sock, SHUT_RDWR);
					close((socks + n)->sock);
					(socks + n)->active = 0;
				} else{
					(socks + peer)->bufwritten += rc;
				}
			} /* END if wfdset */
			if (!(socks + n)->listening) {
				int peer = (socks + n)->peer;
				if ((socks + peer)->bufavail == (socks + peer)->bufwritten) {
					(socks + peer)->bufavail = (socks + peer)->bufwritten = 0;
				}
				if (!(socks + peer)->active && ((socks + peer)->bufwritten
					== (socks + peer)->bufavail)) {
					shutdown((socks + n)->sock, SHUT_RDWR);
					close((socks + n)->sock);
					(socks + n)->active = 0;
				}
			}

		} /* END foreach fd */


	} /* END while(x11_reader_go) */
}  /* END port_forwarder() */