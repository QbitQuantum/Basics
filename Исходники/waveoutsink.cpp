void WaveOutDevice::writeSamples(const void *data, size_t length,
                                 size_t nsamples)
{
    void *bp = const_cast<void *>(data);
    if (m_asbd.mBitsPerChannel <= 8) {
        util::convert_sign(static_cast<uint32_t *>(bp),
                           nsamples * m_asbd.mChannelsPerFrame);
    }
    unsigned obpc = m_asbd.mBytesPerFrame / m_asbd.mChannelsPerFrame;
    unsigned nbpc = ((m_asbd.mBitsPerChannel + 7) & ~7) >> 3;
    util::pack(bp, &length, obpc, nbpc);
    size_t pos = m_ibuffer.size();
    m_ibuffer.resize(pos + length);
    std::memcpy(&m_ibuffer[pos], bp, length);
    if (m_ibuffer.size() < m_asbd.mSampleRate / NUMBUFFERS)
        return;

    DWORD n = WaitForMultipleObjects(util::sizeof_array(m_events), m_events,
                                     0, INFINITE);
    n -= WAIT_OBJECT_0;
    ResetEvent(m_events[n]);
    WAVEHDR& wh = m_packets[n];
    TRYMM(waveOutUnprepareHeader(m_device.get(), &wh, sizeof wh));
    m_buffers[n] = m_ibuffer;
    m_ibuffer.clear();
    wh.lpData = &m_buffers[n][0];
    wh.dwBufferLength = m_buffers[n].size();
    TRYMM(waveOutPrepareHeader(m_device.get(), &wh, sizeof wh));
    TRYMM(waveOutWrite(m_device.get(), &wh, sizeof wh));
}