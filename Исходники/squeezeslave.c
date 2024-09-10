int main(int argc, char *argv[]) {
	slimproto_t slimproto;
	slimaudio_t slimaudio;

	PaDeviceIndex output_device_id = PA_DEFAULT_DEVICE;

	unsigned int output_predelay = 0;
	unsigned int output_predelay_amplitude = 0;

	slimaudio_volume_t volume_control = VOLUME_SOFTWARE;

	unsigned int retry_interval = RETRY_DEFAULT;

	char macaddress[6] = { 0, 0, 0, 0, 0, 1 };

	int keepalive_interval = -1;

	bool listdevs = false;

#ifdef DAEMONIZE
	bool should_daemonize = false;
	char *logfile = NULL;
#endif


#ifdef INTERACTIVE
        fd_set read_fds;
        fd_set write_fds;
        int key = 0;
        unsigned long ir = 0;
	int maxfd = 0;
	char *home;
	struct timeval timeout;
	timeout.tv_usec = 0;

#ifdef __WIN32__
	int WSAerrno;
	int ptw32_processInitialize (void);
	ptw32_processInitialize();
#endif
        // default lircrc file ($HOME/.lircrc)
	home = getenv("HOME");
	if (home == NULL) home = "";
	lircrc = (char *)malloc((strlen(home) + strlen("/.lircrc") + 1) * sizeof(char));
	strcpy(lircrc,home);
	strcat(lircrc,"/.lircrc");
#endif

	char getopt_options[OPTLEN] = "a:d:Y:e:f:hk:Lm:o:P:p:Rr:Vv:";
	static struct option long_options[] = {
		{"predelay_amplitude", required_argument, 0, 'a'},
		{"debug",              required_argument, 0, 'd'},
		{"debuglog",           required_argument, 0, 'Y'},
		{"help",               no_argument,       0, 'h'},
		{"keepalive",          required_argument, 0, 'k'},
		{"list",               no_argument,       0, 'L'},
		{"mac",	               required_argument, 0, 'm'},
		{"output",             required_argument, 0, 'o'},
		{"playerid",           required_argument, 0, 'e'},
		{"firmware",           required_argument, 0, 'f'},
		{"port",               required_argument, 0, 'P'},
		{"predelay",           required_argument, 0, 'p'},
		{"retry",              no_argument,       0, 'R'},
		{"intretry",           required_argument, 0, 'r'},
		{"version",            no_argument,       0, 'V'},
		{"volume",             required_argument, 0, 'v'},
#ifdef PORTAUDIO_DEV
		{"latency",            required_argument, 0, 'y'},
#endif
#ifdef DAEMONIZE
		{"daemonize",          required_argument, 0, 'M'},
#endif
#ifdef __WIN32__
		{"highpriority",       no_argument,       0, 'H'},
#ifdef PA_WASAPI
		{"shared",             no_argument,       0, 'S'},
#endif
#endif
#ifdef INTERACTIVE
		{"lircrc",             required_argument, 0, 'c'},
		{"lirc",               no_argument,       0, 'i'},
		{"lcd",                no_argument,       0, 'l'},
		{"display",            no_argument,       0, 'D'},
		{"width",              required_argument, 0, 'w'},
#endif
		{0, 0, 0, 0}
	};
#ifdef PORTAUDIO_DEV
	strcat (getopt_options, "y:");
#endif	
#ifdef DAEMONIZE	
	strcat (getopt_options, "M:");
#endif
#ifdef INTERACTIVE
	strcat (getopt_options, "c:Dilw:");
#endif
#ifdef __WIN32__
	strcat (getopt_options, "H");
#ifdef PA_WASAPI
	strcat (getopt_options, "S");
#endif
#endif
	while (true) {
		const char shortopt =
			getopt_long_only(argc, argv, getopt_options, long_options, NULL);

		if (shortopt == (char) -1) {
			break;
		}

		switch (shortopt) {
		case 'a':
			output_predelay_amplitude = strtoul(optarg, NULL, 0);
			break;
		case 'd':
#ifdef SLIMPROTO_DEBUG
			if (strcmp(optarg, "all") == 0)
			{
				slimproto_debug = true;
				slimaudio_debug = true;
				slimaudio_buffer_debug = true;
				slimaudio_buffer_debug_v = true;
				slimaudio_decoder_debug = true;
				slimaudio_decoder_debug_r = true;
				slimaudio_decoder_debug_v = true;
				slimaudio_http_debug = true;
				slimaudio_http_debug_v = true;
				slimaudio_output_debug = true;
				slimaudio_output_debug_v = true;
			}
			else if (strcmp(optarg, "slimproto") == 0)
				slimproto_debug = true;
			else if (strcmp(optarg, "slimaudio") == 0)
				slimaudio_debug = true;
			else if (strcmp(optarg, "slimaudio_buffer") == 0)
				slimaudio_buffer_debug = true;
			else if (strcmp(optarg, "slimaudio_buffer_v") == 0)
				slimaudio_buffer_debug_v = true;
			else if (strcmp(optarg, "slimaudio_decoder") == 0)
				slimaudio_decoder_debug = true;
			else if (strcmp(optarg, "slimaudio_decoder_r") == 0)
				slimaudio_decoder_debug_r = true;
			else if (strcmp(optarg, "slimaudio_decoder_v") == 0)
				slimaudio_decoder_debug_v = true;
			else if (strcmp(optarg, "slimaudio_http") == 0)
				slimaudio_http_debug = true;
			else if (strcmp(optarg, "slimaudio_http_v") == 0)
				slimaudio_http_debug_v = true;
			else if (strcmp(optarg, "slimaudio_output") == 0)
				slimaudio_output_debug = true;
			else if (strcmp(optarg, "slimaudio_output_v") == 0)
				slimaudio_output_debug_v = true;
			else
				fprintf(stderr, "%s: Unknown debug option %s\n", argv[0], optarg);
#else
				fprintf(stderr, "%s: Recompile with -DSLIMPROTO_DEBUG to enable debugging.\n", argv[0]);
#endif
			break;
		case 'Y':
#ifdef SLIMPROTO_DEBUG
                        if ( optarg == NULL )
                        {
                                fprintf(stderr, "%s: Cannot parse debug log filename %s\n", argv[0], optarg);
                                exit(-1);
                        } else
                        {
				debuglog = freopen( optarg, "a", stderr);
				if ( debuglog )
					debug_logfile = true;
				else
					fprintf(stderr, "%s: Redirection of stderr to %s failed.\n", argv[0], optarg);
                        }
#endif
			break;

// From server/Slim/Networking/Slimproto.pm from 7.5r28596
// squeezebox(2)
// softsqueeze(3)
// squeezebox2(4)
// transporter(5)
// softsqueeze3(6)
// receiver(7)
// squeezeslave(8)
// controller(9)
// boom(10)
// softboom(11)
// squeezeplay(12)
// radio(13)
// touch(14)

		case 'e':
			player_type = strtoul(optarg, NULL, 0);
			if ( (player_type < 2) || (player_type > 14) )
			{
				player_type = PLAYER_TYPE;
				fprintf(stderr, "%s: Unknown player type, using (%d)\n", argv[0], player_type);
			}
			break;
		case 'f':
			firmware = strtoul(optarg, NULL, 0);
			if ( (firmware < 0) || (firmware > 254) )
			{
				firmware = FIRMWARE_VERSION;
				fprintf(stderr, "%s: Invalid firmware value, using (%d)\n", argv[0], firmware);
			}
			break;
		case 'h':
			print_help();
			exit(0);	
		case 'k':
			keepalive_interval = strtoul(optarg, NULL, 0);
			break;
		case 'm':
			if (parse_macaddress(macaddress, optarg) != 0) {
				fprintf(stderr, "%s: Cannot parse mac address %s\n", argv[0], optarg);
				exit(-1);	
			}
			break;
#ifdef DAEMONIZE
		case 'M':
			if ( optarg == NULL )
			{
				fprintf(stderr, "%s: Cannot parse log filename %s\n", argv[0], optarg);
				exit(-1);	
			} else
			{
				logfile = optarg;
			}
			should_daemonize = true;
			break;
#endif

#ifdef __WIN32__
		case 'H':
			/* Change Window process priority class to HIGH */
			if ( !SetPriorityClass ( GetCurrentProcess(), HIGH_PRIORITY_CLASS ) )
			{
				int dwError = GetLastError();
				fprintf(stderr, "%s: Failed to set priority (%d), using default.\n", argv[0],
					dwError);
			} 
			break;
#ifdef PA_WASAPI
		case 'S':
			wasapi_exclusive = false;
			break;
#endif
#endif
		case 'o':
			output_device_id = strtoul(optarg, NULL, 0);
			output_change = true;
			break;
		case 'p':
			output_predelay = strtoul(optarg, NULL, 0);
			break;
		case 'P':
			port = strtoul(optarg, NULL, 0);
			if ( (port < 0) || (port > 65535) )
			{
				port = SLIMPROTOCOL_PORT;
				fprintf(stderr, "%s: Invalid port value, using (%d)\n", argv[0], port);
			}
			break;
			break;
		case 'R':
			retry_connection = true;
			break;
		case 'r':
			retry_connection = true;
			retry_interval = strtoul(optarg, NULL, 0);
			if ( retry_interval < 1 )
			{
				fprintf (stderr, "Retry option requires value in seconds.\n");
				exit(-1);
			}
			break;
#ifdef INTERACTIVE
		case 'c':
		        free(lircrc);
			lircrc = optarg;
			break;
#ifndef __WIN32__
		case 'i':
			using_lirc = true;
			break;
		case 'l':
			use_lcdd_menu = true;
			break;
#endif
		case 'D':
			using_curses = 1;
			break;
		case 'w':
			linelen = strtoul(optarg, NULL, 0);
			break;
#endif
		case 'L':
			listdevs = true;
			break;
		case 'V':
			print_version();
			exit(0);
			break;
		case 'v':
		 	if (strcmp(optarg, "sw") == 0) {
				volume_control = VOLUME_SOFTWARE;
			}
#ifndef PORTAUDIO_DEV
			else if (strcmp(optarg, "on") == 0 ) {
				volume_control = VOLUME_DRIVER;
			}
#endif
			else if (strcmp(optarg, "off") == 0 ) {
				volume_control = VOLUME_NONE;
			}
			break;
#ifdef PORTAUDIO_DEV
		case 'y':
			modify_latency = true;
			user_latency = strtoul(optarg, NULL, 0);

			if ( user_latency > 1000 )
			{
				fprintf (stderr, "Suggested latency invalid, using device default.\n");
				modify_latency = false;
			}
			break;
#endif
		default:
			break;
		}
	}

	if (listdevs) {
		GetAudioDevices(output_device_id, output_change, true);
		exit(0);
	}

#ifdef DAEMONIZE
	if ( should_daemonize ) {
#ifdef INTERACTIVE
		if ( using_curses || using_lirc || use_lcdd_menu )
		{
			fprintf(stderr, "Daemonize not supported with lirc or display modes.\n");
			exit(-1);
		}
		else
#endif
			init_daemonize();
	}
#endif

	char *slimserver_address = "127.0.0.1";
	if (optind < argc)
		slimserver_address = argv[optind];

	signal(SIGTERM, &exit_handler);
	install_restart_handler();

#ifdef INTERACTIVE
	install_toggle_handler();  //SIGUSR2 to toggle IR/LCD on and off
#endif
	if (slimproto_init(&slimproto) < 0) {
		fprintf(stderr, "Failed to initialize slimproto\n");
		exit(-1);	
	}

	if (slimaudio_init(&slimaudio, &slimproto, output_device_id, output_change) < 0) {
		fprintf(stderr, "Failed to initialize slimaudio\n");
		exit(-1);
	}

	slimproto_add_connect_callback(&slimproto, connect_callback, macaddress);

#ifdef INTERACTIVE
	// Process VFD (display) commands
	if ( using_curses || using_lirc || use_lcdd_menu )
		slimproto_add_command_callback(&slimproto, "vfdc", vfd_callback, macaddress);
#endif

	slimaudio_set_volume_control(&slimaudio, volume_control);
	slimaudio_set_output_predelay(&slimaudio, output_predelay, output_predelay_amplitude);

	if (keepalive_interval >= 0) {
		slimaudio_set_keepalive_interval(&slimaudio, keepalive_interval);
	}

#ifdef INTERACTIVE
	init_lcd();
#endif

	if (slimaudio_open(&slimaudio) < 0) {
		fprintf(stderr, "Failed to open slimaudio\n");
#ifdef INTERACTIVE
		close (lcd_fd);
#endif
		exit(-1);
	}

#ifdef SLIMPROTO_DEBUG
	if (slimaudio_debug)
		fprintf ( stderr, "Using audio device index: %d\n", slimaudio.output_device_id );
#endif

#ifdef INTERACTIVE
        init_lirc();

	setlocale(LC_ALL, "");
	initcurses();
#endif
#ifdef DAEMONIZE
	if ( should_daemonize ) {
		daemonize(logfile);
	}
#endif
	// When retry_connection is true, retry connecting to Squeezebox Server 
	// until we succeed, unless the signal handler tells us to give up.
	do {
		while (slimproto_connect(
			&slimproto, slimserver_address, port) < 0) {
			if (!retry_connection || signal_exit_flag) {
				if (signal_exit_flag) {
					// No message when the exit is triggered
					// by the user.
#ifdef INTERACTIVE
					exitcurses();
					close_lirc();
					close_lcd();
#endif
					exit(0);
				}
#ifdef INTERACTIVE
				exitcurses();
				close_lirc();
				close_lcd();
#endif
				fprintf(stderr, "Connection to Squeezebox Server %s failed.\n", slimserver_address);
				exit(-1);
			}
#ifdef INTERACTIVE
			exitcurses();
#endif
			fprintf(stderr,"Retry in %d seconds.\n", retry_interval);
			Pa_Sleep(1000 * retry_interval);
#ifdef INTERACTIVE
	   	        initcurses();
#endif
		}
                signal_restart_flag = false;
                while (!signal_exit_flag && !signal_restart_flag) {
#ifdef INTERACTIVE
                   if (using_curses == 1 || use_lcdd_menu) {
                      FD_ZERO(&read_fds);
                      FD_ZERO(&write_fds);
		      if (using_curses == 1)
     	                 FD_SET(0, &read_fds); /* watch stdin */
   	              if (use_lcdd_menu) {
		         FD_SET(lcd_fd, &read_fds); 
		         maxfd = lcd_fd;
		      }
   	              if (using_lirc) {
		         FD_SET(lirc_fd, &read_fds); 
                         if (lirc_fd > maxfd) 
		            maxfd = lirc_fd;
                      }
		      timeout.tv_sec = 5;
                      if(select(maxfd + 1, &read_fds, NULL, NULL, &timeout) == -1) {
#ifndef __WIN32__
    	                 if (errno != EINTR)
			 {
		           fprintf(stderr,"Select Error:%d\n", errno);
#else
			 WSAerrno = WSAGetLastError();
			 if ( (WSAerrno != WSAEINTR) && (WSAerrno != WSAENOTSOCK) )
			 {	
		           fprintf(stderr,"Select Error:%d\n", WSAerrno);
#endif
   	                   abort();
	                 }
#ifdef __WIN32__
			 else
				 WaitForSingleObject( GetStdHandle(STD_INPUT_HANDLE), 5000 );
#endif
                      }
		      if (FD_ISSET(0, &read_fds)) {
                         while ((key = getch()) != ERR) {
                            ir = getircode(key);
	                    if (ir == (unsigned long) 0x01) {
  		               signal_exit_flag = 1;
                            }else{
			       if (ir != 0) slimproto_ir(&slimproto, 1, 1, ir);
			    }
		         }
		      } 
		      if (using_lirc && FD_ISSET(lirc_fd, &read_fds)) {
                         while((key = read_lirc()) != 0 ) { 
                            ir = getircode(key);
	                    if (ir == 0x01) { 
  		               signal_exit_flag = 1;
                            } else {
			       if (ir != 0) slimproto_ir(&slimproto, 1, 1, ir);
			    }
		         }
		      } 
		      if (use_lcdd_menu && FD_ISSET(lcd_fd, &read_fds)) {
                         while(read_lcd()); 
		      }
		   } else {
                      wait_for_restart_signal();
		   }
#else
                   wait_for_restart_signal();
#endif
		}
#ifdef INTERACTIVE
                FD_ZERO(&read_fds);
                FD_ZERO(&write_fds);
#endif
		if (signal_restart_flag) { 
#ifdef INTERACTIVE
			exitcurses();
#endif
			fprintf(stderr,"Retry in %d seconds.\n", retry_interval);
			Pa_Sleep(1000 * retry_interval);
#ifdef INTERACTIVE
	   	        initcurses();
#endif
		}
        } while (signal_restart_flag && !signal_exit_flag);

#ifdef INTERACTIVE
	close_lirc();
#endif
	slimaudio_close(&slimaudio);
	slimproto_close(&slimproto);

#ifdef INTERACTIVE
        exitcurses();
        close_lcd();
#endif
#ifdef SLIMPROTO_DEBUG
	if (debug_logfile)
	{
		fclose (debuglog);
	}
#endif
	slimaudio_destroy(&slimaudio);
	slimproto_destroy(&slimproto);
	return 0;
} 