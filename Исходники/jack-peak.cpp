int main (int argc, char **argv) {
	jack_client_t *client;
	jack_thread_info_t thread_info;
	jack_status_t jstat;
	int c;

	memset(&thread_info, 0, sizeof(thread_info));
	thread_info.channels = 2;
	thread_info.delay = 100000;
	thread_info.format = 0;
	thread_info.iecmult = 2.0;
	thread_info.outfd = NULL;
	thread_info.address = "127.0.0.1";
	thread_info.port = 7770;
	thread_info.message = "/1/fader1";

	const char *optstring = "hqpjiomx:d:f:V";
	struct option long_options[] = {
		{ "help",     no_argument,       0, 'h' },
		{ "json",     no_argument,       0, 'j' },
		{ "iec268",   required_argument, 0, 'i' },
		{ "file",     required_argument, 0, 'f' },
		{ "delay",    required_argument, 0, 'd' },
		{ "peakhold", required_argument, 0, 'p' },
		{ "osc",      required_argument, 0, 'o' },
		{ "port",     required_argument, 0, 'x' },
		{ "message",  required_argument, 0, 'm' },
		{ "quiet",    no_argument,       0, 'q' },
		{ "version",  no_argument,       0, 'V' },
		{ 0, 0, 0, 0 }
	};

	int option_index;

	while ((c = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
		switch (c) {
			case 'h':
				usage(argv[0], 0);
				break;
			case 'q':
				want_quiet = 1;
				break;
			case 'i':
				thread_info.format|=2;
				thread_info.iecmult = atof(optarg)/100.0;
				break;
			case 'j':
				thread_info.format|=4;
				break;
			case 'p':
				thread_info.format|=8;
				break;
			case 'f':
				if (thread_info.outfd) fclose(thread_info.outfd);
				thread_info.outfd = fopen(optarg, "w");
				break;
			case 'd':
				if (atol(optarg) < 0 || atol(optarg) > 60000)
					fprintf(stderr, "delay: time out of bounds.\n");
				else
					thread_info.delay = 1000*atol(optarg);
				break;
			case 'm':
				thread_info.message = optarg;
				break;
			case 'o':
				thread_info.address = optarg;
				break;
			case 'x':
				thread_info.port = atoi(optarg); 
				break;
			case 'V':
				printf ("%s %s\n\n",argv[0], VERSION);
				printf(
"Copyright (C) 2012 Robin Gareus <*****@*****.**>\n"
"This is free software; see the source for copying conditions.  There is NO\n"
"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n"
);
				break;
			default:
				fprintf(stderr, "invalid argument.\n");
				usage(argv[0], 0);
				break;
		}
	}


	if (!thread_info.outfd) {
		thread_info.outfd=stdout;
		thread_info.format|=1;
	}

	if (argc <= optind) {
		fprintf(stderr, "At least one port/audio-channel must be given.\n");
		usage(argv[0], 1);
	}

	/* set up JACK client */
	if ((client = jack_client_open("jackpeak", JackNoStartServer, &jstat)) == 0) {
		fprintf(stderr, "Can not connect to JACK.\n");
		exit(1);
	}

	thread_info.client = client;
	thread_info.can_process = 0;
	thread_info.channels = argc - optind;

	jack_set_process_callback(client, process, &thread_info);
	jack_on_shutdown(client, jack_shutdown, &thread_info);
	jack_set_buffer_size_callback(client, jack_bufsiz_cb, &thread_info);

	if (jack_activate(client)) {
		fprintf(stderr, "cannot activate client");
	}

	setup_ports(thread_info.channels, &argv[optind], &thread_info);

	/* set up i/o thread */
	pthread_create(&thread_info.thread_id, NULL, io_thread, &thread_info);
#ifndef _WIN32
	signal (SIGHUP, catchsig);
#endif
	thread_info.samplerate = jack_get_sample_rate(thread_info.client);

	if (!want_quiet) {
		fprintf(stderr, "%i channel%s, @%iSPS.\naddress: %s:%i\nmessage: %s\n",
			thread_info.channels,
			(thread_info.channels>1)?"s":"",
			thread_info.samplerate,
			thread_info.address,
			thread_info.port,
			thread_info.message
		);
	}

	/* all systems go - run the i/o thread */
	thread_info.can_capture = 1;
	pthread_join(thread_info.thread_id, NULL);

	if (thread_info.outfd != stdout)
		fclose(thread_info.outfd);

	jack_client_close(client);

	cleanup(&thread_info);

	return(0);
}