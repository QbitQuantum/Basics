DWORD CBaseMuxerFilter::ThreadProc()
{
    SetThreadPriority(m_hThread, THREAD_PRIORITY_ABOVE_NORMAL);

    POSITION pos;

    for (;;) {
        DWORD cmd = GetRequest();

        switch (cmd) {
            default:
            case CMD_EXIT:
                CAMThread::m_hThread = nullptr;
                Reply(S_OK);
                return 0;

            case CMD_RUN:
                m_pActivePins.RemoveAll();
                m_pPins.RemoveAll();

                pos = m_pInputs.GetHeadPosition();
                while (pos) {
                    CBaseMuxerInputPin* pPin = m_pInputs.GetNext(pos);
                    if (pPin->IsConnected()) {
                        m_pActivePins.AddTail(pPin);
                        m_pPins.AddTail(pPin);
                    }
                }

                m_rtCurrent = 0;

                Reply(S_OK);

                MuxInit();

                try {
                    MuxHeaderInternal();

                    while (!CheckRequest(nullptr) && m_pActivePins.GetCount()) {
                        if (m_State == State_Paused) {
                            Sleep(10);
                            continue;
                        }

                        CAutoPtr<MuxerPacket> pPacket = GetPacket();
                        if (!pPacket) {
                            Sleep(1);
                            continue;
                        }

                        if (pPacket->IsTimeValid()) {
                            m_rtCurrent = pPacket->rtStart;
                        }

                        if (pPacket->IsEOS()) {
                            m_pActivePins.RemoveAt(m_pActivePins.Find(pPacket->pPin));
                        }

                        MuxPacketInternal(pPacket);
                    }

                    MuxFooterInternal();
                } catch (HRESULT hr) {
                    CComQIPtr<IMediaEventSink>(m_pGraph)->Notify(EC_ERRORABORT, hr, 0);
                }

                m_pOutput->DeliverEndOfStream();

                pos = m_pRawOutputs.GetHeadPosition();
                while (pos) {
                    m_pRawOutputs.GetNext(pos)->DeliverEndOfStream();
                }

                m_pActivePins.RemoveAll();
                m_pPins.RemoveAll();

                break;
        }
    }

    ASSERT(0); // this function should only return via CMD_EXIT

    CAMThread::m_hThread = nullptr;
    return 0;
}