/**
 * main
 *
 * executable entry point
 */
INT __cdecl main( INT argc, CHAR **argv )
{
    DWORD IDThread;

    int i;

    /* PAL initialization */
    if( (PAL_Initialize(argc, argv)) != 0 )
    {
        return( FAIL );
    }

    /* set the thread priority of the main to the highest possible value
       this will give the chance to the main thread to create all the
       other threads */
    if(!SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL))
    {
        DWORD dwError;

        dwError = GetLastError();
        Fail( "Unexpected SetThreadPriority() failure with error %d\n",
			  dwError );
    }

    printf( "Launching multiple threads, please wait...\n" );

    /* Create multiple threads. */
    for( i = 0; i < NUM_THREADS; i++ )
    {
        hThread[i] = CreateThread( NULL,         /* no security attributes */
                                   0,            /* use default stack size */
          (LPTHREAD_START_ROUTINE) ThreadFunc,   /* thread function */
                          (LPVOID) i,            /* pass thread index as */
                                                 /* function argument */
                                   CREATE_SUSPENDED, /* create suspended */
                                   &IDThread );  /* returns thread identifier */

        /* Check the return value for success. */
        if( hThread[i] == NULL )
        {
	        /*ERROR */
            DWORD dwError = GetLastError();
            Fail( "Unexpected CreateThread error %d\n",
                  dwError );
        }

        ResumeThread(hThread[i]);
    }

    /* Wait for all threads to finish */
    for (i = 0; i < NUM_THREADS; i++)
    {
        DWORD dwRet;

        dwRet = WaitForSingleObject( hThread[i], INFINITE );

        if( dwRet == WAIT_FAILED )
        {
            /* ERROR */
            DWORD dwError = GetLastError();
            Fail( "Unexpected WaitForSingleObject error %d\n",
                  dwError );
        }
    }

    /* make sure the thread processing times match the priorities */
    for( i=NUM_THREADS-1; i > 0; i-- )
    {
        if( nElapsedTime[i] >= nElapsedTime[i-1] )
        {
            /*
             * a lower-priority thread finished faster than a lower-priority
             * thread -- this shouldn't happen if the dummy thread function
             * is non-trivial in length
             */
            Fail( "Failed: processing time doesn't match thread priority\n" );
        }
    }

    PAL_Terminate();
    return PASS;
}