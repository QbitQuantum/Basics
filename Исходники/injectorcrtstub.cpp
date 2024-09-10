DWORD WINAPI WrapperThreadProc(void *threadData)
{
	ThreadData *td = (ThreadData *)threadData;
	td->wrapperThreadId = GetCurrentThreadId();

	HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, CRTThreadProc, td, 0, NULL);
	WaitForSingleObject(thread, INFINITE);
	DWORD retCode;
	GetExitCodeThread(thread, &retCode);
	CloseHandle(thread);

	HMODULE thisDLL = td->thisDLL;
	HANDLE processHeap = td->processHeap;
	HeapFree(processHeap, 0, td);
	FreeLibraryAndExitThread(thisDLL, 42);
}