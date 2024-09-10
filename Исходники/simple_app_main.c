int main(int argc, char **argv)
{
	// IMPORTANT: This call to tiLogging_Init() MUST BE DONE FIRST.
	// One thing it does is changes the buffering of stdout to line-based,
	// and that works ONLY if the stream has not been used yet, so we
	// MUST NOT printf/log anything before calling it...
	tiLogging_Init(NULL);

	LOG_INFO("Starting...\n");

	// Return value for main
	int ret = 0;

	consoleInput.latestCh = ' ';
	consoleInput.handle = RTI_MAIN_INPUT_RELEASED;

	// setup filedescriptor for stdin
	fds[0].fd = fileno(stdin);
	fds[0].events = POLLIN;

	parse_opts(argc, argv);

	// Initialize shared semaphore. Must happen before program begins execution
	sem_init(&eventSem,0,1);

//	FILE *tmpFile;

	if ((ret = NPI_ClientInit(device)) != NPI_LNX_SUCCESS)
	{
		LOG_FATAL("Failed to start RTI library module, device; %s\n", device);
		print_usage(argv[0]);
		return ret;
	}
	// Get port from device
	char *pDevice = (char *)device;
	char *tmpStr = strtok(pDevice, ":");
	tmpStr = strtok(NULL, ":");
	connectedPort = strtol(tmpStr, NULL, 10);

	// Toggle Timer Print on Server state variable
	//Start RTI thread, management of RTI command in separate thread.
	if ((ret = SimpleAppInit(mode, SIMPLE_App_threadId)) != 0)
	{
		return ret;
	}

	LOG_INFO("Starting timer thread\n");

	//Start RTI timer thread, management of timer in separate thread.
	if ((ret = timer_init(RTI_main_threadId_tblSize)) != 0)
	{
		LOG_FATAL("Failed to start timer thread. Exiting...");
		return ret;
	}

	//first Menu will be display at the end of the RNP initialization.

	int pollRet;

	//MANAGE DISPLAY HERE
	while (1)
	{
		//Wait for Display Mutex release before displaying anything.
		//pthread_mutex_lock(&appDisplayMutex);
		//pthread_mutex_unlock(&appDisplayMutex);

		//Check Display buffer, if not empty display one element

		// Check for input characters, timeout after 500ms
		pollRet = poll(fds, 1, 500);
		if ((pollRet == 1) && (consoleInput.handle == RTI_MAIN_INPUT_RELEASED))
		{
//			consoleInput.latestCh = getchar();
			fgets(consoleInput.latestStr, sizeof(consoleInput.latestStr), stdin);
			// Remove \n character from string
			char* p;
			if ( (p= strchr(consoleInput.latestStr, '\n')) != NULL)
				*p = '\0';
			consoleInput.latestCh = consoleInput.latestStr[0];
			if (consoleInput.latestCh == 'q')
			{
				ret = 0;
				break;
			}
			// Do not act on -1, . and new line (\n)
			if ( (consoleInput.latestCh != -1)
					&& (consoleInput.latestCh != '.')
					&& (consoleInput.latestCh != '\n') )
			{
				// Indicate to application thread that the input is ready
				consoleInput.handle = RTI_MAIN_INPUT_READY;
				// Release resources waiting for this event
				if (sem_post(&eventSem) < 0)
				{
					LOG_ERROR("[MAIN] Failed to post semaphore %p\n", &eventSem);
				}
			}
//			LOG_DEBUG("Character read: \t%c, int: %d\n", consoleInput.latestCh,
//					consoleInput.latestCh);
//			LOG_DEBUG("String read: \t%s\n", consoleInput.latestStr,
//					consoleInput.latestStr);
		}
//		LOG_DEBUG("poll returned: %d; console handle: %d\n", pollRet, consoleInput.handle);
	}

	// Destroy semaphores
	sem_destroy(&eventSem);

	NPI_ClientClose();

	return ret;
}