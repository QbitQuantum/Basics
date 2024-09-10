int cellSyncMutexLock(mem_ptr_t<CellSyncMutex> mutex)
{
	cellSync->Log("cellSyncMutexLock(mutex=0x%x)", mutex.GetAddr());

	if (!mutex.IsGood())
	{
		return CELL_SYNC_ERROR_NULL_POINTER;
	}
	if (mutex.GetAddr() % 4)
	{
		return CELL_SYNC_ERROR_ALIGN;
	}

	be_t<u16> old_order;
	while (true)
	{
		const u32 old_data = mutex->m_data();
		CellSyncMutex new_mutex;
		new_mutex.m_data() = old_data;

		old_order = new_mutex.m_order;
		new_mutex.m_order++;
		if (InterlockedCompareExchange(&mutex->m_data(), new_mutex.m_data(), old_data) == old_data) break;
	}

	while (old_order != mutex->m_freed) 
	{
		Sleep(1);
		if (Emu.IsStopped())
		{
			ConLog.Warning("cellSyncMutexLock(mutex=0x%x) aborted", mutex.GetAddr());
			break;
		}
	}
	_mm_mfence();
	return CELL_OK;
}