void CreateMiniDump(HANDLE hDumpFile, PEXCEPTION_POINTERS exc_ptr)
{
	MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
	exceptionInfo.ThreadId = GetCurrentThreadId();
	exceptionInfo.ExceptionPointers = exc_ptr;
	exceptionInfo.ClientPointers = false;

	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
		hDumpFile, MiniDumpNormal, &exceptionInfo, NULL, NULL);
}