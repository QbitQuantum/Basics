//==============================================================================
Bool Barrier::wait()
{
	ANKI_ASSERT(m_impl);
	BarrierImpl& barrier = *reinterpret_cast<BarrierImpl*>(m_impl);

	EnterCriticalSection(&barrier.m_mtx);
	U32 gen = barrier.m_generation;

	if(--barrier.m_count == 0)
	{
		++barrier.m_generation;
		barrier.m_count = barrier.m_threshold;
		WakeAllConditionVariable(&barrier.m_cvar);
		LeaveCriticalSection(&barrier.m_mtx);
		return true;
	}

	while(gen == barrier.m_generation)
	{
		SleepConditionVariableCS(&barrier.m_cvar, &barrier.m_mtx, INFINITE);
	}

	LeaveCriticalSection(&barrier.m_mtx);
	return false;
}