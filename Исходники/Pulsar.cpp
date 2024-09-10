static int iomtr_set_cpu_affinity(unsigned long affinity_mask)
{
	int res = -1;
	
#if defined(IOMTR_OS_LINUX)
	cpu_set_t s;
	int i, j;
	unsigned long t = 1;
	
	if (!affinity_mask) {
		affinity_mask = 1;
	}
	i = sizeof(unsigned long) * 8;
	if (i > CPU_SETSIZE) {
		i = CPU_SETSIZE;
	}
	CPU_ZERO (&s);
	for (j = 0; j < i; j++)
		if ((t << j) & affinity_mask) {
			CPU_SET(j, &s);
			break;
		}
	/* Developer Note:
	 *
	 * If meet compiling error about following line in a relatively old Linux system,
	 * please try "sched_setaffinity(getpid(), &s)" instead.
	 */
	if (sched_setaffinity(getpid(), CPU_SETSIZE, &s) < 0) {
		cout << "Set CPU affinity fail." << errno << endl;
		if (errno == ENOSYS) {
			cout << "Warning: System does not support set CPU affinity." << endl;
			cout << "Be sure to check if measured results are reasonable." << endl;
		}
	} else {
#ifdef _DEBUG
		cout << "Set CPU affinity sucessfully." << endl;
#endif
	}

#elif defined(IOMTR_OS_WIN32) || defined(IOMTR_OS_WIN64)
	if (!affinity_mask) {
		affinity_mask = 1;
	}

	// not &affinity_mask, MSDN API Doc error.
	res = SetProcessAffinityMask(GetCurrentProcess(), affinity_mask);
	if (!res) {
		res = GetLastError();
		cout << "Set cpu affinity fail with" << res << endl;
		// default to CPU 1
		res = SetProcessAffinityMask(GetCurrentProcess(), 1);
	}
#elif defined(IOMTR_OS_NETWARE) || defined(IOMTR_OS_SOLARIS)
	// nop	
#else
 #warning ===> WARNING: You have to do some coding here to get the port done!
#endif
	return res;
}