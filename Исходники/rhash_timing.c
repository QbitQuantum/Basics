/**
 * Set process priority and affinity to use all cpu's but the first one.
 * This improves benchmark results on a multi-cpu systems.
 *
 * @deprecated This function shall be removed soon.
 */
static void benchmark_cpu_init(void)
{
	DWORD_PTR dwProcessMask, dwSysMask, dwDesired;

	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	if ( GetProcessAffinityMask(GetCurrentProcess(), &dwProcessMask, &dwSysMask) ) {
		dwDesired = dwSysMask & (dwProcessMask & ~1); /* remove the first processor */
		dwDesired = (dwDesired ? dwDesired : dwSysMask & ~1);
		if (dwDesired != 0) {
			SetProcessAffinityMask(GetCurrentProcess(), dwDesired);
		}
	}
}