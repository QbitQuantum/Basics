mpi_plugin_client_state_t *
p_mpi_hook_client_prelaunch(mpi_plugin_client_info_t *job, char ***env)
{
	struct sockaddr_in sin;
	pthread_attr_t attr;
	socklen_t len = sizeof(sin);
	short port1, port2;

	debug("Using mpi/mpich1_p4");
	if ((p4_fd1 = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		error("socket: %m");
		return NULL;
	}
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = PF_INET;
	if (bind(p4_fd1, (struct sockaddr *) &sin, len) < 0) {
		error("bind: %m");
		return NULL;
	}
	if (getsockname(p4_fd1, (struct sockaddr *) &sin, &len) < 0) {
		error("getsockname: %m");
		return NULL;
	}
	port1 = ntohs(sin.sin_port);

	if ((p4_fd2 = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		error("socket: %m");
		return NULL;
	}
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = PF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(p4_fd2, (struct sockaddr *) &sin, len) < 0) {
		error("bind: %m");
		return NULL;
	}
	if (listen(p4_fd2, 64) < 0)
		error("listen: %m");
	if (getsockname(p4_fd2, (struct sockaddr *) &sin, &len) < 0) {
		error("getsockname: %m");
		return NULL;
	}
	port2 = ntohs(sin.sin_port);

	if (pipe(shutdown_pipe) < 0) {
		error ("pipe: %m");
		return (NULL);
	}
	shutdown_complete = false;
	shutdown_timeout = 5;
	slurm_mutex_init(&shutdown_lock);
	pthread_cond_init(&shutdown_cond, NULL);

	/* Process messages in a separate thread */
	slurm_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (pthread_create(&p4_tid, &attr, &mpich1_thr, NULL)) {
		error("pthread_create: %m");
		slurm_attr_destroy(&attr);
		return NULL;
	}
	slurm_attr_destroy(&attr);
	env_array_overwrite_fmt(env, "SLURM_MPICH_PORT1", "%hu", port1);
	env_array_overwrite_fmt(env, "SLURM_MPICH_PORT2", "%hu", port2);
	debug("mpich_p4 plugin listening on fd=%d,%d ports=%d,%d",
		p4_fd1, p4_fd2, port1, port2);

	/* only return NULL on error */
	return (void *)0xdeadbeef;
}