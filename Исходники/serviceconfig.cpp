/******************************************************************
 CaExecServiceConfig - entry point for ServiceConfig Custom Action
				   called as Type 1025 CustomAction (deferred binary DLL)

 NOTE: deferred CustomAction since it modifies the machine
 NOTE: CustomActionData == wzServiceName\twzFirstFailureActionType\twzSecondFailureActionType\twzThirdFailureActionType\tdwResetPeriodInDays\tdwRestartServiceDelayInSeconds\twzProgramCommandLine\twzRebootMessage\twzServiceName\t...
*******************************************************************/
extern "C" UINT __stdcall ExecServiceConfig(
	__in MSIHANDLE hInstall
	)
{
//	AssertSz(FALSE, "debug ExecServiceConfig");
	HRESULT hr = S_OK;
	UINT uiResult = ERROR_SUCCESS;
	DWORD dwError = 0;
	LPVOID lpMsgBuf = NULL;

	LPWSTR pwzData = NULL;
	LPWSTR pwz = NULL;

	LPWSTR pwzServiceName = NULL;
	LPWSTR pwzFirstFailureActionType = NULL;
	LPWSTR pwzSecondFailureActionType = NULL;
	LPWSTR pwzThirdFailureActionType = NULL;
	LPWSTR pwzProgramCommandLine = NULL;
	LPWSTR pwzRebootMessage = NULL;
	DWORD dwResetPeriodInDays = 0;
	DWORD dwRestartServiceDelayInSeconds = 0;

	SC_HANDLE hSCM = NULL;
	SC_HANDLE hService = NULL;
	DWORD dwOpenServiceAccess = SERVICE_CHANGE_CONFIG; // SERVICE_CHANGE_CONFIG is needed for ChangeServiceConfig2()

	SERVICE_FAILURE_ACTIONSW sfa;
	SC_ACTION actions[3];
	BOOL fResult = FALSE;

	// initialize
	hr = WcaInitialize(hInstall, "ExecServiceConfig");
	ExitOnFailure(hr, "failed to initialize");

	hr = WcaGetProperty( L"CustomActionData", &pwzData);
	ExitOnFailure(hr, "failed to get CustomActionData");

	WcaLog(LOGMSG_TRACEONLY, "CustomActionData: %S", pwzData);

	pwz = pwzData;

	// loop through all the passed in data
	while (pwz && *pwz)
	{
		hr = WcaReadStringFromCaData(&pwz, &pwzServiceName);
		ExitOnFailure(hr, "failed to process CustomActionData");
		hr = WcaReadStringFromCaData(&pwz, &pwzFirstFailureActionType);
		ExitOnFailure(hr, "failed to process CustomActionData");
		hr = WcaReadStringFromCaData(&pwz, &pwzSecondFailureActionType);
		ExitOnFailure(hr, "failed to process CustomActionData");
		hr = WcaReadStringFromCaData(&pwz, &pwzThirdFailureActionType);
		ExitOnFailure(hr, "failed to process CustomActionData");
		hr = WcaReadIntegerFromCaData(&pwz, reinterpret_cast<int*>(&dwResetPeriodInDays));
		ExitOnFailure(hr, "failed to process CustomActionData");
		hr = WcaReadIntegerFromCaData(&pwz, reinterpret_cast<int*>(&dwRestartServiceDelayInSeconds));
		ExitOnFailure(hr, "failed to process CustomActionData");
		hr = WcaReadStringFromCaData(&pwz, &pwzProgramCommandLine);
		ExitOnFailure(hr, "failed to process CustomActionData");
		hr = WcaReadStringFromCaData(&pwz, &pwzRebootMessage);
		ExitOnFailure(hr, "failed to process CustomActionData");

		WcaLog(LOGMSG_VERBOSE, "Configuring Service: %S", pwzServiceName);

		// build up SC_ACTION array
		// TODO: why is delay only respected when SC_ACTION_RESTART is requested?
		actions[0].Type = GetSCActionType(pwzFirstFailureActionType);
		actions[0].Delay = 0;
		if (SC_ACTION_RESTART == actions[0].Type)
		{
			actions[0].Delay = dwRestartServiceDelayInSeconds * 1000; // seconds to milliseconds
			dwOpenServiceAccess |= SERVICE_START; // must have SERVICE_START access in order to handle SC_ACTION_RESTART action;
		}

		actions[1].Type = GetSCActionType(pwzSecondFailureActionType);
		actions[1].Delay = 0;
		if (SC_ACTION_RESTART == actions[1].Type)
		{
			actions[1].Delay = dwRestartServiceDelayInSeconds * 1000; // seconds to milliseconds
			dwOpenServiceAccess |= SERVICE_START; // must have SERVICE_START access in order to handle SC_ACTION_RESTART action;
		}

		actions[2].Type = GetSCActionType(pwzThirdFailureActionType);
		actions[2].Delay = 0;
		if (SC_ACTION_RESTART == actions[2].Type)
		{
			actions[2].Delay = dwRestartServiceDelayInSeconds * 1000; // seconds to milliseconds
			dwOpenServiceAccess |= SERVICE_START; // must have SERVICE_START access in order to handle SC_ACTION_RESTART action;
		}

		// build up the SERVICE_FAILURE_ACTIONSW struct
		sfa.dwResetPeriod = dwResetPeriodInDays * 24 * 60 * 60; // days to seconds
		sfa.lpRebootMsg = pwzRebootMessage;
		sfa.lpCommand = pwzProgramCommandLine;
		sfa.cActions = 3;  // the UI always shows 3 actions, so we'll always do 3
		sfa.lpsaActions = actions;

		// Get a handle to the service control manager (if we don't already have)
		if (NULL == hSCM)
		{
			hSCM = ::OpenSCManagerW(NULL, NULL, SC_MANAGER_CONNECT);
			if (hSCM == NULL)
			{
				dwError = ::GetLastError();
				::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lpMsgBuf, 0, NULL);

				ExitOnFailure1(hr = HRESULT_FROM_WIN32(dwError), "failed to get handle to SCM. Error: %S", (LPWSTR)lpMsgBuf);
			}
		}

		hService = ::OpenServiceW(hSCM, pwzServiceName, dwOpenServiceAccess);
		if (hService == NULL)
		{
			dwError = ::GetLastError();
			hr = HRESULT_FROM_WIN32(dwError);
			if (dwError == ERROR_SERVICE_DOES_NOT_EXIST)
			{
				ExitOnFailure1(hr, "Service \"%S\" does not exist on this system.", pwzServiceName);
			}
			else
			{
				::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lpMsgBuf, 0, NULL);
				ExitOnFailure2(hr, "Failed to get handle to the service \"%S\". Error: %S", pwzServiceName, (LPWSTR)lpMsgBuf);
			}
		}

		// Call ChangeServiceConfig2 to actually set up the failure actions
		fResult = ChangeServiceConfig2W(hService, SERVICE_CONFIG_FAILURE_ACTIONS, (LPVOID)&sfa);
		if (fResult == FALSE)
		{
			dwError = ::GetLastError();
			hr = HRESULT_FROM_WIN32(dwError);
			::FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&lpMsgBuf, 0, NULL);

			// check if this is a service that can't be modified
			if(dwError == ERROR_CANNOT_DETECT_PROCESS_ABORT)
			{
				WcaLog(LOGMSG_STANDARD, "WARNING: Service \"%S\" is not configurable on this server and will not be set.", pwzServiceName);
			}
			ExitOnFailure1(hr, "Cannot change service configuration. Error: %S", (LPWSTR)lpMsgBuf);
		}

		// Per-service cleanup
		dwResetPeriodInDays = 0;
		dwRestartServiceDelayInSeconds = 0;

		hr = WcaProgressMessage(COST_SERVICECONFIG, FALSE);
		ExitOnFailure(hr, "failed to send progress message");
	}

LExit:
	// Clean up handles
	ReleaseStr(pwzServiceName);
	ReleaseStr(pwzFirstFailureActionType);
	ReleaseStr(pwzSecondFailureActionType);
	ReleaseStr(pwzThirdFailureActionType);
	ReleaseStr(pwzProgramCommandLine);
	ReleaseStr(pwzRebootMessage);
	ReleaseStr(pwzData);

	if (lpMsgBuf) // Allocated with FormatString
		::LocalFree(lpMsgBuf);

	if (hService)
		::CloseServiceHandle(hService);
	if (hSCM)
		::CloseServiceHandle(hSCM);

	if (FAILED(hr))
		uiResult = ERROR_INSTALL_FAILURE;
	return WcaFinalize(uiResult);
}