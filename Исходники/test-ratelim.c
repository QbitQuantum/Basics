int
main(int argc, char **argv)
{
	int i,j;
	double ratio;

#ifdef _WIN32
	WORD wVersionRequested = MAKEWORD(2,2);
	WSADATA wsaData;
	int err;

	err = WSAStartup(wVersionRequested, &wsaData);
#endif

#ifndef _WIN32
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
#endif
	for (i = 1; i < argc; ++i) {
		for (j = 0; options[j].name; ++j) {
			if (!strcmp(argv[i],options[j].name)) {
				if (handle_option(argc,argv,&i,&options[j])<0)
					return 1;
				goto again;
			}
		}
		fprintf(stderr, "Unknown option '%s'\n", argv[i]);
		usage();
		return 1;
	again:
		;
	}
	if (cfg_help) {
		usage();
		return 0;
	}

	cfg_tick.tv_sec = cfg_tick_msec / 1000;
	cfg_tick.tv_usec = (cfg_tick_msec % 1000)*1000;

	seconds_per_tick = ratio = cfg_tick_msec / 1000.0;

	cfg_connlimit *= ratio;
	cfg_grouplimit *= ratio;

	{
		struct timeval tv;
		evutil_gettimeofday(&tv, NULL);
#ifdef _WIN32
		srand(tv.tv_usec);
#else
		srandom(tv.tv_usec);
#endif
	}

#ifndef EVENT__DISABLE_THREAD_SUPPORT
	evthread_enable_lock_debuging();
#endif

	return test_ratelimiting();
}