void CSystemInfo::GetWinSystemInfo()
{
	HQUERY	hQuery = NULL ;
	char   szPathBuffer[MAX_PATH];

	if( PdhOpenQuery(NULL, NULL, &hQuery) != ERROR_SUCCESS )
		return ;

	ZeroMemory(szPathBuffer, sizeof(szPathBuffer));

	PDH_FMT_COUNTERVALUE  fmtValue;

	//CPU使用率
//	strcpy(szPathBuffer, "\\Processor(_Total)\\% Processor Time");
	strcpy(szPathBuffer, "\\Processor(0)\\% Processor Time");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nCPU = fmtValue.longValue ;
	}

	//进程数
	strcpy(szPathBuffer, "\\System\\Processes");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nProcessNumber = fmtValue.longValue;
	}

	//线程数
	strcpy(szPathBuffer, "\\System\\Threads");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nThreadNumber =fmtValue.longValue;
	}

	strcpy(szPathBuffer, "\\Memory\\Commit Limit");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nMemoryTotal =fmtValue.longValue;
	}

	strcpy(szPathBuffer, "\\Memory\\Committed Bytes");
	if( GetSysItemInfo(hQuery, szPathBuffer,  PDH_FMT_LONG, fmtValue) )
	{
		nUserMemory =fmtValue.longValue;
	}

	PdhCloseQuery(hQuery);
}