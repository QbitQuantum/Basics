static int WINAPI
sample_load(void *thr_data)
{
	HQUERY hQuery = NULL;
	HCOUNTER hCounterQueueLength, *hCounterCpuLoad;
	int nextsample = 0, i, exit_status = 0;
	PDH_STATUS pdhStatus;
	PDH_FMT_COUNTERVALUE counterval;
	long queuelen;
	double cpuload;
	char counterpath[35];

	EnterCriticalSection(&cs);
	for (i=0; i < NUM_SAMPLES; i++) {
		samples[i].load = 0;
		samples[i].sampletime = (time_t)0;
	}
	LeaveCriticalSection(&cs);

	if(!pdhAddCounterPtr)
	{
		if(!pdhModule)
		{
			pdhModule = GetModuleHandle(TEXT("pdh"));
		}

		if(pdhModule)
			pdhAddCounterPtr = (PdhAddCounterPtr)GetProcAddress(pdhModule, "PdhAddEnglishCounterA");
		
		if(!pdhAddCounterPtr)
			pdhAddCounterPtr = PdhAddCounter;
	}

	pdhStatus = PdhOpenQuery(NULL, 0, &hQuery);
	if (pdhStatus != ERROR_SUCCESS) {
		/* dprintf(D_ALWAYS, "PdhOpenQuery returns 0x%x\n", 
			    (int)pdhStatus); */
		return pdhStatus;
	}

	pdhStatus = pdhAddCounterPtr(hQuery, 
							  "\\System\\Processor Queue Length", 
							  0, &hCounterQueueLength);
	
	if (pdhStatus != ERROR_SUCCESS) {
		/* dprintf(D_ALWAYS, "PdhAddCounter returns 0x%x\n", 
						   (int)pdhStatus); */
		PdhCloseQuery(hQuery);
		return pdhStatus;
	}
	hCounterCpuLoad = (HCOUNTER *) malloc(sizeof(HCOUNTER)*ncpus);
	ASSERT( hCounterCpuLoad );
	for (i=0; i < ncpus; i++) {
		sprintf(counterpath, "\\Processor(%d)\\%% Processor Time", i);
		pdhStatus = pdhAddCounterPtr(hQuery, counterpath, 0, 
								  hCounterCpuLoad+i);
		
		if (pdhStatus != ERROR_SUCCESS) {
			/* dprintf(D_ALWAYS, "PdhAddCounter returns 0x%x\n", 
							   (int)pdhStatus); */
			PdhCloseQuery(hQuery);
			return pdhStatus;
		}
	}

	while (1) {

		pdhStatus = PdhCollectQueryData(hQuery);
		if (pdhStatus != ERROR_SUCCESS) {
			/* dprintf(D_ALWAYS, "PdhCollectQueryData returns 0x%x\n", 
							   (int)pdhStatus); */
			exit_status = 4;
			break;
		}

		pdhStatus = PdhGetFormattedCounterValue(hCounterQueueLength, 
												PDH_FMT_LONG,
												NULL, &counterval);
		if (pdhStatus != ERROR_SUCCESS) {
			/* dprintf(D_ALWAYS, "PdhGetFormattedCounterValue returns 0x%x\n",
							   (int)pdhStatus); */
			exit_status = 5;
			break;
		}
		queuelen = counterval.longValue;
		cpuload = 0.0;
		for (i=0; i < ncpus; i++) {
			pdhStatus = PdhGetFormattedCounterValue(hCounterCpuLoad[i], 
													PDH_FMT_DOUBLE,
													NULL, &counterval);
			if (pdhStatus != ERROR_SUCCESS) {
				/* dprintf(D_ALWAYS, "PdhGetFormattedCounterValue returns 0x%x\n",
								   (int)pdhStatus); */
				exit_status = 6;
				break;
			}
			cpuload += counterval.doubleValue/100.0;
		}

		EnterCriticalSection(&cs);
		/* 
		** Here is the code to simulate Unix style load average on Win32.
		** If the system is not fully utilized, the length of the processor
		** queue should be near 0.  When the system is fully utilized,
		** we must discount two items on the processor queue: the system
		** thread and the thread which we displaced to take our measurement.
		** If there are more than 2 items on the queue, we want to add this
		** to our load average to show the additional load on the system.
		*/
		if (queuelen > 2) {
			samples[nextsample].load = cpuload + queuelen - 2;
		} else {
			samples[nextsample].load = cpuload;
		}
		samples[nextsample].sampletime = time(NULL);
		LeaveCriticalSection(&cs);
		nextsample++;
		nextsample %= NUM_SAMPLES;

		Sleep(SAMPLE_INTERVAL);
	}

	// we encountered a problem, so clean up everything and exit.
	for (i=0; i<ncpus;i++) { PdhRemoveCounter(hCounterCpuLoad[i]); }
	free(hCounterCpuLoad);
	PdhCloseQuery(hQuery);

	return exit_status;	
}