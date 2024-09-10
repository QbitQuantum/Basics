int main(void)
{
	char udn[20];
	int i;
	char friendlyname[100];

	#ifdef WIN32
	WSADATA wsaData;
	#endif

	_CrtSetDbgFlag (
		_CRTDBG_ALLOC_MEM_DF       | 
		_CRTDBG_DELAY_FREE_MEM_DF  |
		_CRTDBG_LEAK_CHECK_DF      
		//_CRTDBG_CHECK_ALWAYS_DF
		);

	/* Randomized udn generation */
	#ifdef WIN32
	srand(GetTickCount());
	#endif

	#ifdef _POSIX
	srand((unsigned int)time(NULL));
	#endif

	for (i=0;i<19;i++)
	{
		udn[i] = (rand() % 25) + 66;
	}
	udn[19] = 0;

	/* generate a friendly name that has the host name in it */
	#ifdef WIN32
	if (WSAStartup(MAKEWORD(1,1), &wsaData) != 0) {exit(1);}
	#endif
	memcpy(friendlyname,"Intel MicroSTB (",16);
	gethostname(friendlyname+16,75);
	#ifdef WIN32
	memcpy(friendlyname+strlen(friendlyname),")/Win32\0",8);
	#endif
	#ifdef _POSIX
	memcpy(friendlyname+strlen(friendlyname),")/Posix\0",8);
	#endif

	/* Setup the callbacks */
	RemoteIOConnectionChanged = &XrtVideo_ConnectionChangedSink;
	RemoteIOReset = &XrtVideo_ResetSink;
	RemoteIOCommand = &XrtVideo_CommandSink;
	
	/* Setup the Remote IO Global Values */
	RemoteIO_Application		= "XRT20:Sample Client";
	RemoteIO_MaxCommandSize		= 65000;			// Set the maximum command size, keep this at 64k
	RemoteIO_DisplayEncoding	= RemoteIO_JPEG;	// Set the image format, see (enum RemoteIOImageFormat) for complete list.
	RemoteIO_DisplayWidth		= 640;				// Set the display width
	RemoteIO_DisplayHeight		= 480;				// Set the display height
	RemoteIO_DeviceInformation	= "";				// Set propriatary information about the device

	/*
	 *	Set of commands that can be sent back to the host PC. These can be used even
	 *	if remoting is not connected. For a device with an IR remote, only SendKeyPress is used.	
	 */
	/*
	RemoteIO_SendCommand(unsigned short command, char* data, int datalength);
	RemoteIO_SendKeyPress(int key);
	RemoteIO_SendKeyUp(int key);
	RemoteIO_SendKeyDown(int key);
	RemoteIO_SendMouseUp(int X,int Y,int Button);
	RemoteIO_SendMouseDown(int X,int Y,int Button);
	RemoteIO_SendMouseMove(int X,int Y);
	*/

	/* renderer callbacks. */
	MROnVolumeChangeRequest			= &MROnVolumeChangeRequestSink;
	MROnMuteChangeRequest			= &MROnMuteChangeRequestSink;
	MROnMediaChangeRequest			= &MROnMediaChangeRequestSink;
	MROnGetPositionRequest			= &MROnGetPositionRequestSink;
	MROnSeekRequest					= &MROnSeekRequestSink;
	MROnNextPreviousRequest			= &MROnNextPreviousRequestSink;
	MROnStateChangeRequest			= &MROnStateChangeRequestSink;
	MROnPlayModeChangeRequest		= &MROnPlayModeChangeRequestSink;



	printf("Intel MicroSTB Sample Client\r\n");

	StbChain = ILibCreateChain();
	StbLTM = ILibCreateLifeTime(StbChain);

	#ifdef _DEBUG
	printf("StbLTM=%p\r\n", StbLTM);
	#endif

	// Create the stack for the Media Server, Media Renderer, and RIOClient
	StbStack = UpnpCreateMicroStack(StbChain,friendlyname, udn, "0000001", 1600, 0);


	InitMms(StbChain, StbStack, ".\\");

	//ILibAddToChain(StbChain, StbLTM); /* seems to resolve dealyed event delivery */

    MR_ExtendedM3uProcessor = CreatePlaylistParser(StbChain, 3);
	MR_MediaRenderer = CreateMediaRenderer(StbChain, StbStack, StbLTM);
	MR_RendererLogic = RSL_CreateRendererStateLogic
		(
		StbChain,
		MR_MediaRenderer,
		InstructPlaylistLogic_FindTargetUri,
		InstructCodec_SetupStream,
		InstructCodec_Play,
		InstructCodec_Stop,
		InstructCodec_Pause,
		QueryCodec_IsBusy,
		Validate_MediaUri
		);


	/* Create the RemoteIO client */
	CreateRemoteIO(StbChain, StbStack);

	/* initialize emulated rendering module */
	CodecWrapper_Init(MAX_STREAMS);

	STBS_Init(StbChain);

	/*
	 *	Set up the app to periodically monitor the available list
	 *	of IP addresses.
	 */
	sem_init(&UpnpIPAddressListLock, 0, 1);

	#ifdef _POSIX
	UpnpMonitor = ILibCreateLifeTime(StbChain);
	UpnpIPAddressListLength = ILibGetLocalIPAddressList(&UpnpIPAddressList);
	ILibLifeTime_Add(UpnpMonitor,NULL,4,&UpnpIPAddressMonitor,NULL);
	#endif
	#ifdef _WINSOCK1
	UpnpMonitor = ILibCreateLifeTime(StbChain);
	UpnpIPAddressListLength = ILibGetLocalIPAddressList(&UpnpIPAddressList);
	ILibLifeTime_Add(UpnpMonitor,NULL,4,&UpnpIPAddressMonitor,NULL);
	#endif
	#ifdef _WINSOCK2
	UpnpMonitorSocket = socket(AF_INET,SOCK_DGRAM,0);
	WSAIoctl(UpnpMonitorSocket,SIO_ADDRESS_LIST_CHANGE,NULL,0,NULL,0,&UpnpMonitorSocketReserved,&UpnpMonitorSocketStateObject,&UpnpIPAddressMonitor);
	#endif

	// for the media server
	UpdateIPAddresses(UpnpIPAddressList, UpnpIPAddressListLength);

	/* start UPnP - blocking call*/
	#ifdef _POSIX
	signal(SIGINT,BreakSink);
	#endif

	#ifdef WIN32
	/* Setup a thread to allow user to stop renderer when user hits key */
	CreateThread(NULL,0,&Run,NULL,0,NULL);
	#endif

	ILibStartChain(StbChain); 	

	StopMms();
	
	STBS_Uninit();

	/* be sure to FREE the address list */
	sem_destroy(&UpnpIPAddressListLock);
	FREE(UpnpIPAddressList);
	UpnpIPAddressList = NULL;
	
	/* clean up wsastartup */
	#ifdef WIN32
	WSACleanup();
	#endif

	return 0;
}