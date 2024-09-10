int _tmain(int argc, _TCHAR* argv[])
{
  splash(argv[0]);

  if((argc < 4) || ((argc > 5) && (strcmp("log", argv[5])))){
    printf("Usage: %s <ServerIP> <ClientIP> <OSCIP> <OSCPort> [\"log\"]", argv[0]);
  }else{


    int retCode;
    char* OSCIP = argv[3];
    int OSCPort = atoi(argv[4]);

    //EU
    printf("\n\nBanana hammock!!\n\n");

    // Set callback handlers
    theClient.SetMessageCallback(MessageHandler);
    theClient.SetVerbosityLevel(Verbosity_Debug);
    theClient.SetDataCallback( DataHandler, &theClient );	// this function will receive data from the server

    // Connect to NatNet server
    strcpy(szServerIPAddress, argv[1]);	// specified on command line
    strcpy(szMyIPAddress, argv[2]);	// specified on command line
    printf("Connecting to server at %s from %s...\n", szServerIPAddress, szMyIPAddress);

    // Connect to NatNet server


    retCode = theClient.Initialize(szMyIPAddress, szServerIPAddress);
    if (retCode != ErrorCode_OK)
      {
	printf("Unable to connect to server.  Error code: %d. Exiting", retCode);
	return 1;
      }
    else
      {

	// print server info
	sServerDescription ServerDescription;
	memset(&ServerDescription, 0, sizeof(ServerDescription));
	theClient.GetServerDescription(&ServerDescription);
	if(!ServerDescription.HostPresent)
	  {
	    printf("Unable to connect to server. Host not present. Exiting.");
	    return 1;
	  }
	printf("[OSCNatNetClient] Server application info:\n");
	printf("Application: %s (ver. %d.%d.%d.%d)\n",
	       ServerDescription.szHostApp,
	       ServerDescription.HostAppVersion[0],
	       ServerDescription.HostAppVersion[1],
	       ServerDescription.HostAppVersion[2],
	       ServerDescription.HostAppVersion[3]);
	printf("NatNet Version: %d.%d.%d.%d\n",
	       ServerDescription.NatNetVersion[0],
	       ServerDescription.NatNetVersion[1],
	       ServerDescription.NatNetVersion[2],
	       ServerDescription.NatNetVersion[3]);
	printf("Server IP:%s\n", szServerIPAddress);
	printf("Server Name:%s\n\n", ServerDescription.szHostComputerName);

	//EU - init UDP socket
	transmitSocket = new UdpTransmitSocket(IpEndpointName(OSCIP, OSCPort));
	printf("OSC IP:%s\n", OSCIP);
	printf("OSC Port:%d\n", OSCPort);
      }

    // send/receive test request
    printf("[OSCNatNetClient] Sending Test Request\n");
    void* response;
    int nBytes;
    retCode = theClient.SendMessageAndWait("TestRequest", &response, &nBytes);
    if (retCode == ErrorCode_OK)
      {
	printf("[OSCNatNetClient] Received: %s", (char*)response);
      }




    //Writing Session data to file

    char szFile[MAX_PATH];
    char szFolder[MAX_PATH];
#ifdef __linux__
    sprintf(szFolder, "./");
#else
    GetCurrentDirectory(MAX_PATH, szFolder);
#endif
    char timeLabel[50];
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    //create time label for files
    strftime (timeLabel,80,"%d.%m.%y %H.%M.%S",timeinfo);

    // Retrieve MarkerSets from server
    printf("\n\n[OSCNatNetClient] Requesting all data definitions for current session...");
    sDataDescriptions* pDataDefs = NULL;
    theClient.GetDataDescriptions(&pDataDefs);
    if(!pDataDefs){

      printf("[OSCNatNetClient] Unable to retrieve current session.");
      //return 1;

    }else{
      sprintf(szFile, "%s\\SessionData %s.txt", szFolder, timeLabel);
      fps = fopen(szFile, "w");
      if(!fps)
	{
	  printf("error opening output file %s.  Exiting.", szFile);
	  exit(1);
	}
      _WriteHeader(fps, pDataDefs);
      fclose(fps);
    }


    // Prepare data file for frame info

    if(argc > 5){

      sprintf(szFile, "%s\\FrameData %s.txt", szFolder, timeLabel);
      fpf = fopen(szFile, "w");
      if(!fpf){
	printf("error opening output file %s.  Exiting.", szFile);
	exit(1);
      }
    }



    // Ready to receive marker stream!
    printf("\nOSCNatNetClient is connected to server and listening for data... press 'q' for quitting\n");
    int c;
    bool bExit = false;
    while(c =_getch()){
      switch(c){
      case 'q':
	bExit = true;
	printf("\nQuitting...\n\n");
	break;
      case 'r':
	printf("\nReseting Client...\n\n");
	resetClient();
	break;
      default:
	printf("not an option\n\n");
	break;
      }
      if(bExit)
	break;
    }

    printf("clean up\n\n");
    // Done - clean up.
    theClient.Uninitialize();
    if(fpf != NULL) fclose(fpf);

    return ErrorCode_OK;
  }
}