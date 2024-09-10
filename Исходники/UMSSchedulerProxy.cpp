    /// <summary>
    ///     Returns all items on the UMS completion list.  Note that this indirectly manipulates the transfer list.  This
    ///     will literally dequeue everything from BOTH lists and hand it to the caller.
    /// </summary>
    /// <returns>
    ///     The first UMSThreadProxy on the completion list.
    /// </returns>
    UMSThreadProxy *UMSSchedulerProxy::GetCompletionListItems()
    {
        SweepCompletionList();

        InterlockedExchange(&m_pushedBackCount, 0);

        //
        // Yep, there's a race where we could inadvertently set the event for an item which is pushed in this window from another thread
        // but popped right here.  The worst thing that comes out of said race is an extra awakening of a virtual processor to check
        // an empty completion list.
        //

        PSLIST_ENTRY pItem = InterlockedFlushSList(&m_transferList);
        UMSThreadProxy *pProxy = pItem == NULL ? NULL : CONTAINING_RECORD(pItem, UMSThreadProxy, m_listEntry);

#if defined(_DEBUG)
        UMSThreadProxy *pTrav = pProxy;
        while (pTrav != NULL)
        {
            pTrav->m_UMSDebugBits |= UMS_DEBUGBIT_PULLEDFROMTRANSFERLIST;
            pTrav = static_cast<UMSThreadProxy *>(pTrav->GetNextUnblockNotification());
        }
#endif // _DEBUG

        return pProxy;
    }