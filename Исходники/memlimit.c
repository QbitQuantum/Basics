static int
memlimit_rlimit(size_t * memlimit)
{
	SYSTEM_INFO sysinfo;
	HANDLE hproc;
	SIZE_T dwmin = 0;
	SIZE_T dwmax = 345; /* Seems like the default max from msdn */

	sysinfo.dwPageSize = 4096;	/* Default to 4K */
	GetSystemInfo(&sysinfo);

	hproc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
						FALSE, _getpid());
	if (!GetProcessWorkingSetSize(hproc, &dwmin, &dwmax)) {
#ifdef DEBUG
		fprintf(stderr, "failed to get max working set size. E=%d\n",
				GetLastError());
#endif
	}
	CloseHandle(hproc);
	*memlimit = dwmax * sysinfo.dwPageSize;
	return (0);
}