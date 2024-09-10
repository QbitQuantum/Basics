LONG WINAPI ProcessException_ice(PEXCEPTION_POINTERS pExceptionInfo)
{
     /* 异常信息结构体 */
    MINIDUMP_EXCEPTION_INFORMATION  ExInfo;
    /* dump生成目录 */
    wchar_t appdir[MAX_PATH+1] = {0};
	HANDLE hFile = NULL;
    if ( !(GetEnvironmentVariableW(L"APPDATA",appdir,MAX_PATH) > 0) )
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}
    PathAppendW(appdir,L"minidump.dmp");
    /* 创建文件句柄 */
    hFile = CreateFileW(appdir,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        TRUNCATE_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
	if (INVALID_HANDLE_VALUE == hFile && ERROR_FILE_NOT_FOUND == GetLastError())
	{
	    hFile = CreateFileW(appdir,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
	}
	if (INVALID_HANDLE_VALUE == hFile)
		return EXCEPTION_CONTINUE_SEARCH;
    ExInfo.ThreadId = GetCurrentThreadId();
    ExInfo.ExceptionPointers = pExceptionInfo;
    ExInfo.ClientPointers = TRUE;

    /* MiniDumpWriteDump输出dump */
    MiniDumpWriteDump_func(GetCurrentProcess(), 
        GetCurrentProcessId(),
        hFile,
        MiniDumpNormal,
        &ExInfo,
        NULL,
        NULL );

    CloseHandle(hFile);
    return EXCEPTION_EXECUTE_HANDLER;
}