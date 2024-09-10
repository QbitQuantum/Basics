long ConfigCollectorTask(CmdMethodIndex MethodChoice, char *MachUser, char *MachPwd, char * InstallPath)
{
	USES_CONVERSION;

	CComPtr<ITaskScheduler> Sched;

	HRESULT hr;
	hr = Sched.CoCreateInstance(CLSID_CTaskScheduler);
	if (FAILED(hr)) {
		SchedError = 8;
		return hr;
	}

	//hr = Sched->SetTargetComputer(RemoteName);
	//if (FAILED(hr)) 
	//	return hr;

	hr = Sched->Delete(CONFIG_TASK_NAME);
	hr = Sched->Delete(CONFIG_CHECK_TASK_NAME);

	if (MethodChoice == MethodDisable)
		return ERROR_SUCCESS;

	/////////////////////////////////////////////////////////
	//
	// If we got this far, we have stuff to configure
	//
	/////////////////////////////////////////////////////////

	CComPtr<ITask> InstallTask;
	hr = Sched->NewWorkItem(CONFIG_TASK_NAME, CLSID_CTask, IID_ITask, (IUnknown **) &InstallTask);
	if (FAILED(hr)) {
		SchedError = 9;
		return hr;
	}

	//hr = InstallTask->SetAccountInformation(L"Administrator",L"admin4u");
	//if (FAILED(hr))
	//	return hr;

	WCHAR CollectorPath[2* MAX_PATH + 1];
	swprintf (CollectorPath, L"%s\\%s", A2W(InstallPath), TASK_EXEC);
	
	hr = InstallTask->SetApplicationName(CollectorPath);
	if (FAILED(hr)) {
		SchedError = 10;
		return hr;
	}

	WCHAR WMachUser[256];
	WCHAR WMachPwd[256];

	wcscpy(WMachUser, A2W(MachUser));
	wcscpy(WMachPwd, A2W(MachPwd));

	hr = InstallTask->SetAccountInformation(WMachUser, WMachPwd);

	hr = InstallTask->SetMaxRunTime(MAX_RUN_TIME_MS);
	if (FAILED(hr)) {
		SchedError = 11;
		return hr;
	}


#ifdef DEBUG
	hr = InstallTask->SetFlags(0);
#else
	hr = InstallTask->SetFlags(TASK_FLAG_HIDDEN);
#endif
	if (FAILED(hr)) {
		SchedError = 12;
		return hr;
	}

	CComPtr<ITaskTrigger> InstallTrigger;

	WORD InstTriggerNum;

	hr = InstallTask->CreateTrigger(&InstTriggerNum, & InstallTrigger);
	if (FAILED(hr)) {
		SchedError = 13;
		return hr;
	}

	TASK_TRIGGER InstallTriggerData;

	ZeroMemory(&InstallTriggerData, sizeof(TASK_TRIGGER));

	SYSTEMTIME CurrTime;
	GetLocalTime(&CurrTime);

	if (CurrTime.wDay > 28)
		CurrTime.wDay = 28;

	InstallTriggerData.wBeginDay = CurrTime.wDay;
	InstallTriggerData.wBeginMonth = CurrTime.wMonth;
	InstallTriggerData.wBeginYear = CurrTime.wYear;
	InstallTriggerData.wStartHour = CurrTime.wHour ; // make sure it does not run immediately
	InstallTriggerData.wStartMinute = CurrTime.wMinute;
	InstallTriggerData.cbTriggerSize = sizeof (TASK_TRIGGER);

	switch (MethodChoice) {
	
	case MethodStartup:
		InstallTriggerData.TriggerType = TASK_EVENT_TRIGGER_AT_SYSTEMSTART;
		break;

	case MethodDay:
		InstallTriggerData.TriggerType = TASK_TIME_TRIGGER_DAILY;
		InstallTriggerData.Type.Daily.DaysInterval = 1;
		break;

	case MethodWeek:
		InstallTriggerData.TriggerType = TASK_TIME_TRIGGER_WEEKLY;
		InstallTriggerData.Type.Weekly.WeeksInterval  = 1;
		InstallTriggerData.Type.Weekly.rgfDaysOfTheWeek = (1 << CurrTime.wDayOfWeek);
		break;

	case MethodMonth:
		InstallTriggerData.TriggerType = TASK_TIME_TRIGGER_MONTHLYDATE;
		InstallTriggerData.Type.MonthlyDate.rgfDays = (1 << CurrTime.wDay);
		InstallTriggerData.Type.MonthlyDate.rgfMonths = SCHED_ALL_MONTHS;
		break;

	default:
		return ERROR_GEN_FAILURE;
	}

	hr = InstallTrigger->SetTrigger(& InstallTriggerData);
	if (FAILED(hr)) {
		SchedError = 14;
		return hr;
	}

	// Persist!
	CComQIPtr<IPersistFile> TaskPersist = InstallTask;
	if (TaskPersist == NULL)
		return E_FAIL;
	
	hr = TaskPersist->Save(NULL, TRUE);
	if (FAILED(hr)) {
		SchedError = 15;
		return hr;	
	}

	//////////////////////////////////////////////////////
	//
	// Now Config the Checker Task if needed
	//
	//////////////////////////////////////////////////////

	if (MethodChoice == MethodStartup) // don't need to check if startup is applied.
		return ERROR_SUCCESS;

	CComPtr<ITask> CheckTask;
	hr = Sched->NewWorkItem(CONFIG_CHECK_TASK_NAME, CLSID_CTask, IID_ITask, (IUnknown **) &CheckTask);
	if (FAILED(hr)) {
		SchedError = 109;
		return hr;
	}

	//hr = CheckTask->SetAccountInformation(L"Administrator",L"admin4u");
	//if (FAILED(hr))
	//	return hr;
	
	hr = CheckTask->SetApplicationName(CollectorPath);
	if (FAILED(hr)) {
		SchedError = 110;
		return hr;
	}

	// The /C is to check on startup for excess time passed.
	hr = CheckTask->SetParameters(L"/C");
	if (FAILED(hr)) {
		SchedError = 116;
		return hr;
	}


	hr = CheckTask->SetAccountInformation(WMachUser, WMachPwd);

	hr = CheckTask->SetMaxRunTime(MAX_RUN_TIME_MS);
	if (FAILED(hr)) {
		SchedError = 111;
		return hr;
	}

#ifdef DEBUG
	hr = CheckTask->SetFlags(0);
#else
	hr = CheckTask->SetFlags(TASK_FLAG_HIDDEN);
#endif

	if (FAILED(hr)) {
		SchedError = 112;
		return hr;
	}

	CComPtr<ITaskTrigger> CheckTrigger;

	hr = CheckTask->CreateTrigger(&InstTriggerNum, & CheckTrigger);
	if (FAILED(hr)) {
		SchedError = 113;
		return hr;
	}

	TASK_TRIGGER CheckTriggerData;

	ZeroMemory(&CheckTriggerData, sizeof(TASK_TRIGGER));

	CheckTriggerData.wBeginDay = CurrTime.wDay;
	CheckTriggerData.wBeginMonth = CurrTime.wMonth;
	CheckTriggerData.wBeginYear = CurrTime.wYear;
	CheckTriggerData.wStartHour = CurrTime.wHour ; // make sure it does not run immediately
	
	CheckTriggerData.cbTriggerSize = sizeof (TASK_TRIGGER);

	CheckTriggerData.TriggerType = TASK_EVENT_TRIGGER_AT_SYSTEMSTART;

	hr = CheckTrigger->SetTrigger(& CheckTriggerData);
	if (FAILED(hr)) {
		SchedError = 114;
		return hr;
	}

	// Persist!
	CComQIPtr<IPersistFile> CheckTaskPersist = CheckTask;
	if (CheckTaskPersist == NULL)
		return E_FAIL;
	
	hr = CheckTaskPersist->Save(NULL, TRUE);
	if (FAILED(hr)) {
		SchedError = 115;
		return hr;	
	}

	return ERROR_SUCCESS;
}