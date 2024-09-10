DWORD QueueGet (QUEUE_OBJECT *q, PVOID msg, DWORD msize, DWORD MaxWait)
{
    AcquireSRWLockExclusive (&q->qGuard);
    if (q->msgArray == NULL) return 1;  /* Queue has been destroyed */

    while (QueueEmpty (q))
    {
        if (!SleepConditionVariableSRW (&q->qNe, &q->qGuard, INFINITE, 0))
            ReportError(_T("QueueGet failed. SleepConditionVariableCS."), 1, TRUE);
    }

    /* remove the message from the queue */
    QueueRemove (q, msg, msize);
    /* Signal that the queue is not full as we've removed a message */
    WakeConditionVariable (&q->qNf);
    ReleaseSRWLockExclusive (&q->qGuard);
    return 0;
}