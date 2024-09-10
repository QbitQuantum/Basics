/*
 * Disables the cache.
 */
void fscache_disable(void)
{
	struct fscache *cache;

	if (!core_fscache)
		return;

	/* update the thread specific fscache initialization */
	cache = fscache_getcache();
	if (!cache)
		BUG("fscache_disable() called on a thread where fscache has not been initialized");
	if (!cache->enabled)
		BUG("fscache_disable() called on an fscache that is already disabled");
	cache->enabled--;
	if (!cache->enabled) {
		TlsSetValue(dwTlsIndex, NULL);
		trace_printf_key(&trace_fscache, "fscache_disable: lstat %u, opendir %u, "
			"total requests/misses %u/%u\n",
			cache->lstat_requests, cache->opendir_requests,
			cache->fscache_requests, cache->fscache_misses);
		mem_pool_discard(cache->mem_pool, 0);
		hashmap_free(&cache->map, 0);
		free(cache);
	}

	/* update the global fscache initialization */
	EnterCriticalSection(&fscache_cs);
	initialized--;
	if (!initialized) {
		/* reset opendir and lstat to the original implementations */
		opendir = dirent_opendir;
		lstat = mingw_lstat;
	}
	LeaveCriticalSection(&fscache_cs);

	trace_printf_key(&trace_fscache, "fscache: disable\n");
	return;
}