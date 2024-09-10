void main(int argc, char **argv) {

HWND hWin;
vrpn_Sound_Server_A3D * soundServer = NULL;
vrpn_Tracker_Remote   * tracker_connection;
char                    tracker_device[512];
char                    tracker_name[512];
vrpn_Connection       * connection;
vrpn_Connection       * trackerCon;
int                     got_report;

int USE_TRACKER;

	char	* config_file_name = "vrpn.cfg";
	FILE	* config_file;
	char 	* client_name   = NULL;
	int	    client_port   = 4150;
	int	    bail_on_error = 1;
	int	    verbose       = 1;
	int	    auto_quit     = 0;
	int	    realparams    = 0;
	int 	  loop          = 0;
	int	    port          = vrpn_DEFAULT_LISTEN_PORT_NO;

	connection = new vrpn_Synchronized_Connection (port);
	
	// Open the configuration file
	if (verbose) printf("Reading from config file %s\n", config_file_name);
	
	if ( (config_file = fopen(config_file_name, "r")) == NULL) 
	{
		perror("Cannot open config file");
		printf("  (filename %s)\n", config_file_name);
		return;
	}
		
	// Read the configuration file, creating a device for each entry.
	// Each entry is on one line, which starts with the name of the
	//   class of the object that is to be created.
	// If we fail to open a certain device, print a message and decide
	//  whether we should bail.
	{	
		char	line[512];	// Line read from the input file
		char *pch;
		char    scrap[512], s2[512];
	
		// Read lines from the file until we run out
		while ( fgets(line, sizeof(line), config_file) != NULL ) 
		{
			
			// Make sure the line wasn't too long
			if (strlen(line) >= sizeof(line)-1) 
			{
				printf("Line too long in config file: %s\n",line);
				if (bail_on_error) { return; }
				else { continue; }	// Skip this line
			}
			
			if ((strlen(line)<3)||(line[0]=='#')) 
			{
				// comment or empty line -- ignore
				continue;
			}
			
			// copy for strtok work
			strncpy(scrap, line, sizeof(line) - 1);
			// Figure out the device from the name and handle appropriately
			
			// WARNING: SUBSTRINGS WILL MATCH THE EARLIER STRING, SO 
			// ADD AN EMPTY SPACE TO THE END OF STATIC STRINGS!!!!
			
			//	  #define isit(s) !strncmp(line,s,strlen(s))
#define isit(s) !strcmp(pch=strtok(scrap," \t"),s)
#define next() pch += strlen(pch) + 1
	
			#ifdef _WIN32

			if(isit("vrpn_Sound_Server"))
			{
				printf("%s\n",pch); 
				next();
				printf("%s\n",pch);
				if (sscanf(pch,"%511s\t%d\t%511s\t%511s",s2,&USE_TRACKER,tracker_name, tracker_device) != 4) 
				{
					printf("Bad vrpn_Server_Sound line: %s\n",line);
					if (bail_on_error) 
					{ 
						return; 
					}
					else 
					{ 
						continue; 
					}	// Skip this line
				}

				hWin = GetConsoleHwnd();

				printf("Begin initializing A3D Sound Server\n");	
				soundServer = NULL;
				soundServer = new vrpn_Sound_Server_A3D(s2, connection,hWin);
				if (soundServer == NULL) 
					printf("Can't create sound server\n");
        printf("End A3D Sound Server initialization\n");	
				
			}
#endif
		}
	}

	fclose(config_file);

	// Open remote tracker if we are to use one

	if (USE_TRACKER) {
		
		char newname[1024];
		sprintf(newname,"%s@%s",(const char*)tracker_device, (const char*)tracker_name);
		printf("Using tracker: %s\n",newname);
		trackerCon = vrpn_get_connection_by_name(tracker_name);
		tracker_connection = new vrpn_Tracker_Remote((const char *) newname);
		// SET UP TRACKER HANDLER
		if (trackerCon->doing_okay()) {
			printf( "TC OK.\n");
		} else {
			printf( "TC Not OK.\n");
		}
	}
	else printf("Not using tracker\n");

	loop = 0;
	
	if (client_name) 
	{
		printf( "vrpn_serv: connecting to client: %s:%d\n",
			client_name, client_port);
		if (connection->connect_to_client(client_name, client_port))
		{
			printf( "server: could not connect to client %s:%d\n", client_name, client_port);
		}
	}
	
		
// ********************************************************************
// **                                                                **
// **                MAIN LOOP                                       **
// **                                                                **
// ********************************************************************
float fPrevTime = 0.0f;
float fFrameTime;
float fTime;
int counter = 0;
int stopNow = 0;
int numconnections = 0;
char buf[1024];

	printf("Begin main loop\n");

	while (!stopNow && 	!_kbhit()) {

    soundServer->GetLastError(buf);

    if (!strncmp(buf,"ERROR",5)) {
		  printf("%s", buf);
    }
      counter++;

  	  // record time since last frame 
      if (counter==NUM_SPIN) {
	    fTime = (float)timeGetTime();
	    counter = 0;

	    fFrameTime = (fTime - fPrevTime) * 0.001f;
	  
	    printf("Running at %4.2f Hz\n", (float) NUM_SPIN/fFrameTime);

        fPrevTime = fTime;
      }

	  soundServer->mainloop();
						
		// ensure we get a new report!
		if (USE_TRACKER) {
		  tracker_connection->mainloop();
		  got_report = 0;
		  if (trackerCon->doing_okay())
		    while (!got_report) 
			  tracker_connection->mainloop(); 
		}

		// Send and receive all messages
		connection->mainloop();
		if (numconnections==0 && connection->connected())
           numconnections++;
	
		if (((numconnections!=0) & (!connection->connected())) | !connection->doing_okay())  {
			soundServer->shutDown();
		  numconnections=0;
		}
	}

	printf("about to shutdown\n");
//	delete connection;
   delete soundServer;
}