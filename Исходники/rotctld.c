int main (int argc, char *argv[])
{
	ROT *my_rot;		/* handle to rot (instance) */
	rot_model_t my_model = ROT_MODEL_DUMMY;

	int retcode;		/* generic return code from functions */

	int verbose = 0;
	int show_conf = 0;
	int dump_caps_opt = 0;
	const char *rot_file=NULL;
	int serial_rate = 0;
	char conf_parms[MAXCONFLEN] = "";

	struct addrinfo hints, *result;
	int sock_listen;
	int reuseaddr = 1;

	while(1) {
		int c;
		int option_index = 0;

		c = getopt_long (argc, argv, SHORT_OPTIONS,
			long_options, &option_index);
		if (c == -1)
			break;

		switch(c) {
			case 'h':
				usage();
				exit(0);
			case 'V':
				version();
				exit(0);
			case 'm':
				if (!optarg) {
					usage();	/* wrong arg count */
					exit(1);
				}
				my_model = atoi(optarg);
				break;
			case 'r':
				if (!optarg) {
					usage();	/* wrong arg count */
					exit(1);
				}
				rot_file = optarg;
				break;
			case 's':
				if (!optarg) {
					usage();	/* wrong arg count */
					exit(1);
				}
				serial_rate = atoi(optarg);
				break;
			case 'C':
				if (!optarg) {
					usage();	/* wrong arg count */
					exit(1);
				}
				if (*conf_parms != '\0')
					strcat(conf_parms, ",");
				strncat(conf_parms, optarg, MAXCONFLEN-strlen(conf_parms));
				break;
			case 't':
				if (!optarg) {
					usage();        /* wrong arg count */
					exit(1);
				}
				portno = optarg;
				break;
			case 'T':
				if (!optarg) {
					usage();	/* wrong arg count */
					exit(1);
				}
				src_addr = optarg;
				break;
			case 'v':
				verbose++;
				break;
			case 'L':
				show_conf++;
				break;
			case 'l':
				list_models();
				exit(0);
			case 'u':
				dump_caps_opt++;
				break;
			case 'e':
				opt_end = 1;
				fprintf(stderr, "-e|--end-marker option is deprecated!\nPlease consider using the Extended Response protocol instead.\n");
				break;
			default:
				usage();	/* unknown option? */
				exit(1);
		}
	}

	rig_set_debug(verbose);

	rig_debug(RIG_DEBUG_VERBOSE, "rotctld, %s\n", hamlib_version);
	rig_debug(RIG_DEBUG_VERBOSE, "Report bugs to "
			"<*****@*****.**>\n\n");

  	my_rot = rot_init(my_model);

	if (!my_rot) {
		fprintf(stderr, "Unknown rot num %d, or initialization error.\n",
						my_model);
		fprintf(stderr, "Please check with --list option.\n");
		exit(2);
	}

	retcode = set_conf(my_rot, conf_parms);
	if (retcode != RIG_OK) {
		fprintf(stderr, "Config parameter error: %s\n", rigerror(retcode));
		exit(2);
	}

	if (rot_file)
		strncpy(my_rot->state.rotport.pathname, rot_file, FILPATHLEN - 1);

	/* FIXME: bound checking and port type == serial */
	if (serial_rate != 0)
		my_rot->state.rotport.parm.serial.rate = serial_rate;

	/*
	 * print out conf parameters
	 */
	if (show_conf) {
		rot_token_foreach(my_rot, print_conf_list, (rig_ptr_t)my_rot);
	}

	/*
	 * print out conf parameters, and exits immediately
	 * We may be interested only in only caps, and rig_open may fail.
	 */
	if (dump_caps_opt) {
		dumpcaps_rot(my_rot, stdout);
		rot_cleanup(my_rot); /* if you care about memory */
		exit(0);
	}

	retcode = rot_open(my_rot);
	if (retcode != RIG_OK) {
	  	fprintf(stderr,"rot_open: error = %s \n", rigerror(retcode));
		exit(2);
	}

	if (verbose > 0)
		printf("Opened rot model %d, '%s'\n", my_rot->caps->rot_model,
						my_rot->caps->model_name);

	rig_debug(RIG_DEBUG_VERBOSE, "Backend version: %s, Status: %s\n",
			my_rot->caps->version, rig_strstatus(my_rot->caps->status));

#ifdef __MINGW32__
# ifndef SO_OPENTYPE
#  define SO_OPENTYPE     0x7008
# endif
# ifndef SO_SYNCHRONOUS_NONALERT
#  define SO_SYNCHRONOUS_NONALERT 0x20
# endif
# ifndef INVALID_SOCKET
#  define INVALID_SOCKET -1
# endif

	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(1,1), &wsadata) == SOCKET_ERROR) {
		fprintf(stderr,"WSAStartup socket error\n");
		exit(1);
	}

	int sockopt = SO_SYNCHRONOUS_NONALERT;
	setsockopt(INVALID_SOCKET, SOL_SOCKET, SO_OPENTYPE, (char *)&sockopt, sizeof(sockopt));
#endif

	/*
	 * Prepare listening socket
	 */
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM;/* TCP socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */

	retcode = getaddrinfo(src_addr, portno, &hints, &result);
	if (retcode != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(retcode));
		exit(2);
	}

	sock_listen = socket(result->ai_family, result->ai_socktype,
			result->ai_protocol);
	if (sock_listen < 0)  {
		perror("ERROR opening socket");
		exit(1);
	}

	if (setsockopt(sock_listen, SOL_SOCKET, SO_REUSEADDR,
				(char *)&reuseaddr,sizeof(reuseaddr)) < 0) {
		rig_debug(RIG_DEBUG_ERR, "setsockopt: %s\n", strerror(errno));
		exit (1);
	}
	if (bind(sock_listen, result->ai_addr, result->ai_addrlen) < 0) {
		rig_debug(RIG_DEBUG_ERR, "binding: %s\n", strerror(errno));
		exit (1);
	}

	freeaddrinfo(result);           /* No longer needed */

	if (listen(sock_listen,4) < 0) {
		rig_debug(RIG_DEBUG_ERR, "listening: %s\n", strerror(errno));
		exit (1);
	}

	/*
	 * main loop accepting connections
	 */
	do {
#ifdef HAVE_PTHREAD
		pthread_t thread;
		pthread_attr_t attr;
#endif
		struct handle_data *arg;

		arg = malloc(sizeof(struct handle_data));
		if (!arg) {
			rig_debug(RIG_DEBUG_ERR, "malloc: %s\n", strerror(errno));
			exit (1);
		}

		arg->rot = my_rot;
		arg->clilen = sizeof(arg->cli_addr);
		arg->sock = accept(sock_listen, (struct sockaddr *) &arg->cli_addr,
				&arg->clilen);
		if (arg->sock < 0) {
			rig_debug(RIG_DEBUG_ERR, "accept: %s\n", strerror(errno));
			break;
		}

		rig_debug(RIG_DEBUG_VERBOSE, "Connection opened from %s:%d\n",
				inet_ntoa(arg->cli_addr.sin_addr),
				ntohs(arg->cli_addr.sin_port));

#ifdef HAVE_PTHREAD
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

		retcode = pthread_create(&thread, &attr, handle_socket, arg);
		if (retcode != 0) {
			rig_debug(RIG_DEBUG_ERR, "pthread_create: %s\n", strerror(retcode));
			break;
		}
#else
		handle_socket(arg);
#endif
	}
	while (retcode == 0);

	rot_close(my_rot); /* close port */
	rot_cleanup(my_rot); /* if you care about memory */

#ifdef __MINGW32__
	WSACleanup();
#endif

	return 0;
}