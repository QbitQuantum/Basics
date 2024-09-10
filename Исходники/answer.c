answer()
{
	register PLAYER		*pp;
	register int		newsock;
	register FILE		*tmpfd;
# ifdef MONITOR
	static FLAG		monitor;
# endif MONITOR
	static char		name[NAMELEN];
	static int		socklen;
	static u_long		machine;
	static u_long		uid;
	static SOCKET		sockstruct;
# ifdef OLDIPC
	extern SOCKET		Daemon;
# endif OLDIPC

# ifdef INTERNET
	socklen = sizeof sockstruct;
# else
	socklen = sizeof sockstruct - 1;
# endif INTERNET
	errno = 0;
# ifndef OLDIPC
	if ((newsock = accept(Socket, &sockstruct, &socklen)) < 0)
# else OLDIPC
	if (accept(Socket, &sockstruct) < 0)
# endif OLDIPC
	{
		if (errno == EINTR)
			return;
		perror("accept");
		cleanup(1);
	}
# ifdef OLDIPC
	newsock = Socket;
	Socket = socket(SOCK_STREAM, 0, (struct sockaddr *) &Daemon,
		SO_ACCEPTCONN);
	if (Socket < 0) {
		perror("new accept socket");
		cleanup(1);
	}
	Sock_mask = (1 << Socket);
	Fds_mask |= Sock_mask;
	if (Socket >= Num_fds)
		Num_fds = Socket + 1;
# endif OLDIPC

	tmpfd = fdopen(newsock, "w");

# ifdef INTERNET
	machine = ntohl(((struct sockaddr_in *) &sockstruct)->sin_addr.s_addr);
# else INTERNET
	if (machine == 0)
		machine = gethostid();
# endif INTERNET
	(void) putw(getpid(), tmpfd);
	(void) read(newsock, (char *) &uid, sizeof uid);
	uid = ntohl(uid);
	(void) read(newsock, name, NAMELEN);
	(void) read(newsock, Ttyname, NAMELEN);
# ifdef MONITOR
	(void) read(newsock, (char *) &monitor, sizeof monitor);
# endif MONITOR

	if (reached_limit(machine)) {
		socklen = 0;
		(void) write(newsock, (char *) &socklen, sizeof socklen);
		(void) close(newsock);
# ifdef OLDIPC
		Fds_mask &= ~(1 << newsock);
# endif OLDIPC
		return;
	}

# ifdef MONITOR
	if (monitor)
		if (End_monitor < &Monitor[MAXMON])
			pp = End_monitor++;
		else {
			socklen = 0;
			(void) write(newsock, (char *) &socklen,
				sizeof socklen);
			(void) close(newsock);
			return;
		}
	else
# endif MONITOR
		if (End_player < &Player[MAXPL])
			pp = End_player++;
		else {
			socklen = 0;
			(void) write(newsock, (char *) &socklen,
				sizeof socklen);
			(void) close(newsock);
			return;
		}

	pp->p_ident = get_ident(machine, uid, name);
	pp->p_output = tmpfd;
	pp->p_death[0] = '\0';
	pp->p_fd = newsock;
	pp->p_mask = (1 << pp->p_fd);
# ifndef OLDIPC
	Fds_mask |= pp->p_mask;
	if (pp->p_fd >= Num_fds)
		Num_fds = pp->p_fd + 1;
# endif OLDIPC

	pp->p_y = 0;
	pp->p_x = 0;

# ifdef MONITOR
	if (monitor)
		stmonitor(pp);
	else
# endif MONITOR
		stplayer(pp);
}