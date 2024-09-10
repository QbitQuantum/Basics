void  PALAPI Run_Thread (LPVOID lpParam)
{
    unsigned int i = 0;
    DWORD dwWaitResult; 

    struct statistics stats;
    DWORD dwStartTime;

	stats.relationId = RELATION_ID;
    stats.processId = USE_PROCESS_COUNT;
    stats.operationsFailed = 0;
    stats.operationsPassed = 0;
    stats.operationsTotal  = 0;
    stats.operationTime    = 0;

    int Id=(int)lpParam;
    
    dwWaitResult = WaitForSingleObject( 
                            StartTestsEvHandle,   // handle to mutex
                            TIMEOUT);  

    if(dwWaitResult != WAIT_OBJECT_0)
    {
        Trace("Error while waiting for StartTest Event@ thread %d\n", Id);
        testStatus = FAIL;
    }

    dwStartTime = GetTickCount();

    for( i = 0; i < REPEAT_COUNT; i++ )
    {
        dwWaitResult = WaitForSingleObject( 
                            hMutexHandle,   // handle to mutex
                            TIMEOUT);  

        if(dwWaitResult != WAIT_OBJECT_0)
        {
//            Trace("Error while waiting for onject @ thread %d, # iter %d, Error Returned [%d]\n", Id, i, GetLastError());
            stats.operationsFailed += 1;
            stats.operationsTotal  += 1;
            testStatus = FAIL;
            continue;
        }
        if (! ReleaseMutex(hMutexHandle)) 
        { 
            // Deal with error.
//            Trace("Error while releasing mutex @ thread %d # iter %d\n", Id, i);
            stats.operationsFailed += 1;
            stats.operationsTotal  += 1;
            // Probably need to have while true loop to attempt to release mutex...
            testStatus = FAIL;
            continue;
        } 
    
        stats.operationsTotal  += 1;
        stats.operationsPassed += 1;  
//        Trace("Successs while releasing mutex @ iteration %d -> thread %d -> Process count %d\n", i, Id, USE_PROCESS_COUNT);
        
    }
    stats.operationTime = GetTimeDiff(dwStartTime); 
    if(resultBuffer->LogResult(Id, (char *)&stats))
    {
        Fail("Error:%d: while writing to shared memory, Thread Id is[%d] and Process id is [%d]\n", GetLastError(), Id, USE_PROCESS_COUNT);
    }
}