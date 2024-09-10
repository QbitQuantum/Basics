NTSTATUS
NTAPI
ConMgrDisplayCurrentChannel(VOID)
{
    NTSTATUS Status;
    BOOLEAN HasRedraw;

    /* Make sure the lock is held */
    SacAssertMutexLockHeld();

    /* Check if we can redraw */
    Status = ChannelHasRedrawEvent(CurrentChannel, &HasRedraw);
    if (NT_SUCCESS(Status))
    {
        /* Enable writes */
        _InterlockedExchange(&CurrentChannel->WriteEnabled, 1);
        if (HasRedraw)
        {
            /* If we can redraw, set the event */
            ChannelSetRedrawEvent(CurrentChannel);
        }

        /* Flush the output */
        Status = ChannelOFlush(CurrentChannel);
    }

    /* All done, return the status */
    return Status;
}