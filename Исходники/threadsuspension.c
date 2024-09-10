/* 
 * Main Test Case worker thread which will suspend and resume all other worker threads
 */
DWORD
PALAPI 
suspendandresumethreads( LPVOID lpParam )
{
       
	unsigned int loopcount = REPEAT_COUNT;
	int Id=(int)lpParam;
	unsigned int i,j,k;
	DWORD dwStart;
	 DWORD dwWaitResult=0;
	 DWORD dwLastError = 0;
	struct statistics stats;
	  struct statistics* buffer;

	  

	//Initialize the Statistics Structure
	stats.relationId = RELATION_ID;
	stats.processId = USE_PROCESS_COUNT;
	stats.operationsFailed = 0;
	stats.operationsPassed = 0;
	stats.operationsTotal  = 0;
	stats.operationTime    = 0;

	
	
	//Wait for event to signal to start test	
	WaitForSingleObject(g_hEvent,INFINITE);
	if (WAIT_OBJECT_0 != dwWaitResult)
	{
		Fail ("suspendandresumethreads: Wait for Single Object (g_hEvent) failed.  Failing test.\n"
	    "GetLastError returned %d\n", GetLastError()); 
	}

	 
	//Capture Start Import 
	dwStart = GetTickCount();

	for(i = 0; i < loopcount; i++)
	{

		failFlag = false;
		
		//Suspend Worker Threads
		for (k=0;k<WORKER_THREAD_MULTIPLIER_COUNT;k++)
		{
			for (j=0;j<4;j++)
			{
				if (-1 == SuspendThread(hThread[j][k]))
				{
					//If the operation indicate failure
					failFlag = true;
				}
			}
		}


		//Resume Worker Threads
		for (k=0;k<WORKER_THREAD_MULTIPLIER_COUNT;k++)
		{
			for (j=0;j<4;j++)
			{

				//Only suspend if not already in suspended state
				
				if (-1 == ResumeThread(hThread[j][k]))
				{
					//If the operation indicate failure
					failFlag = true;
				}
			
			}
		}


		//Check for Fail Flag.  If set increment number of failures
		// If Fail flag not set then increment number of operations and number of passe
		if (failFlag == true) 
			{
				stats.operationsFailed++;
			}
		else
			{
				stats.operationsPassed +=1;
		
			}
		stats.operationsTotal  +=1;
		
	}

	stats.operationTime = GetTickCount() - dwStart;

	/*Trace("\n\n\n\nOperation Time: %d milliseconds\n", stats.operationTime);
	Trace("Operation Passed: %d\n", stats.operationsPassed);
	Trace("Operation Total: %d\n", stats.operationsTotal);
	Trace("Operation Failed: %d\n", stats.operationsFailed);
		*/
	if(resultBuffer->LogResult(Id, (char *)&stats))
    	{
        	Fail("Error while writing to shared memory, Thread Id is[%d] and Process id is [%d]\n", Id, USE_PROCESS_COUNT);
    	}

	 buffer = (struct statistics *)resultBuffer->getResultBuffer(Id);
       //Trace("\n%d,%d,%d,%lu\n", buffer->operationsFailed, buffer->operationsPassed, buffer->operationsTotal, buffer->operationTime );
            
	
    return 0;
}