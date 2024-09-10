DWORD QueueGet (QUEUE_OBJECT *q, PVOID msg, DWORD msize, DWORD MaxWait)
{
    DWORD TotalWaitTime = 0;
    BOOL TimedOut = FALSE;

    WaitForSingleObject (q->qGuard, INFINITE);
    if (q->msgArray == NULL) return 1;  /* Queue has been destroyed */

    while (QueueEmpty (q) && !TimedOut)
    {
        ReleaseMutex (q->qGuard);
        WaitForSingleObject (q->qNe, CV_TIMEOUT);
        if (MaxWait != INFINITE)
        {
            TotalWaitTime += CV_TIMEOUT;
            TimedOut = (TotalWaitTime > MaxWait);
        }
        WaitForSingleObject (q->qGuard, INFINITE);
    }
    /* remove the message from the queue */
    if (!TimedOut) QueueRemove (q, msg, msize);
    /* Signal that the queue is not full as we've removed a message */
    PulseEvent (q->qNf);
    ReleaseMutex (q->qGuard);

    return TimedOut ? WAIT_TIMEOUT : 0;
}