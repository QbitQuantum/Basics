int sys_cond_wait(u32 cond_id, u64 timeout)
{
	sys_cond.Log("sys_cond_wait(cond_id=%d, timeout=%lld)", cond_id, timeout);

	Cond* cond;
	if (!Emu.GetIdManager().GetIDData(cond_id, cond))
	{
		return CELL_ESRCH;
	}

	Mutex* mutex = cond->mutex;
	u32 tid = GetCurrentPPUThread().GetId();

	if (mutex->m_mutex.GetOwner() != tid)
	{
		return CELL_EPERM;
	}

	cond->m_queue.push(tid);

	mutex->recursive = 0;
	mutex->m_mutex.unlock(tid);

	u32 counter = 0;
	const u32 max_counter = timeout ? (timeout / 1000) : ~0;

	while (true)
	{
		/* switch (mutex->m_mutex.trylock(tid))
		{
		case SMR_OK: mutex->m_mutex.unlock(tid); break;
		case SMR_SIGNAL: mutex->recursive = 1; return CELL_OK;
		} */
		if (mutex->m_mutex.GetOwner() == tid)
		{
			_mm_mfence();
			mutex->recursive = 1;
			return CELL_OK;
		}

		Sleep(1);

		if (counter++ > max_counter)
		{
			cond->m_queue.invalidate(tid);
			return CELL_ETIMEDOUT;
		}
		if (Emu.IsStopped())
		{
			ConLog.Warning("sys_cond_wait(id=%d) aborted", cond_id);
			return CELL_OK;
		}
	}
}