    // Flushes all available packets over the network... returns number of bytes sent
    bool AsyncStream::Flush(Socket &s)
    {
        OVR_CAPTURE_CPU_ZONE(AsyncStream_Flush);

        bool okay = true;

        // Take ownership of any pending data...
        SpinLock(m_bufferLock);
        Swap(m_cacheBegin, m_flushBegin);
        Swap(m_cacheTail,  m_flushTail);
        Swap(m_cacheEnd,   m_flushEnd);
        SpinUnlock(m_bufferLock);

        // Signal that we just swapped in a new buffer... wake up any threads that were waiting on us to flush.
        m_gate.Open();

        if(m_flushTail > m_flushBegin)
        {
            const size_t sendSize = (size_t)(m_flushTail-m_flushBegin);

            // first send stream header...
            StreamHeaderPacket streamheader;
            streamheader.threadID   = m_threadID;
            streamheader.streamSize = sendSize;
            okay = s.Send(&streamheader, sizeof(streamheader));

            // This send payload...
            okay = okay && s.Send(m_flushBegin, sendSize);
            m_flushTail = m_flushBegin;
        }

        OVR_CAPTURE_ASSERT(m_flushBegin == m_flushTail); // should be empty at this point...

        return okay;
    }