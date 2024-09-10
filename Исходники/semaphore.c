     /* Thread two calls this method, which wakes up thread one.
      * This method does **NOT** block!
      *
      * Use wakeupOtherThread(TRUE) if one is uncertain as to
      * whether another thread is already waiting.  Do not do:
      *   if ( getIsThreadWaiting() == TRUE ) wakeupOtherThread();
      * As this could lead to a race condition wherein a thread
      * starts waiting after the getIsThreadWaiting() function.
      *
      * The argument name is complex.  But I wanted to be able
      * to use TRUE/TRUE for waitForSignal()/wakeupOtherThread()
      * in the case where waitForSignal() occurs prior to 
      * the wakeupOtherThread().
      *
      * So, use FALSE to report when no other thread is present,
      * and TRUE to prevent such reporting.
      */
status_t
Semaphore::wakeupOtherThread( BOOLEAN theDoNotReportIfNoOtherThread /*=FALSE*/)
{
  lock("Semaphore:wakeupOtherThread");

  setWakeupAlreadyReceivedNoMutex(); /* Race conditions are a bitch! */

  if ( getIsThreadWaitingNoMutex() == FALSE )
  {
    if ( theDoNotReportIfNoOtherThread == FALSE )
    {
      FLUSHALL();
      cerr << "[Semaphore:waitForSignal]  Warning:  "
	   << "No thread is waiting on this Semaphore." << endl;
    }
    unlock("Semaphore::waitForSignal");    
    return FAILURE;
  }

	/* Only doing sem_post if we have a thread waiting... */
  if ( sem_post ( & getSemaphoreDataNoMutex() ) != 0 )
  {
    PERROR ( "[Semaphore:waitForSignal]  Error:  sem_post() failed.   " );
    unlock("Semaphore:wakeupOtherThread");
    return FAILURE;
  }

  unlock("Semaphore:wakeupOtherThread");
  return SUCCESS;
}