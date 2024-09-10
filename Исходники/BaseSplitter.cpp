DWORD CBaseSplitterFilter::ThreadProc()
{
    if (m_pSyncReader) {
        m_pSyncReader->SetBreakEvent(GetRequestHandle());
    }

    if (!DemuxInit()) {
        for (;;) {
            DWORD cmd = GetRequest();
            if (cmd == CMD_EXIT) {
                CAMThread::m_hThread = nullptr;
            }
            Reply(S_OK);
            if (cmd == CMD_EXIT) {
                return 0;
            }
        }
    }

    m_eEndFlush.Set();
    m_fFlushing = false;

    for (DWORD cmd = DWORD_ERROR; ; cmd = GetRequest()) {
        if (cmd == CMD_EXIT) {
            m_hThread = nullptr;
            Reply(S_OK);
            return 0;
        }

        SetThreadPriority(m_hThread, m_priority = THREAD_PRIORITY_NORMAL);

        m_rtStart = m_rtNewStart;
        m_rtStop = m_rtNewStop;

        DemuxSeek(m_rtStart);

        if (cmd != DWORD_ERROR) {
            Reply(S_OK);
        }

        m_eEndFlush.Wait();

        m_pActivePins.RemoveAll();

        POSITION pos = m_pOutputs.GetHeadPosition();
        while (pos && !m_fFlushing) {
            CBaseSplitterOutputPin* pPin = m_pOutputs.GetNext(pos);
            if (pPin->IsConnected() && pPin->IsActive()) {
                m_pActivePins.AddTail(pPin);
                pPin->DeliverNewSegment(m_rtStart, m_rtStop, m_dRate);
            }
        }

        do {
            m_bDiscontinuitySent.RemoveAll();
        } while (!DemuxLoop());

        pos = m_pActivePins.GetHeadPosition();
        while (pos && !CheckRequest(&cmd)) {
            m_pActivePins.GetNext(pos)->QueueEndOfStream();
        }
    }
    UNREACHABLE_CODE(); // we should only exit via CMD_EXIT
#pragma warning(pop)
}