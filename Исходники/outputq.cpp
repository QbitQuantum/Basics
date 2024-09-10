//
//  COutputQueue Constructor :
//
//  Determines if a thread is to be created and creates resources
//
//     pInputPin  - the downstream input pin we're queueing samples to
//
//     phr        - changed to a failure code if this function fails
//                  (otherwise unchanges)
//
//     bAuto      - Ask pInputPin if it can block in Receive by calling
//                  its ReceiveCanBlock method and create a thread if
//                  it can block, otherwise not.
//
//     bQueue     - if bAuto == FALSE then we create a thread if and only
//                  if bQueue == TRUE
//
//     lBatchSize - work in batches of lBatchSize
//
//     bBatchEact - Use exact batch sizes so don't send until the
//                  batch is full or SendAnyway() is called
//
//     lListSize  - If we create a thread make the list of samples queued
//                  to the thread have this size cache
//
//     dwPriority - If we create a thread set its priority to this
//
COutputQueue::COutputQueue(
             IPin         *pInputPin,          //  Pin to send stuff to
             HRESULT      *phr,                //  'Return code'
             BOOL          bAuto,              //  Ask pin if queue or not
             BOOL          bQueue,             //  Send through queue
             LONG          lBatchSize,         //  Batch
             BOOL          bBatchExact,        //  Batch exactly to BatchSize
             LONG          lListSize,
             DWORD         dwPriority,
             bool          bFlushingOpt        // flushing optimization
            ) : m_lBatchSize(lBatchSize),
                m_bBatchExact(bBatchExact && (lBatchSize > 1)),
                m_hThread(NULL),
                m_hSem(NULL),
                m_List(NULL),
                m_pPin(pInputPin),
                m_ppSamples(NULL),
                m_lWaiting(0),
                m_pInputPin(NULL),
                m_bSendAnyway(FALSE),
                m_nBatched(0),
                m_bFlushing(FALSE),
                m_bFlushed(TRUE),
                m_bFlushingOpt(bFlushingOpt),
                m_bTerminate(FALSE),
                m_hEventPop(NULL),
                m_hr(S_OK)
{
    ASSERT(m_lBatchSize > 0);


    if (FAILED(*phr)) {
        return;
    }

    //  Check the input pin is OK and cache its IMemInputPin interface

    *phr = pInputPin->QueryInterface(IID_IMemInputPin, (void **)&m_pInputPin);
    if (FAILED(*phr)) {
        return;
    }

    // See if we should ask the downstream pin

    if (bAuto) {
        HRESULT hr = m_pInputPin->ReceiveCanBlock();
        if (SUCCEEDED(hr)) {
            bQueue = hr == S_OK;
        }
    }

    //  Create our sample batch

    m_ppSamples = new PMEDIASAMPLE[m_lBatchSize];
    if (m_ppSamples == NULL) {
        *phr = E_OUTOFMEMORY;
        return;
    }

    //  If we're queueing allocate resources

    if (bQueue) {
        DbgLog((LOG_TRACE, 2, TEXT("Creating thread for output pin")));
        m_hSem = CreateSemaphore(NULL, 0, 0x7FFFFFFF, NULL);
        if (m_hSem == NULL) {
            DWORD dwError = GetLastError();
            *phr = AmHresultFromWin32(dwError);
            return;
        }
        m_List = new CSampleList(NAME("Sample Queue List"),
                                 lListSize,
                                 FALSE         // No lock
                                );
        if (m_List == NULL) {
            *phr = E_OUTOFMEMORY;
            return;
        }


        DWORD dwThreadId;
        m_hThread = CreateThread(NULL,
                                 0,
                                 InitialThreadProc,
                                 (LPVOID)this,
                                 0,
                                 &dwThreadId);
        if (m_hThread == NULL) {
            DWORD dwError = GetLastError();
            *phr = AmHresultFromWin32(dwError);
            return;
        }
        SetThreadPriority(m_hThread, dwPriority);
    } else {
        DbgLog((LOG_TRACE, 2, TEXT("Calling input pin directly - no thread")));
    }
}