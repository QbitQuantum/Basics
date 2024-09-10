// Stop
void COpcThreadPool::Stop()
{
	COpcLock cLock(*this);

	// delete any remaining messages.
	while (m_cQueue.GetCount() > 0)
	{
		COpcMessage* pMessage = m_cQueue.RemoveHead();
		delete pMessage;
	}
	
	// close handle.
	CloseHandle(m_hEvent);
	m_hEvent = NULL;
}