 ~TimerQ() {
   if (TimerQueue)
     DeleteTimerQueueEx(TimerQueue, NULL);
 };