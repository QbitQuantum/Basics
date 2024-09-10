int mythfile_close(int fileID)
{
    int result = -1;

    LOG(VB_FILE, LOG_DEBUG, LOC + QString("mythfile_close(%1)").arg(fileID));

    m_fileWrapperLock.lockForRead();
    if (m_ringbuffers.contains(fileID))
    {
        RingBuffer *rb = m_ringbuffers[fileID];
        m_ringbuffers.remove(fileID);
        delete rb;

        result = 0;
    }
    else if (m_remotefiles.contains(fileID))
    {
        RemoteFile *rf = m_remotefiles[fileID];
        m_remotefiles.remove(fileID);
        delete rf;

        result = 0;
    }
    else if (m_localfiles.contains(fileID))
    {
        close(m_localfiles[fileID]);
        m_localfiles.remove(fileID);
        result = 0;
    }
    m_fileWrapperLock.unlock();

    return result;
}