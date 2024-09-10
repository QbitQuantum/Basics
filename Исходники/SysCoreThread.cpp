void SysCoreThread::ExecuteTaskInThread()
{
	Threading::EnableHiresScheduler(); // Note that *something* in SPU2-X and GSdx also set the timer resolution to 1ms.
	m_sem_event.WaitWithoutYield();

	m_mxcsr_saved.bitmask = _mm_getcsr();

	PCSX2_PAGEFAULT_PROTECT {
		while(true) {
			StateCheckInThread();
			DoCpuExecute();
		}
	} PCSX2_PAGEFAULT_EXCEPT;
}