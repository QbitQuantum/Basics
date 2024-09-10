int main(int argc, char **argv) {
	int opt;
	Octstr *address;
	int udpsock;

	gwlib_init();

	/* Set defaults that can't be set statically */
	hostname = octstr_create("localhost");

	while ((opt = getopt(argc, argv, "hg:p:i:m:")) != EOF) {
		switch(opt) {
		case 'g':
			octstr_destroy(hostname);
			hostname = octstr_create(optarg);
			break;

		case 'p':
			port = atoi(optarg);
			break;

		case 'i':
			interval = atof(optarg);
			break;

		case 'm':
			maxsize = atol(optarg);
			if (maxsize > UDP_MAXIMUM) {
				maxsize = UDP_MAXIMUM;
				warning(0, "-m: truncated to UDP maximum of"
					"%ld bytes.", maxsize);
			}
			break;

		case 'h':
			help();
			exit(0);
			break;

		case '?':
		default:
			error(0, "Unknown option '%c'", opt);
			help();
			exit(1);
			break;
		}
	}

	address = udp_create_address(hostname, port);
	udpsock = udp_client_socket();
	if (udpsock < 0)
		exit(1);

	for ( ; optind < argc; optind++) {
		send_file(udpsock, argv[optind], address);
		if (interval > 0 && optind + 1 < argc)
			gwthread_sleep(interval);
	}

	octstr_destroy(address);
	octstr_destroy(hostname);
	gwlib_shutdown();
    	return 0;
}