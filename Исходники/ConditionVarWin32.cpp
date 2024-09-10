void sys::ConditionVarDataWin32::waitImpl(HANDLE externalMutex)
{
    // Mark that we're no longer waiting
    // If we woke up via broadcast(), determine if we're the last waiter
    bool lastWaiter;
    {
        const ScopedCriticalSection lock(mNumWaitersCS);
        --mNumWaiters;
        lastWaiter = (mWasBroadcast && mNumWaiters == 0);
    }

    if (lastWaiter)
    {
        // Atomically signals the mWaitersAreDone event and waits until it can
        // acquire the external mutex.  This is used to ensure fairness.
        /// @note  Fairness relies on the fact that Windows NT mutex requests
        ///        are queued in FIFO order.  As a result, all waiting threads
        ///        will acquire the external mutex before any of them can
        ///        reacquire it a second time.
        ///        Need the atomicity of SignalObjectAndWait() here to ensure
        ///        that the last thread gets his chance to wait on the
        ///        external mutex.
        SignalObjectAndWait(mWaitersAreDone, externalMutex, INFINITE, FALSE);
    }
    else
    {
        // We need to wait until we get the external mutex back
        WaitForSingleObject(externalMutex, INFINITE);
    }
}