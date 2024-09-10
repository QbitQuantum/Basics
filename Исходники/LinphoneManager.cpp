LinphoneManager::LinphoneManager()
{
	m_linphoneStatus = LINPHONE_STATUS_NOT_INIT;
	pthread_mutex_init(&m_linphoneStatusMutex,NULL);
	SECURITY_ATTRIBUTES rPipeSa;
	SECURITY_ATTRIBUTES wPipeSa;
	rPipeSa.nLength = sizeof(SECURITY_ATTRIBUTES);
	rPipeSa.lpSecurityDescriptor = NULL;
	rPipeSa.bInheritHandle = TRUE;
	wPipeSa.nLength = sizeof(SECURITY_ATTRIBUTES);
	wPipeSa.lpSecurityDescriptor = NULL;
	wPipeSa.bInheritHandle = TRUE;
	if(!CreatePipe(&m_pipeRead[0],&m_pipeWrite[0],&rPipeSa,0))
	{
		log_printf(LOG_ALL_OUT,LOG_LEVEL_ERROR,"error at create pipe\n");
	}
	if(!CreatePipe(&m_pipeRead[1],&m_pipeWrite[1],&wPipeSa,0))
	{
		log_printf(LOG_ALL_OUT,LOG_LEVEL_ERROR,"error at create pipe\n");
	}
	STARTUPINFOA si;
	si.cb = sizeof(STARTUPINFOA);
	GetStartupInfoA(&si);
	si.hStdError = m_pipeWrite[0];
	si.hStdOutput = m_pipeWrite[0];
	si.hStdInput = m_pipeRead[1];
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
	log_printf(LOG_ALL_OUT,LOG_LEVEL_INFO,"start to create linphone process.\n");
	if (!CreateProcessA(NULL,LINPHONEC_LOCATION,NULL,NULL,TRUE,NULL,NULL,NULL,&si,&m_linphoneProcess)) 
	{
		log_printf(LOG_ALL_OUT,LOG_LEVEL_ERROR,"error at create process\n");
	}
	CloseHandle(m_pipeWrite[0]);
	CloseHandle(m_pipeRead[1]);
	SetLinphoneStatus(LINPHONE_STATUS_ON_IDLE);
	int ret = pthread_create(&m_readLinphoneOutput,NULL,ReadLinphoneOutputProc,this);
	if(0 != ret)
	{
		log_printf(LOG_ALL_OUT,LOG_LEVEL_ERROR,"Create read linphone output thread failed,%d\n",ret);
	}
}