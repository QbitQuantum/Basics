void Master::start()
{
	//init script
	Config *pConfig = Config::getInstance();
	if(!pConfig->sScriptFile.empty()){
		pScript = new Script();
		if(!pScript->load(pConfig->sScriptFile)){
			printf("init script failed\n");
			return ;
		}
	}
	
	//session initialize
	Session::init();
	
	//create share memory
	if(!createGlobals()){
		return ;
	}
		
	//create server
	pServer = new Server(NULL);
	if(pServer->createTcpServer(pConfig->nPort) != 0){
		printf("create tcp server failed, port=%d, errno=%d, errstr=%s\n", 
			pConfig->nPort, errno, strerror(errno));
		return ;
	}
	
	//create worker
	pWorkers = (Worker**)zmalloc(pConfig->nWorkers * sizeof(Worker*));
	bUseAcceptMutex = pConfig->nWorkers > 1;
	for(int i = 0; i < pConfig->nWorkers; ++i){
		pWorkers[i] = new Worker(this, i);
		pWorkers[i]->start();
	}
	
	//set title
	char title[256];
	snprintf(title, 256, "fooking gateway master, %s", pConfig->sFile.c_str());
	utils::setProcTitle(title);
		
	//init signal
	setupSignal();
	
	//started log
	LOG_INFO("server started, listenfd=%d, port=%d", pServer->getSocket().getFd(), pConfig->nPort);

	//wait worker exit
	bRunning = true;
	while(bRunning)
	{
		int ret = 0;
		int pid = ::wait(&ret);
		if(pid <= 0){
			continue;
		}
		
		int found = -1;
		for(int i = 0; i < pConfig->nWorkers; ++i){
			Worker *pWorker = pWorkers[i];
			if(pWorker->getPid() == pid){
				found = pWorker->id();
				delete pWorker;
				break;
			}
		}
		
		if(found == -1){
			LOG_ERR("worker exited, not found workerid");
		}else{
			LOG_INFO("worker exited, id=%d, pid=%d", found, pid);
			atomic_fetch_sub(&pGlobals->clients, pGlobals->workerClients[found]);
			pGlobals->workerClients[found] = 0;
			
			//free lock
			if(bUseAcceptMutex){
				UnLockAcceptMutex(&pGlobals->lock, pid);
			}
			
			//restart
			pWorkers[found] = new Worker(this, found);
			pWorkers[found]->start();
		}
	}
}