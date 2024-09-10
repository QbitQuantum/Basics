THREAD_ENTRY_DECLARE start_and_watch_server(THREAD_ENTRY_PARAM)
{
/**************************************
 *
 *	s t a r t _ a n d _ w a t c h _ s e r v e r
 *
 **************************************
 *
 * Functional description
 *
 *      This function is where the server process is created and
 * the thread waits for this process to exit.
 *
 **************************************/
	Firebird::ContextPoolHolder threadContext(getDefaultMemoryPool());

	HANDLE procHandle = NULL;
	bool done = true;
	const UINT error_mode = SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX |
		SEM_NOOPENFILEERRORBOX | SEM_NOALIGNMENTFAULTEXCEPT;
	SC_HANDLE hScManager = 0, hService = 0;

	// get the guardian startup information
	const short option = Config::getGuardianOption();

	char prefix_buffer[MAXPATHLEN];
	GetModuleFileName(NULL, prefix_buffer, sizeof(prefix_buffer));
	Firebird::PathName path = prefix_buffer;
	path = path.substr(0, path.rfind(PathUtils::dir_sep) + 1) + FBSERVER;
	path = "\"" + path + "\"";
	Firebird::PathName prog_name = path + " -a -n";

	// if the guardian is set to FOREVER then set the error mode
	UINT old_error_mode = 0;
	if (option == START_FOREVER)
		old_error_mode = SetErrorMode(error_mode);

	// Spawn the new process
	do {
		SERVICE_STATUS ServiceStatus;
		char out_buf[1024];
		BOOL success;
		int error = 0;

		if (service_flag)
		{
			if (hService)
			{
				while ((QueryServiceStatus(hService, &ServiceStatus) == TRUE) &&
					(ServiceStatus.dwCurrentState != SERVICE_STOPPED))
				{
					Sleep(500);
				}
			}

			procHandle = CreateMutex(NULL, FALSE, mutex_name->c_str());

			// start as a service.  If the service can not be found or
			// fails to start, close the handle to the mutex and set
			// success = FALSE
			if (!hScManager)
				hScManager = OpenSCManager(NULL, NULL, GENERIC_READ);
			if (!hService)
			{
				hService = OpenService(hScManager, remote_name->c_str(),
					GENERIC_READ | GENERIC_EXECUTE);
			}
			success = StartService(hService, 0, NULL);
			if (success != TRUE)
				error = GetLastError();
			// if the server is already running, then inform it that it should
			// open the guardian mutex so that it may be governed.
			if (!error || error == ERROR_SERVICE_ALREADY_RUNNING)
			{
				// Make sure that it is actually ready to receive commands.
				// If we were the one who started it, then it will need a few
				// seconds to get ready.
				while ((QueryServiceStatus(hService, &ServiceStatus) == TRUE) &&
					(ServiceStatus.dwCurrentState != SERVICE_RUNNING))
				{
					Sleep(500);
				}
				ControlService(hService, SERVICE_CREATE_GUARDIAN_MUTEX, &ServiceStatus);
				success = TRUE;
			}
		}
		else
		{
			HWND hTmpWnd = FindWindow(szClassName, szWindowName);
			if (hTmpWnd == NULL)
			{
				STARTUPINFO si;
				SECURITY_ATTRIBUTES sa;
				PROCESS_INFORMATION pi;
				ZeroMemory(&si, sizeof(si));
				si.cb = sizeof(si);
				sa.nLength = sizeof(sa);
				sa.lpSecurityDescriptor = NULL;
				sa.bInheritHandle = TRUE;
				success = CreateProcess(NULL, const_cast<char*>(prog_name.c_str()),
										&sa, NULL, FALSE, 0, NULL, NULL, &si, &pi);
				if (success != TRUE)
					error = GetLastError();

				procHandle = pi.hProcess;
				// TMN: 04 Aug 2000 - closed the handle that previously leaked.
				CloseHandle(pi.hThread);
			}
			else
			{
				SendMessage(hTmpWnd, WM_COMMAND, (WPARAM) IDM_GUARDED, 0);
				DWORD server_pid;
				GetWindowThreadProcessId(hTmpWnd, &server_pid);
				procHandle = OpenProcess(SYNCHRONIZE | PROCESS_QUERY_INFORMATION, FALSE, server_pid);
				if (procHandle == NULL)
				{
					error = GetLastError();
					success = FALSE;
				}
				else {
					success = TRUE;
				}
			}
		}

		if (success != TRUE)
		{
			// error creating new process
			char szMsgString[256];
			LoadString(hInstance_gbl, IDS_CANT_START_THREAD, szMsgString, 256);
			sprintf(out_buf, "%s : %s errno : %d", path.c_str(), szMsgString, error);
			write_log(IDS_CANT_START_THREAD, out_buf);

			if (service_flag)
			{
				SERVICE_STATUS status_info;
				// wait a second to get the mutex handle (just in case) and
				// then close it
				WaitForSingleObject(procHandle, 1000);
				CloseHandle(procHandle);
				hService = OpenService(hScManager, remote_name->c_str(),
					GENERIC_READ | GENERIC_EXECUTE);
				ControlService(hService, SERVICE_CONTROL_STOP, &status_info);
				CloseServiceHandle(hScManager);
				CloseServiceHandle(hService);
				CNTL_stop_service(); //service_name->c_str());
			}
			else
			{
				MessageBox(NULL, out_buf, NULL, MB_OK | MB_ICONSTOP);
				PostMessage(hWndGbl, WM_CLOSE, 0, 0);
			}
			return 0;
		}
		else
		{
			char szMsgString[256];
			LoadString(hInstance_gbl, IDS_STARTING_GUARD, szMsgString, 256);
			sprintf(out_buf, "%s: %s\n", szMsgString, path.c_str());
			write_log(IDS_LOG_START, out_buf);
		}

		// wait for process to terminate
		DWORD exit_status;
		if (service_flag)
		{
			while (WaitForSingleObject(procHandle, 500) == WAIT_OBJECT_0)
			{
				ReleaseMutex(procHandle);
				Sleep(100);
			}

			const int ret_val = WaitForSingleObject(procHandle, INFINITE);
			if (ret_val == WAIT_ABANDONED)
				exit_status = CRASHED;
			else if (ret_val == WAIT_OBJECT_0)
				exit_status = NORMAL_EXIT;

			CloseHandle(procHandle);
		}
		else
		{
			while (WaitForSingleObject(procHandle, INFINITE) == WAIT_FAILED)
				;
			GetExitCodeProcess(procHandle, &exit_status);
			CloseHandle(procHandle);
		}

		if (exit_status != NORMAL_EXIT)
		{
			// check for startup error
			if (exit_status == STARTUP_ERROR)
			{
				char szMsgString[256];
				LoadString(hInstance_gbl, IDS_STARTUP_ERROR, szMsgString, 256);
				sprintf(out_buf, "%s: %s (%lu)\n", path.c_str(), szMsgString, exit_status);
				write_log(IDS_STARTUP_ERROR, out_buf);
				done = true;

			}
			else
			{
				char szMsgString[256];
				LoadString(hInstance_gbl, IDS_ABNORMAL_TERM, szMsgString, 256);
				sprintf(out_buf, "%s: %s (%lu)\n", path.c_str(), szMsgString, exit_status);
				write_log(IDS_LOG_TERM, out_buf);

				// switch the icons if the server restarted
				if (!service_flag)
					PostMessage(hWndGbl, WM_SWITCHICONS, 0, 0);
				if (option == START_FOREVER)
					done = false;
			}
		}
		else
		{
			// Normal shutdown - ie: via ibmgr - don't restart the server
			char szMsgString[256];
			LoadString(hInstance_gbl, IDS_NORMAL_TERM, szMsgString, 256);
			sprintf(out_buf, "%s: %s\n", path.c_str(), szMsgString);
			write_log(IDS_LOG_STOP, out_buf);
			done = true;
		}

		if (option == START_ONCE)
			done = true;
	} while (!done);


	// If on WINNT
	if (service_flag)
	{
		CloseServiceHandle(hScManager);
		CloseServiceHandle(hService);
		CNTL_stop_service(); //(service_name->c_str());
	}
	else
		PostMessage(hWndGbl, WM_CLOSE, 0, 0);

	return 0;
}