error_code sys_lwmutex_destroy(ppu_thread& ppu, vm::ptr<sys_lwmutex_t> lwmutex)
{
	sysPrxForUser.trace("sys_lwmutex_destroy(lwmutex=*0x%x)", lwmutex);

	if (g_cfg.core.hle_lwmutex)
	{
		return sys_mutex_destroy(lwmutex->sleep_queue);
	}

	// check to prevent recursive locking in the next call
	if (lwmutex->vars.owner.load() == ppu.id)
	{
		return CELL_EBUSY;
	}

	// attempt to lock the mutex
	if (error_code res = sys_lwmutex_trylock(ppu, lwmutex))
	{
		return res;
	}

	// call the syscall
	if (error_code res = _sys_lwmutex_destroy(lwmutex->sleep_queue))
	{
		// unlock the mutex if failed
		sys_lwmutex_unlock(ppu, lwmutex);

		return res;
	}

	// deleting succeeded
	lwmutex->vars.owner.release(lwmutex_dead);

	return CELL_OK;
}