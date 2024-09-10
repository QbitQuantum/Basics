DWORD
WINAPI
ep_DriverService(void *arg)
{
	const CONFIG_DATA *cd = GetConfigData();

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	// Build the threadpool
	POOL_DATA pd;
	ZeroMemory(&pd, sizeof(POOL_DATA));
	pd.hSharedDriverHandle = g_hDriver;
	const DWORD dwNumChannels = NUM_EVENTTYPES-1; // -1 to ignore EVENT_NONE
	THREADPOOL *tp = ThreadPoolAlloc(cd->dThreadPoolSize, dwNumChannels, PfWorkerInit, PfWorkerWork, PfWorkerDestroy, &pd, sizeof(WORKER_DATA), THREAD_PRIORITY_NORMAL);
	if (!tp) Die("Unable to allocate threadpool");

	// Create the read file event for use with overlapped I/O
	HANDLE hReadFileEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hReadFileEvent == NULL) Die("Unable to create read file event");

	// Allocate memory for the buffer to be read from the kernel
	PROCFILTER_REQUEST *req = (PROCFILTER_REQUEST*)_malloca(PROCFILTER_REQUEST_SIZE);
	while (true) {
		if (WaitForSingleObject(g_hStopTheadEvent, 0) == WAIT_OBJECT_0) break;

		// Read request from driver using synch/asynch calls according to https://support.microsoft.com/en-us/kb/156932
		DWORD dwBytesRead = 0;
		OVERLAPPED overlapped;
		ZeroMemory(&overlapped, sizeof(OVERLAPPED));
		ResetEvent(hReadFileEvent);
		overlapped.hEvent = hReadFileEvent;
		BOOL rc = ReadFile(g_hDriver, req, PROCFILTER_REQUEST_SIZE, &dwBytesRead, &overlapped);
		DWORD dwErrorCode = GetLastError();
		if (rc) {
			// Successfully completed a synchronous read, do nothing
		} else if (dwErrorCode == ERROR_IO_PENDING) {
			// Successfully completed an asynchronous read, so wait for it
			DWORD dwNumberOfBytesTransferred = 0;
			if (!GetOverlappedResult(g_hDriver, &overlapped, &dwNumberOfBytesTransferred, TRUE)) {
				dwErrorCode = GetLastError();
				if (dwErrorCode == ERROR_OPERATION_ABORTED || dwErrorCode == ERROR_INVALID_HANDLE) break;
				// Cancel the pending IO to ensure the IO operation does not complete after this function ends
				// and the result is stored to an invalid location
				CancelIo(g_hDriver);
				Die("GetOverlappedResult() failure in reader: %d", dwErrorCode);
			}
			dwErrorCode = GetLastError();
			dwBytesRead = dwNumberOfBytesTransferred;
		} else if (dwErrorCode == ERROR_OPERATION_ABORTED || dwErrorCode == ERROR_INVALID_HANDLE) {
			break;
		} else {
			Die("Unable to read data from driver: %d / %ls", dwErrorCode, ErrorText(dwErrorCode));
		}
		LogDebugFmt("Read event from driver: PID:%u Event:%u", req->dwProcessId, req->dwEventType);
		ULONG64 ulStartPerformanceCount = GetPerformanceCount();
		
		// Validate the size of data read
		if (dwBytesRead < sizeof(PROCFILTER_REQUEST) || dwBytesRead > PROCFILTER_REQUEST_SIZE) {
			Die("Read invalid size from driver device: %u < %u || %u > %u  ReadFile:%hs ErrorCode:%d",
				dwBytesRead, sizeof(PROCFILTER_REQUEST), dwBytesRead, PROCFILTER_REQUEST_SIZE, rc ? "TRUE" : "FALSE", dwErrorCode);
		}
		if (dwBytesRead != req->dwRequestSize) {
			Die("Read partial packet from driver device: Read:%u PacketSize:%u", dwBytesRead, req->dwRequestSize);
		}
		
		// Post a copy of the retrieved data to a worker thread
		LogDebug("Posting work task to worker");
		// Allocate memory for the task data, the structure of which includes only the header portion of the procfilter request,
		// so allocate only the exact size needed
		WORKER_TASK_DATA *wtd = (WORKER_TASK_DATA*)malloc(sizeof(WORKER_TASK_DATA) + (dwBytesRead - sizeof(PROCFILTER_REQUEST)));
		if (!wtd) Die("Memory allocation failure for ProcFilter request");
		memcpy(&wtd->peProcFilterRequest, req, dwBytesRead);
		wtd->ulStartPerformanceCount = ulStartPerformanceCount;
		LogDebugFmt("Posting to threadpool: PID:%u Event:%u", req->dwProcessId, req->dwEventType);
		if (ThreadPoolPost(tp, req->dwEventType, false, g_hStopTheadEvent, wtd)) {
			LogDebug("Posted work task to worker");
		} else {
			LogDebugFmt("Failed to post task to worker");
			free(wtd);
		}
	}

	_freea(req);

	ThreadPoolFree(tp);

	CloseHandle(hReadFileEvent);
	
	// Driver closing is done here since this thread could terminate due to an error situation
	// and if closing were done elsewhere (such as service exit) the driver device would be kept open, consequently
	// blocking process creation events until service shutdown
	CloseHandle(g_hDriver);
	g_hDriver = INVALID_HANDLE_VALUE;

	return 0;
}