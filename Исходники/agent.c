static void agent_run(unsigned const char key[KDF_HASH_LEN])
{
	_cleanup_free_ char *path;
	char *agent_timeout_str;
	unsigned int agent_timeout;
	struct sockaddr_un sa, listensa;
	struct ucred cred;
	int fd, listenfd;
	socklen_t len;

	signal(SIGHUP, agent_cleanup);
	signal(SIGINT, agent_cleanup);
	signal(SIGQUIT, agent_cleanup);
	signal(SIGTERM, agent_cleanup);
	signal(SIGALRM, agent_cleanup);
	agent_timeout_str = getenv("LPASS_AGENT_TIMEOUT");
	agent_timeout = 60 * 60; /* One hour by default. */
	if (agent_timeout_str && strlen(agent_timeout_str))
		agent_timeout = strtoul(agent_timeout_str, NULL, 10);
	if (agent_timeout)
		alarm(agent_timeout);

	path = agent_socket_path();
	if (strlen(path) >= sizeof(sa.sun_path))
		die("Path too large for agent control socket.");

	fd = socket(AF_UNIX, SOCK_STREAM, 0);

	memset(&sa, 0, sizeof(sa));
	sa.sun_family = AF_UNIX;
	strlcpy(sa.sun_path, path, sizeof(sa.sun_path));

	unlink(path);

	if (bind(fd, (struct sockaddr *)&sa, SUN_LEN(&sa)) < 0 || listen(fd, 16) < 0) {
		listenfd = errno;
		close(fd);
		unlink(path);
		errno = listenfd;
		die_errno("bind|listen");
	}

	for (len = sizeof(listensa); (listenfd = accept(fd, (struct sockaddr *)&listensa, &len)) > 0; len = sizeof(listensa)) {
		if (agent_socket_get_cred(listenfd, &cred) < 0) {
			close(listenfd);
			continue;
		}
		if (cred.uid != getuid() || cred.gid != getgid() || !process_is_same_executable(cred.pid)) {
			close(listenfd);
			continue;
		}

#if SOCKET_SEND_PID == 1
		pid_t pid = getpid();
		IGNORE_RESULT(write(listenfd, &pid, sizeof(pid)));
#endif
		IGNORE_RESULT(write(listenfd, key, KDF_HASH_LEN));
		close(listenfd);
	}

	listenfd = errno;
	close(fd);
	unlink(path);
	errno = listenfd;
	die_errno("accept");
}