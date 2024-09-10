int main(int argc, char **argv)
{
	int i, j;
	struct timeval time_interval;
	fd_set useRead;
	fd_set useExcept;
	int selRet;
	char errTxt[256];
	RsslBuffer errorText = {255, (char*)errTxt};
	RsslInProgInfo inProg = RSSL_INIT_IN_PROG_INFO;
	RsslRet	retval = 0;
	int iargs;
	RsslErrorInfo rsslErrorInfo;
	RsslBool cacheOption = RSSL_FALSE;

	RsslReactorOMMProviderRole providerRole;

	RsslBindOptions sopts = RSSL_INIT_BIND_OPTS;

	RsslCreateReactorOptions reactorOpts;

	RsslReactorDispatchOptions dispatchOpts;

	time_t nextSendTime;

	/* Initialize RSSL. The locking mode RSSL_LOCK_GLOBAL_AND_CHANNEL is required to use the RsslReactor. */
	if (rsslInitialize(RSSL_LOCK_GLOBAL_AND_CHANNEL, &rsslErrorInfo.rsslError) != RSSL_RET_SUCCESS)
	{
		printf("rsslInitialize(): failed <%s>\n",rsslErrorInfo.rsslError.text);
		/* WINDOWS: wait for user to enter something before exiting  */
#ifdef _WIN32
		printf("\nPress Enter or Return key to exit application:");
		getchar();
#endif
		exit(RSSL_RET_FAILURE);
	}

	rsslClearOMMProviderRole(&providerRole);

	providerRole.base.channelEventCallback = channelEventCallback;
	providerRole.base.defaultMsgCallback = defaultMsgCallback;
	providerRole.loginMsgCallback = loginMsgCallback;
	providerRole.directoryMsgCallback = directoryMsgCallback;
	providerRole.dictionaryMsgCallback = dictionaryMsgCallback;
	providerRole.tunnelStreamListenerCallback = tunnelStreamListenerCallback;

	rsslClearCreateReactorOptions(&reactorOpts);

	if (!(pReactor = rsslCreateReactor(&reactorOpts, &rsslErrorInfo)))
	{
		printf("Reactor creation failed: %s\n", rsslErrorInfo.rsslError.text);
		cleanUpAndExit();
	}

	snprintf(portNo, 128, "%s", defaultPortNo);
	snprintf(serviceName, 128, "%s", defaultServiceName);
	setServiceId(1);
	for(iargs = 1; iargs < argc; ++iargs)
	{
		if (0 == strcmp("-p", argv[iargs]))
		{
			++iargs; if (iargs == argc) exitWithUsage();
			snprintf(portNo, 128, "%s", argv[iargs]);
		}
		else if (0 == strcmp("-s", argv[iargs]))
		{
			++iargs; if (iargs == argc) exitWithUsage();
			snprintf(serviceName, 128, "%s", argv[iargs]);
		}
		else if (0 == strcmp("-id", argv[iargs]))
		{
			long tmpId = 0;
			++iargs; if (iargs == argc) exitWithUsage();
			tmpId = atol(argv[iargs]);
			if (tmpId < 0)
			{
				printf("ServiceId must be positive.\n");
				exitWithUsage();
			}
			setServiceId(tmpId);
		}
		else if (0 == strcmp("-x", argv[iargs]))
		{
			xmlTrace = RSSL_TRUE;
			snprintf(traceOutputFile, 128, "RsslVAProvider\0");
		}
		else if (0 == strcmp("-runtime", argv[iargs]))
		{
			++iargs; if (iargs == argc) exitWithUsage();
			timeToRun = atoi(argv[iargs]);
		}
		else if (0 == strcmp("-cache", argv[iargs]))
		{
			cacheOption = RSSL_TRUE;
		}
		else
		{
			printf("Error: Unrecognized option: %s\n\n", argv[iargs]);
			exitWithUsage();
		}
	}
	printf("portNo: %s\n", portNo);
	printf("serviceName: %s\n", serviceName);
	printf("serviceId: %llu\n", getServiceId());

	/* Initialiize client session information */
	for (i = 0; i < MAX_CLIENT_SESSIONS; i++)
	{
		clearClientSessionInfo(&clientSessions[i]);
	}

	initializeCache(cacheOption);

	/* Initialize login handler */
	initLoginHandler();

	/* Initialize source directory handler */
	initDirectoryHandler();

	/* Initialize dictionary provider */
	initDictionaryProvider();

	/* Initialize market price handler */
	initItemHandler();

	/* Initialize symbol list item list */
	initSymbolListItemList();

	/* Initialize market by order items */
	initMarketByOrderItems();


	/* set service name in directory handler */
	setServiceName(serviceName);

	/* load dictionary */
	if (loadDictionary() != RSSL_RET_SUCCESS)
	{
		/* exit if dictionary cannot be loaded */
		/* WINDOWS: wait for user to enter something before exiting  */
#ifdef _WIN32
		printf("\nPress Enter or Return key to exit application:");
		getchar();
#endif
		exit(RSSL_RET_FAILURE);
	}

	initializeCacheDictionary();

	/* Initialize run-time */
	initRuntime();

	FD_ZERO(&readFds);
	FD_ZERO(&exceptFds);
	
	sopts.guaranteedOutputBuffers = 500;
	sopts.serviceName = portNo;
	sopts.majorVersion = RSSL_RWF_MAJOR_VERSION;
	sopts.minorVersion = RSSL_RWF_MINOR_VERSION;
	sopts.protocolType = RSSL_RWF_PROTOCOL_TYPE;

	/* Create the server. */
	if (!(rsslSrvr = rsslBind(&sopts, &rsslErrorInfo.rsslError)))
	{
		printf("Unable to bind RSSL server: <%s>\n",rsslErrorInfo.rsslError.text);
		/* WINDOWS: wait for user to enter something before exiting  */
#ifdef _WIN32
		printf("\nPress Enter or Return key to exit application:");
		getchar();
#endif
		exit(RSSL_RET_FAILURE);
	}

	FD_SET(rsslSrvr->socketId, &readFds);
	FD_SET(pReactor->eventFd, &readFds);
	
	rsslClearReactorDispatchOptions(&dispatchOpts);
	dispatchOpts.maxMessages = MAX_CLIENT_SESSIONS;

	// initialize next send time
	nextSendTime = time(NULL) + UPDATE_INTERVAL;

	/* this is the main loop */
	while(RSSL_TRUE)
	{
		useRead = readFds;
		useExcept = exceptFds;
		time_interval.tv_sec = UPDATE_INTERVAL;
		time_interval.tv_usec = 0;

		/* Call select() to check for any messages */
		selRet = select(FD_SETSIZE,&useRead,
		    NULL,&useExcept,&time_interval);

		if (selRet > 0)
		{
			RsslRet ret;

			/* Accept connection, if one is waiting */
			if (FD_ISSET(rsslSrvr->socketId, &useRead))
			{
				RsslClientSessionInfo *pClientSessionInfo = NULL;
				RsslReactorAcceptOptions aopts;

				rsslClearReactorAcceptOptions(&aopts);

				/* find an available client session */
				for (i = 0; i < MAX_CLIENT_SESSIONS; i++)
				{
					if (!clientSessions[i].isInUse)
					{
						pClientSessionInfo = &clientSessions[i];
						pClientSessionInfo->isInUse = RSSL_TRUE;
						break;
					}
				}

				/* Reject the channel if we are out of client sessions */
				if (!pClientSessionInfo)
					aopts.rsslAcceptOptions.nakMount = RSSL_TRUE;
				else
					aopts.rsslAcceptOptions.userSpecPtr = pClientSessionInfo;


				printf("Accepting new connection...\n");
				if (rsslReactorAccept(pReactor, rsslSrvr, &aopts, (RsslReactorChannelRole*)&providerRole, &rsslErrorInfo) != RSSL_RET_SUCCESS)
				{
					printf("rsslReactorAccept() failed: %s(%s)\n", rsslErrorInfo.rsslError.text, rsslErrorInfo.errorLocation);
					cleanUpAndExit();
				}
			}

			/* Call rsslReactorDispatch().  This will handle any events that have occurred on its channels.
			 * If there are events or messages for the application to process, they will be delivered
			 * through the callback functions given by the providerRole object. 
			 * A return value greater than RSSL_RET_SUCCESS indicates there may be more to process. */
			while ((ret = rsslReactorDispatch(pReactor, &dispatchOpts, &rsslErrorInfo)) > RSSL_RET_SUCCESS)
				;

			if (ret < RSSL_RET_SUCCESS)
			{
				printf("rsslReactorDispatch() failed: %s\n", rsslErrorInfo.rsslError.text);
				cleanUpAndExit();
			}
		}
		else if (selRet < 0)
		{
#ifdef _WIN32
			if (WSAGetLastError() == WSAEINTR)
				continue;
			printf("Error: select: %d\n", WSAGetLastError());
#else
			if (errno == EINTR)
				continue;
			perror("select");
#endif
			cleanUpAndExit();
		}

		// send any updates at next send time
		if (time(NULL) >= nextSendTime)
		{
			/* Send market price updates for each connected channel */
			updateItemInfo();
			for (i = 0; i < MAX_CLIENT_SESSIONS; i++)
			{
				if (clientSessions[i].clientChannel != NULL)
				{
					if (sendItemUpdates(pReactor, clientSessions[i].clientChannel) != RSSL_RET_SUCCESS)
					{
						removeClientSessionForChannel(pReactor, clientSessions[i].clientChannel);
					}

					// send any tunnel stream messages
					for (j = 0; j < MAX_TUNNEL_STREAMS; j++)
					{
						if (clientSessions[i].simpleTunnelMsgHandler[j].tunnelStreamHandler.pTunnelStream != NULL)
						{
							handleSimpleTunnelMsgHandler(pReactor, clientSessions[i].clientChannel, &clientSessions[i].simpleTunnelMsgHandler[j]);
						}
					}
				}
			}

			nextSendTime += UPDATE_INTERVAL;
		}

		/* Handle run-time */
		handleRuntime();
	}
}