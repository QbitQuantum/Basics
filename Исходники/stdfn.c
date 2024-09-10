/*
 * This call tries to evenly balance the affinities for an array of
 * num_threads, according to the number of cores at our disposal...
 */
BOOL SetThreadAffinity(DWORD_PTR* thread_affinity, size_t num_threads)
{
	size_t i, j, pc;
	DWORD_PTR affinity, dummy;

	memset(thread_affinity, 0, num_threads * sizeof(DWORD_PTR));
	if (!GetProcessAffinityMask(GetCurrentProcess(), &affinity, &dummy))
		return FALSE;
	uuprintf("\r\nThread affinities:");
	uuprintf("  avail:\t%s", printbitslz(affinity));

	// If we don't have enough virtual cores to evenly spread our load forget it
	pc = popcnt64(affinity);
	if (pc < num_threads)
		return FALSE;

	// Spread the affinity as evenly as we can
	thread_affinity[num_threads - 1] = affinity;
	for (i = 0; i < num_threads - 1; i++) {
		for (j = 0; j < pc / num_threads; j++) {
			thread_affinity[i] |= affinity & (-1LL * affinity);
			affinity ^= affinity & (-1LL * affinity);
		}
		uuprintf("  thr_%d:\t%s", i, printbitslz(thread_affinity[i]));
		thread_affinity[num_threads - 1] ^= thread_affinity[i];
	}
	uuprintf("  thr_%d:\t%s", i, printbitslz(thread_affinity[i]));
	return TRUE;
}