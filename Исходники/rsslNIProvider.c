/*** MAIN ***/
int main(int argc, char **argv)
{
	RsslErrorInfo error;
	RsslError rsslErr;
	RsslCreateReactorOptions reactorOpts;
	RsslReactorDispatchOptions dispatchOpts;
	RsslInt32 j;

	RsslReactorOMMNIProviderRole role;
	RsslDataDictionary dictionary = RSSL_INIT_DATA_DICTIONARY;
	
	char err[128];
	RsslBuffer errBuf = {128, &err[0]};
	
	int selRet;

	time_t currentTime = 0;
	RsslRet ret;

	RsslInitializeExOpts initOpts = RSSL_INIT_INITIALIZE_EX_OPTS;

	rsslInitNIChannelCommand(&chnlCommand);

	handleConfig(argc, argv, &chnlCommand);

	initializeCache(cacheCommandlineOption);
	
	initOpts.jitOpts.libcryptoName = libcryptoName;
	initOpts.jitOpts.libsslName = libsslName;
	initOpts.jitOpts.libcurlName = libcurlName;
	initOpts.rsslLocking = RSSL_LOCK_GLOBAL_AND_CHANNEL;

	/* Initialize run-time */
	initRuntime();

	rsslInitializeEx(&initOpts, &rsslErr);

	/* Setup role */
	rsslClearOMMNIProviderRole((RsslReactorOMMNIProviderRole*)&role);
	role.pLoginRequest = (RsslRDMLoginRequest*)&chnlCommand.loginRequest;
	role.loginMsgCallback = processLoginResponse;
	role.pDirectoryRefresh = &chnlCommand.directoryRefresh;
	role.base.channelEventCallback = channelEventCallback;
	role.base.defaultMsgCallback = processResponse;

	printf("Connections:\n");

	chnlCommand.pRole = (RsslReactorChannelRole*)&role;
	chnlCommand.cOpts.rsslConnectOptions.guaranteedOutputBuffers = 500;
	chnlCommand.cOpts.rsslConnectOptions.majorVersion = RSSL_RWF_MAJOR_VERSION;
	chnlCommand.cOpts.rsslConnectOptions.minorVersion = RSSL_RWF_MINOR_VERSION;
	chnlCommand.cOpts.rsslConnectOptions.userSpecPtr = (void*)&chnlCommand;

//	printf("	%s:%s:%s\n", chnlCommand.hostName, chnlCommand.port, chnlCommand.serviceName);

	printf("		MarketPriceItems:");
	for(j = 0; j < CHAN_CMD_MAX_ITEMS; ++j)
	{
		RsslNIItemInfo *pItem = &chnlCommand.marketPriceItemInfo[j];
		if (pItem->isActive)
		printf(" %.*s", (int)sizeof(pItem->Itemname), pItem->Itemname);
	}

	printf("		MarketByOrderItems:");
	for(j = 0; j < CHAN_CMD_MAX_ITEMS; ++j)
	{
		RsslNIItemInfo *pItem = &chnlCommand.marketByOrderItemInfo[j];
		if (pItem->isActive)
		printf(" %.*s", (int)sizeof(pItem->Itemname), pItem->Itemname);
	}


	printf("\n");

	printf("\n");
	
	/* Load local dictionary */
	if(rsslLoadFieldDictionary("RDMFieldDictionary", &dictionary, &errBuf) < RSSL_RET_SUCCESS)
	{
		printf("Dictionary error: %s\n", errBuf.data);
		exit(-1);
	}
	
	chnlCommand.dictionary = &dictionary;
	
	initializeCacheDictionary(&dictionary);

	rsslClearCreateReactorOptions(&reactorOpts);
	reactorOpts.dispatchDecodeMemoryBufferSize = 1024;

	setupLoginRequest(&chnlCommand, 1);

	setupDirectoryResponseMsg(&chnlCommand, -1);
	
	if (!(pReactor = rsslCreateReactor(&reactorOpts, &error)))
	{
		printf("Error: %s", error.rsslError.text);
		exit(-1);
	}
	
	

	FD_ZERO(&readFds);
	FD_ZERO(&writeFds);
	FD_ZERO(&exceptFds);

	FD_SET(pReactor->eventFd, &readFds);

	if (rsslReactorConnect(pReactor, &chnlCommand.cOpts, chnlCommand.pRole, &error) != RSSL_RET_SUCCESS)
		printf("Error rsslReactorConnect(): %s\n", error.rsslError.text);
		
	rsslClearReactorDispatchOptions(&dispatchOpts);
	//dispatchOpts.pReactorChannel = &chnlCommand.reactorChannel;

	printf("Connection started!\n");

	while ( RSSL_TRUE )
	{
		struct timeval selectTime;
		int dispatchCount = 0;
		fd_set useReadFds = readFds, useWriteFds = writeFds, useExceptFds = exceptFds;
		selectTime.tv_sec = 1; selectTime.tv_usec = 0;

		handleRuntime();

		selRet = select(FD_SETSIZE, &useReadFds, &useWriteFds, &useExceptFds, &selectTime);

		if (selRet == 0 ) /* no messages received, send updates and continue */
		{
			// Update items
			updateItemInfo(&chnlCommand);

			/* Send market price updates for each connected channel */
			if (chnlCommand.startWrite == RSSL_TRUE)
			{
				if ((chnlCommand.reactorChannel != NULL) && (chnlCommand.reactorChannel->socketId != -1))
				{
					if (sendItemUpdates(pReactor,chnlCommand.reactorChannel) != RSSL_RET_SUCCESS)
						recoverConnection(pReactor, chnlCommand.reactorChannel, &chnlCommand);
				}
			}
			else
			{
				if (cacheInfo.useCache)
					cacheItemData(&chnlCommand);
			}
		}
		else if (selRet > 0)
		{
			RsslRet ret;
			while ((ret = rsslReactorDispatch(pReactor, &dispatchOpts, &error)) > 0);

			if(ret < 0)
			{
				printf("dispatch error! %i\n %s\n %s\n", ret, error.rsslError.text, error.errorLocation);
				/* Reactor has shutdown. Clean up and exit. */
				cleanUpAndExit();
			}
		}
	
		/* get current time */
		if ((currentTime = time(NULL)) < 0)
		{
			printf("time() failed.\n");
		}

		// send login reissue if login reissue time has passed
		if (chnlCommand.canSendLoginReissue == RSSL_TRUE &&
			currentTime >= (RsslInt)chnlCommand.loginReissueTime)
		{
			RsslReactorSubmitMsgOptions submitMsgOpts;
			RsslErrorInfo rsslErrorInfo;

			rsslClearReactorSubmitMsgOptions(&submitMsgOpts);
			submitMsgOpts.pRDMMsg = (RsslRDMMsg*)chnlCommand.pRole->ommNIProviderRole.pLoginRequest;
			if ((ret = rsslReactorSubmitMsg(pReactor,chnlCommand.reactorChannel,&submitMsgOpts,&rsslErrorInfo)) != RSSL_RET_SUCCESS)
			{
				printf("Login reissue failed:  %d(%s)\n", ret, rsslErrorInfo.rsslError.text);
			}
			else
			{
				printf("Login reissue sent\n");
			}
			chnlCommand.canSendLoginReissue = RSSL_FALSE;
		}
	}
}