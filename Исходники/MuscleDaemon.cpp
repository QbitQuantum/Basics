void
App::ArgvReceived(int32 argc, char **argv)
{
	printf("ArgvReceived\n");
	
	Message args; 
	(void) ParseArgs(argc, argv, args);
	HandleStandardDaemonArgs(args);

	const char * value;
	if (args.HasName("help")) {
		Log(MUSCLE_LOG_INFO, "Usage:  muscled [port=%u] [listen=ip:port] [displaylevel=lvl] [filelevel=lvl] [logfile=filename]\n", DEFAULT_MUSCLED_PORT); 
#ifdef MUSCLE_ENABLE_MEMORY_TRACKING
		Log(MUSCLE_LOG_INFO, "					 [maxmem=megs]\n");
#endif
		Log(MUSCLE_LOG_INFO, "					 [maxnodespersession=num] [remap=oldip=newip]\n");
		Log(MUSCLE_LOG_INFO, "					 [ban=ippattern] [require=ippattern]\n");
		Log(MUSCLE_LOG_INFO, "					 [privban=ippattern] [privunban=ippattern]\n");
		Log(MUSCLE_LOG_INFO, "					 [privkick=ippattern] [privall=ippattern]\n");
		Log(MUSCLE_LOG_INFO, "					 [maxsendrate=kBps] [maxreceiverate=kBps]\n");
		Log(MUSCLE_LOG_INFO, "					 [maxcombinedrate=kBps] [maxmessagesize=k]\n");
		Log(MUSCLE_LOG_INFO, "					 [maxsessions=num] [maxsessionsperhost=num]\n");
		Log(MUSCLE_LOG_INFO, "					 [localhost=ipaddress] [daemon]\n");
		Log(MUSCLE_LOG_INFO, " - port may be any number between 1 and 65536\n");
		Log(MUSCLE_LOG_INFO, " - listen is like port, except it includes a local interface IP as well.\n");
		Log(MUSCLE_LOG_INFO, " - lvl is: none, critical, errors, warnings, info, debug, or trace.\n");
#ifdef MUSCLE_ENABLE_MEMORY_TRACKING
		Log(MUSCLE_LOG_INFO, " - maxmem is the max megabytes of memory the server may use (default=unlimited)\n");
#endif
		Log(MUSCLE_LOG_INFO, " - You may also put one or more ban=<pattern> arguments in.\n");
		Log(MUSCLE_LOG_INFO, "	Each pattern specifies one or more IP addresses to\n");
		Log(MUSCLE_LOG_INFO, "	disallow connections from, e.g. ban=192.168.*.*\n");
		Log(MUSCLE_LOG_INFO, " - You may put one or more require=<pattern> arguments in.\n");
		Log(MUSCLE_LOG_INFO, "	If any of these are present, then only IP addresses that match\n");
		Log(MUSCLE_LOG_INFO, "	at least one of them will be allowed to connect.\n");
		Log(MUSCLE_LOG_INFO, " - To assign privileges, specify one of the following:\n");
		Log(MUSCLE_LOG_INFO, "	privban=<pattern>, privunban=<pattern>,\n");
		Log(MUSCLE_LOG_INFO, "	privkick=<pattern> or privall=<pattern>.\n");
		Log(MUSCLE_LOG_INFO, "	privall assigns all privileges to the matching IP addresses.\n");
		Log(MUSCLE_LOG_INFO, " - remap tells muscled to treat connections from a given IP address\n");
		Log(MUSCLE_LOG_INFO, "	as if they are coming from another (for stupid NAT tricks, etc)\n");
		Log(MUSCLE_LOG_INFO, " - If daemon is specified, muscled will run as a background process.\n");
	}

	{
		for (int32 i = 0; (args.FindString("port", i, &value) == B_NO_ERROR); i++) {
			int16 port = atoi(value);
			
			if (port >= 0)
				listenPorts.PutWithDefault(IPAddressAndPort(invalidIP, port));
		}

		for (int32 i = 0; (args.FindString("listen", i, &value) == B_NO_ERROR); i++) {
			IPAddressAndPort iap(value, DEFAULT_MUSCLED_PORT, false);
			
			if (iap.GetPort() > 0)
				listenPorts.PutWithDefault(iap);
			else
				LogTime(MUSCLE_LOG_ERROR, "Unable to parse IP/port string [%s]\n", value);
		}
	}

	{
		for (int32 i = 0; (args.FindString("remap", i, &value) == B_NO_ERROR); i++) {
			StringTokenizer tok(value, ",=");
			const char * from = tok();
			const char * to = tok();
			ip_address fromIP = from ? Inet_AtoN(from) : 0;
			
			if ((fromIP != invalidIP)&&(to)) {
				char ipbuf[64]; Inet_NtoA(fromIP, ipbuf);
				LogTime(MUSCLE_LOG_INFO, "Will treat connections coming from [%s] as if they were from [%s].\n", ipbuf, to);
				tempRemaps.Put(fromIP, to);
			} else
				LogTime(MUSCLE_LOG_ERROR, "Error parsing remap argument (it should look something like remap=192.168.0.1,132.239.50.8).\n");
		}
	}

#ifdef MUSCLE_ENABLE_MEMORY_TRACKING
	if (args.FindString("maxmem", &value) == B_NO_ERROR) {
		int megs = muscleMax(1, atoi(value));
		LogTime(MUSCLE_LOG_INFO, "Limiting memory usage to %i megabyte%s.\n", megs, (megs==1)?"":"s");
		maxBytes = megs*1024L*1024L;
	}
#endif

	if (args.FindString("maxmessagesize", &value) == B_NO_ERROR) {
		int k = muscleMax(1, atoi(value));
		LogTime(MUSCLE_LOG_INFO, "Limiting message sizes to %i kilobyte%s.\n", k, (k==1)?"":"s");
		maxMessageSize = k*1024L;
	}

	if (args.FindString("maxsendrate", &value) == B_NO_ERROR) {
		float k = (float) atof(value);
		maxSendRate = muscleMax((uint32)0, (uint32)(k * 1024.0f));
	}

	if (args.FindString("maxreceiverate", &value) == B_NO_ERROR) {
		float k = (float) atof(value);
		maxReceiveRate = muscleMax((uint32)0, (uint32)(k * 1024.0f));
	}

	if (args.FindString("maxcombinedrate", &value) == B_NO_ERROR) {
		float k = (float) atof(value);
		maxCombinedRate = muscleMax((uint32)0, (uint32)(k * 1024.0f));
	}

	if (args.FindString("maxnodespersession", &value) == B_NO_ERROR) {
		maxNodesPerSession = atoi(value);
		LogTime(MUSCLE_LOG_INFO, "Limiting nodes-per-session to "UINT32_FORMAT_SPEC".\n", maxNodesPerSession);
	}

	if (args.FindString("maxsessions", &value) == B_NO_ERROR) {
		maxSessions = atoi(value);
		LogTime(MUSCLE_LOG_INFO, "Limiting total session count to "UINT32_FORMAT_SPEC".\n", maxSessions);
	}

	if (args.FindString("maxsessionsperhost", &value) == B_NO_ERROR) {
		maxSessionsPerHost = atoi(value);
		LogTime(MUSCLE_LOG_INFO, "Limiting session count for any given host to "UINT32_FORMAT_SPEC".\n", maxSessionsPerHost);
	}
	
	if (args.FindString("privatekey", &value) == B_NO_ERROR) {
		fprivateKeyFilePath = new String(value);	
		//const String * fprivateKeyFilePath = args.GetStringPointer("privatekey");
		//LogTime(MUSCLE_LOG_INFO, "Limiting session count for any given host to "UINT32_FORMAT_SPEC".\n", fprivateKeyFilePath);
	}

	{
		for (int32 i = 0; (args.FindString("ban", i, &value) == B_NO_ERROR); i++) {
			LogTime(MUSCLE_LOG_INFO, "Banning all clients whose IP addresses match [%s].\n", value);	
			bans.AddTail(value);
		}
	}

	{
		for (int32 i = 0; (args.FindString("require", i, &value) == B_NO_ERROR); i++) {
			LogTime(MUSCLE_LOG_INFO, "Allowing only clients whose IP addresses match [%s].\n", value);	
			requires.AddTail(value);
		}
	}
	
	{
		const char * privNames[] = {"privkick", "privban", "privunban", "privall"};
		for (int p = 0; p <= PR_NUM_PRIVILEGES; p++) {  // if (p == PR_NUM_PRIVILEGES), that means all privileges
			for (int32 q=0; (args.FindString(privNames[p], q, &value) == B_NO_ERROR); q++) {
				LogTime(MUSCLE_LOG_INFO, "Clients whose IP addresses match [%s] get %s privileges.\n", value, privNames[p]+4);
				char tt[32]; 
				muscleSprintf(tt, "priv%i", p);
				tempPrivs.AddString(tt, value);
			}
		}
	}
}