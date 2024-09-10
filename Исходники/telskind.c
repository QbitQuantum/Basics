int main(int argc, char *argv[]) {
	int i, j;
	int thisSocket, thatSocket;
	int *confPort;
	unsigned int tmpSeconds;

	char *confConfig, *confEngine, *confPassword;
	char magicCookie[] = "TELLUTELLUTELLUTELLUTELLUTELLU";

	size_t s;

	uid_t *thisUid;
	gid_t *thisGid;

	/*
	 *
	 * Initialize default values.
	 *
	 */

	pMainMainInfo = &mainMainInfo;
	pMainThreadInfo = &mainThreadInfo;

	memset(pMainMainInfo, 0, sizeof(mainMainInfo));
	memset(pMainThreadInfo, 0, sizeof(mainThreadInfo));

	/*
	 *
	 * Read command line and parse configuration file.
	 *
	 */

	cmdRead(argv, argc);

	if((confConfig = configFetch("config_file", &i)) != NULL) {
		if(configRead(confConfig) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to read configuration file");
		}
	}
	else {
		if(configRead(CONFIG_DEFAULT_FILE) != 0) {
			warningMessage(ERROR_SLIGHT, "Error occurred while trying to read configuration file");
		}
	}

	cmdRead(argv, argc);

	nodeInitNames();

	/*
	 *
	 * Initialize thread pool.
	 *
	 */

	if((threadPool = malloc(sizeof(struct threadInfo) * THREAD_TELSKIND)) == NULL) {
		warningMessage(ERROR_FATAL, "Error occurred while trying to allocate memory for thread pool");
	}

	memset(threadPool, 0, sizeof(struct threadInfo) * THREAD_TELSKIND);

	/*
	 *
	 * Initialize configurable subroutines.
	 *
	 */

	pMainThreadInfo->threadReady = 1;

	for(j = 0; j < THREAD_TELSKIND; j++) {
		threadPool[j].threadReady = 1;

		threadPool[j].magicCookie = magicCookie;
		threadPool[j].pMainInfo = pMainMainInfo;

		if((confEngine = configFetch("storage_engine", &i)) != NULL) {
			if(strncasecmp(confEngine, "plain", strlen(confEngine)) == 0) {
				threadPool[j].dbInfo.connect = plainConnect;
				threadPool[j].dbInfo.disconnect = plainDisconnect;
				threadPool[j].dbInfo.escape = plainEscape;
				threadPool[j].dbInfo.push = plainPush;
				threadPool[j].dbInfo.pull = plainPull;
				threadPool[j].dbInfo.round = plainRound;
				threadPool[j].dbInfo.free = plainFree;
				threadPool[j].dbInfo.expire = plainExpire;
				threadPool[j].dbInfo.cookie = plainCookie;
				threadPool[j].dbInfo.insert = plainInsert;
				threadPool[j].dbInfo.login = plainLogin;
				threadPool[j].dbInfo.logout = plainLogout;
				threadPool[j].dbInfo.session = plainSession;
				threadPool[j].dbInfo.permission = plainPermission;

				pMainThreadInfo->dbInfo.connect = plainConnect;
				pMainThreadInfo->dbInfo.disconnect = plainDisconnect;
				pMainThreadInfo->dbInfo.escape = plainEscape;
				pMainThreadInfo->dbInfo.push = plainPush;
				pMainThreadInfo->dbInfo.pull = plainPull;
				pMainThreadInfo->dbInfo.round = plainRound;
				pMainThreadInfo->dbInfo.free = plainFree;
				pMainThreadInfo->dbInfo.expire = plainExpire;
				pMainThreadInfo->dbInfo.cookie = plainCookie;
				pMainThreadInfo->dbInfo.insert = plainInsert;
				pMainThreadInfo->dbInfo.login = plainLogin;
				pMainThreadInfo->dbInfo.logout = plainLogout;
				pMainThreadInfo->dbInfo.session = plainSession;
				pMainThreadInfo->dbInfo.permission = plainPermission;

				continue;
			}
		}

		threadPool[j].dbInfo.connect = mysqlConnect;
		threadPool[j].dbInfo.disconnect = mysqlDisconnect;
		threadPool[j].dbInfo.escape = mysqlEscape;
		threadPool[j].dbInfo.push = mysqlPush;
		threadPool[j].dbInfo.pull = mysqlPull;
		threadPool[j].dbInfo.round = mysqlRound;
		threadPool[j].dbInfo.free = mysqlFree;
		threadPool[j].dbInfo.expire = mysqlExpire;
		threadPool[j].dbInfo.cookie = mysqlCookie;
		threadPool[j].dbInfo.insert = mysqlInsert;
		threadPool[j].dbInfo.login = mysqlLogin;
		threadPool[j].dbInfo.logout = mysqlLogout;
		threadPool[j].dbInfo.session = mysqlSession;
		threadPool[j].dbInfo.permission = mysqlPermission;

		pMainThreadInfo->dbInfo.connect = mysqlConnect;
		pMainThreadInfo->dbInfo.disconnect = mysqlDisconnect;
		pMainThreadInfo->dbInfo.escape = mysqlEscape;
		pMainThreadInfo->dbInfo.push = mysqlPush;
		pMainThreadInfo->dbInfo.pull = mysqlPull;
		pMainThreadInfo->dbInfo.round = mysqlRound;
		pMainThreadInfo->dbInfo.free = mysqlFree;
		pMainThreadInfo->dbInfo.expire = mysqlExpire;
		pMainThreadInfo->dbInfo.cookie = mysqlCookie;
		pMainThreadInfo->dbInfo.insert = mysqlInsert;
		pMainThreadInfo->dbInfo.login = mysqlLogin;
		pMainThreadInfo->dbInfo.logout = mysqlLogout;
		pMainThreadInfo->dbInfo.session = mysqlSession;
		pMainThreadInfo->dbInfo.permission = mysqlPermission;
	}

	/*
	 *
	 * Initialize magick cookie.
	 *
	 */

	if((confPassword = configFetch("agent_password", &i)) != NULL) {
		s = strlen(confPassword);

		if(s > DATA_COOKIE_SIZE) {
			s = DATA_COOKIE_SIZE;
		}

		strncpy(magicCookie, confPassword, s);
	}

	/*
	 *
	 * Initialize main thread.
	 *
	 */

	configSetUmask(0077);

	if(configSetLocale(CONFIG_DEFAULT_LOCALE) != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to set default locale");
	}

	if(configChangeRoot(CONFIG_DEFAULT_ROOT) != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to change root directory");
	}

	if(configCloseInput() != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to close standard input");
	}

	if(configDaemonize() != 0) {
		warningMessage(ERROR_SLIGHT, "Error occurred while trying to daemonize process");
	}

	threadStack(THREAD_TELSKIND);
	beginProcess(pMainThreadInfo);

	/*
	 *
	 * Initialize timer.
	 *
	 */

	if(timerInit(TIMER_RESOLUTION_STATUS, 0, timerStatThreads) != 0) {
		warningMessage(ERROR_FATAL, "Error occurred while trying to initialize timer");
	}

	/*
	 *
	 * Initialize worker threads.
	 *
	 */

	pMainMainInfo->allRunning = 0;
	pMainMainInfo->theEnd = 0;
	pMainMainInfo->threadEnd = 0;

	for(i = 0; i < THREAD_TELSKIND; i++) {
		if(threadInit(&threadPool[i], workerThread, &threadPool[i]) != 0) {
			warningMessage(ERROR_FATAL, "Error occurred while trying to initialize worker thread");
		}

		j = 0;

		while(threadPool[i].threadReady != 0) {
			timerWait(&tmpSeconds, 0, THREAD_AGAIN);

			if(j == 10000 || j == 20000 || j == 30000 || j == 40000 || j == 50000) {
				warningMessage(ERROR_SLIGHT, "Waiting for worker threads to start taking too long, still waiting");
			}
			else if(j >= 60000) {
				warningMessage(ERROR_FATAL, "Waiting for threads to start taking too long");
			}

			j++;
		}
	}

	/*
	 *
	 * Create socket to listen.
	 *
	 */

	if((confPort = configFetch("listen_port", &i)) != NULL) {
		thisSocket = netCreateListenSocket(*confPort);
	}
	else {
		thisSocket = netCreateListenSocket(CONFIG_DEFAULT_PORT);
	}

	/*
	 *
	 * Create process id, shm segment, switch user and group id's.
	 *
	 */

	pidCreate();
	shmCreate(DAEMON_TELSKIND, THREAD_TELSKIND);

	if((thisUid = configFetch("user_id", &i)) != NULL) {
		if(*thisUid != -1) {
			if(uidSwitch(*thisUid) != 0) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to change user id");
			}
		}
	}

	if((thisGid = configFetch("group_id", &i)) != NULL) {
		if(*thisGid != -1) {
			if(gidSwitch(*thisGid) != 0) {
				warningMessage(ERROR_SLIGHT, "Error occurred while trying to change group id");
			}
		}
	}

	/*
	 *
	 * Serve connected clients.
	 *
	 */

	startProcess(THREAD_TELSKIND);

	pMainMainInfo->allRunning++;
	pMainMainInfo->rushThreadCounter = 0;

	while(pMainMainInfo->theEnd == 0) {
		thatSocket = netWaitConnection(thisSocket, pMainThreadInfo);

		if(pMainMainInfo->theEnd != 0) {
			break;
		}
mainLoop:
		for(i = 0; i < THREAD_TELSKIND; i++) {
			if(threadPool[i].threadReady == 0) {
				threadPool[i].threadReady++;
				threadPool[i].threadSocket = thatSocket;

				shmUpdate(i, DAEMON_TELSKIND);

				if(threadWake(&threadPool[i]) != 0) {
					netCloseSocket(threadPool[i].threadSocket);

					threadPool[i].threadReady = 0;
					threadPool[i].threadSocket = 0;

					warningMessage(ERROR_SLIGHT, "Error occurred while trying to start worker thread");
				}

				pMainMainInfo->rushThreadCounter = 0;

				break;
			}
		}

		if(i == THREAD_TELSKIND) {
			if(pMainMainInfo->rushThreadCounter > 1000) {
				pMainMainInfo->rushThreadCounter = 0;

				warningMessage(ERROR_SLIGHT, "No free worker thread available, dropping agent");

				netCloseSocket(thatSocket);
			}
			else {
				pMainMainInfo->rushThreadCounter++;

				if(pMainMainInfo->rushThreadCounter < 2) {
					warningMessage(ERROR_SLIGHT, "No free worker thread available, it may be necessary to enlarge the thread pool");
				}

				timerWait(&tmpSeconds, 0, THREAD_AGAIN);

				goto mainLoop;
			}
		}
	}

	/*
	 *
	 * Free allocated resources and terminate program.
	 *
	 */

	netCloseSocket(thisSocket);

	pMainMainInfo->threadEnd++;

	if(timerInit(TIMER_RESOLUTION_THREADSTOP, 0, timerStopThreads) == 0) {
		pMainMainInfo->timerThreadAccess = 1;

		for(i = 0; i < THREAD_TELSKIND; i++) {
			threadWake(&threadPool[i]);
		}

		pMainMainInfo->timerThreadAccess = 0;
	}
	else {
		for(i = 0; i < THREAD_TELSKIND; i++) {
			threadKill(&threadPool[i]);
		}
	}

	timesProcess(pMainThreadInfo);

	pidRemove();
	shmRemove(DAEMON_TELSKIND);

	free(threadPool);

	exitProcess(0);
	exit(0);
}