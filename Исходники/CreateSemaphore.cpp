int __cdecl main (int argc, char **argv) 
{

    BufferStructure Buffer, *pBuffer;

    pBuffer = &Buffer;
   
    if(0 != (PAL_Initialize(argc, argv)))
    {
        return ( FAIL );
    }

    /*
     * Create Semaphores
     */
    hSemaphoreM = CreateSemaphoreW (
	NULL,            
	1,               
	1,               
	NULL);           

    if ( NULL == hSemaphoreM ) 
    {
	Fail ( "hSemaphoreM = CreateSemaphoreW () - returned NULL\n"
	       "Failing Test.\nGetLastError returned %d\n", GetLastError());
    }


    hSemaphoreE = CreateSemaphoreW (
	NULL,            
	_BUF_SIZE ,      
	_BUF_SIZE ,      
	NULL);           

    if ( NULL == hSemaphoreE ) 
    {
	Fail ( "hSemaphoreE = CreateSemaphoreW () - returned NULL\n"
	       "Failing Test.\nGetLastError returned %d\n", GetLastError());
    }
    
    hSemaphoreF = CreateSemaphoreW (
	NULL,            
	0,               
	_BUF_SIZE ,      
	NULL);           

    if ( NULL == hSemaphoreF ) 
    {
	Fail ( "hSemaphoreF = CreateSemaphoreW () - returned NULL\n"
	       "Failing Test.\nGetLastError returned %d\n", GetLastError());
    }


    /* 
     * Initialize Buffer
     */
    pBuffer->writeIndex = pBuffer->readIndex = 0;

    /* 
     * Create Consumer
     */
    hThread = CreateThread(
	NULL,            
	0,               
	consumer,        
	&Buffer,         
	0,               
	&dwThreadId);    

    if ( NULL == hThread ) 
    {
	Fail ( "CreateThread() returned NULL.  Failing test.\n"
	       "GetLastError returned %d\n", GetLastError()); 
    }
    
    /* 
     * Start producing 
     */
    producer(pBuffer);
    
    /*
     * Wait for consumer to complete
     */
    WaitForSingleObject (hThread, INFINITE);

    /* 
     * Compare items produced vs. items consumed
     */
    if ( 0 != strncmp (producerItems, consumerItems, PRODUCTION_TOTAL) )
    {
	Fail("The producerItems string %s\n and the consumerItems string "
	     "%s\ndo not match. This could be a problem with the strncmp()"
	     " function\n FailingTest\nGetLastError() returned %d\n", 
	     producerItems, consumerItems, GetLastError());
    }

    Trace ("producerItems and consumerItems arrays match.  All %d\nitems "
	   "were produced and consumed in order.\nTest passed.\n",
	   PRODUCTION_TOTAL);

    PAL_Terminate();
    return ( PASS );

}