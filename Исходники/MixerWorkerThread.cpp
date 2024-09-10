void MixerWorkerThread::JobQueue::wait()
{
	while (m_itemsDone < m_writeIndex)
	{
#if defined(LMMS_HOST_X86) || defined(LMMS_HOST_X86_64)
		_mm_pause();
#endif
	}
}