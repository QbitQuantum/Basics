/***************************************************
StartShutdown
    purpose
        Tells the thread that it should shutdown
        immediatly, also sets a shutdown flag that
        the rest of the class must monitor
    params
        None
    return
        UTE_SUCCESS  if successful - this does not mean the thread has
            shutdown, but that the process has started
****************************************************/
int CUT_WSThread::StartShutdown(){
    WSACancelBlockingCall();
    m_nShutDownFlag = TRUE;
    return OnError(UTE_SUCCESS);
}