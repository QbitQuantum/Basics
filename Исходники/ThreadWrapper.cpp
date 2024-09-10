void cThreadWrapper::Suspend()
{
	m_dwThreadSuspendCount = SuspendThread(m_hThreadHandle);
}