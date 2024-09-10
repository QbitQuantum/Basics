VOID
NTAPI
KiDispatchInterrupt(VOID)
{
    PKIPCR Pcr = (PKIPCR)KeGetPcr();
    PKPRCB Prcb = &Pcr->PrcbData;
    PVOID OldHandler;
    PKTHREAD NewThread, OldThread;

    /* Disable interrupts */
    _disable();

    /* Check for pending timers, pending DPCs, or pending ready threads */
    if ((Prcb->DpcData[0].DpcQueueDepth) ||
        (Prcb->TimerRequest) ||
        (Prcb->DeferredReadyListHead.Next))
    {
        /* Switch to safe execution context */
        OldHandler = Pcr->NtTib.ExceptionList;
        Pcr->NtTib.ExceptionList = EXCEPTION_CHAIN_END;

        /* Retire DPCs while under the DPC stack */
        //KiRetireDpcListInDpcStack(Prcb, Prcb->DpcStack);
        // FIXME!!! //
        KiRetireDpcList(Prcb);

        /* Restore context */
        Pcr->NtTib.ExceptionList = OldHandler;
    }

    /* Re-enable interrupts */
    _enable();

    /* Check for quantum end */
    if (Prcb->QuantumEnd)
    {
        /* Handle quantum end */
        Prcb->QuantumEnd = FALSE;
        KiQuantumEnd();
    }
    else if (Prcb->NextThread)
    {       
        /* Capture current thread data */
        OldThread = Prcb->CurrentThread;
        NewThread = Prcb->NextThread;

        /* Set new thread data */
        Prcb->NextThread = NULL;
        Prcb->CurrentThread = NewThread;

        /* The thread is now running */
        NewThread->State = Running;
        OldThread->WaitReason = WrDispatchInt;

        /* Make the old thread ready */
        KxQueueReadyThread(OldThread, Prcb);

        /* Swap to the new thread */
        KiSwapContext(APC_LEVEL, OldThread);
    }
}