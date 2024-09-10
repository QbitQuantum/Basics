//===========================================================
// Entry point where control comes on an unhandled exception
//===========================================================
LONG WINAPI WheatyExceptionReport::WheatyUnhandledExceptionFilter(
		PEXCEPTION_POINTERS pExceptionInfo) {
	TCHAR module_folder_name[MAX_PATH];
	GetModuleFileName(0, module_folder_name, MAX_PATH);
	TCHAR* pos = _tcsrchr(module_folder_name, '\\');
	if (!pos)
		return 0;
	pos[0] = '\0';
	++pos;

	TCHAR crash_folder_path[MAX_PATH];
	sprintf(crash_folder_path, "%s\\%s", module_folder_name, CrashFolder);
	if (!CreateDirectory(crash_folder_path, NULL)) {
		if (GetLastError() != ERROR_ALREADY_EXISTS)
			return 0;
	}

	SYSTEMTIME systime;
	GetLocalTime(&systime);
	sprintf(m_szDumpFileName, "%s\\%s_%s_[%u-%u_%u-%u-%u].dmp",
			crash_folder_path, _HASH, pos, systime.wDay, systime.wMonth,
			systime.wHour, systime.wMinute, systime.wSecond);

	sprintf(m_szLogFileName, "%s\\%s_%s_[%u-%u_%u-%u-%u].txt",
			crash_folder_path, _HASH, pos, systime.wDay, systime.wMonth,
			systime.wHour, systime.wMinute, systime.wSecond);

	m_hDumpFile = CreateFile(m_szDumpFileName, GENERIC_WRITE, 0, 0, OPEN_ALWAYS,
			FILE_FLAG_WRITE_THROUGH, 0);

	m_hReportFile = CreateFile(m_szLogFileName, GENERIC_WRITE, 0, 0,
			OPEN_ALWAYS, FILE_FLAG_WRITE_THROUGH, 0);

	if (m_hDumpFile) {
		MINIDUMP_EXCEPTION_INFORMATION info;
		info.ClientPointers = FALSE;
		info.ExceptionPointers = pExceptionInfo;
		info.ThreadId = GetCurrentThreadId();

		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
				m_hDumpFile, MiniDumpWithIndirectlyReferencedMemory, &info, 0,
				0);

		CloseHandle(m_hDumpFile);
	}

	if (m_hReportFile) {
		SetFilePointer(m_hReportFile, 0, 0, FILE_END);

		GenerateExceptionReport(pExceptionInfo);

		CloseHandle(m_hReportFile);
		m_hReportFile = 0;
	}

	if (m_previousFilter)
		return m_previousFilter(pExceptionInfo);
	else
		return EXCEPTION_EXECUTE_HANDLER/*EXCEPTION_CONTINUE_SEARCH*/;
}