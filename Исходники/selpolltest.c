int
main(int argc, char **argv)
{
	register int op;
	bpf_u_int32 localnet, netmask;
	register char *cp, *cmdbuf, *device;
	int doselect, dopoll, dotimeout, dononblock;
	struct bpf_program fcode;
	char ebuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *devlist;
	int selectable_fd;
	int status;
	int packet_count;

	device = NULL;
	doselect = 0;
	dopoll = 0;
	dotimeout = 0;
	dononblock = 0;
	if ((cp = strrchr(argv[0], '/')) != NULL)
		program_name = cp + 1;
	else
		program_name = argv[0];

	opterr = 0;
	while ((op = getopt(argc, argv, "i:sptn")) != -1) {
		switch (op) {

		case 'i':
			device = optarg;
			break;

		case 's':
			doselect = 1;
			break;

		case 'p':
			dopoll = 1;
			break;

		case 't':
			dotimeout = 1;
			break;

		case 'n':
			dononblock = 1;
			break;

		default:
			usage();
			/* NOTREACHED */
		}
	}

	if (doselect && dopoll) {
		fprintf(stderr, "selpolltest: choose select (-s) or poll (-p), but not both\n");
		return 1;
	}
	if (dotimeout && !doselect && !dopoll) {
		fprintf(stderr, "selpolltest: timeout (-t) requires select (-s) or poll (-p)\n");
		return 1;
	}
	if (device == NULL) {
		if (pcap_findalldevs(&devlist, ebuf) == -1)
			error("%s", ebuf);
		if (devlist == NULL)
			error("no interfaces available for capture");
		device = strdup(devlist->name);
		pcap_freealldevs(devlist);
	}
	*ebuf = '\0';
	pd = pcap_open_live(device, 65535, 0, 1000, ebuf);
	if (pd == NULL)
		error("%s", ebuf);
	else if (*ebuf)
		warning("%s", ebuf);
	if (pcap_lookupnet(device, &localnet, &netmask, ebuf) < 0) {
		localnet = 0;
		netmask = 0;
		warning("%s", ebuf);
	}
	cmdbuf = copy_argv(&argv[optind]);

	if (pcap_compile(pd, &fcode, cmdbuf, 1, netmask) < 0)
		error("%s", pcap_geterr(pd));

	if (pcap_setfilter(pd, &fcode) < 0)
		error("%s", pcap_geterr(pd));
	if (pcap_get_selectable_fd(pd) == -1)
		error("pcap_get_selectable_fd() fails");
	if (dononblock) {
		if (pcap_setnonblock(pd, 1, ebuf) == -1)
			error("pcap_setnonblock failed: %s", ebuf);
	}
	selectable_fd = pcap_get_selectable_fd(pd);
	printf("Listening on %s\n", device);
	if (doselect) {
		for (;;) {
			fd_set setread, setexcept;
			struct timeval seltimeout;

			FD_ZERO(&setread);
			FD_SET(selectable_fd, &setread);
			FD_ZERO(&setexcept);
			FD_SET(selectable_fd, &setexcept);
			if (dotimeout) {
				seltimeout.tv_sec = 0;
				seltimeout.tv_usec = 1000;
				status = select(selectable_fd + 1, &setread,
				    NULL, &setexcept, &seltimeout);
			} else {
				status = select(selectable_fd + 1, &setread,
				    NULL, &setexcept, NULL);
			}
			if (status == -1) {
				printf("Select returns error (%s)\n",
				    strerror(errno));
			} else {
				if (status == 0)
					printf("Select timed out: ");
				else
					printf("Select returned a descriptor: ");
				if (FD_ISSET(selectable_fd, &setread))
					printf("readable, ");
				else
					printf("not readable, ");
				if (FD_ISSET(selectable_fd, &setexcept))
					printf("exceptional condition\n");
				else
					printf("no exceptional condition\n");
				packet_count = 0;
				status = pcap_dispatch(pd, -1, countme,
				    (u_char *)&packet_count);
				if (status < 0)
					break;
				printf("%d packets seen, %d packets counted after select returns\n",
				    status, packet_count);
			}
		}
	} else if (dopoll) {
		for (;;) {
			struct pollfd fd;
			int polltimeout;

			fd.fd = selectable_fd;
			fd.events = POLLIN;
			if (dotimeout)
				polltimeout = 1;
			else
				polltimeout = -1;
			status = poll(&fd, 1, polltimeout);
			if (status == -1) {
				printf("Poll returns error (%s)\n",
				    strerror(errno));
			} else {
				if (status == 0)
					printf("Poll timed out\n");
				else {
					printf("Poll returned a descriptor: ");
					if (fd.revents & POLLIN)
						printf("readable, ");
					else
						printf("not readable, ");
					if (fd.revents & POLLERR)
						printf("exceptional condition, ");
					else
						printf("no exceptional condition, ");
					if (fd.revents & POLLHUP)
						printf("disconnect, ");
					else
						printf("no disconnect, ");
					if (fd.revents & POLLNVAL)
						printf("invalid\n");
					else
						printf("not invalid\n");
				}
				packet_count = 0;
				status = pcap_dispatch(pd, -1, countme,
				    (u_char *)&packet_count);
				if (status < 0)
					break;
				printf("%d packets seen, %d packets counted after poll returns\n",
				    status, packet_count);
			}
		}
	} else {
		for (;;) {
			packet_count = 0;
			status = pcap_dispatch(pd, -1, countme,
			    (u_char *)&packet_count);
			if (status < 0)
				break;
			printf("%d packets seen, %d packets counted after pcap_dispatch returns\n",
			    status, packet_count);
		}
	}
	if (status == -2) {
		/*
		 * We got interrupted, so perhaps we didn't
		 * manage to finish a line we were printing.
		 * Print an extra newline, just in case.
		 */
		putchar('\n');
	}
	(void)fflush(stdout);
	if (status == -1) {
		/*
		 * Error.  Report it.
		 */
		(void)fprintf(stderr, "%s: pcap_loop: %s\n",
		    program_name, pcap_geterr(pd));
	}
	pcap_close(pd);
	exit(status == -1 ? 1 : 0);
}