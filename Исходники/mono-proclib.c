gint32
mono_cpu_usage (MonoCpuUsageState *prev)
{
	gint32 cpu_usage = 0;
	gint64 cpu_total_time;
	gint64 cpu_busy_time;

#ifndef HOST_WIN32
	struct rusage resource_usage;
	gint64 current_time;
	gint64 kernel_time;
	gint64 user_time;

	if (getrusage (RUSAGE_SELF, &resource_usage) == -1) {
		g_error ("getrusage() failed, errno is %d (%s)\n", errno, strerror (errno));
		return -1;
	}

	current_time = mono_100ns_ticks ();
	kernel_time = resource_usage.ru_stime.tv_sec * 1000 * 1000 * 10 + resource_usage.ru_stime.tv_usec * 10;
	user_time = resource_usage.ru_utime.tv_sec * 1000 * 1000 * 10 + resource_usage.ru_utime.tv_usec * 10;

	cpu_busy_time = (user_time - (prev ? prev->user_time : 0)) + (kernel_time - (prev ? prev->kernel_time : 0));
	cpu_total_time = (current_time - (prev ? prev->current_time : 0)) * mono_cpu_count ();

	if (prev) {
		prev->kernel_time = kernel_time;
		prev->user_time = user_time;
		prev->current_time = current_time;
	}
#else
	guint64 idle_time;
	guint64 kernel_time;
	guint64 user_time;

	if (!GetSystemTimes ((FILETIME*) &idle_time, (FILETIME*) &kernel_time, (FILETIME*) &user_time)) {
		g_error ("GetSystemTimes() failed, error code is %d\n", GetLastError ());
		return -1;
	}

	cpu_total_time = (gint64)((user_time - (prev ? prev->user_time : 0)) + (kernel_time - (prev ? prev->kernel_time : 0)));
	cpu_busy_time = (gint64)(cpu_total_time - (idle_time - (prev ? prev->idle_time : 0)));

	if (prev) {
		prev->idle_time = idle_time;
		prev->kernel_time = kernel_time;
		prev->user_time = user_time;
	}
#endif

	if (cpu_total_time > 0 && cpu_busy_time > 0)
		cpu_usage = (gint32)(cpu_busy_time * 100 / cpu_total_time);

	g_assert (cpu_usage >= 0);
	g_assert (cpu_usage <= 100);

	return cpu_usage;
}