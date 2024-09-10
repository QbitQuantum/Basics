int
main(int argc, char **argv)
{
	int ch, i, nprocs = 1, is_parent = 1, port, *sockets, fds[2];
	pid_t pid;
	char *sp, *ap, *host, *cmd = argv[0];
	struct hostent *he;

	/* Defaults */
	params.count = -1;
	params.rpc = -1;
	params.concurrency = 1;
	memset(params.buckets, 0, sizeof(params.buckets));
	params.buckets[0] = 1;
	params.buckets[1] = 10;
	params.buckets[2] = 100;
	params.nbuckets = 4;

	memset(&counts, 0, sizeof(counts));

	while((ch = getopt(argc, argv, "c:b:n:p:r:i:h")) != -1){
		switch(ch){
		case 'b':
			sp = optarg;

			memset(params.buckets, 0, sizeof(params.buckets));

			for(i=0; i<MAX_BUCKETS && (ap=strsep(&sp, ",")) != nil; i++)
				params.buckets[i] = atoi(ap);

			params.nbuckets = i;

			if(params.buckets[0] == 0)
				panic("first bucket must be >0\n");

			for(i=1; params.buckets[i]!=0; i++){
				if(params.buckets[i]<params.buckets[i-1])
					panic("invalid bucket specification!\n");
			}
			break;

		case 'c':
			params.concurrency = atoi(optarg);
			break;

		case 'n':
			params.count = atoi(optarg);
			break;

		case 'p':
			nprocs = atoi(optarg);
			break;

		case 'i':
			reporttv.tv_sec = atoi(optarg);
			break;

		case 'r':
			params.rpc = atoi(optarg);
			break;

		case 'h':
			usage(cmd);
			break;
		}
	}

	argc -= optind;
	argv += optind;

	host = "127.0.0.1";
	port = 80;
	switch(argc){
	case 2:
		port = atoi(argv[1]);
	case 1:
		host = argv[0];
	case 0:
		break;
	default:
		panic("only 0 or 1(host port) pair are allowed\n");
	}
	
	http_hostname = host;
	http_port = port;
	if(snprintf(http_hosthdr, sizeof(http_hosthdr), "%s:%d", host, port) > sizeof(http_hosthdr))
		panic("snprintf");

	for(i = 0; params.buckets[i] != 0; i++)
		request_timeout = params.buckets[i];

	if(params.count > 0)
		params.count /= nprocs;

#if 0
	event_init();
	dispatch(mkhttp(), 1);
	event_dispatch(); exit(0);
#endif

	fprintf(stderr, "# params: c=%d p=%d n=%d r=%d\n", 
	    params.concurrency, nprocs, params.count, params.rpc);

	fprintf(stderr, "# ts\t\terrors\ttimeout\tcloses\t");
	for(i=0; params.buckets[i]!=0; i++)
		fprintf(stderr, "<%d\t", params.buckets[i]);

	fprintf(stderr, ">=%d\thz\n", params.buckets[i - 1]);

	if((sockets = calloc(nprocs + 1, sizeof(int))) == nil)
		panic("malloc\n");

	sockets[nprocs] = -1;

	for(i=0; i<nprocs; i++){
		if(socketpair(AF_UNIX, SOCK_STREAM, 0, fds) < 0){
			perror("socketpair");
			exit(1);
		}

		sockets[i] = fds[0];

		if((pid = fork()) < 0){
			kill(0, SIGINT);
			perror("fork");
			exit(1);
		}else if(pid != 0){
			close(fds[1]);
			continue;
		}

		is_parent = 0;

		event_init();

		/* Set up output. */
		if(dup2(fds[1], STDOUT_FILENO) < 0){
			perror("dup2");
			exit(1);
		}

		close(fds[1]);

		for(i=0; i<params.concurrency; i++)
			dispatch(mkhttp(), 1);

		evtimer_set(&reportev, reportcb, nil);
		evtimer_add(&reportev, &reporttv);

		event_dispatch();

		break;
	}

	if(is_parent)
		parentd(nprocs, sockets);

	return(0);
}