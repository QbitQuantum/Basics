DWORD QueuePut (QUEUE_OBJECT *q, PVOID msg, DWORD mSize, DWORD maxWait)
{
    WaitForSingleObject (q->qGuard, INFINITE);
    if (q->msgArray == NULL) return 1;  /* Queue has been destroyed */
    while (QueueFull (q))
    {
        SignalObjectAndWait (q->qGuard, q->qNf, INFINITE, FALSE);
        WaitForSingleObject (q->qGuard, INFINITE);
    }
    /* Put the message in the queue */
    QueueInsert (q, msg, mSize);
    /* Signal that the queue is not empty as we've inserted a message */
    PulseEvent (q->qNe);
    ReleaseMutex (q->qGuard);

    return 0;
}