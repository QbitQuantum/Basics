int main(int argc, char *argv[])
{  
#ifndef WIN32
	setlinebuf(stdout);
#endif

	// Default values
	int listenPort = DEFAULTPORT;
	int connectionCount = 1000;

	time_t timerInterval = 10;	// 60 seconds
	time_t rotateCheckTimer = time(0) + timerInterval;
	int rotateSizeLimit = 50000000;	// 50 MB
	bool useLogFile = false;
	bool daemonMode = false;
	
	// Process command line arguments
	for (int i = 1; i < argc; i++)
	{
		if (strlen(argv[i]) == 2 && argc>=i+1)
		{
			switch (argv[i][1]) 
			{
				case 'd':
				{
					daemonMode = true;
					break;
				}
				case 'p':
				{
					listenPort = atoi(argv[i+1]);
					i++; // eat port number parameter
					if (listenPort < 1 || listenPort > 65535)
					{
						fprintf(stderr, "Master server port is invalid, should be between 0 and 65535.\nIt is also advisable to use a number above well known ports (>1024).\n");
						return 1;
					}
					break;
				}
				case 'c':
				{
					connectionCount = atoi(argv[i+1]);
					i++;
					if (connectionCount < 0)
					{
						fprintf(stderr, "Connection count must be higher than 0.\n");
						return 1;
					}
					break;
				}
				case 'l':
				{				
					useLogFile = Log::EnableFileLogging(logfile);
					break;
				}
				case 'e':
				{
					int debugLevel = atoi(argv[i+1]);
					Log::sDebugLevel = debugLevel;
					i++;
					if (debugLevel < 0 || debugLevel > 9)
					{
						fprintf(stderr, "Log level can be 0(errors), 1(warnings), 2(informational), 9(debug)\n");
						return 1;
					}
					break;
				}
				case 's':
				{
					int statDelay =  atoi(argv[i+1]);
					i++;
					if (statDelay < 0)
					{
						fprintf(stderr, "Statistics print delay must not be lower than 0. Use 0 to disable.\n");
						return 1;
					}
					databaseServer.SetStatDelay(statDelay);
					Log::printStats = true;
					break;
				}					
				case '?':
					usage();
					return 0;
				default:
					fprintf(stderr, "Parsing error, unknown parameter\n\n");
					usage();
					return 1;
			}
		}
		else
		{
			printf("Parsing error, incorrect parameters\n\n");
			usage();
			return 1;
		}
	}
	
#ifndef WIN32
	if (daemonMode)
	{
		printf("Running in daemon mode, file logging enabled...\n");
		if (!useLogFile)
			useLogFile = Log::EnableFileLogging(logfile);
		// Don't change cwd to /
		// Beware that log/pid files are placed wherever this was launched from
		daemon(1, 0);
	}
	
	if (!WriteProcessID(argv[0], &pidFile[0], fileBufSize))
		perror("Warning, failed to write own PID value to PID file\n");
#endif

	// Start the peers
	RakPeerInterface *masterPeer = RakNetworkFactory::GetRakPeerInterface();
	masterPeer->SetMaximumIncomingConnections(connectionCount);
	SocketDescriptor sd(listenPort,0);
	masterPeer->Startup(connectionCount, 30, &sd, 1);
	masterPeer->AttachPlugin(&databaseServer);
		
	Log::print_log("Unity master server version %s\n", VERSION);
	Log::print_log("Master server port set to %d\n",listenPort);
	Log::print_log("%d connection count limit\n", connectionCount);
	if (Log::printStats)
		Log::print_log("%d sec delay between statistics print to log\n", databaseServer.GetStatDelay());
	
	// Register signal handlers
#ifndef WIN32
	if (signal(SIGHUP, Log::RotateLogFile) == SIG_ERR)
		Log::error_log("Problem setting up hangup signal handler");
#endif
	if (signal(SIGINT, shutdown) == SIG_ERR || signal(SIGTERM, shutdown) == SIG_ERR)
		Log::error_log("Problem setting up terminate signal handler");
	else
		Log::print_log("To quit press Ctrl-C\n----------------------------------------------------\n");

	Packet *p;
	while (!quit)
	{
		p=masterPeer->Receive();
		while (p)
		{
			ProcessPacket(p);
			masterPeer->DeallocatePacket(p);
			p=masterPeer->Receive();
		}
		// Is it time to rotate the logs?
		if (useLogFile)
		{
			if (rotateCheckTimer < time(0))
			{
				// We should always be writing to the end of the stream, so the current position should give the total size
				int position = Log::GetLogSize();
				if (position > rotateSizeLimit) {
					Log::info_log("Rotating logs, size limit reached\n");
					Log::RotateLogFile(0);
				}
				rotateCheckTimer = time(0) + timerInterval;
			}
		}
		RakSleep(30);
	}

	if (pidFile)
	{
		if (remove(pidFile) != 0)
			fprintf(stderr, "Failed to remove PID file at %s\n", pidFile);
	}	
	masterPeer->Shutdown(100,0);
	RakNetworkFactory::DestroyRakPeerInterface(masterPeer);
				
	return 0;
}