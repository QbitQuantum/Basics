static HANDLE CreateThreadWrapper(_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes, _In_ SIZE_T dwStackSize, _In_ LPTHREAD_START_ROUTINE lpStartAddress,
	_In_opt_ __drv_aliasesMem LPVOID lpParameter, _In_ DWORD dwCreationFlags, _Out_opt_ LPDWORD lpThreadId)
{
	//MessageBoxA(NULL, "CreateThreadWrapper called", "CreateThreadWrapper called", 0);
	// find the name parameter by frobbling the parent stack
	char* parentStackPtr = reinterpret_cast<char*>(_AddressOfReturnAddress());
	char* threadName = *reinterpret_cast<char**>(parentStackPtr + 0x50 /* offset from base pointer to argument */ + 0x60 /* offset from function stack frame stack to base pointer */ + 8 /* return address offset */);

	// create metadata for passing to the thread
	struct WrapThreadMeta
	{
		char* threadName;
		LPTHREAD_START_ROUTINE origRoutine;
		void* originalData;
	};

	WrapThreadMeta* parameter = new WrapThreadMeta{ threadName, lpStartAddress, lpParameter };

	// create a thread with 'our' callback
	HANDLE hThread = CreateThread(lpThreadAttributes, dwStackSize, [](void* arguments)
	{
		// get and free metadata
		WrapThreadMeta* metaPtr = reinterpret_cast<WrapThreadMeta*>(arguments);
		WrapThreadMeta meta = *metaPtr;
		delete metaPtr;

		// set thread name, if any
		if (meta.threadName)
		{
			SetThreadName(-1, meta.threadName);
		}

		// invoke original thread start
		return meta.origRoutine(meta.originalData);
	}, parameter, dwCreationFlags, lpThreadId);

	return hThread;
}