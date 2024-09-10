LONG WINAPI DumpException(LPEXCEPTION_POINTERS exceptionInfo)
{
	HMODULE hLibrary = LoadLibrary(TEXT("dbghelp.dll"));
	LPMINIDUMPWRITEDUMP miniDumpWriteDump = (LPMINIDUMPWRITEDUMP)GetProcAddress(hLibrary,"MiniDumpWriteDump");
	if(!hLibrary || !miniDumpWriteDump)
	{
		FreeLibrary(hLibrary);

		TCHAR message[512];
		wsprintf(message,TEXT("The program needs to close because of a unhandled 0x%08lX exception which occurred at 0x%08lX.\n")\
						 TEXT("No additional information about the problem could be stored. We apologize for the inconvenience."),exceptionInfo->ExceptionRecord->ExceptionCode,exceptionInfo->ExceptionRecord->ExceptionAddress);

		MessageBox(GetDesktopWindow(),message,TEXT("Unhandled Exception"),MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);

		return EXCEPTION_EXECUTE_HANDLER;
	}

	// Just create the dump file in the current working directory
	TCHAR dump[MAX_PATH] = {TEXT("Dump.dmp")};
	TCHAR compressed[MAX_PATH] = {TEXT("Dump.cab")};

	GetDateFormat(LOCALE_USER_DEFAULT,NULL,NULL,TEXT("'Dump'ddMMyyyy'.dmp'"),dump,_countof(dump));
	GetDateFormat(LOCALE_USER_DEFAULT,NULL,NULL,TEXT("'Dump'ddMMyyyy'.cab'"),compressed,_countof(compressed));
	
	TCHAR directory[MAX_PATH];
	GetCurrentDirectory(_countof(directory),directory);

	HANDLE hFile = CreateFile(dump,GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,NULL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		FreeLibrary(hLibrary);

		TCHAR message[512];
		wsprintf(message,TEXT("The program needs to close because of a unhandled 0x%08lX exception which occurred at 0x%08lX.\n")\
						 TEXT("A file containing more information about the ")\
						 TEXT("occured exception could not be written.\nPlease ")\
						 TEXT("check if you have write permissions. We apologize for the inconvenience.\n\n%s\\%s"),exceptionInfo->ExceptionRecord->ExceptionCode,exceptionInfo->ExceptionRecord->ExceptionAddress,directory,dump);

		MessageBox(GetDesktopWindow(),message,TEXT("Unhandled Exception"),MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);

		return EXCEPTION_EXECUTE_HANDLER;
	}

	MINIDUMP_EXCEPTION_INFORMATION info = {0};
	info.ClientPointers = TRUE;
	info.ExceptionPointers = exceptionInfo;
	info.ThreadId = GetCurrentThreadId();

	miniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(),hFile,MiniDumpWithFullMemory,&info,NULL,NULL);
	
	FlushFileBuffers(hFile);
	CloseHandle(hFile);
	FreeLibrary(hLibrary);

	BOOL result = FALSE;

#ifndef DUMP_EXCEPTION_NO_COMPRESS

	STARTUPINFO			startupInfo;
	PROCESS_INFORMATION processInfo;

	ZeroMemory(&startupInfo,sizeof(startupInfo));
	ZeroMemory(&processInfo,sizeof(processInfo));

	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESHOWWINDOW;
	startupInfo.wShowWindow = SW_HIDE;

	TCHAR makecab[MAX_PATH] = {TEXT("")};
	ExpandEnvironmentStrings(TEXT("%SYSTEMROOT%\\System32\\makecab.exe"),makecab,_countof(makecab));

	TCHAR parameters[MAX_PATH] = {TEXT("")};

	wcscat_s(parameters,_countof(parameters),TEXT("\""));
	wcscat_s(parameters,_countof(parameters),makecab);
	wcscat_s(parameters,_countof(parameters),TEXT("\""));
	wcscat_s(parameters,_countof(parameters),TEXT(" "));
	wcscat_s(parameters,_countof(parameters),dump);
	wcscat_s(parameters,_countof(parameters),TEXT(" "));
	wcscat_s(parameters,_countof(parameters),compressed);

	result = CreateProcess(makecab,			// Application name
					parameters,		// Application arguments
					0,
					0,
					CREATE_NO_WINDOW,
					0,
					0,
					0,								// Working directory
					&startupInfo,
					&processInfo);

#endif
	
	TCHAR message[512];
	wsprintf(message,TEXT("The program needs to close because of a unhandled 0x%08lX exception which occurred at 0x%08lX.\n")\
					 TEXT("A file containing more information about the ")\
					 TEXT("occured exception has been written to the current directory.\nPlease ")\
					 TEXT("send us this file to help us in finding and repairing ")\
					 TEXT("the problem. We apologize for the inconvenience.\n\n%s\\%s"),exceptionInfo->ExceptionRecord->ExceptionCode,exceptionInfo->ExceptionRecord->ExceptionAddress,directory,result ? compressed : dump);

	MessageBox(GetDesktopWindow(),message,TEXT("Unhandled Exception"),MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);
	
#ifndef DUMP_EXCEPTION_NO_COMPRESS

	if(result)
	{
		// Wait until child process exits
		WaitForSingleObject(processInfo.hProcess,INFINITE);

		DWORD code;

		if(GetExitCodeProcess(processInfo.hProcess,&code) && !code)
		{
			// Delete the original file
			DeleteFile(dump);
		}
		else
		{
			wsprintf(message,	TEXT("The exception information file could not be compressed because of a error.\n")\
								TEXT("Information about the exeption can be found in the original uncompressed file.\n\n%s\\%s"),directory,dump);

			MessageBox(GetDesktopWindow(),message,TEXT("Compression Failed"),MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);
		}

		// Close process and thread handles. 
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}

#endif

	return EXCEPTION_EXECUTE_HANDLER;
}