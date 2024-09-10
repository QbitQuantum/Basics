/*
 * Function: create_listen_socket()
 *
 * Descripton:
 *  Create a socket to listen for connections on a socket.
 *  The socket discripter is stored info_p->listen_sd.
 *
 * Argument:
 *  info_p:	pointer to a server infomation
 *
 * Return value:
 *  None
 */
void
create_listen_socket(struct server_info *info_p)
{
    int on;			/* on/off at an socket option */
    int err;			/* return value of getaddrinfo */
    struct addrinfo hints;	/* hints for getaddrinfo() */
    struct addrinfo *res;	/* pointer to addrinfo */

    /* Set the hints to addrinfo() */
    memset(&hints, '\0', sizeof(struct addrinfo));
    hints.ai_family = info_p->family;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    /* Translate the network and service information of the server */
    err = getaddrinfo(NULL, info_p->portnum, &hints, &res);
    if (err) {
	fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(err));
	exit(EXIT_FAILURE);
    }
    if (res->ai_next) {
	fprintf(stderr, "getaddrinfo(): multiple address is found.");
	exit(EXIT_FAILURE);
    }

    /* Create a socket for listening. */
    info_p->listen_sd = socket(res->ai_family,
	    res->ai_socktype, res->ai_protocol);
    if (info_p->listen_sd < 0)
	fatal_error("socket()");

#ifdef IPV6_V6ONLY
    /* Don't accept IPv4 mapped address if the protocol family is IPv6 */
    if (res->ai_family == PF_INET6) {
	on = 1;
	if (setsockopt(info_p->listen_sd,
		    IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(int)))
	    fatal_error("setsockopt()");
    }
#endif

    /* Enable to reuse the socket */
    on = 1;
    if (setsockopt(info_p->listen_sd,
		SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)))
	fatal_error("setsockopt()");

    /* Disable the Nagle algorithm, when small sending mode */
    if (info_p->small_sending) {
	on = 1;
	if (setsockopt(info_p->listen_sd,
		    IPPROTO_TCP, TCP_NODELAY, &on, sizeof(int)))
	    fatal_error("setsockopt()");
	if (debug) {
	    fprintf(stderr, "small sending[on]\n");
	}
    }

    /* Maximize socket buffer, when window scaling mode */
    if (info_p->window_scaling)
	maximize_sockbuf(info_p->listen_sd);

    /* Bind to the local address */
    if (bind(info_p->listen_sd, res->ai_addr, res->ai_addrlen) < 0)
	fatal_error("bind()");
    freeaddrinfo(res);

    /* Start to listen for connections */
    if (listen(info_p->listen_sd, 5) < 0)
	fatal_error("listen()");
}