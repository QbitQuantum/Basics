RC GHJ::Execute()
{
	RC rc = Initialize();
	if(rc!=SUCCESS)
	{
		return rc;
	} 

	DOUBLE cpuTimeBefore = 0;
	DOUBLE cpuTimeAfter = 0;
	DOUBLE cpuTime = 0;
	StopWatch stwTotalTime;
	StopWatch stwJoinTime;
	StopWatch stwPartitionTime;
	UINT64 totalTime = 0;
	UINT64 partitionTime = 0;
	UINT64 joinTime = 0;

	stwTotalTime.Start();
	stwPartitionTime.Start();
	cpuTimeBefore = GetCpuTime();

	PartitionTable(m_Params.RELATION_R_PATH, m_Params.R_KEY_POS, &m_InBuffer, m_BucketBuffer, m_FileHandle);

	/*************************************************************************/ 

	//再次对桶装配过程中需要的全局变量初始化 
	for(UINT partitionIndex=0; partitionIndex < m_PartitionNum; partitionIndex++)
	{   
		ResetPage(&m_BucketPage[partitionIndex], &m_BucketBuffer[partitionIndex]); 
	}

	PartitionTable(m_Params.RELATION_S_PATH, m_Params.S_KEY_POS, &m_InBuffer, m_BucketBuffer, m_FileHandle);

	partitionTime = stwPartitionTime.NowInMilliseconds();
	stwJoinTime.Start();

	HashJoin(&m_Pool);


	cpuTimeAfter = GetCpuTime(); 
	totalTime = stwTotalTime.NowInMilliseconds();
	joinTime = stwJoinTime.NowInMilliseconds();
	cpuTime = cpuTimeAfter - cpuTimeBefore;


	FILE *fp;   
	CHAR *reportFilePath = new CHAR[MAX_PATH];   
	LPWSTR tempReportPath = new TCHAR[MAX_PATH];
	swprintf(tempReportPath, MAX_PATH, L"%s%s", m_Params.WORK_SPACE_PATH, L"GHJ_Report.csv" ); 
	// convert file path to char  
	size_t  count = wcstombs(reportFilePath, tempReportPath, MAX_PATH); 

	CHAR *reportTitle = "Relation Size,Memory Size,Bucket Size,Partition,Read Buffer Size,Write Buffer Size,Total Execute Time(ms),Partition Time(ms),Join Time(ms),CPU Time\n";
	CHAR *reportContent = new CHAR[1024];
	sprintf(reportContent, "%d,%d,%.f,%d,%d,%d,%lld,%lld,%lld,%.f", 
		m_R_FileSize, 
		m_Params.BUFFER_POOL_SIZE/SSD_PAGE_SIZE, 
		m_BucketSize, 
		m_PartitionNum, 
		m_Params.READ_BUFFER_SIZE/SSD_PAGE_SIZE,
		m_Params.WRITE_BUFFER_SIZE/SSD_PAGE_SIZE, 
		totalTime, 
		partitionTime, 
		joinTime, 
		cpuTime);
	fp=fopen(reportFilePath, "w+b"); 
	fprintf(fp, reportTitle);
	fprintf(fp, reportContent);
	fclose(fp);

	delete reportFilePath;
	delete tempReportPath; 
	delete reportContent;

	//连接结束后 删除所有的临时文件 
	LPWSTR tempBucketName = new TCHAR[MAX_PATH];
	for(UINT partitionIndex=0;partitionIndex < m_PartitionNum;partitionIndex++)
	{
		swprintf_s(tempBucketName, MAX_PATH, L"%s%d%s.tmp", m_Params.WORK_SPACE_PATH, partitionIndex, m_Params.RELATION_R_NO_EXT);
		DeleteFile(tempBucketName);

		swprintf_s(tempBucketName, MAX_PATH, L"%s%d%s.tmp", m_Params.WORK_SPACE_PATH, partitionIndex, m_Params.RELATION_S_NO_EXT);
		DeleteFile(tempBucketName); 
	}

	delete tempBucketName;
	delete m_Pool.data;
	CloseHandle(m_hOutFile);

	ShowMB(L"GHJ done"); 

	return SUCCESS;
}