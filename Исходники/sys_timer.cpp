s32 sys_timer_sleep(u32 sleep_time)
{
	sys_timer.trace("sys_timer_sleep(sleep_time=%d)", sleep_time);

	const u64 start_time = get_system_time();

	const u64 useconds = sleep_time * 1000000ull;

	u64 passed;

	while (useconds > (passed = get_system_time() - start_time) + 1000)
	{
		CHECK_EMU_STATUS;

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	
	if (useconds > passed)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(useconds - passed));
	}

	return CELL_OK;
}