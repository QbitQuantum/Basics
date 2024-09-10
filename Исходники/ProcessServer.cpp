int main( int argc, char ** argv )
{
	CharString iniFile = "./ProcessServer.ini";
	if ( argc > 1 )
		iniFile = argv[1];

	Settings settings( "ProcessServer", iniFile );
	
	// initialize the logging first thing before we do anything else..
	std::string logFile( settings.get( "logFile", "ProcessServer.log" ) );
	std::string logExclude( settings.get( "logExclude", "" ) );
	unsigned int nMinLogLevel = settings.get( "logLevel", LL_STATUS );
	new FileReactor( logFile, nMinLogLevel, logExclude );

	bool bRemoteUpdate = settings.get( "remoteUpdate", 1 ) != 0;
	bool bLocalUpdate = settings.get( "localUpdate", (dword)0 ) != 0;

	CharString sPath( FileDisk::currentDirectory() );
	if (! sPath.endsWith( PATH_SEPERATOR ) )
		sPath += PATH_SEPERATOR;

#if !defined(_DEBUG)
	// update the files
	if ( settings.get( "doUpdate", 1 ) != 0 )
	{
		settings.put( "doUpdate", (dword)0 );

		if ( bLocalUpdate )
		{
			CharString updatePath = settings.get( "localUpdatePath", "" );
			if ( updatePath.length() > 0 )
			{
				FileDisk::normalizePath( updatePath.buffer() );
				if (! updatePath.endsWith( PATH_SEPERATOR ) )
					updatePath += PATH_SEPERATOR;

				// copy the files from a directory
				if ( localUpdate( sPath, updatePath ) )
					return -3;		// let the service/script update our files..
			}
		}
	}
#endif

	// do the update next time!
	settings.put( "doUpdate", 1 );

	ProcessServer::Context context;
	context.logFile = logFile.c_str();
	context.name = settings.get( "name", "ProcessServer" );
	context.config = iniFile;
	context.gameId = settings.get( "gameId", 1 );
	context.processGroup = settings.get( "processGroup", 1 );
	context.networkGroup = settings.get( "networkGroup", 1 );
	context.metaAddress = settings.get( "metaAddress", "meta-server.palestar.com" );
	context.metaPort = settings.get( "metaPort", 9000 );
	context.uid = settings.get( "uid", "DSS" );
	context.pw = settings.get( "pw", "darkspace" );
	context.address = settings.get( "address", "" );
	context.port = settings.get( "port", 8000 );
	context.maxClients = settings.get( "maxClients", 1000 );
	context.processFile = iniFile;
	context.syncClock = settings.get ("syncClock", (dword)0 ) != 0;

	// start the server
	MyProcessServer theServer;
	if (! theServer.start( context ) )
		return -1;

	// signal that we are running
	Event serverRunning( "ProcessServerRun" );
	serverRunning.signal();

	dword nNextUpdateCheck = Time::seconds() + settings.get("updateTime",300);
	dword nLastCRC = 0;

	// run the server forever, unless it crashes
	Event serverStop( "ProcessServerStop" );
	while( theServer.running() && !theServer.shutdownCompleted() )
	{
		if (! serverStop.wait( 10 ) )
		{
			LOG_STATUS( "ProcessServer", "Recevied shutdown signal." );
			theServer.shutdown();

			serverStop.clear();
		}

		theServer.update();
		theServer.updatePerformanceMonitor();

#if !defined(_DEBUG)
		if ( bRemoteUpdate && nNextUpdateCheck < Time::seconds() )
		{
			// check for new code update
			MirrorClient mirrorClient;
			if ( mirrorClient.open( 
				settings.get( "mirrorAddress", "mirror-server.palestar.com" ),
				settings.get( "mirrorPort", 9200 ), sPath, NULL, true ) )
			{
				// attempt to login, ingore if failed
				mirrorClient.login( settings.get( "uid", "" ), settings.get( "pw", "" ) );

				// get the CRC only, only do a sync if remote files have been changed...
				dword nCRC = mirrorClient.getCRC();
				if ( nCRC != nLastCRC )
				{
					nLastCRC = nCRC;

					dword nJobID = mirrorClient.syncronize();
					if ( nJobID != 0 && mirrorClient.waitJob( nJobID, 86400 * 1000 ) )
					{
						int nWarningTime = settings.get( "warningTime", 300 );

						LOG_STATUS( "ProcessServer", "Files updated -- Restarting the server in %d seconds.", nWarningTime );

						CharString sWarningMessage = settings.get( "warningMessage", 
							CharString().format("/notice /%s Updating in $T...", context.name.cstr() ) );
						while( nWarningTime > 0 )
						{
							CharString sTimeLeft;
							sTimeLeft.format("%d %s", 
								nWarningTime > 60 ? nWarningTime / 60 : nWarningTime,
								nWarningTime > 60 ? "minute(s)" : "second(s)");

							// replace the "$T" token with the time remaining...
							CharString sChat = sWarningMessage;
							sChat.replace( "$T", sTimeLeft );

							theServer.sendChat( sChat );

							int nSleepTime = 0;
							if ( nWarningTime > (60 * 10) )
								nSleepTime = 60 * 5;			// sleep for 5 minutes
							else
								nSleepTime = 60;				// sleep for 1 minute

							if ( nSleepTime > nWarningTime )
								nSleepTime = nWarningTime;

							nWarningTime -= nSleepTime;

							dword nEndSleep = Time::seconds() + nSleepTime;
							while( Time::seconds() < nEndSleep )
							{
								if (! serverStop.wait( 10 ) )
								{
									LOG_STATUS( "ProcessServer", "Received stop signal, stopping now." );
									nSleepTime = nWarningTime = 0;		// stop now... no warning
									break;
								}

								theServer.update();
								theServer.updatePerformanceMonitor();
							}
						}

						// start the shutdown, server will exit once the last process has stopped..
						theServer.shutdown();
					}
				}
				mirrorClient.close();
			}
			else
			{
				LOG_ERROR( "ProcessServer", "Failed to connect to MirrorServer!" );
			}
		

			nNextUpdateCheck = Time::seconds() + settings.get("updateTime",300);
		}
#endif
	}

	theServer.stop();

	return 0;
}