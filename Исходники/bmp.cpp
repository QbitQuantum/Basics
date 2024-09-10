LONG WINAPI CBMPApp::MyUnhandledExceptionFilter(struct _EXCEPTION_POINTERS* ExceptionInfo)
{	
	typedef BOOL (WINAPI * PMiniDumpWriteDump)(
		__in HANDLE hProcess,
		__in DWORD ProcessId,
		__in HANDLE hFile,
		__in MINIDUMP_TYPE DumpType,
		__in_opt PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
		__in_opt PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
		__in_opt PMINIDUMP_CALLBACK_INFORMATION CallbackParam
		);
	PMiniDumpWriteDump MiniDumpWriteDump=NULL; 

	HMODULE hModule=LoadLibrary(_T("dbghelp.dll"));
	if( hModule!=NULL)
	{
		MiniDumpWriteDump=(PMiniDumpWriteDump)GetProcAddress(hModule,"MiniDumpWriteDump");
		if( MiniDumpWriteDump==NULL)
		{
			FreeLibrary(hModule);
			hModule=NULL;

			return EXCEPTION_CONTINUE_SEARCH;
		}
	}

	CTime tm=CTime::GetCurrentTime();	
	CString strTm=tm.Format("%d-%H-%M-%S.dmp");	
	CString strFileName=CPathUtilEx::Instance()->GetImagePath()+strTm;		
	HANDLE lhDumpFile=CreateFile(strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);	
	if( INVALID_HANDLE_VALUE==lhDumpFile)
	{		
		FreeLibrary(hModule);
		hModule=NULL;

		return EXCEPTION_CONTINUE_SEARCH;
	}

	MINIDUMP_EXCEPTION_INFORMATION loExceptionInfo;
	loExceptionInfo.ExceptionPointers = ExceptionInfo;
	loExceptionInfo.ThreadId = GetCurrentThreadId();
	loExceptionInfo.ClientPointers = TRUE;
	if( !MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),lhDumpFile,\
		(MINIDUMP_TYPE)(MINIDUMP_TYPE)(MiniDumpNormal/*|MiniDumpWithDataSegs|MiniDumpWithFullMemory|MiniDumpWithHandleData*/),&loExceptionInfo, NULL, NULL))
	{
		//
	}

	CloseHandle(lhDumpFile);

	FreeLibrary(hModule);
	hModule=NULL;
	return EXCEPTION_CONTINUE_SEARCH;
}