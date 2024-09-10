/**
 * @brief
 *	Open a connection with a pbs server.
 *	Do not allow TCP to block us if Server host is down
 *	At this point, this does not attempt to find a fail_over Server
 *
 * @param[in]   server - specifies the server to which to connect
 * @param[in]   tout - timeout value for select
 *
 * @return int
 * @retval >= 0	index to the internal connection table representing the
 *		connection made.
 * @retval -1	error encountered in getting index
 */
int
pbs_connect_noblk(char *server, int tout)
{
	int out;
	int i;
	pbs_socklen_t l;
	int n;
	struct timeval tv;
	fd_set fdset;
	struct batch_reply *reply;
	char server_name[PBS_MAXSERVERNAME+1];
	unsigned int server_port;
	struct addrinfo *aip, *pai;
	struct addrinfo hints;
	struct sockaddr_in *inp;
	short int connect_err = 0;

	struct sockaddr_in sockname;
	pbs_socklen_t	 socknamelen;

#ifdef WIN32
	int     non_block = 1;
	struct sockaddr_in to_sock;
	struct sockaddr_in from_sock;
#endif

#ifndef WIN32
	int nflg;
	int oflg;
#endif

	/* initialize the thread context data, if not already initialized */
	if (pbs_client_thread_init_thread_context() != 0)
		return -1;

	if (pbs_loadconf(0) == 0)
		return -1;

	/* get server host and port	*/

	server = PBS_get_server(server, server_name, &server_port);
	if (server == NULL) {
		pbs_errno = PBSE_NOSERVER;
		return -1;
	}

	/* Reserve a connection state record */
	if (pbs_client_thread_lock_conntable() != 0)
		return -1;

	out = -1;
	for (i=1;i<NCONNECTS;i++) {
		if (connection[i].ch_inuse) continue;
		out = i;
		connection[out].ch_inuse = 1;
		connection[out].ch_errno = 0;
		connection[out].ch_socket= -1;
		connection[out].ch_errtxt = NULL;
		break;
	}

	if (pbs_client_thread_unlock_conntable() != 0)
		return -1; /* pbs_errno set by the function */

	if (out < 0) {
		pbs_errno = PBSE_NOCONNECTS;
		return -1;
	}


	/* get socket	*/

#ifdef WIN32
	/* the following lousy hack is needed since the socket call needs */
	/* SYSTEMROOT env variable properly set! */
	if (getenv("SYSTEMROOT") == NULL) {
		setenv("SYSTEMROOT", "C:\\WINNT", 1);
		setenv("SystemRoot", "C:\\WINNT", 1);
	}
	connection[out].ch_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (connection[out].ch_socket < 0) {
		setenv("SYSTEMROOT", "C:\\WINDOWS", 1);
		setenv("SystemRoot", "C:\\WINDOWS", 1);
		connection[out].ch_socket = socket(AF_INET, SOCK_STREAM, 0);
	}
#else
	connection[out].ch_socket = socket(AF_INET, SOCK_STREAM, 0);
#endif
	if (connection[out].ch_socket < 0) {
		connection[out].ch_inuse = 0;
		pbs_errno = ERRORNO;
		return -1;
	}

	/* set socket non-blocking */

#ifdef WIN32
	if (ioctlsocket(connection[out].ch_socket, FIONBIO, &non_block) == SOCKET_ERROR)
#else
	oflg = fcntl(connection[out].ch_socket, F_GETFL) & ~O_ACCMODE;
	nflg = oflg | O_NONBLOCK;
	if (fcntl(connection[out].ch_socket, F_SETFL, nflg) == -1)
#endif
		goto err;

	/* and connect... */

	strcpy(pbs_server, server);    /* set for error messages from commands */
	memset(&hints, 0, sizeof(struct addrinfo));
	/*
	 *      Why do we use AF_UNSPEC rather than AF_INET?  Some
	 *      implementations of getaddrinfo() will take an IPv6
	 *      address and map it to an IPv4 one if we ask for AF_INET
	 *      only.  We don't want that - we want only the addresses
	 *      that are genuinely, natively, IPv4 so we start with
	 *      AF_UNSPEC and filter ai_family below.
	 */
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(server, NULL, &hints, &pai) != 0) {
		CLOSESOCKET(connection[out].ch_socket);
		connection[out].ch_inuse = 0;
		pbs_errno = PBSE_BADHOST;
		return -1;
	}
	for (aip = pai; aip != NULL; aip = aip->ai_next) {
		/* skip non-IPv4 addresses */
		if (aip->ai_family == AF_INET) {
			inp = (struct sockaddr_in *) aip->ai_addr;
			break;
		}
	}
	if (aip == NULL) {
		/* treat no IPv4 addresses as getaddrinfo() failure */
		CLOSESOCKET(connection[out].ch_socket);
		connection[out].ch_inuse = 0;
		pbs_errno = PBSE_BADHOST;
		freeaddrinfo(pai);
		return -1;
	} else
		inp->sin_port = htons(server_port);
	if (connect(connection[out].ch_socket,
		aip->ai_addr,
		aip->ai_addrlen) < 0) {
		connect_err = 1;
	}
	if (connect_err == 1)
	{
		/* connect attempt failed */
		pbs_errno = ERRORNO;
		switch (pbs_errno) {
#ifdef WIN32
			case WSAEWOULDBLOCK:
#else
			case EINPROGRESS:
			case EWOULDBLOCK:
#endif
				while (1) {
					FD_ZERO(&fdset);
					FD_SET(connection[out].ch_socket, &fdset);
					tv.tv_sec = tout;
					tv.tv_usec = 0;
					n = select(connection[out].ch_socket+1, NULL, &fdset, NULL, &tv);
					if (n > 0) {
						pbs_errno = 0;
						l = sizeof(pbs_errno);
						(void)getsockopt(connection[out].ch_socket,
							SOL_SOCKET, SO_ERROR,
							&pbs_errno, &l);
						if (pbs_errno == 0)
							break;
						else
							goto err;
					} if ((n < 0) &&
#ifdef WIN32
						(ERRORNO == WSAEINTR)
#else
						(ERRORNO == EINTR)
#endif
						) {
						continue;
					} else {
						goto err;
					}
				}
				break;

			default:
err:
				CLOSESOCKET(connection[out].ch_socket);
				connection[out].ch_inuse = 0;
				freeaddrinfo(pai);
				return -1;	/* cannot connect */

		}
	}
	freeaddrinfo(pai);

	/* reset socket blocking */
#ifdef WIN32
	non_block = 0;
	if (ioctlsocket(connection[out].ch_socket, FIONBIO, &non_block) == SOCKET_ERROR)
#else
	if (fcntl(connection[out].ch_socket, F_SETFL, oflg) < 0)
#endif
		goto err;

	/*
	 * multiple threads cant get the same connection id above,
	 * so no need to lock this piece of code
	 */
	/* setup connection level thread context */
	if (pbs_client_thread_init_connect_context(out) != 0) {
		CLOSESOCKET(connection[out].ch_socket);
		connection[out].ch_inuse = 0;
		/* pbs_errno set by the pbs_connect_init_context routine */
		return -1;
	}
	/*
	 * even though the following is communication with server on
	 * a connection handle, it does not need to be lock since
	 * this connection handle has not be returned back yet to the client
	 * so others threads cannot use it
	 */

	/* send "dummy" connect message */
	DIS_tcp_setup(connection[out].ch_socket);
	if ((i = encode_DIS_ReqHdr(connection[out].ch_socket,
		PBS_BATCH_Connect, pbs_current_user)) ||
		(i = encode_DIS_ReqExtend(connection[out].ch_socket,
		NULL))) {
		pbs_errno = PBSE_SYSTEM;
		return -1;
	}
	if (DIS_tcp_wflush(connection[out].ch_socket)) {
		pbs_errno = PBSE_SYSTEM;
		return -1;
	}
	reply = PBSD_rdrpy(out);
	PBSD_FreeReply(reply);

	/*do configured authentication (kerberos, pbs_iff, whatever)*/

	/*Get the socket port for engage_authentication()*/
	socknamelen = sizeof(sockname);
	if (getsockname(connection[out].ch_socket, (struct sockaddr *)&sockname, &socknamelen))
		return -1;
	if (engage_authentication(connection[out].ch_socket,
		server,
		server_port,
		&sockname) == -1) {
		CLOSESOCKET(connection[out].ch_socket);
		connection[out].ch_inuse = 0;
		pbs_errno = PBSE_PERM;
		return -1;
	}

	/* setup DIS support routines for following pbs_* calls */
	DIS_tcp_setup(connection[out].ch_socket);
	pbs_tcp_timeout = PBS_DIS_TCP_TIMEOUT_VLONG;	/* set for 3 hours */

	return out;
}