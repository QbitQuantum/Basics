bool CAsynPipe::Connect(const CAddress& Address)
{
	m_eState = eAPS_Connecting;
	CPipeThread* pThread = CPipeThreadMgr::Inst()->GetThread(GetThreadId());
	(new(pThread) CPipeConnectJob(GetLocalID(), Address, pThread))->Add(pThread);
	return true;
}