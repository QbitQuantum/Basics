void ConfigStorage::acquire()
{
	fb_assert(m_recursive >= 0);
	const ThreadId currTID = getThreadId();

	if (m_mutexTID == currTID)
		m_recursive++;
	else
	{
		m_sharedMemory->mutexLock();

		fb_assert(m_recursive == 0);
		m_recursive = 1;

		fb_assert(m_mutexTID == 0);
		m_mutexTID = currTID;
	}
}