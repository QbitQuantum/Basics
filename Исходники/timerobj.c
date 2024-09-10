BOOLEAN
FASTCALL
KiSignalTimer(IN PKTIMER Timer)
{
    BOOLEAN RequestInterrupt = FALSE;
    PKDPC Dpc = Timer->Dpc;
    ULONG Period = Timer->Period;
    LARGE_INTEGER Interval, SystemTime;
    DPRINT("KiSignalTimer(): Timer %p\n", Timer);

    /* Set default values */
    Timer->Header.Inserted = FALSE;
    Timer->Header.SignalState = TRUE;

    /* Check if the timer has waiters */
    if (!IsListEmpty(&Timer->Header.WaitListHead))
    {
        /* Check the type of event */
        if (Timer->Header.Type == TimerNotificationObject)
        {
            /* Unwait the thread */
            KxUnwaitThread(&Timer->Header, IO_NO_INCREMENT);
        }
        else
        {
            /* Otherwise unwait the thread and signal the timer */
            KxUnwaitThreadForEvent((PKEVENT)Timer, IO_NO_INCREMENT);
        }
    }

    /* Check if we have a period */
    if (Period)
    {
        /* Calculate the interval and insert the timer */
        Interval.QuadPart = Int32x32To64(Period, -10000);
        while (!KiInsertTreeTimer(Timer, Interval));
    }

    /* Check if we have a DPC */
    if (Dpc)
    {
        /* Insert it in the queue */
        KeQuerySystemTime(&SystemTime);
        KeInsertQueueDpc(Dpc,
                         ULongToPtr(SystemTime.LowPart),
                         ULongToPtr(SystemTime.HighPart));
        RequestInterrupt = TRUE;
    }

    /* Return whether we need to request a DPC interrupt or not */
    return RequestInterrupt;
}