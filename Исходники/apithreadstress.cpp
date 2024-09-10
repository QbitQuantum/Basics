void APIThreadStress::SyncThreadStress()
{
    APIThreadStress *pThis = (APIThreadStress *) ClrFlsGetValue(TlsIdx_StressThread);

    if (pThis != NULL)
    {
        LOG((LF_SYNC, LL_INFO1000, "Syncing stress operation on thread %d\n", GetCurrentThreadId()));

        ::ResetEvent(pThis->m_syncEvent);

        if (InterlockedDecrement(&pThis->m_runCount) == 0)
            ::SetEvent(pThis->m_syncEvent);
        else
            WaitForSingleObjectEx(pThis->m_syncEvent, INFINITE, FALSE);
        InterlockedIncrement(&pThis->m_runCount);

        LOG((LF_SYNC, LL_INFO1000, "Resuming stress operation on thread %d\n", GetCurrentThreadId()));
    }
}