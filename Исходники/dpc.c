VOID
NTAPI
KiTimerExpiration(IN PKDPC Dpc,
                  IN PVOID DeferredContext,
                  IN PVOID SystemArgument1,
                  IN PVOID SystemArgument2)
{
    ULARGE_INTEGER SystemTime, InterruptTime;
    LARGE_INTEGER Interval;
    LONG Limit, Index, i;
    ULONG Timers, ActiveTimers, DpcCalls;
    PLIST_ENTRY ListHead, NextEntry;
    KIRQL OldIrql;
    PKTIMER Timer;
    PKDPC TimerDpc;
    ULONG Period;
    DPC_QUEUE_ENTRY DpcEntry[MAX_TIMER_DPCS];
    PKSPIN_LOCK_QUEUE LockQueue;
#ifdef CONFIG_SMP
    PKPRCB Prcb = KeGetCurrentPrcb();
#endif

    /* Disable interrupts */
    _disable();

    /* Query system and interrupt time */
    KeQuerySystemTime((PLARGE_INTEGER)&SystemTime);
    InterruptTime.QuadPart = KeQueryInterruptTime();
    Limit = KeTickCount.LowPart;

    /* Bring interrupts back */
    _enable();

    /* Get the index of the timer and normalize it */
    Index = PtrToLong(SystemArgument1);
    if ((Limit - Index) >= TIMER_TABLE_SIZE)
    {
        /* Normalize it */
        Limit = Index + TIMER_TABLE_SIZE - 1;
    }

    /* Setup index and actual limit */
    Index--;
    Limit &= (TIMER_TABLE_SIZE - 1);

    /* Setup accounting data */
    DpcCalls = 0;
    Timers = 24;
    ActiveTimers = 4;

    /* Lock the Database and Raise IRQL */
    OldIrql = KiAcquireDispatcherLock();

    /* Start expiration loop */
    do
    {
        /* Get the current index */
        Index = (Index + 1) & (TIMER_TABLE_SIZE - 1);

        /* Get list pointers and loop the list */
        ListHead = &KiTimerTableListHead[Index].Entry;
        while (ListHead != ListHead->Flink)
        {
            /* Lock the timer and go to the next entry */
            LockQueue = KiAcquireTimerLock(Index);
            NextEntry = ListHead->Flink;

            /* Get the current timer and check its due time */
            Timers--;
            Timer = CONTAINING_RECORD(NextEntry, KTIMER, TimerListEntry);
            if ((NextEntry != ListHead) &&
                (Timer->DueTime.QuadPart <= InterruptTime.QuadPart))
            {
                /* It's expired, remove it */
                ActiveTimers--;
                KiRemoveEntryTimer(Timer);

                /* Make it non-inserted, unlock it, and signal it */
                Timer->Header.Inserted = FALSE;
                KiReleaseTimerLock(LockQueue);
                Timer->Header.SignalState = 1;

                /* Get the DPC and period */
                TimerDpc = Timer->Dpc;
                Period = Timer->Period;

                /* Check if there's any waiters */
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
                if (TimerDpc)
                {
#ifdef CONFIG_SMP
                    /* 
                     * If the DPC is targeted to another processor,
                     * then insert it into that processor's DPC queue
                     * instead of delivering it now.
                     * If the DPC is a threaded DPC, and the current CPU
                     * has threaded DPCs enabled (KiExecuteDpc is actively parsing DPCs),
                     * then also insert it into the DPC queue for threaded delivery,
                     * instead of doing it here.
                     */
                    if (((TimerDpc->Number >= MAXIMUM_PROCESSORS) &&
                        ((TimerDpc->Number - MAXIMUM_PROCESSORS) != Prcb->Number)) ||
                        ((TimerDpc->Type == ThreadedDpcObject) && (Prcb->ThreadDpcEnable)))
                    {
                        /* Queue it */
                        KeInsertQueueDpc(TimerDpc,
                                         UlongToPtr(SystemTime.LowPart),
                                         UlongToPtr(SystemTime.HighPart));
                    }
                    else
#endif
                    {
                        /* Setup the DPC Entry */
                        DpcEntry[DpcCalls].Dpc = TimerDpc;
                        DpcEntry[DpcCalls].Routine = TimerDpc->DeferredRoutine;
                        DpcEntry[DpcCalls].Context = TimerDpc->DeferredContext;
                        DpcCalls++;
                        ASSERT(DpcCalls < MAX_TIMER_DPCS);
                    }
                }

                /* Check if we're done processing */
                if (!(ActiveTimers) || !(Timers))
                {
                    /* Release the dispatcher while doing DPCs */
                    KiReleaseDispatcherLock(DISPATCH_LEVEL);

                    /* Start looping all DPC Entries */
                    for (i = 0; DpcCalls; DpcCalls--, i++)
                    {
                        /* Call the DPC */
                        DpcEntry[i].Routine(DpcEntry[i].Dpc,
                                            DpcEntry[i].Context,
                                            UlongToPtr(SystemTime.LowPart),
                                            UlongToPtr(SystemTime.HighPart));
                    }

                    /* Reset accounting */
                    Timers = 24;
                    ActiveTimers = 4;

                    /* Lock the dispatcher database */
                    KiAcquireDispatcherLock();
                }
            }
            else
            {
                /* Check if the timer list is empty */
                if (NextEntry != ListHead)
                {
                    /* Sanity check */
                    ASSERT(KiTimerTableListHead[Index].Time.QuadPart <=
                           Timer->DueTime.QuadPart);

                    /* Update the time */
                    _disable();
                    KiTimerTableListHead[Index].Time.QuadPart =
                        Timer->DueTime.QuadPart;
                    _enable();
                }

                /* Release the lock */
                KiReleaseTimerLock(LockQueue);

                /* Check if we've scanned all the timers we could */
                if (!Timers)
                {
                    /* Release the dispatcher while doing DPCs */
                    KiReleaseDispatcherLock(DISPATCH_LEVEL);

                    /* Start looping all DPC Entries */
                    for (i = 0; DpcCalls; DpcCalls--, i++)
                    {
                        /* Call the DPC */
                        DpcEntry[i].Routine(DpcEntry[i].Dpc,
                                            DpcEntry[i].Context,
                                            UlongToPtr(SystemTime.LowPart),
                                            UlongToPtr(SystemTime.HighPart));
                    }

                    /* Reset accounting */
                    Timers = 24;
                    ActiveTimers = 4;

                    /* Lock the dispatcher database */
                    KiAcquireDispatcherLock();
                }

                /* Done looping */
                break;
            }
        }
    } while (Index != Limit);

    /* Verify the timer table, on debug builds */
    if (KeNumberProcessors == 1) KiCheckTimerTable(InterruptTime);

    /* Check if we still have DPC entries */
    if (DpcCalls)
    {
        /* Release the dispatcher while doing DPCs */
        KiReleaseDispatcherLock(DISPATCH_LEVEL);

        /* Start looping all DPC Entries */
        for (i = 0; DpcCalls; DpcCalls--, i++)
        {
            /* Call the DPC */
            DpcEntry[i].Routine(DpcEntry[i].Dpc,
                                DpcEntry[i].Context,
                                UlongToPtr(SystemTime.LowPart),
                                UlongToPtr(SystemTime.HighPart));
        }

        /* Lower IRQL if we need to */
        if (OldIrql != DISPATCH_LEVEL) KeLowerIrql(OldIrql);
    }
    else
    {
        /* Unlock the dispatcher */
        KiReleaseDispatcherLock(OldIrql);
    }
}