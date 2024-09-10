CMyAsyncHttp::CMyAsyncHttp()
{
	m_TaskThread	=NULL;
	m_ThreadPool	=NULL;
	m_TimeOut		=MAX_WAIT_TIME;
	m_TaskArg.iAcceptType	=&m_AcceptType;
	m_TaskArg.iCharset		=&m_Charset;
	m_TaskArg.iEncode		=&m_Encode;
	m_TaskArg.iHttpHeader	=&m_HttpHeader;
	m_TaskArg.iHttpState	=&m_HttpState;
	m_TaskArg.iPassword		=&m_Password;
	m_TaskArg.iUserName		=&m_UserName;
	m_TaskArg.iRefer		=&m_Refer;
	m_TaskArg.iPath			=&m_Path;
	m_TaskArg.iUrl			=&m_Url;
	m_TaskArg.iVerb			=&m_Verb;

	m_TaskArg.iTaskRunTarget1	=&m_TaskThread;
	m_TaskArg.iTaskRunTarget2	=&m_ThreadPool;
	m_TaskArg.iConnect		=&m_Connect;
	m_TaskArg.iExtraData	=&m_ExtraData;
	m_TaskArg.iFinishNotify	=&m_FinishNotify;
	m_TaskArg.iHttp			=&m_Http;
	m_TaskArg.iIOStream		=&m_Data;
	m_TaskArg.iNotifyEvent	=&m_Notify;
	m_TaskArg.iSession		=&m_Session;
	m_TaskArg.iStatusCode	=&m_StatusCode;
	m_TaskArg.iStreamLen	=&m_DataLen;
	m_TaskArg.iTerminateEvent	=&m_TerminateEvent;
	m_TaskArg.iTaskList[0]	=&m_ORequestTask;
	m_TaskArg.iTaskList[1]	=&m_SRequestTask;
	m_TaskArg.iTaskList[2]	=&m_ReadResponseTask;
	
	m_TaskArg.iTimeOut		=&m_TimeOut;

	m_TaskArg.iAssignTaskThread	=&m_AssignTaskThread;  
	m_TaskArg.iAsyncResult	=0;

	m_TerminateEvent	=CreateEvent(false,false,NULL);
	m_Notify			=CreateEvent(false,false,NULL);
	m_FinishNotify		=CreateEvent(false,false,NULL);

	m_AssignTaskThread	=false;
	if(m_Mutex)
		m_Mutex				=CreateMutex(false,NULL);

	m_HttpState	=HTTP_FINISH;
	m_Session=::InternetOpen("Async_Http",PRE_CONFIG_INTERNET_ACCESS,
		NULL,INTERNET_INVALID_PORT_NUMBER,INTERNET_FLAG_ASYNC);
#ifdef _DEBUG
	if(!m_Session)
		LOG(TAG,"Open Internet failed!");
#endif
//	CSetCallBackThread callbackThread;
//	callbackThread.Start((void*)m_Session);
//	WaitForSingleObject(callbackThread.GetThreadHandle(),-1);
	if(INTERNET_INVALID_STATUS_CALLBACK==
		InternetSetStatusCallback(m_Session,(INTERNET_STATUS_CALLBACK)Callback))
//	if(INTERNET_INVALID_STATUS_CALLBACK==(INTERNET_STATUS_CALLBACK)callbackThread.GetRunValue())
	{
#ifdef _DEBUG
		LOG(TAG,"InternetSetStatusCallback failed");
#endif
	}
}