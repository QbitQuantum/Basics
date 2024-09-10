void CKDMTCriticalSection::Stop()
{
	if (!ReleaseSemaphore(m_hSemaphore, 1, NULL))
		TRACE(_T("CKDMTCriticalSection::Stop release semaphore failed\n"));
}