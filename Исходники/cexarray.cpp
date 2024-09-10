LONG WINAPI DebugTools::SelfUnhandledException(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
	wchar_t path[MAX_PATH];
	::GetModuleFileNameW(nullptr,path,MAX_PATH);
	wcscat_s(path,L".dmp");
	HANDLE hDumpFile=CreateFileW(path,GENERIC_WRITE,0,nullptr,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,nullptr);
	MINIDUMP_EXCEPTION_INFORMATION eInfo;
	eInfo.ThreadId = GetCurrentThreadId();
	eInfo.ExceptionPointers = ExceptionInfo;
	eInfo.ClientPointers = FALSE;

	MINIDUMP_CALLBACK_INFORMATION cbMiniDump;
	cbMiniDump.CallbackRoutine = 0;
	cbMiniDump.CallbackParam = 0;

	MiniDumpWriteDump(
		GetCurrentProcess(),
		GetCurrentProcessId(),
		hDumpFile,
		MiniDumpNormal,
		&eInfo,
		nullptr,
		&cbMiniDump);
	CloseHandle(hDumpFile);

	return EXCEPTION_EXECUTE_HANDLER;
}