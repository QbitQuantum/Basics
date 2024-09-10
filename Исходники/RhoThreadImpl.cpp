void CRhoThreadImpl::start(IRhoRunnable* pRunnable, IRhoRunnable::EPriority ePriority)
{
    m_hThread = ::CreateThread(NULL, 0, runProc, pRunnable, 0, NULL);
    setThreadPriority(ePriority);
}