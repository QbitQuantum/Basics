HRESULT CMSPThread::QueueWorkItem(
    LPTHREAD_START_ROUTINE Function,
    PVOID Context,
    BOOL  fSynchronous
    )
{
    LOG((MSP_TRACE, "CMSPThread::QueueWorkItem - enter"));


    //
    // Create a command block for this.
    //

    COMMAND_QUEUE_ITEM * pItem = new COMMAND_QUEUE_ITEM;

    if ( ! pItem )
    {
        LOG((MSP_ERROR, "CMSPThread::QueueWorkItem - "
            "can't allocate new queue item - exit E_OUTOFMEMORY"));

        return E_OUTOFMEMORY;
    }


    //
    // Create an event to wait on if this is a synchronous work item.
    // Otherwise the thread proc gets a NULL event handle and it knows not to
    // signal it since it's an asynchronous work item.
    //

    TCHAR *ptczEventName = NULL;

#if DBG

    static LONG lSequenceNumber = 0;


    //
    // in debug build, use named events
    //

    TCHAR tszEventName[MAX_PATH];

    InterlockedIncrement(&lSequenceNumber);


    //
    // identify events by the address of the correspoding queue item, and by 
    // the sequence number
    //

    _stprintf_s(tszEventName,
        _T("CMSPThread_QueueWorkitemEvent_pid[0x%lx]_CMSPThread[%p]_Event[%p]_eventNumber[%lu]"),
        GetCurrentProcessId(), this, pItem, lSequenceNumber);

    LOG((MSP_TRACE, "CMSPThread::QueueWorkItem - creating event[%S]", tszEventName));

    ptczEventName = &tszEventName[0];

#endif


    HANDLE hEvent = NULL;

    if (fSynchronous)
    {
        hEvent = ::CreateEvent(NULL, 
                               FALSE,           // flag for manual-reset event 
                               FALSE,           // initial state is not set.
                               ptczEventName);  // No name in release, named in debug

        if ( hEvent == NULL )
        {
            LOG((MSP_ERROR, "CMSPThread::QueueWorkItem - "
                "Can't create the Job Done event"));

            delete pItem;
            pItem = NULL;

            return E_FAIL;
        }
    }


    //
    // we already have the q item, now initialize it.
    //

    pItem->node.cmd        = WORK_ITEM;
    pItem->node.pfn        = Function;
    pItem->node.pContext   = Context;
    pItem->node.hEvent     = hEvent;


    //
    // Put the command block on the queue. The queue is protected by a
    // critical section.
    //

    m_QueueLock.Lock();
    InsertTailList(&m_CommandQueue, &(pItem->link));


    //
    // Signal the thread to process the command.
    //

    if (SignalThreadProc() == 0)
    {

        //
        // failed to signal processing thread
        // cleanup and return error
        //

        
        //
        // remove the queue entry we have submitted
        //

        RemoveTailList(&m_CommandQueue);


        //
        // unlock the queue so other threads can use it
        //

        m_QueueLock.Unlock();


        //
        // close handle and delete pItem that we have created -- 
        // no one else is going to do this for us
        //

        if (NULL != hEvent)
        {
            ::CloseHandle(hEvent);
            hEvent = NULL;
        }

        delete pItem;
        pItem = NULL;


        LOG((MSP_ERROR, "CMSPThread::QueueWorkItem - "
            "can't signal the thread"));

        return E_FAIL;
    }


    //
    // unlock the event queue, so it can be used by processing and other 
    // threads
    //

    m_QueueLock.Unlock();


    //
    // If this is a sychronous work item, wait for it to complete and
    // then close the event handle.
    //
    // FEATUREFEATURE: Rather than creating and deleting an event for each
    // work item, have a cache of events that can be reused.
    //

    if (fSynchronous)
    {
        LOG((MSP_TRACE, "CMSPThread::QueueWorkItem - "
            "blocked waiting for synchronous work item to complete"));
        
        // Wait for the synchronous work item to complete.

        HANDLE hEvents[2];
        DWORD dwEvent;

        hEvents[0] = hEvent;
        hEvents[1] = m_hThread;

        dwEvent = WaitForMultipleObjects( 
            2,
            hEvents,
            FALSE,
            INFINITE);

        switch (dwEvent)
        {
        case WAIT_OBJECT_0 + 0:
            break;

        case WAIT_OBJECT_0 + 1:
            LOG((MSP_ERROR, "CMSPThread::QueueWorkItem - "
                "thread exited"));

            //
            // if the item is still in the queue, remove it (since the thread 
            // won't)
            //

            m_QueueLock.Lock();
            
            if (IsNodeOnList(&m_CommandQueue, &(pItem->link)))
            {
                RemoveEntryList(&(pItem->link));
                delete pItem;
            }

            m_QueueLock.Unlock();
          

            //
            // time to close event and fail
            //

            ::CloseHandle(hEvent);

            return E_FAIL;        

        default:
            LOG((MSP_ERROR, "CMSPThread::QueueWorkItem - "
                "WaitForSingleObject failed"));
        }

        ::CloseHandle(hEvent);
    }

    LOG((MSP_TRACE, "CMSPThread::QueueWorkItem - exit S_OK"));

    return S_OK;
}