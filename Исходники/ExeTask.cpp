ExeTask::ExeTask(RemoteCLI* svr, ExeTaskTreeNode* parent, std::string workName, int nameLine, std::string bhvname, RFSMtask* task, ModelBinder* tmPlugin, int exeType, int callstmtLine, unsigned int tp)
:ExeTaskTreeNode(parent, svr, workName, nameLine, task->getBlockID(), task->getFileName(), callstmtLine, tp)
{
	m_tmPlugin = tmPlugin;

	m_task				= task;
	m_startBehavior		= bhvname;
	m_behaviorTAB		= NULL;
	m_connTAB			= NULL;
//	m_outModelTAB		= new ValueMap();
	m_wVarTAB			= new ValueMap();
	m_monitorOff		= true;
	m_monCount			= 0;

	std::string logName("ExeTask-");
	logName.append(workName);

	if(TaskConfig::getIsTaskLog()){
		m_logFile = new LogFile((char*)(logName.c_str()), TaskConfig::getLogSize());
		m_logFile->setLevel( Log::LOG_LEVEL_DEBUG, true);
		m_logFile->setLevel( Log::LOG_LEVEL_TRACE, true);
		m_logFile->setLevel( Log::LOG_LEVEL_ERROR, true);
	}
	else{
		m_logFile = NULL;
	}

	pthread_cond_init(&m_SLEEPstmt_wakeup_cond, NULL);
	pthread_mutex_init(&m_SLEEPstmt_wakeup_mu, NULL);


	m_runner = new TaskRunner(this, tmPlugin, m_logFile);
	if(exeType == DEBUG){
		m_runner->setAsDebugMode();
	}
	else if(exeType == MONITOR){
		m_runner->setAsMonitorMode();
	}

	//이걸 여기서 초기화 하는 것은 LogFile  매개변수 전달 때문이다.
	//if(m_tmPlugin->isSimul()) m_tmPlugin->initSimul(m_logFile);
	
	m_running = false;

#ifdef _WIN32
	m_TimerQueue = CreateTimerQueue();
#endif
}