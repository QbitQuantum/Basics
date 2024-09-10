int sys_lwcond_wait(mem_ptr_t<sys_lwcond_t> lwcond, u64 timeout)
{
	sys_lwcond.Log("sys_lwcond_wait(lwcond_addr=0x%x, timeout=%lld)", lwcond.GetAddr(), timeout);

	if (!lwcond.IsGood())
	{
		return CELL_EFAULT;
	}

	SleepQueue* sq;
	if (!Emu.GetIdManager().GetIDData((u32)lwcond->lwcond_queue, sq))
	{
		return CELL_ESRCH;
	}

	mem_ptr_t<sys_lwmutex_t> mutex(lwcond->lwmutex);
	u32 tid_le = GetCurrentPPUThread().GetId();
	be_t<u32> tid = tid_le;

	if (mutex->mutex.owner.GetOwner() != tid)
	{
		return CELL_EPERM; // caller must own this lwmutex
	}

	sq->push(tid_le);

	mutex->recursive_count = 0;
	mutex->mutex.owner.unlock(tid);

	u32 counter = 0;
	const u32 max_counter = timeout ? (timeout / 1000) : ~0;
	while (true)
	{
		/* switch (mutex->trylock(tid))
		{
		case SMR_OK: mutex->unlock(tid); break;
		case SMR_SIGNAL: return CELL_OK;
		} */
		if (mutex->mutex.owner.GetOwner() == tid)
		{
			_mm_mfence();
			mutex->recursive_count = 1;
			return CELL_OK;
		}

		Sleep(1);

		if (counter++ > max_counter)
		{
			sq->invalidate(tid_le);
			return CELL_ETIMEDOUT;
		}
		if (Emu.IsStopped())
		{
			ConLog.Warning("sys_lwcond_wait(sq=%d) aborted", (u32)lwcond->lwcond_queue);
			return CELL_OK;
		}
	}
}