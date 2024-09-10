ULONG UpdateDotNetTraceInfoWithTimeout(
    __in PASMPAGE_CONTEXT Context,
    __in BOOLEAN ClrV2,
    __in_opt PLARGE_INTEGER Timeout
    )
{
    HANDLE threadHandle;

    // ProcessDotNetTrace is not guaranteed to complete within any period of time, because
    // the target process might terminate before it writes the DCStartComplete_V1 event.
    // If the timeout is reached, the trace handle is closed, forcing ProcessTrace to stop
    // processing.

    Context->TraceClrV2 = ClrV2;
    Context->TraceResult = 0;
    Context->TraceHandleActive = 0;
    Context->TraceHandle = 0;

    threadHandle = PhCreateThread(0, UpdateDotNetTraceInfoThreadStart, Context);

    if (NtWaitForSingleObject(threadHandle, FALSE, Timeout) != STATUS_WAIT_0)
    {
        // Timeout has expired. Stop the trace processing if it's still active.
        // BUG: This assumes that the thread is in ProcessTrace. It might still be
        // setting up though!
        if (_InterlockedExchange(&Context->TraceHandleActive, 0) == 1)
        {
            CloseTrace(Context->TraceHandle);
        }

        NtWaitForSingleObject(threadHandle, FALSE, NULL);
    }

    NtClose(threadHandle);

    return Context->TraceResult;
}