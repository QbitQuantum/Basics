s32 sys_spu_thread_write_snr(u32 id, u32 number, u32 value)
{
	sys_spu.trace("sys_spu_thread_write_snr(id=0x%x, number=%d, value=0x%x)", id, number, value);

	LV2_LOCK;

	const auto thread = idm::get<SPUThread>(id);

	if (!thread)
	{
		return CELL_ESRCH;
	}

	if (number > 1)
	{
		return CELL_EINVAL;
	}

	const auto group = thread->tg.lock();

	if (!group)
	{
		throw EXCEPTION("Invalid SPU thread group");
	}

	//if (group->state < SPU_THREAD_GROUP_STATUS_WAITING || group->state > SPU_THREAD_GROUP_STATUS_RUNNING) // ???
	//{
	//	return CELL_ESTAT;
	//}

	thread->push_snr(number, value);

	return CELL_OK;
}