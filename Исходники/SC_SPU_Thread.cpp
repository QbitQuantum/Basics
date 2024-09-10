//178
int sys_spu_thread_group_join(u32 id, mem32_t cause, mem32_t status)
{
	sc_spu.Warning("sys_spu_thread_group_join(id=0x%x, cause_addr=0x%x, status_addr=0x%x)", id, cause.GetAddr(), status.GetAddr());

	SpuGroupInfo* group_info;
	if(!Emu.GetIdManager().GetIDData(id, group_info))
	{
		return CELL_ESRCH;
	}

	if (_InterlockedCompareExchange(&group_info->lock, 1, 0)) //get lock
	{
		return CELL_EBUSY;
	}

	cause = SYS_SPU_THREAD_GROUP_JOIN_ALL_THREADS_EXIT;
	status = 0; //unspecified because of ALL_THREADS_EXIT

	for(int i=0; i<g_spu_group_thr_count; i++)
	{
		if(group_info->threads[i])
		{
			while (!group_info->threads[i]->IsStopped()) Sleep(1);
		}
	}

	_InterlockedExchange(&group_info->lock, 0); //release lock
	return CELL_OK;
}