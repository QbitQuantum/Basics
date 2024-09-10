int process_time(pid_t pid, time64_t* createTime, time64_t* kernelTime, time64_t* userTime)
{
#if defined(_WIN32)
	HANDLE handle;
	FILETIME ftCreateTime, ftExitTime, ftKernelTime, ftUserTime;
	SYSTEMTIME stime;
	FILETIME ftime;

	ULONGLONG rt;
	ULARGE_INTEGER kt, ut;

	memset(&ftUserTime, 0xCC, sizeof(ftUserTime));
	handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if(!handle)
		return (int)GetLastError();
	
	if(!GetProcessTimes(handle, &ftCreateTime, &ftExitTime, &ftKernelTime, &ftUserTime))
	{
		CloseHandle(handle);
		return (int)GetLastError();
	}
	CloseHandle(handle);
	
	GetSystemTime(&stime);
	SystemTimeToFileTime(&stime, &ftime);

	kt = FILETIME2UINT64(&ftime);
	ut = FILETIME2UINT64(&ftCreateTime);
	rt = kt.QuadPart > ut.QuadPart ? kt.QuadPart-ut.QuadPart : 0; // for resolution problem
	kt = FILETIME2UINT64(&ftKernelTime);
	ut = FILETIME2UINT64(&ftUserTime);

	*createTime = rt/10000; // nanosecond -> millisecond
	*userTime = ut.QuadPart/10000;
	*kernelTime = kt.QuadPart/10000;
	return 0;
#else
	char content[2*1024] = {0};

	int r;
	unsigned long int utime, stime;
	unsigned long long starttime;
	float uptime = 0.0f;

	sprintf(content, "/proc/%d/stat", pid);
	r = tools_cat(content, content, sizeof(content));
	if(r < 0)
		return r;

	// linux: man proc
	// cat proc/self/stat
	// (1-pid-%d, 2-filename-%s, 3-state-%c, 4-ppid-%d, 5-pgrp-%d, 
	//	6-session-%d, 7-tty_nr-%d, 8-tpgid-%d, 9-flags-%u, 10-minflt-%lu, 
	//	11-cminflt-%lu, 12-majflt-%lu, 13-cmajflt-%lu, 14-utime-%lu, 15-stime-%lu, 
	//	16-cutime-%ld, 17-cstime-%ld, 18-priority-%ld, 19-nice-%ld, 20-num_threads-%ld, 
	//	21-itrealvalue-%ld, 22-starttime-%llu, 23-vsize-%lu, 24-rss-%ld, 25-rsslim-%lu, 
	//	26-startcode-%lu, 27-endcode-%lu, 28-startstack-%lu, 29-kstkesp-%lu, 30-kstkeip-%lu, 
	//	31-signal-%lu, 32-blocked-%lu, 33-sigignore-%lu, 34-sigcatch-%lu, 35-wchan-%lu, 
	//	36-nswap-%lu, 37-cnswap-%lu, 38-exit_signal-%d, 39-processor-%d, 40-rt_priority-%u, 
	//	41-policy-%u, 42-delayacct_blkio_ticks-%llu, 43-guest_time-%lu, 44-cguest_time-%ld)
	if(3 != sscanf(content, 
		// warning: use of assignment suppression and length modifier together in gnu_scanf format [-Wformat]
		//"%*d %*s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %lu %lu %*ld %*ld %*ld %*ld %*ld %*ld %llu", 
		"%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu %*d %*d %*d %*d %*d %*d %llu", 
		&utime, &stime, &starttime))
		return -(int)EINVAL;

	assert(sysconf(_SC_CLK_TCK) == HZ);
	system_uptime(&uptime);
	*createTime = (time64_t)uptime*1000 - starttime*1000/HZ; // jiffies -> millisecond
	*userTime = utime * 1000 / HZ;
	*kernelTime = stime * 1000 / HZ;
	return 0;
#endif
}