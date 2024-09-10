void GProcThrd_Create(void)
{
	if(bGProcThrdThreadIsActive)
		return;

	DWORD dwNP = GWkrThrd_GetNumberOfProcessors();
	
	if(!dwGProcThrdThreadNumber)
		dwGProcThrdThreadNumber = dwNP * 2 + 2;

	if(dwGProcThrdThreadNumber < dwNP)
		dwGProcThrdThreadNumber = dwNP;

	hGProcThrdThreadCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, dwGProcThrdThreadNumber);
	if(NULL == hGProcThrdThreadCompletionPort)
	{
		GLog_Write("GProcThrd_Create：完成端口句柄创建失败");
		return;
	}
	
	pGProcThrdThreadAddr = (PGTHREAD)GMem_Alloc(dwGProcThrdThreadNumber * sizeof(GTHREAD));
	if(!pGProcThrdThreadAddr)
	{
		dwGProcThrdThreadNumber = 0;
		CloseHandle(hGProcThrdThreadCompletionPort);
		GLog_Write("GProcThrd_Create：从GMem分配工作者内存失败");
		return;
	}

	DWORD i;
 	PGTHREAD pThread;
	
	pThread = pGProcThrdThreadAddr;
	for(i = 0; i < dwGProcThrdThreadNumber; i++)
	{
		GThrd_CreateThread(pThread, GTHREAD_TYPE_IOCP, "处理者", &GProcesserThreadProc);
		if(!pThread->dwThreadId)
		{
			GLog_Write("GProcThrd_Create：创建处理者线程失败");
			return;
		}
		pThread = pThread + 1;
	}
	bGProcThrdThreadIsActive = TRUE;		
}