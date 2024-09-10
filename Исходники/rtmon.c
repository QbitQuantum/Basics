int
main(int argc, char **argv)
{
	FILE *fp;
	struct rtnl_handle rth;
	int family = AF_UNSPEC;
	unsigned groups = ~0U;
	int llink = 0;
	int laddr = 0;
	int lroute = 0;
	char *file = NULL;

	while (argc > 1) {
		if (matches(argv[1], "-family") == 0) {
			argc--;
			argv++;
			if (argc <= 1)
				usage();
			if (strcmp(argv[1], "inet") == 0)
				family = AF_INET;
			else if (strcmp(argv[1], "inet6") == 0)
				family = AF_INET6;
			else if (strcmp(argv[1], "link") == 0)
				family = AF_INET6;
			else if (strcmp(argv[1], "help") == 0)
				usage();
			else {
				fprintf(stderr, "Protocol ID \"%s\" is unknown, try \"rtmon help\".\n", argv[1]);
				exit(-1);
			}
		} else if (strcmp(argv[1], "-4") == 0) {
			family = AF_INET;
		} else if (strcmp(argv[1], "-6") == 0) {
			family = AF_INET6;
		} else if (strcmp(argv[1], "-0") == 0) {
			family = AF_PACKET;
		} else if (matches(argv[1], "-Version") == 0) {
			printf("rtmon utility, iproute2-ss%s\n", SNAPSHOT);
			exit(0);
		} else if (matches(argv[1], "file") == 0) {
			argc--;
			argv++;
			if (argc <= 1)
				usage();
			file = argv[1];
		} else if (matches(argv[1], "link") == 0) {
			llink=1;
			groups = 0;
		} else if (matches(argv[1], "address") == 0) {
			laddr=1;
			groups = 0;
		} else if (matches(argv[1], "route") == 0) {
			lroute=1;
			groups = 0;
		} else if (strcmp(argv[1], "all") == 0) {
			groups = ~0U;
		} else if (matches(argv[1], "help") == 0) {
			usage();
		} else {
			fprintf(stderr, "Argument \"%s\" is unknown, try \"rtmon help\".\n", argv[1]);
			exit(-1);
		}
		argc--;	argv++;
	}

	if (file == NULL) {
		fprintf(stderr, "Not enough information: argument \"file\" is required\n");
		exit(-1);
	}
	if (llink)
		groups |= RTMGRP_LINK;
	if (laddr) {
		if (!family || family == AF_INET)
			groups |= RTMGRP_IPV4_IFADDR;
		if (!family || family == AF_INET6)
			groups |= RTMGRP_IPV6_IFADDR;
	}
	if (lroute) {
		if (!family || family == AF_INET)
			groups |= RTMGRP_IPV4_ROUTE;
		if (!family || family == AF_INET6)
			groups |= RTMGRP_IPV6_ROUTE;
	}

	fp = fopen(file, "w");
	if (fp == NULL) {
		perror("Cannot fopen");
		exit(-1);
	}

	if (rtnl_open(&rth, groups) < 0)
		exit(1);

	if (rtnl_wilddump_request(&rth, AF_UNSPEC, RTM_GETLINK) < 0) {
		perror("Cannot send dump request");
		exit(1);
	}

	write_stamp(fp);

	if (rtnl_dump_filter(&rth, dump_msg, fp, NULL, NULL) < 0) {
		fprintf(stderr, "Dump terminated\n");
		return 1;
	}

	init_phase = 0;

	if (rtnl_listen(&rth, dump_msg, (void*)fp) < 0)
		exit(2);

	exit(0);
}