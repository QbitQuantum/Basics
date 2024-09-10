		unsigned long CrashFilter(LPEXCEPTION_POINTERS pException, int exceptionCode)
		{
			unsigned long result;
			if ((result = UnhandledExceptionFilter(pException)) != EXCEPTION_EXECUTE_HANDLER)
			{
				return result;
			}
			else if (avmthane::show_error)
			{
				// if -error option dont do a dump 
				return EXCEPTION_CONTINUE_SEARCH;
			}

			AvmLog("avmplus crash: exception 0x%08lX occurred\n", exceptionCode);

			typedef BOOL (WINAPI *MINIDUMP_WRITE_DUMP)(
				HANDLE hProcess,
				DWORD ProcessId,
				HANDLE hFile,
				MINIDUMP_TYPE DumpType,
				PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
				PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
				PMINIDUMP_CALLBACK_INFORMATION CallbackParam
				);

			HMODULE hDbgHelp = LoadLibrary("dbghelp.dll");
			MINIDUMP_WRITE_DUMP MiniDumpWriteDump_ = (MINIDUMP_WRITE_DUMP)GetProcAddress(hDbgHelp, 
				"MiniDumpWriteDump");

			if (MiniDumpWriteDump_)
			{
				MINIDUMP_EXCEPTION_INFORMATION  M;
				const char DumpPath[] = "avmplusCrash.dmp";

				M.ThreadId = GetCurrentThreadId();
				M.ExceptionPointers = pException;
				M.ClientPointers = 0;

				AvmLog("Writing minidump crash log to %s\n", DumpPath);

				HANDLE hDumpFile = CreateFile(DumpPath, GENERIC_WRITE, 0, 
					NULL, CREATE_ALWAYS,
					FILE_ATTRIBUTE_NORMAL, NULL);

				MiniDumpWriteDump_(GetCurrentProcess(),
					GetCurrentProcessId(),
					hDumpFile,
					MiniDumpNormal,
					(pException) ? &M : NULL, NULL, NULL);

				CloseHandle(hDumpFile);
			}
			else
			{
				AvmLog("minidump not available, no crash log written.\n");
			}

			return result;
		}