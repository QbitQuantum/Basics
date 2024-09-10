int main(int argc, char **argv)
{
	int force = 0, lsock, csock, one = 0, jeden = 1, local_port;
	int detach = 1, sa_len, conn_limit = 0, optc;
	char *username = NULL, *bind_host = NULL;
	struct sockaddr *sa;
	struct sockaddr_in laddr, caddr;
	struct sockaddr_in6 laddr6;
	unsigned int caddrlen = sizeof(caddr);
	struct passwd *pw = NULL;
	
	while ((optc = getopt(argc, argv, "1dv46fHs:l:I:i:hu:m:L:A:p:")) != -1) {
		switch (optc) {
			case '1':
				one = 1;
				break;
			case 'd':
				detach = 0;
				break;
			case 'v':
				verbose = 1;
				break;
			case '4':
				break;
			case '6':
				remote_hint = AF_INET;
				local_hint = AF_INET6;
				break;
			case 's':
				source_host = xstrdup(optarg);
				break;
			case 'l':
				bind_host = xstrdup(optarg);
				break;
			case 'r':
				force = 1;
				break;
			case 'i':
				ircpass = xstrdup(optarg);
				clear_argv(argv[optind - 1]);
				break;
			case 'I':
				ircsendpass = xstrdup(optarg);
				clear_argv(argv[optind - 1]);
				break;
			case 'h':
				hexdump = 1;
				break;
			case 'u':
				username = xstrdup(optarg);
				break;
			case 'm':
				map_file = xstrdup(optarg);
				break;
			case 'L':
				conn_limit = atoi(optarg);
				break;
			case 'p':
				pid_file = xstrdup(optarg);
				break;
			case 'H':
				hint_optional = 1;
				break;
			default:
				return 1;
		}
	}

	if (hexdump)
		verbose = 1;

	if (verbose)
		detach = 0;
	
	if (detach)
		verbose = 0;

	if (argc - optind < 2) {
		usage(argv[0]);
		exit(1);
	}

	if (username && !(pw = getpwnam(username))) {
		fprintf(stderr, "%s: unknown user %s\n", argv[0], username);
		exit(1);
	}
  
	if (map_file)
		map_read();
  
	local_port = atoi(argv[optind++]);
	remote_host = argv[optind++];
	remote_port = (argc == optind) ? local_port : atoi(argv[optind]);

	debug("resolving %s\n", remote_host);

	if (!(sa = resolve_host(remote_host, remote_hint)) && !force) {
		fprintf(stderr, "%s: unable to resolve host %s\n", argv[0], remote_host);
		exit(1);
	}

	free(sa);
	sa = NULL;

	if (bind_host) {
		debug("resolving %s\n", bind_host);

		if (!(sa = resolve_host(bind_host, local_hint))) {
			fprintf(stderr, "%s: unable to resolve host %s\n", argv[0], remote_host);
			exit(1);
		}
	}
 
	debug("local: %s,%d; ", (bind_host) ? bind_host : "default", local_port);
	debug("remote: %s,%d; ", remote_host, remote_port);

	if (map_file)
		debug("source: mapped\n");
	else
		debug("source: %s\n", (source_host) ? source_host : "default");

	if (local_hint == AF_INET) {
		lsock = socket(PF_INET, SOCK_STREAM, 0);

		memset(&laddr, 0, (sa_len = sizeof(laddr)));
		laddr.sin_family = AF_INET;
		laddr.sin_port = htons(local_port);
		
		if (sa) {
			memcpy(&laddr.sin_addr, &((struct sockaddr_in*) sa)->sin_addr, sizeof(struct in_addr));
			free(sa);
		}
		
		sa = (struct sockaddr*) &laddr;
	} else {
		lsock = socket(PF_INET6, SOCK_STREAM, 0);
		
		memset(&laddr6, 0, (sa_len = sizeof(laddr6)));
		laddr6.sin6_family = AF_INET6;
		laddr6.sin6_port = htons(local_port);
		
		if (sa) {
			memcpy(&laddr6.sin6_addr, &((struct sockaddr_in6*) sa)->sin6_addr, sizeof(struct in6_addr));
			free(sa);
		}

		sa = (struct sockaddr*) &laddr6;
	}

	if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &jeden, sizeof(jeden)) == -1) {
		perror("setsockopt");
		exit(1);
	}
  
	if (bind(lsock, sa, sa_len)) {
		perror("bind");
		exit(1);
	}    
  
	if (listen(lsock, 100)) {
		perror("listen");
		exit(1);
	}

	if (detach) {
		int i, ret;

		signal(SIGHUP, sighup);
		
		for (i = 0; i < 3; i++)
			close(i);

		ret = fork();
		
		if (ret == -1) {
			perror("fork");
			exit(1);
		}

		if (ret)
			exit(0);
	}

	if (pid_file) {
		FILE *f = fopen(pid_file, "w");

		if (!f)
			debug("warning: cannot write to pidfile (%s)\n", strerror(errno));
		else {
			fprintf(f, "%d", getpid());
			fclose(f);
		}
	}

	if (username && ((setgid(pw->pw_gid) == -1) || (setuid(pw->pw_uid) == -1))) {
		perror("setuid/setgid");
		exit(1);
	}

	setsid();
	signal(SIGCHLD, sigchld);
	signal(SIGTERM, sigterm);
	signal(SIGINT, sigterm);
	signal(SIGHUP, sighup);
    
	for (;;) {  
		int ret;
		fd_set rds;

		FD_ZERO(&rds);
		FD_SET(lsock, &rds);

		if (select(lsock + 1, &rds, NULL, NULL, NULL) == -1) {
			if (errno == EINTR)
				continue;

			perror("select");
			break;
		}

		if ((csock = accept(lsock, (struct sockaddr*) &caddr, &caddrlen)) == -1) {
			perror("accept");
			break;
		}

		inet_ntop(caddr.sin_family, (caddr.sin_family == AF_INET) ?
			&caddr.sin_addr :
			(void*) &(((struct sockaddr_in6*)&caddr)->sin6_addr),
			remote, sizeof(remote));

		debug("<%d> connection from %s,%d", csock, remote, ntohs(caddr.sin_port));

		if (conn_limit && (conn_count >= conn_limit)) {
			debug(" -- rejected due to limit.\n");
			shutdown(csock, 2);
			close(csock);
			continue;
		}
		
		if (conn_limit) {
			conn_count++;
			debug(" (no. %d)", conn_count);
		}
		
		fflush(stdout);
    
		if ((ret = fork()) == -1) {
			debug(" -- fork() failed.\n");
			shutdown(csock, 2);
			close(csock);
			continue;
		}
    
		if (!ret) {
			signal(SIGHUP, SIG_IGN);
			close(lsock);
			debug("\n");
			make_tunnel(csock, remote);
			debug("<%d> connection closed\n", csock);
			exit(0);
		} 

		close(csock);
    
		if (one) {
			shutdown(lsock, 2);
			close(lsock);
			exit(0);
		}

	}

	close(lsock);
  
	exit(1);
}