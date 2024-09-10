bool InstallThread(ULONG th32ThreadID, int reason)
{
	PExecutionBlock pCtx = NULL;

	pCtx = InitBlock(th32ThreadID);
	if (pCtx == NULL) {
		wprintf(L"unable to install thread %d (OOM?)\n", th32ThreadID);
		return false;
	}

	KnownThreadCount++;

	// OpenThreads for neighbor threads
	pCtx->hThr = OpenThread(THREAD_SET_CONTEXT | THREAD_GET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, th32ThreadID);

	// install branch tracing
	CONTEXT ContextRecord = { 0 };
	ContextRecord.ContextFlags = CONTEXT_ALL;

	wprintf(L"%d) attaching to thread ID: %d in process %d\n", reason, th32ThreadID, GetCurrentProcessId());

	if (!GetThreadContext(pCtx->hThr, &ContextRecord))
		wprintf(L"unable to get context on thread %d\n", th32ThreadID);

	// installed a thread
	EnterThreadTable(th32ThreadID, true);

	ContextRecord.EFlags |= 0x100;	// single step
	ContextRecord.Dr7 |= 0x300;		// setup branch tracing 

	if (!SetThreadContext(pCtx->hThr, &ContextRecord))
		wprintf(L"unable to set context on thread %d\n", th32ThreadID);


	return true;
}