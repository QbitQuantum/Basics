s32 cellSysutilCheckCallback(ppu_thread& ppu)
{
	cellSysutil.trace("cellSysutilCheckCallback()");

	const auto cbm = fxm::get_always<sysutil_cb_manager>();

	while (true)
	{
		std::lock_guard<std::mutex> lock(cbm->mutex);

		if (cbm->registered.empty())
		{
			break;
		}

		const auto func = std::move(cbm->registered.front());

		cbm->registered.pop();

		if (s32 res = func(ppu))
		{
			return res;
		}
	}

	return CELL_OK;
}