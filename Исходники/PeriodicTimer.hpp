 void stop()
 {
   if (isRunning()) {
     DeleteTimerQueueTimer(mTimerQueue, mTimerHandle, NULL);
     mTimerHandle = NULL;
     mTimerQueue = NULL;
   }
 }