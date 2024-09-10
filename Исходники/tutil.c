PLATAPI void plat_cv_wait_timed(plat_thread_cv_t* cv, plat_thread_mutex_t* mutex, ts_time_t timeout) {
	DWORD millis;

	millis = (timeout == TS_TIME_MAX)
					? INFINITE
					: timeout / T_MS;

	SleepConditionVariableCS(&cv->tcv_cond_var,
							 &mutex->tm_crit_section,
							 millis);
}