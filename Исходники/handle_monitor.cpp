int wmain(int argc, WCHAR *argv[])
{

	/* Display welcome message */
	printf("handle_monitor %s - Adam Kramer\n", VERSION_NUMBER);

	/* These variables hold configuration options, which can be altered by arguments passed */
	BOOL bIncludeSigned = FALSE;
	BOOL bSuspendProcess = FALSE;
	BOOL bVerbose = FALSE;
	DWORD dNumberCycles = 10;
	DWORD dHandleChangeThreshold = 10;
	DWORD dIterationPause = 1000;

	/* Process arguments */
	if (argc > 1)
	{
		for (int iNumberArgs = 1; iNumberArgs < argc; iNumberArgs++)
		{
			/* /signed - will include signed files in the alerts */
			if (!wcscmp(argv[iNumberArgs], L"/signed"))
			{
				bIncludeSigned = TRUE;
				printf("Info: Will show signed files as well as unsigned\n");
			}
			/* /suspect - will attempt to suspend suspicious processes */
			else if (!wcscmp(argv[iNumberArgs], L"/suspend"))
			{
				bSuspendProcess = TRUE;
				printf("Info: Will attempt to suspend suspicious processes\n");
			}
			/* /verbose - will display details of iterations and hidden results */
			else if (!wcscmp(argv[iNumberArgs], L"/verbose"))
			{
				bVerbose = TRUE;
				printf("Info: Will display verbose status messages\n");
			}
			/* /cycles - allows the user to set cycles completed before analysis */
			else if (WCHAR* wSetCycles = wcsstr(argv[iNumberArgs], L"/cycles="))
			{
				wSetCycles = wcschr(wSetCycles, '=');

				if (!(dNumberCycles = _wtol(++wSetCycles)))
				{
					printf("Error: Invalid /cycles parameter\n");
					return 1;
				}

				printf("Info: Setting number of cycles to %d\n", dNumberCycles);
			}
			/* /threshold - allows the user to set the threshold for minimum number of new handles which are suspicious */
			else if (WCHAR* wSetThreshold = wcsstr(argv[iNumberArgs], L"/threshold="))
			{
				wSetThreshold = wcschr(wSetThreshold, '=');

				if (!(dHandleChangeThreshold = _wtol(++wSetThreshold)))
				{
					printf("Error: Invalid /threshold parameter\n");
					return 1;
				}

				printf("Info: Setting handle threshold to %d\n", dHandleChangeThreshold);
			}
			/* /pause - allows the user to set a pause between cycles (reduce system load, increase window for finding something) */
			else if (WCHAR* wSetPause = wcsstr(argv[iNumberArgs], L"/pause="))
			{
				wSetPause = wcschr(wSetPause, '=');

				dIterationPause = _wtol(++wSetPause);
				printf("Info: Setting pause between cycles to %dms\n", dIterationPause);
			}
		}
		/* End of argument processing */
	}
	else
	{
		/* No argument passed, accordingly display the usage instructions */
		printf("Usage: handle_monitor.exe <optional parameters>\n\n");
		printf("Optional parameters:\n");
		printf("/cycles=X - Set number of cycles before a review [Default: 10]\n");
		printf("/threshold=X - Set suspicion threshold for number of new handles [Default: 10]\n");
		printf("/pause=X - Set pause in milliseconds between cycles [Default: 1000]\n");
		printf("/signed - Include signed executables in review process\n");
		printf("/suspend - Suspend processes identified as suspicious\n");
		printf("/verbose - Display verbose progress messages\n\n");
		printf("Info: No parameters specified, launching monitoring (Ctrl+C to stop)\n");
	}

	/* Import functions manually from NTDLL */
	_NtQuerySystemInformation NtQuerySystemInformation =
		(_NtQuerySystemInformation)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQuerySystemInformation");

	_NtDuplicateObject NtDuplicateObject =
		(_NtDuplicateObject)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtDuplicateObject");

	_NtQueryObject NtQueryObject =
		(_NtQueryObject)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryObject");

	/* Master loop! - This runs forever until a user presses Ctrl+C */
	for (;;)
	{
		/* Update user that process is starting (if /verbose mode activiated) */
		if (bVerbose)
			printf("Verbose Info: Starting sequence\n");

		/* Variables used for retrieving handles */
		NTSTATUS status;
		ULONG handleInfoSize = 0x10000;
		HANDLE processHandle;
		ULONG i;
		PSYSTEM_HANDLE_INFORMATION handleInfo;

		/* Used in each handle iteration to identify the index in iProcessArray of the specific process */
		int iCurrentProcess_ArrayIndex = -1;

		/* Handle array - PROCESS INDEX / HANDLE NUMBER / TEXT OF HANDLE
			This holds all handles which have been found per process */
		auto cHandleArray = new WCHAR[MAX_PROCESSES][MAX_FILE_HANDLES][MAX_PATH]();
		signed int iProcessArray[MAX_PROCESSES][3] = { 0 };

		/* Set process array to -1, which indicates nothing has been set */
		for (int j = 0; j < (MAX_PROCESSES - 1); j++)
			iProcessArray[j][0] = -1;

		/* Loop dNumberCycles [default: 10] times before analysing result */
		for (unsigned int iCycleCounter = 1; iCycleCounter <= dNumberCycles; iCycleCounter++)
		{
			handleInfoSize = 0x10000;
			handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(handleInfoSize);

			/* NtQuerySystemInformation won't give us the correct buffer size, so we guess by doubling the buffer size. */
			while ((status = NtQuerySystemInformation(SystemHandleInformation, handleInfo, handleInfoSize, NULL)) == STATUS_INFO_LENGTH_MISMATCH)
				handleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(handleInfo, handleInfoSize *= 2);

			/* NtQuerySystemInformation stopped giving us STATUS_INFO_LENGTH_MISMATCH. */
			if (!NT_SUCCESS(status))
			{
				printf("NtQuerySystemInformation failed!\n");
				return 1;
			}

			/* Loop for each handle on the system, processing it accordingly... */
			for (i = 0; i < handleInfo->HandleCount; i++)
			{
				SYSTEM_HANDLE handle = handleInfo->Handles[i];
				HANDLE dupHandle = NULL;
				POBJECT_TYPE_INFORMATION objectTypeInfo;

				/* Open a handle to the process associated with the handle */
				if (!(processHandle = OpenProcess(PROCESS_DUP_HANDLE, FALSE, handle.ProcessId)))
					continue;

				/* Duplicate the handle so we can query it. */
				if (!NT_SUCCESS(NtDuplicateObject(processHandle, (HANDLE)handle.Handle, GetCurrentProcess(), &dupHandle, GENERIC_READ, 0, 0)))
				{
					CloseHandle(processHandle);
					CloseHandle(dupHandle);
					continue;
				}

				/* Query the object type */
				objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(0x1000);
				if (!NT_SUCCESS(NtQueryObject(dupHandle, ObjectTypeInformation, objectTypeInfo, 0x1000, NULL)))
				{
					free(objectTypeInfo);
					CloseHandle(processHandle);
					CloseHandle(dupHandle);
					continue;
				}

				/* If it's not a file handle, go to next one (as we're only interested in file handles) */
				if (wcscmp(objectTypeInfo->Name.Buffer, L"File"))
				{
					free(objectTypeInfo);
					CloseHandle(processHandle);
					CloseHandle(dupHandle);
					continue;
				}

				/* Identify the filename from the handle we're looking at */
				WCHAR* wHandleFileName = new WCHAR[MAX_PATH]();

				if (!GetFileNameFromHandle(dupHandle, wHandleFileName))
				{
					free(objectTypeInfo);
					free(wHandleFileName);
					CloseHandle(processHandle);
					CloseHandle(dupHandle);
					continue;
				}

				/* This is where we add our findings to the database */
				iCurrentProcess_ArrayIndex = -1;

				/* Check whether we've already got an entry for the process we're looking at */
				for (int j = 0; j < (MAX_PROCESSES - 1); j++)
					if (iProcessArray[j][PROCESS_ARRAY_INDEX] == handle.ProcessId)
						iCurrentProcess_ArrayIndex = j;

				/* If not, create a new entry for the process associated with the current handle */
				if (iCurrentProcess_ArrayIndex == -1)
					for (int j = 0; j < (MAX_PROCESSES - 1); j++)
						if (iProcessArray[j][PROCESS_ARRAY_INDEX] == -1)
						{
							iProcessArray[j][PROCESS_ARRAY_INDEX] = handle.ProcessId;
							iCurrentProcess_ArrayIndex = j;
							break;
						}

				/* If there's more than MAX_PROCESSES, throw an error
					TODO: Tidy this up, identify number of running processes dynamically and set array size accordingly */
				if (iCurrentProcess_ArrayIndex == -1)
				{
					printf("Error: Too many processes running!\n");
					return 1;
				}

				/* Look through the handle array, to see whether the filename can be found */
				WCHAR cCurrentHandleText[MAX_PATH];
				for (int j = 0; j < (MAX_FILE_HANDLES - 1); j++)
				{
					/* If we hit NULL, there are no more to find, so add ours */
					swprintf_s(cCurrentHandleText, MAX_PATH, L"%ls", wHandleFileName);

					if (!wcscmp(cHandleArray[iCurrentProcess_ArrayIndex][j], L"")){
						wcscpy_s(cHandleArray[iCurrentProcess_ArrayIndex][j], cCurrentHandleText);
						break;
					}
					/* If we find ours, then stop searching */
					else if (!wcscmp(cHandleArray[iCurrentProcess_ArrayIndex][j], cCurrentHandleText))
						break;
				}

				/* If it's the first (or last) cycle, tally how many entries in the handle array for this
					particular process we have so far */

				if (iCycleCounter == 1)
					for (int j = 0; j < (MAX_FILE_HANDLES - 1); j++)
						if (!wcscmp(cHandleArray[iCurrentProcess_ArrayIndex][j], L"")){
							iProcessArray[iCurrentProcess_ArrayIndex][PROCESS_ARRAY_COUNT_START_CYCLE] = (j - 1);
							break;
						}

				if (iCycleCounter == dNumberCycles)
					for (int j = 0; j < (MAX_FILE_HANDLES - 1); j++)
						if (!wcscmp(cHandleArray[iCurrentProcess_ArrayIndex][j], L"")) {
							iProcessArray[iCurrentProcess_ArrayIndex][PROCESS_ARRAY_COUNT_END_CYCLE] = (j - 1);
							break;
						}

				free(objectTypeInfo);
				free(wHandleFileName);
				CloseHandle(dupHandle);
				CloseHandle(processHandle);
			}
			free(handleInfo);

			/* If the iteration pause is not 0, sleep for the requested time [Default: 1000ms] */
			if (dIterationPause)
				Sleep(dIterationPause);

			/* If /verbose active - inform user which cycle we are on */
			if (bVerbose)
				if (iCycleCounter == 1)
					printf("Verbose Info: Completed cycle %d", iCycleCounter);
				else if (iCycleCounter == dNumberCycles)
					printf(" %d\n", iCycleCounter);
				else
					printf(" %d", iCycleCounter);
		}

		/* If /verbose active - inform user we are now starting a review */
		if (bVerbose)
			printf("Verbose Info: Cycles completed, beginning review\n");

		/* Check if any of them met threshold*/
		for (int j = 0; j < (MAX_PROCESSES - 1); j++)
		{
			if (iProcessArray[j][PROCESS_ARRAY_COUNT_END_CYCLE] < iProcessArray[j][PROCESS_ARRAY_COUNT_START_CYCLE])
				continue;

			/* dHandleDelta is the difference between number of handles for a process from first cycle to the last one  */
			DWORD dHandleDelta = (iProcessArray[j][PROCESS_ARRAY_COUNT_END_CYCLE] - iProcessArray[j][PROCESS_ARRAY_COUNT_START_CYCLE]);

			/* Check whether the delta is equal or above the threshold */
			if (dHandleDelta >= dHandleChangeThreshold)
			{
				HANDLE pHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, iProcessArray[j][PROCESS_ARRAY_INDEX]);
				TCHAR tProcessName[MAX_PATH];
				GetModuleFileNameEx(pHandle, 0, tProcessName, MAX_PATH);
				CloseHandle(pHandle);

				/* If we don't want signed, yet it is signed, skip... */
				if (!bIncludeSigned && (is_signed(tProcessName) == 0))
				{
					if (bVerbose)
						wprintf(L"Verbose Info: Skipping alert on %s (%d) despite trigger, as it is signed (use /signed to alert on signed executables too)\n", tProcessName, iProcessArray[j][PROCESS_ARRAY_INDEX]);
					continue;
				}

				/* Inform the user if we have a suspicious process */
				wprintf(L"Alert! Process: %s (%d) has had a suspicious number of handles (%d) created in the last cycle\nNew handles created during this cycle:\n", tProcessName, iProcessArray[j][PROCESS_ARRAY_INDEX], dHandleDelta);

				for (DWORD k = 1; k <= dHandleDelta; k++)
					wprintf(L"%s\n", cHandleArray[j][iProcessArray[j][PROCESS_ARRAY_COUNT_START_CYCLE] + k]);

				if (bSuspendProcess)
				{

					printf("Info: Attempting to suspend process %d\n", iProcessArray[j][PROCESS_ARRAY_INDEX]);

					/* Attach debugger to process (freeze it!)*/
					if (!DebugActiveProcess(iProcessArray[j][PROCESS_ARRAY_INDEX]))
					{
						printf("Info: Could not attach to process %d as a debugger\n", iProcessArray[j][PROCESS_ARRAY_INDEX]);
					}
					else
					{
						DebugSetProcessKillOnExit(FALSE);

						printf("Info: Successfully attached to process %d as debugger\n", iProcessArray[j][PROCESS_ARRAY_INDEX]);
						printf("Info: It will remain frozen until this process is terminated\n");
					}
				}

				printf("------------------------------------------------------------------------------\n");

			}
		}

		if (bVerbose)
			printf("Verbose Info: Review complete\n");

		free(cHandleArray);

	}

	return 0;
}