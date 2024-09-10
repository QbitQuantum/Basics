DWORD OutputMonitor::__ProcessImpl()
{
    DWORD dret;
    int ret;
    HANDLE hWaitHandle[2];

    hWaitHandle[0] = this->m_hDBWinDataReady;
    hWaitHandle[1] = this->m_ThreadControl.exitevt;

    /*make sure buffer ready for client handle*/
    SetEvent(this->m_hDBWinBufferReady);

    while(this->m_ThreadControl.running) {
        dret = WaitForMultipleObjectsEx(2,hWaitHandle,FALSE,INFINITE,TRUE);
        if(dret == WAIT_OBJECT_0) {
            ret = this->__HandleBufferIn();
            if(ret < 0) {
                ret = GETERRNO();
                dret = -ret;
                goto out;
            }
        } else if(dret == WAIT_FAILED || dret == WAIT_ABANDONED) {
            ret = GETERRNO();
            dret = -ret;
            goto out;
        }
    }

    ret = 0;

out:
    this->m_ThreadControl.exited = 1;
    SETERRNO(ret);
    return dret;
}