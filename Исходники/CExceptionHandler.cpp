void CExceptionHandler::WriteExceptionReport()
#endif
{
	// Get the current time and date
	time_t t = time(NULL);
	const struct tm * tm = localtime(&t);

	// Get the 'crashinfo' directory path
	String strPath(SharedUtility::GetAbsolutePath("crashinfo"));

	// Create the 'crashinfo' directory if needed
	if(!SharedUtility::Exists(strPath))
		SharedUtility::CreateDirectory(strPath);

	// Append the client or server string to the path
#ifdef _SERVER
	strPath.Append("\\Server");
#else
	strPath.Append("\\Client");
#endif

	// Append the operating system string to the path
	strPath.Append("-" OS_STRING);

	// Append the version, date and time to the path
	strPath.AppendF("-" MOD_VERSION_STRING "-%04d.%02d.%02d-%02d.%02d.%02d", (tm->tm_year + 1900), (tm->tm_mon + 1), tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);

	// Get the log file path
	String strLogPath("%s.log", strPath.Get());

	// Open the log file
	FILE * fFile = fopen(strLogPath, "w");

	// Did the log file open successfully?
	if(fFile)
	{
		String strReportData;

		// Write the unhandled exception report start notice to the log file
		fprintf(fFile, "-- Unhandled Exception Report Start --\n");

#ifdef WIN32
		// Write the exception code and exception code string to the log file
		strReportData.AppendF("Exception code: 0x%p (%s)\n", ExceptionInfo->ExceptionRecord->ExceptionCode, 
			ExceptionCodeToString(ExceptionInfo->ExceptionRecord->ExceptionCode));

		// Write the exception address to the log file
#ifndef _SERVER
		strReportData.AppendF("Exception address: 0x%p (Game base: 0x%p)\n", ExceptionInfo->ExceptionRecord->ExceptionAddress, CGame::GetBase());
		strReportData.AppendF("Exception real-add: 0x%p / 0x%p\n", ((int)ExceptionInfo->ExceptionRecord->ExceptionAddress-CGame::GetBase()), (CGame::GetBase()-(int)ExceptionInfo->ExceptionRecord->ExceptionAddress));
#else
		strReportData.AppendF("Exception address: 0x%p\n", ExceptionInfo->ExceptionRecord->ExceptionAddress);
#endif
		// Create a tool help 32 process snapshot
		HANDLE hModuleSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());

		if(hModuleSnapShot)
		{
			MODULEENTRY32 ModuleEntry;
			ModuleEntry.dwSize = sizeof(ModuleEntry);

			if(Module32First(hModuleSnapShot, &ModuleEntry))
			{
				// Enumerate through all modules
				while(Module32Next(hModuleSnapShot, &ModuleEntry))
				{
					// See if exception was within this module
					if((ExceptionInfo->ContextRecord->Eip >= (DWORD)ModuleEntry.modBaseAddr) && (ExceptionInfo->ContextRecord->Eip <= ((DWORD)ModuleEntry.modBaseAddr + ModuleEntry.modBaseSize)))
					{
						strReportData.AppendF("Exception module: %s (+0x%p)\n", ModuleEntry.szModule, (ExceptionInfo->ContextRecord->Eip - (DWORD)ModuleEntry.modBaseAddr));
						break;
					}
				}
			}
		}

		// Write the registers segment header
		strReportData.AppendF("Exception registers: \n");

		// If we have segments context information then write it to the log file
		if(ExceptionInfo->ContextRecord->ContextFlags & CONTEXT_SEGMENTS)
		{
			strReportData.AppendF("GS=0x%p FS=0x%p ES=0x%p DS=0x%p\n", ExceptionInfo->ContextRecord->SegGs, 
				ExceptionInfo->ContextRecord->SegFs, ExceptionInfo->ContextRecord->SegEs, 
				ExceptionInfo->ContextRecord->SegDs);
		}

		// If we have integer context information then write it to the log file
		if(ExceptionInfo->ContextRecord->ContextFlags & CONTEXT_INTEGER)
		{
			strReportData.AppendF("EDI=0x%p ESI=0x%p EBX=0x%p EDX=0x%p\n", ExceptionInfo->ContextRecord->Edi, 
				ExceptionInfo->ContextRecord->Esi, ExceptionInfo->ContextRecord->Ebx,
				ExceptionInfo->ContextRecord->Edx);
			strReportData.AppendF("ECX=0x%p EAX=0x%p\n", ExceptionInfo->ContextRecord->Ecx, 
				ExceptionInfo->ContextRecord->Eax);
		}

		// If we have control context information then write it to the log file
		if(ExceptionInfo->ContextRecord->ContextFlags & CONTEXT_CONTROL)
		{
			strReportData.AppendF("EBP=0x%p EIP=0x%p CS=0x%p EFLAGS=0x%p\n", ExceptionInfo->ContextRecord->Ebp, 
				ExceptionInfo->ContextRecord->Eip, ExceptionInfo->ContextRecord->SegCs, 
				ExceptionInfo->ContextRecord->EFlags);
			strReportData.AppendF("ESP=0x%p SS=0x%p\n", ExceptionInfo->ContextRecord->Esp, 
				ExceptionInfo->ContextRecord->SegSs);
		}
#else
		void * pArray[50];
		int iSize = backtrace(pArray, 50);
		char ** szMessages = backtrace_symbols(pArray, iSize);

		for(int i = 0; i < iSize && (szMessages[i] != NULL); i++)
			strReportData.AppendF("[Backtrace %d]: %s\n", i, szMessages[i]);
#endif

		// If we have a callback call it
		if(m_pfnCallback)
			m_pfnCallback(strReportData);

		// Print the report data to the log file
		fprintf(fFile, strReportData.Get());

		// Write the unhandled exception report end notice to the log file
		fprintf(fFile, "--Unhandled Exception Report End --\n");

		// Close the log file
		fclose(fFile);
	}
	else
		CLogFile::Printf("Failed to open the crash log file.");

#ifdef WIN32
	// Get the minidump file path
	String strMiniDumpPath("%s.dmp", strPath.Get());

	// Open the minidump file
	HANDLE hFile = CreateFileA(strMiniDumpPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL , NULL);

	// Did the minidump file open successfully?
	if(hFile)
	{
		// Create the minidump exception information
		MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
		exceptionInfo.ThreadId = GetCurrentThreadId();
		exceptionInfo.ExceptionPointers = ExceptionInfo;
		exceptionInfo.ClientPointers = FALSE;

		// Write the minidump to the minidump file
		if(!MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &exceptionInfo, NULL, NULL))
			CLogFile::Printf("Failed to write the minidump file.");

		// Close the minidump file
		CloseHandle(hFile);
	}
	else
		CLogFile::Printf("Failed to open the minidump file.");
#endif

	// Print a message in the log file
	CLogFile::Printf("IV:MP has crashed. Please see %s for more information.", strLogPath.Get());
}