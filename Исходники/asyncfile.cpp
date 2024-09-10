bool AsyncFile::waitForReadyRead(int msecs)
{
//    qDebug() << "waitForReadyRead";
    DWORD dwWaitOvpOprn = WaitForSingleObjectEx(overlapped.overlapped.hEvent, msecs, true);
//    qDebug() << "waitForReadyRead finished" << errorMessage(dwWaitOvpOprn);
    switch (dwWaitOvpOprn) {
    case WAIT_FAILED:
        return false;
    case WAIT_OBJECT_0:
        return true;
    case WAIT_TIMEOUT:
        return false;
    }

//    if( m_bAborted )
//    {
//        return FALSE;
//    }

    return true;
}