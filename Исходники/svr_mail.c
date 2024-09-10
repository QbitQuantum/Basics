/**
 * @brief
 *  	A thread safe way to connect to hostaddr at port
 *
 * @param[in]	host	-	destination host machine
 * @param[in]	port	-	port number
 *
 * @return	int
 * @retval	0	: success
 * @retval	-1	: error and errno will be set.
 */
int
create_socket_and_connect(char *host, unsigned int port)
{
	struct sockaddr_in remote;
	int		 sock;

	int		ret;
	int		non_block = 1;
	fd_set	writeset;
	struct	timeval tv;
	struct in_addr  haddr;
	unsigned long hostaddr;
	struct hostent *hp;

	hp = gethostbyname(host);
	if (hp == NULL) {
		errno = WSAGetLastError();
		return (-1);
	}

	memcpy((void *)&haddr, (void *)hp->h_addr_list[0], hp->h_length);
	hostaddr = ntohl(haddr.s_addr);

	/* get socket					*/

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		errno = WSAGetLastError();
		return (-1);
	}
	/*	If local privilege port requested, bind to one	*/
	/*	Must be root privileged to do this		*/

	/*	connect to specified server host and port	*/

	remote.sin_addr.s_addr = htonl(hostaddr);
	remote.sin_port = htons((unsigned short)port);
	remote.sin_family = AF_INET;

	/* force socket to be non-blocking so we can timeout wait on it */

	if (ioctlsocket(sock, FIONBIO, &non_block) == SOCKET_ERROR) {
		errno = WSAGetLastError();
		return (-1);
	}
	FD_ZERO(&writeset);
	FD_SET((unsigned int)sock, &writeset);
	tv.tv_sec = 20;		/* connect timeout */
	tv.tv_usec = 0;

	if (connect(sock, (struct sockaddr *)&remote, sizeof(remote)) < 0) {
		errno = WSAGetLastError();
		switch (errno) {
			case WSAEINTR:
			case WSAEADDRINUSE:
			case WSAETIMEDOUT:
			case WSAECONNREFUSED:
				closesocket(sock);
				return (-1);
			case WSAEWOULDBLOCK:
				ret = select(1, NULL, &writeset, NULL, &tv);
				if (ret <= 0) {
					return (-1);
				}
				/* reset to blocking */
				non_block = 0;
				if (ioctlsocket(sock, FIONBIO, &non_block) == SOCKET_ERROR) {
					errno = WSAGetLastError();
					return (-1);
				}
				return (sock);
			default:
				closesocket(sock);
				return (-1);
		}

	} else {
		return (sock);
	}
}