double getCpuUsage()
{ 
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo; 
	SYSTEM_TIME_INFORMATION SysTimeInfo; 
	SYSTEM_BASIC_INFORMATION SysBaseInfo; 
 
	LONG status; 

	//change char** to lpcwstr
	char a[] = "ntdll";
	WCHAR wsz[64]; 
	swprintf(wsz, L"%S", a);
	LPCWSTR ntdll = wsz;

	NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle(ntdll),"NtQuerySystemInformation");
	// get number of processors in the system 
	status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL); 
	if (status != NO_ERROR) 
		return -1;
 
	if (!NtQuerySystemInformation) 
		return -1;
 
	// get number of processors in the system 
	status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL); 
	if (status != NO_ERROR) 
		return -1;
 
	// get new system time 
	status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0); 
	if (status!=NO_ERROR) 
		return -1;
 
	// get new CPU's idle time 
	status =NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL); 
	if (status != NO_ERROR) 
		return -1;
 
	if ( m_iNumberProcessors != SysBaseInfo.bKeNumberProcessors)
	{
		//save
		m_iNumberProcessors = SysBaseInfo.bKeNumberProcessors;
		//if sppi not null clear
		if (m_pSPPI != NULL) delete []m_pSPPI;
		if (m_PUT != NULL) delete []m_PUT;
		//malloc and point
		m_pSPPI = new SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION[m_iNumberProcessors];
		m_PUT = new m_PROCESSORS_USE_TIME[m_iNumberProcessors];
	}
 
	// get ProcessorPer time 
	status =NtQuerySystemInformation(SystemProcessorPerformanceInformation, m_pSPPI, sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * m_iNumberProcessors, NULL); 
	if (status != NO_ERROR) 
		return -1;
 
	// if it's a first call - skip it 
	if (liOldIdleTime.QuadPart != 0) 
	{ 
		// CurrentValue = NewValue - OldValue 
		dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime); 
 
		dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(liOldSystemTime);
 
		// CurrentCpuIdle = IdleTime / SystemTime 
		dbIdleTime = dbIdleTime / dbSystemTime;
 
		// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors 
		dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SysBaseInfo.bKeNumberProcessors;
 
		//calc Processors
		for (int i = 0; i < m_iNumberProcessors; i++)
		{
			m_PUT[i].dbCurrentTime = Li2Double(m_pSPPI[i].KernelTime) + Li2Double(m_pSPPI[i].UserTime) + 
										Li2Double(m_pSPPI[i].DpcTime) + Li2Double(m_pSPPI[i].InterruptTime) - m_PUT[i].dbOldCurrentTime;
			m_PUT[i].dbIdleTime = Li2Double(m_pSPPI[i].IdleTime) - m_PUT[i].dbOldIdleTime;
 
			// CurrentCpuIdle = IdleTime / SystemTime 
			m_PUT[i].dbIdleTime = m_PUT[i].dbIdleTime / m_PUT[i].dbCurrentTime;
 
			// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors 
			m_PUT[i].dbIdleTime = 100.0 - m_PUT[i].dbIdleTime * 100.0;
 
		}
	}
 
	// store new CPU's idle and system time 
	liOldIdleTime = SysPerfInfo.liIdleTime; 
	liOldSystemTime = SysTimeInfo.liKeSystemTime;
 
	for (int i = 0; i < m_iNumberProcessors; i++)
	{
		m_PUT[i].dbOldCurrentTime = Li2Double(m_pSPPI[i].KernelTime) + Li2Double(m_pSPPI[i].UserTime) + 
										Li2Double(m_pSPPI[i].DpcTime) + Li2Double(m_pSPPI[i].InterruptTime);
 
		m_PUT[i].dbOldIdleTime = Li2Double(m_pSPPI[i].IdleTime);
	}
 
	return dbIdleTime;
}