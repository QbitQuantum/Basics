s32 sys_lwcond_wait(PPUThread& ppu, vm::ptr<sys_lwcond_t> lwcond, u64 timeout)
{
	sysPrxForUser.trace("sys_lwcond_wait(lwcond=*0x%x, timeout=0x%llx)", lwcond, timeout);

	const be_t<u32> tid = ppu.get_id();

	const vm::ptr<sys_lwmutex_t> lwmutex = lwcond->lwmutex;

	if (lwmutex->vars.owner.load() != tid)
	{
		// if not owner of the mutex
		return CELL_EPERM;
	}

	// save old recursive value
	const be_t<u32> recursive_value = lwmutex->recursive_count;

	// set special value
	lwmutex->vars.owner = lwmutex_reserved;
	lwmutex->recursive_count = 0;

	// call the syscall
	s32 res = _sys_lwcond_queue_wait(ppu, lwcond->lwcond_queue, lwmutex->sleep_queue, timeout);

	if (res == CELL_OK || res == CELL_ESRCH)
	{
		if (res == CELL_OK)
		{
			lwmutex->all_info--;
		}

		// restore owner and recursive value
		const auto old = lwmutex->vars.owner.exchange(tid);
		lwmutex->recursive_count = recursive_value;

		if (old != lwmutex_reserved)
		{
			throw EXCEPTION("Locking failed (lwmutex=*0x%x, owner=0x%x)", lwmutex, old);
		}

		return res;
	}

	if (res == CELL_EBUSY || res == CELL_ETIMEDOUT)
	{
		const s32 res2 = sys_lwmutex_lock(ppu, lwmutex, 0);

		if (res2 == CELL_OK)
		{
			// if successfully locked, restore recursive value
			lwmutex->recursive_count = recursive_value;

			return res == CELL_EBUSY ? CELL_OK : res;
		}

		return res2;
	}

	if (res == CELL_EDEADLK)
	{
		// restore owner and recursive value
		const auto old = lwmutex->vars.owner.exchange(tid);
		lwmutex->recursive_count = recursive_value;

		if (old != lwmutex_reserved)
		{
			throw EXCEPTION("Locking failed (lwmutex=*0x%x, owner=0x%x)", lwmutex, old);
		}

		return CELL_ETIMEDOUT;
	}

	throw EXCEPTION("Unexpected syscall result (lwcond=*0x%x, result=0x%x)", lwcond, res);
}