HRESULT CNodeApplicationManager::Initialize(IHttpContext* context)
{
	HRESULT hr;
	BOOL isInJob, createJob;
	JOBOBJECT_EXTENDED_LIMIT_INFORMATION jobInfo;

	if (this->initialized)
	{
		return S_OK;
	}

	ErrorIf(NULL == (this->eventProvider = new CNodeEventProvider()), ERROR_NOT_ENOUGH_MEMORY);
	CheckError(this->eventProvider->Initialize());
	ErrorIf(NULL != this->asyncManager, ERROR_INVALID_OPERATION);
	ErrorIf(NULL == (this->asyncManager = new CAsyncManager()), ERROR_NOT_ENOUGH_MEMORY);
	CheckError(this->asyncManager->Initialize(context));
	ErrorIf(NULL == (this->fileWatcher = new CFileWatcher()), ERROR_NOT_ENOUGH_MEMORY);
	CheckError(this->fileWatcher->Initialize(context));

	// determine whether node processes should be created in a new job object
	// or whether current job object is adequate; the goal is to kill node processes when
	// the IIS worker process is killed while preserving current job limits, if any
	
	ErrorIf(!IsProcessInJob(GetCurrentProcess(), NULL, &isInJob), HRESULT_FROM_WIN32(GetLastError()));
	if (!isInJob)
	{
		createJob = TRUE;
	}
	else
	{
		ErrorIf(!QueryInformationJobObject(NULL, JobObjectExtendedLimitInformation, &jobInfo, sizeof jobInfo, NULL), 
			HRESULT_FROM_WIN32(GetLastError()));

        if (jobInfo.BasicLimitInformation.LimitFlags & JOB_OBJECT_LIMIT_SILENT_BREAKAWAY_OK )
        {
            createJob = TRUE;
        }
        else if(jobInfo.BasicLimitInformation.LimitFlags & JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE )
        {
            createJob = FALSE;
        }
        else if(jobInfo.BasicLimitInformation.LimitFlags & JOB_OBJECT_LIMIT_BREAKAWAY_OK )
        {
            createJob = TRUE;
			this->breakAwayFromJobObject = TRUE;
        }
        else
        {
            createJob = TRUE;
        }
	}

	if (createJob)
	{
		ErrorIf(NULL == (this->jobObject = CreateJobObject(NULL, NULL)), HRESULT_FROM_WIN32(GetLastError()));
		RtlZeroMemory(&jobInfo, sizeof jobInfo);
		jobInfo.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
		ErrorIf(!SetInformationJobObject(this->jobObject, JobObjectExtendedLimitInformation, &jobInfo, sizeof jobInfo), 
			HRESULT_FROM_WIN32(GetLastError()));
	}

	this->initialized = TRUE;

	this->GetEventProvider()->Log(L"iisnode initialized the application manager", WINEVENT_LEVEL_INFO);

	return S_OK;
Error:

	this->GetEventProvider()->Log(L"iisnode failed to initialize the application manager", WINEVENT_LEVEL_ERROR);

	if (NULL != this->asyncManager)
	{
		delete this->asyncManager;
		this->asyncManager = NULL;
	}

	if (NULL != this->jobObject)
	{
		CloseHandle(this->jobObject);
		this->jobObject = NULL;
	}

	if (NULL != this->fileWatcher)
	{
		delete this->fileWatcher;
		this->fileWatcher = NULL;
	}

	return hr;
}