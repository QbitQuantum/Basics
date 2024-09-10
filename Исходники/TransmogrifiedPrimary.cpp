    /// <summary>
    ///     Wait for a proxy to appear on the completion list
    /// </summary>
    UMSThreadProxy * TransmogrifiedPrimary::WaitForBlockedThread(UMSThreadProxy * pProxy)
    {
        //
        // While waiting on the completion list we need to poll proxies for execution, if any.
        // This is required because the current proxy could be blocked for a resource that is
        // held by a UT that is suspended (and needs to be polled for subsequent execution).
        //
        const int maxCount = 2;
        HANDLE hObjects[maxCount];
        int count = 0;
        hObjects[count++] = m_poller.GetEvent();
        hObjects[count++] = m_hCompletionListEvent;
        
        CONCRT_COREASSERT(count == maxCount);

        DWORD timeout = INFINITE;

        for(;;)
        {
            DWORD result = WaitForMultipleObjectsEx(count, hObjects, FALSE, timeout, FALSE);
            DWORD index = (result == WAIT_TIMEOUT) ? 0 : (result - WAIT_OBJECT_0);

            if (index == 0)
            {
                bool done = m_poller.DoPolling();

                //
                // Poll every interval
                //
                timeout = done ? INFINITE : UMSBackgroundPoller::PollInterval();
            }
            else
            {
                CONCRT_COREASSERT(index == 1);

                // Proxy came back on the completion list
                PUMS_CONTEXT pUMSContext = NULL;
                if (!UMS::DequeueUmsCompletionListItems(m_pCompletionList, 0, &pUMSContext))
                    throw scheduler_resource_allocation_error(HRESULT_FROM_WIN32(GetLastError()));

                //
                // The completed thread should be the one we are running
                //
                UMSThreadProxy *pCompletedProxy = UMSThreadProxy::FromUMSContext(pUMSContext);
                CONCRT_COREASSERT(pCompletedProxy == pProxy && UMS::GetNextUmsListItem(pUMSContext) == NULL);
                return pCompletedProxy;
            }
        }
    }