void main(int argc, char *argv[]) {
	int c, usgflg=0, infd, printerfd;
	int cpid, sprv;
	int pipefd[2];
	char *dialstr;
	unsigned long rprv;

	dialstr = 0;

	while ((c = getopt(argc, argv, "b:d:")) != -1)
		switch (c) {
		case 'b':
			blocksize = atoi(optarg)/10;
			if (blocksize > MESGSIZE || blocksize < 1)
				blocksize = MESGSIZE;
			break;
		case 'd':
			debug = atoi(optarg);
			dial_debug = debug;
			break;
		case '?':
			fprintf(stderr, "unknown option %c\n", c);
			usgflg++;
			break;
		}
	if (optind < argc)
		dialstr = argv[optind++];
	else
		usgflg++;
	if (usgflg) {
		fprintf(stderr, "usage: %s [-b baudrate] net!host!service [infile]\n",
			argv[0]);
		exit (2);
	}
	if (optind < argc) {
		infd = open(argv[optind], 0);
		if (infd < 0) {
			fprintf(stderr, "cannot open %s\n", argv[optind]);
			exit(1);
		}
		optind++;
	} else
		infd = 0;

	if (debug & 02)
		fprintf(stderr, "blocksize=%d\n", blocksize);
	if (debug)
		fprintf(stderr, "dialing address=%s\n", dialstr);
	printerfd = dial(dialstr, 0, 0, 0);
	if (printerfd < 0)
		exit(1);

	fprintf(stderr, "printer startup\n");

	if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pipefd) < 0) {
		perror("socketpair");
		exit(1);
	}
	switch(cpid = fork()){
	case -1:
		perror("fork error");
		exit(1);
	case 0:				/* child - to printer */
		close(pipefd[1]);
		sprv = sendfile(infd, printerfd, pipefd[0]);
		if (debug)
			fprintf(stderr, "to remote - exiting\n");
		exit(sprv);
	default:			/* parent - from printer */
		close(pipefd[0]);
		rprv = readprinter(printerfd, pipefd[1]);
		if (debug)
			fprintf(stderr, "from remote - exiting\n");
		while(wait(&sprv) != cpid)
			;
		exit(rprv|sprv);
	}
}