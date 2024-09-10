void refManagerImpl::releaseStrong()
{
	if (m_strongCount.decrement() <= 0)
		deleteObject();

	releaseWeak();
}