//------------------------------------------------------------------------------------------------------------------
// getcpuload()
//   directly prints the CPU usage on screen. This function need to be called twice with a minimum of 1 seconds
//   delay (msdn guideline) to display something usefull.
//   Also returns the usage in percent 0-100 where 100 means the system is working at maximum capacity.
//   Note for multiprocessor systems:
//   If one CPU is working at max capacity the result will (if using (_total) for PdhAddCounter() ) show a maximum
//   workload of 50% unless the other CPU(s) is also working at max load. 
//------------------------------------------------------------------------------------------------------------------
int getcpuload()
{
	static PDH_STATUS            status;
	static PDH_FMT_COUNTERVALUE  value;
	static HQUERY                query;
	static HCOUNTER              counter;
	static DWORD                 ret;
	static char                  runonce=1;
	char                         cput=0;

	if(runonce)
	{
		status = PdhOpenQuery(NULL, 0, &query);
		if(status != ERROR_SUCCESS)
		{
			printf("PdhOpenQuery() ***Error: 0x%X\n",status);
			return 0;
		}

		PdhAddCounter(query, TEXT("\\Processor(_Total)\\% Processor Time"),0,&counter); // A total of ALL CPU's in the system
		//PdhAddCounter(query, TEXT("\\Processor(0)\\% Processor Time"),0,&counter);    // For systems with more than one CPU (Cpu0)
		//PdhAddCounter(query, TEXT("\\Processor(1)\\% Processor Time"),0,&counter);    // For systems with more than one CPU (Cpu1)
		runonce=0;
		PdhCollectQueryData(query); // No error checking here
		return 0;
	}

	status = PdhCollectQueryData(query);
	if(status != ERROR_SUCCESS)
	{
		printf("PhdCollectQueryData() ***Error: 0x%X\n",status);
		if(status==PDH_INVALID_HANDLE) 
			printf("PDH_INVALID_HANDLE\n");
		else if(status==PDH_NO_DATA)
			printf("PDH_NO_DATA\n");
		else
			printf("Unknown error\n");
		return 0;
	}

	status = PdhGetFormattedCounterValue(counter, PDH_FMT_DOUBLE | PDH_FMT_NOCAP100 ,&ret, &value);
	if(status != ERROR_SUCCESS)
	{
		printf("PdhGetFormattedCounterValue() ***Error: 0x%X\n",status);
		return 0;
	}
	cput = value.doubleValue;

	printf("\n\nCPU Total usage: %3d%%\n",cput);

	return cput;
}