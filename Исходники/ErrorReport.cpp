bool ErrorReport::GetMiscCrashInfo() {
	
	// Get crash time
	m_CrashDateTime = QDateTime::currentDateTime();
	
	m_ProcessArchitecture = ARX_ARCH_NAME;
	
	m_OSName = QString::fromUtf8(platform::getOSName().c_str());
	m_OSArchitecture = QString::fromUtf8(platform::getOSArchitecture().c_str());
	m_OSDistribution = QString::fromUtf8(platform::getOSDistribution().c_str());
	
#if ARX_PLATFORM == ARX_PLATFORM_WIN32
	
	// Open parent process handle
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_pCrashInfo->processId);
	if(hProcess != NULL)
	{
		// Get memory usage info
		PROCESS_MEMORY_COUNTERS meminfo;
		BOOL bGetMemInfo = GetProcessMemoryInfo(hProcess, &meminfo, sizeof(PROCESS_MEMORY_COUNTERS));
		if(bGetMemInfo)
			m_ProcessMemoryUsage = meminfo.WorkingSetSize;

		// Determine the period of time the process is working.
		FILETIME CreationTime, ExitTime, KernelTime, UserTime;
		BOOL bGetTimes = GetProcessTimes(hProcess, &CreationTime, &ExitTime, &KernelTime, &UserTime);
		if(bGetTimes)
		{
			SYSTEMTIME AppStartTime;
			FileTimeToSystemTime(&CreationTime, &AppStartTime);

			SYSTEMTIME CurTime;
			GetSystemTime(&CurTime);
			ULONG64 uCurTime = ConvertSystemTimeToULONG64(CurTime);
			ULONG64 uStartTime = ConvertSystemTimeToULONG64(AppStartTime);

			// Check that the application works for at least one minute before crash.
			// This might help to avoid cyclic error report generation when the applciation
			// crashes on startup.
			m_RunningTimeSec = (double)(uCurTime-uStartTime)*10E-08;
		}
	}
	else
	{
		m_DetailedError = QString("Unable to obtain an handle to the crashed process (Error %1).").arg(QString::number(GetLastError()));
		return false;
	}
	
	if(m_pCrashInfo->exceptionCode != 0)
	{
		QString exceptionStr = GetExceptionString(m_pCrashInfo->exceptionCode).c_str();
		if(!exceptionStr.isEmpty())
		{
			m_ReportDescription += "\nException code:\n  ";
			m_ReportDescription += exceptionStr;
			m_ReportDescription += "\n";
		}
	}

	std::string callStack, callstackTop;
	u32 callstackCrc;

	bool bCallstack = GetCallStackInfo(hProcess, m_pCrashInfo->threadHandle, &m_pCrashInfo->contextRecord, callStack, callstackTop, callstackCrc);
	if(!bCallstack) 
	{
		m_DetailedError = "A failure occured when obtaining information regarding the callstack.";
		return false;
	}
	
	m_ReportUniqueID = QString("[%1]").arg(QString::number(callstackCrc, 16).toUpper());
	
	m_ReportDescription = m_pCrashInfo->detailedCrashInfo;
	m_ReportDescription += "\nCallstack:\n";
	m_ReportDescription += callStack.c_str();
	m_ReportTitle = QString("%1 %2").arg(m_ReportUniqueID, callstackTop.c_str());

	QString registers(GetRegisters(&m_pCrashInfo->contextRecord).c_str());
	if(!registers.isEmpty())
	{
		m_ReportDescription += "\nRegisters:\n";
		m_ReportDescription += registers;
	}
	
	CloseHandle(hProcess);
	
	m_ReportDescriptionText = m_ReportDescription;
	
#else // ARX_PLATFORM != ARX_PLATFORM_WIN32
	
	getResourceUsage(m_pCrashInfo->processId, m_ProcessMemoryUsage, m_RunningTimeSec);
	
#endif

	return true;
}