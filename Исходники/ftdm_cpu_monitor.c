FT_DECLARE(ftdm_status_t) ftdm_cpu_get_system_idle_time(struct ftdm_cpu_monitor_stats *p, double *idle_percentage)
{
	FILETIME idleTime;
	FILETIME kernelTime;
	FILETIME userTime;
	int64_t i64UserTime;
	int64_t i64KernelTime;
	int64_t i64IdleTime;
  
	if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
		return FTDM_FAIL;
	}
  
	i64UserTime = (int64_t)userTime.dwLowDateTime | ((int64_t)userTime.dwHighDateTime << 32);

	i64KernelTime = (int64_t)kernelTime.dwLowDateTime | ((int64_t)kernelTime.dwHighDateTime << 32);

	i64IdleTime = (int64_t)idleTime.dwLowDateTime | ((int64_t)idleTime.dwHighDateTime << 32);

	if (p->valid_last_times) {
		int64_t i64User = i64UserTime - p->i64LastUserTime;
		int64_t i64Kernel = i64KernelTime - p->i64LastKernelTime;
		int64_t i64Idle = i64IdleTime - p->i64LastIdleTime;
		int64_t i64System = i64User + i64Kernel;
		*idle_percentage = 100.0 * i64Idle / i64System;
	} else {
		*idle_percentage = 100.0;
		p->valid_last_times = 1;
	}

	/* Remember current value for the next call */
	p->i64LastUserTime = i64UserTime;
	p->i64LastKernelTime = i64KernelTime;
	p->i64LastIdleTime = i64IdleTime;

	/* Success */
	return FTDM_SUCCESS;
}