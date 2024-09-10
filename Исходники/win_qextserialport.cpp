void Win_QextSerialPort::monitorCommEvent()
{
    DWORD eventMask = 0;

    ResetEvent(m_Overlap.hEvent);
    if (!WaitCommEvent(m_WinHandle, & eventMask, & m_Overlap))
    {
        if (GetLastError() != ERROR_IO_PENDING)
        {
            qCritical("WaitCommEvent error %ld\n", GetLastError());
        }
    }

    if (WaitForSingleObject(m_Overlap.hEvent, INFINITE) == WAIT_OBJECT_0) 
    {
        //overlap event occured
        DWORD undefined;
        if (!GetOverlappedResult(m_WinHandle, & m_Overlap, & undefined, false)) 
        {
            qWarning("Comm event overlapped error %ld", GetLastError());
            return;
        }
        if (eventMask & EV_RXCHAR) 
        {
            if (sender() != this)
                emit readyRead();
        }
        if (eventMask & EV_TXEMPTY) 
        {
            DWORD numBytes;
            GetOverlappedResult(m_WinHandle, & m_OverlapWrite, & numBytes, true);
            m_pBytesToWriteLock->lockForWrite();

            if (sender() != this)
            {
                emit bytesWritten(bytesToWrite());
            }

            m_BytesToWrite = 0;
            m_pBytesToWriteLock->WriteUnlock();
        }
        if (eventMask & EV_DSR)
        {
            if (lineStatus() & LS_DSR)
            {
                emit dsrChanged(true);
            }
            else
            {
                emit dsrChanged(false);
            }
        }
    }
}