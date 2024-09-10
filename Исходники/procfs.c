static int stat_gettext(int tag, char *buf)
{
	char *original_buf = buf;
	/* TODO: Support more than one processors */
	LARGE_INTEGER idle_time, kernel_time, user_time;
	GetSystemTimes((FILETIME *)&idle_time, (FILETIME *)&kernel_time, (FILETIME *)&user_time);
	uint64_t user = user_time.QuadPart / (TICKS_PER_SECOND / USER_HZ);
	uint64_t nice = 0;
	uint64_t system = kernel_time.QuadPart / (TICKS_PER_SECOND / USER_HZ);
	uint64_t idle = idle_time.QuadPart / (TICKS_PER_SECOND / USER_HZ);
	system -= idle; /* KernelTime includes IdleTime */
	uint64_t iowait = 0;
	uint64_t irq = 0;
	uint64_t softirq = 0;
	uint64_t steal = 0, guest = 0, guest_nice = 0;

	buf += ksprintf(buf, "cpu   %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu\n",
		user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice);
	buf += ksprintf(buf, "intr  %llu\n", 0);
	buf += ksprintf(buf, "swap  %llu %llu\n", 0);
	uint64_t ctxt = 0;
	buf += ksprintf(buf, "ctxt  %llu\n", ctxt);
	/* Boot time */
	SYSTEM_TIMEOFDAY_INFORMATION tod_info;
	NtQuerySystemInformation(SystemTimeOfDayInformation, &tod_info, sizeof(tod_info), NULL);
	uint64_t btime = filetime_to_unix_sec((FILETIME *)&tod_info.BootTime);
	buf += ksprintf(buf, "btime %llu\n", btime);
	uint64_t processes = 0;
	buf += ksprintf(buf, "processes %llu\n", processes);
	int procs_running = 1;
	buf += ksprintf(buf, "procs_running %d\n", procs_running);
	int procs_blocked = 0;
	buf += ksprintf(buf, "procs_blocked %d\n", procs_blocked);
	return buf - original_buf;
}