/*
 *  stress_socket_client()
 *	client reader
 */
static void stress_socket_client(
	uint64_t *const counter,
	const uint32_t instance,
	const uint64_t max_ops,
	const char *name,
	const pid_t ppid)
{
	struct sockaddr *addr;

	setpgid(0, pgrp);
	stress_parent_died_alarm();

	do {
		char buf[SOCKET_BUF];
		int fd;
		int retries = 0;
		socklen_t addr_len = 0;
retry:
		if (!opt_do_run) {
			(void)kill(getppid(), SIGALRM);
			exit(EXIT_FAILURE);
		}
		if ((fd = socket(opt_socket_domain, SOCK_STREAM, 0)) < 0) {
			pr_fail_dbg(name, "socket");
			/* failed, kick parent to finish */
			(void)kill(getppid(), SIGALRM);
			exit(EXIT_FAILURE);
		}

		stress_set_sockaddr(name, instance, ppid,
			opt_socket_domain, opt_socket_port,
			&addr, &addr_len);
		if (connect(fd, addr, addr_len) < 0) {
			(void)close(fd);
			usleep(10000);
			retries++;
			if (retries > 100) {
				/* Give up.. */
				pr_fail_dbg(name, "connect");
				(void)kill(getppid(), SIGALRM);
				exit(EXIT_FAILURE);
			}
			goto retry;
		}

		do {
			ssize_t n = recv(fd, buf, sizeof(buf), 0);
			if (n == 0)
				break;
			if (n < 0) {
				if (errno != EINTR)
					pr_fail_dbg(name, "recv");
				break;
			}
		} while (opt_do_run && (!max_ops || *counter < max_ops));
		(void)shutdown(fd, SHUT_RDWR);
		(void)close(fd);
	} while (opt_do_run && (!max_ops || *counter < max_ops));

#ifdef AF_UNIX
	if (opt_socket_domain == AF_UNIX) {
		struct sockaddr_un *addr_un = (struct sockaddr_un *)addr;
		(void)unlink(addr_un->sun_path);
	}
#endif
	/* Inform parent we're all done */
	(void)kill(getppid(), SIGALRM);
}