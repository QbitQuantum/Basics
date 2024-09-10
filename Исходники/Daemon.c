/* 
 * prepare_listen_socket: 
 * It creates a new socket of the desired `family' and binds it to the 
 * specified `port'. It sets also the reuseaddr and NONBLOCK
 * socket options, because this new socket shall be used to listen() and
 * accept().
 * If `dev' is not null, the socket will be binded to the device named 
 * `dev'->dev_name with the SO_BINDTODEVICE socket option.
 * The created socket is returned.
 */
int
prepare_listen_socket(int family, int socktype, u_short port,
					  interface * dev)
{
	struct addrinfo hints, *ai, *aitop;
	char strport[NI_MAXSERV];
	int err, s;

	setzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_flags = AI_PASSIVE;
	snprintf(strport, NI_MAXSERV, "%u", port);

	err = getaddrinfo(NULL, strport, &hints, &aitop);
	if (err) {
		error("Getaddrinfo error: %s", gai_strerror(err));
		return -1;
	}

	for (ai = aitop; ai; ai = ai->ai_next) {
		if (ai->ai_family != AF_INET && ai->ai_family != AF_INET6)
			continue;

		s = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (s == -1)
			/* Maybe we can use another socket... */
			continue;

		/* Bind the created socket to the device named dev->dev_name */
		if (dev && (set_bindtodevice_sk(s, dev->dev_name) < 0)) {
			inet_close(&s);
			continue;
		}

		if (set_reuseaddr_sk(s) < 0) {
			inet_close(&s);
			continue;
		}

		/* Let's bind it! */
		if (bind(s, ai->ai_addr, ai->ai_addrlen) < 0) {
			error("Cannot bind the port %d: %s. Trying another "
				  "socket...", port, strerror(errno));
			inet_close(&s);
			continue;
		}
		freeaddrinfo(aitop);
		return s;
	}

	error("Cannot open inbound socket on port %d: %s", port,
		  strerror(errno));
	freeaddrinfo(aitop);
	return -1;
}