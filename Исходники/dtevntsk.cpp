STDMETHODIMP CPTEventSink::FireEvent(
    IN const MSP_EVENT_INFO * pEventInfo
    )
{
    LOG((MSP_TRACE, "CPTEventSink::FireEvent enter"));


    //
    // make sure we got a good mspeventitem structure
    //

    if( ! (void*)pEventInfo)
    {
        LOG((MSP_ERROR, "CPTEventSink::FireEvent -"
            "pEventItem is bad, returns E_POINTER"));
        return E_POINTER;
    }


    //
    // Create an MSPEVENTITEM
    //

    MSPEVENTITEM *pEventItem = AllocateEventItem();

    if (NULL == pEventItem)
    {
        LOG((MSP_ERROR, "CPTEventSink::FireEvent -"
            "failed to create MSPEVENTITEM. returning E_OUTOFMEMORY "));

        return E_OUTOFMEMORY;
    }


    //
    // make a shallow copy of the structure
    //

    pEventItem->MSPEventInfo = *pEventInfo;


    Lock();

    HRESULT hr = E_FAIL;

    if (NULL != m_pMSPStream)
    {
    
        //
        // nicely ask stream to process our event
        //

        LOG((MSP_TRACE, "CPTEventSink::FireEvent - passing event [%p] to the stream", pEventItem));


        AsyncEventStruct *pAsyncEvent = new AsyncEventStruct;

        if (NULL == pAsyncEvent)
        {
            LOG((MSP_ERROR, 
                "CPTEventSink::FireEvent - failed to allocate memory for AsyncEventStruct"));

            hr = E_OUTOFMEMORY;
        }
        else
        {

            //
            // stuff the structure with the addref'fed stream on which the 
            // event will be fired and the actual event to fire
            //

            ULONG ulRC =  m_pMSPStream->AddRef();

            if (1 == ulRC)
            {
                //
                // this is a workaround for a timing window: the stream could 
                // be in its desctructor while we are doing the addref. this 
                // condition is very-vary rare, as the timing window is very
                // narrow.
                //
                // the good thing is that stream destructor will not finish 
                // while we are here, because it will try to get event sink's 
                // critical section in its call to SetSinkStream() to set our 
                // stream pointer to NULL.
                // 
                // so if we detect that the refcount after our addref is 1, 
                // that would mean that the stream is in (or is about to start
                // executing its desctructor). in which case we should do 
                // nothing.
                //
                // cleanup and return a failure.
                //

                Unlock();

                LOG((MSP_ERROR, 
                    "CPTEventSink::FireEvent - stream is going away"));

                delete pAsyncEvent;
                pAsyncEvent = NULL;

                FreeEventItem(pEventItem);
                pEventItem = NULL;

                return TAPI_E_INVALIDSTREAM;
            }



            pAsyncEvent->pMSPStream = m_pMSPStream;

            pAsyncEvent->pEventItem = pEventItem;


            //
            // now use thread pool api to schedule the event for future async 
            // processing
            //

            BOOL bQueueSuccess = QueueUserWorkItem(
                CPTEventSink::FireEventCallBack,
                (void *)pAsyncEvent,
                WT_EXECUTEDEFAULT);

            if (!bQueueSuccess)
            {
                
                DWORD dwLastError = GetLastError();

                LOG((MSP_ERROR, 
                    "CPTEventSink::FireEvent - QueueUserWorkItem failed. LastError = %ld", dwLastError));


                //
                // undo the addref we did on the stream object. the event will 
                // be freed later
                //

                m_pMSPStream->Release();


                //
                // the event was not enqueued. delete now.
                //

                delete pAsyncEvent;
                pAsyncEvent = NULL;


                //
                // map the code and bail out
                //

                hr = HRESULT_FROM_WIN32(dwLastError);
            }
            else
            {
                
                //
                // log the event we have submitted, so we can match submission 
                // with processing from the log
                //

                LOG((MSP_TRACE,
                    "CPTEventSink::FireEvent - submitted event [%p]", pAsyncEvent));

                hr = S_OK;

            } // async event structure submitted

        } // async event structure allocated 

    } // msp stream exists
    else
    {
        hr = TAPI_E_INVALIDSTREAM;

        LOG((MSP_ERROR, 
            "CPTEventSink::FireEvent - stream pointer is NULL"));
    }


    Unlock();


    //
    // if we don't have a stream, or if the stream refused to process the 
    // event, cleanup and return an error
    //

    if (FAILED(hr))
    {

        LOG((MSP_ERROR, "CPTEventSink::FireEvent - call to HandleStreamEvent failed. hr = 0x%08x", hr));

        FreeEventItem(pEventItem);

        return hr;
    }


    LOG((MSP_TRACE, "CPTEventSink::FireEvent - exit"));

    return S_OK;
}