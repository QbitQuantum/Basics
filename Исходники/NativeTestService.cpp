//
// Purpose: 
//   The service code
//
// Parameters:
//   dwArgc - Number of arguments in the lpszArgv array
//   lpszArgv - Array of strings. The first string is the name of
//     the service and subsequent strings are passed by the process
//     that called the StartService function to start the service.
// 
// Return value:
//   None
//
VOID ServiceInit(DWORD dwArgc, LPTSTR* lpszArgv)
{
	// Create an event. The control handler function, ServiceCtrlHandler,
	// signals this event when it receives the stop control code.

	ghServiceStopEvent = CreateEvent(
		NULL,    // default security attributes
		TRUE,    // manual reset event
		FALSE,   // not signaled
		NULL);   // no name

	if (ghServiceStopEvent == NULL)
	{
		ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
		return;
	}

	InitModulePath();
	CreateLogFile();

	// Write the service arguments to the registry key:
	// HKEY_USERS\.DEFAULT\dotnetTests\ServiceController\<ServiceName>\ServiceArguments
	// to verify that they were correctly passed through.

	std::wstring keyPath = L".DEFAULT\\dotnetTests\\ServiceController\\";
	keyPath += gServiceName;

	HKEY hKey;
	LONG result = RegCreateKeyEx(
		HKEY_USERS,
		keyPath.c_str(),
		0,
		NULL,
		REG_OPTION_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		NULL);

	if (result != ERROR_SUCCESS)
	{
		LogMessage(L"warning: failed to open or create registry key 'HKEY_USERS\\%s' (%d)\n", keyPath.c_str(), result);
	}
	else
	{
		// Join the arguments array, separating each argument with a comma

		std::wstring argsString;
		DWORD i = 1;

		for (; i < dwArgc - 1; i++)
		{
			argsString += lpszArgv[i];
			argsString += L',';
		}

		if (i < dwArgc)
		{
			argsString += lpszArgv[i];
		}

		// Write the result to the value "ServiceArguments"

		LPCTSTR valueName = L"ServiceArguments";
		result = RegSetValueEx(
			hKey,
			valueName,
			0,
			REG_SZ,
			(const BYTE*) argsString.c_str(),
			(DWORD) ((argsString.length() + 1) * sizeof(wchar_t)));

		if (result != ERROR_SUCCESS)
		{
			LogMessage(L"warning: failed to set value '%s' = '%s' in registry key 'HKEY_USERS\\%s' (%d)\n", valueName, argsString.c_str(), keyPath.c_str(), result);
		}

		RegCloseKey(hKey);
	}

	// Report running status when initialization is complete.

	ServiceReportStatus(SERVICE_RUNNING, NO_ERROR, 0);

	while (1)
	{
		// Check whether to stop the service.

        // If the tests haven't finished within 90 seconds, just end the program anyways.
		DWORD error = WaitForSingleObject(ghServiceStopEvent, 90000);

		// We're stopping, delete the log file
		DWORD logError = DeleteLogFile();

        // If WaitForSingleObject fails, use that code.
        // Otherwise use the result of DeleteLogFile.
        if (error == ERROR_SUCCESS)
        {
            error = logError;
        }

		ServiceReportStatus(SERVICE_STOPPED, error, 0);
		return;
	}
}