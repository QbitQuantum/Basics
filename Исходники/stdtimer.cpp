static
void
initTimer( HANDLE gDoneEvent )
{
    HANDLE hTimer = NULL;
    HANDLE hTimerQueue = NULL;
    int arg = 123;

    // Use an event object to track the TimerRoutine execution
    gDoneEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    if ( ! gDoneEvent )
    {
        printf( "CreateEvent failed (%d)\n", GetLastError() );
        //         return 1;
    }

    // Create the timer queue.
    hTimerQueue = CreateTimerQueue();
    if ( ! hTimerQueue )
    {
        printf( "CreateTimerQueue failed (%d)\n", GetLastError() );
        //         return 2;
    }

    // Set a timer to call the timer routine in 10 seconds.
    if ( ! CreateTimerQueueTimer( &hTimer, hTimerQueue,
                                  (WAITORTIMERCALLBACK)&StandardTimer::check,
                                  &gDoneEvent , TIMEDELTA, TIMEDELTA, 0 ) )
    {
        printf( "CreateTimerQueueTimer failed (%d)\n", GetLastError() );
        //         return 3;
    }

    // TODO: Do other useful work here

    printf( "Call timer routine in 10 seconds...\n" );

    //     // Wait for the timer-queue thread to complete using an event
    //     // object. The thread will signal the event at that time.

    //     if (WaitForSingleObject(gDoneEvent, INFINITE) != WAIT_OBJECT_0)
    //         printf("WaitForSingleObject failed (%d)\n", GetLastError());

    //     // Delete all timers in the timer queue.
    //     if (!DeleteTimerQueue(hTimerQueue))
    //         printf("DeleteTimerQueue failed (%d)\n", GetLastError());
}