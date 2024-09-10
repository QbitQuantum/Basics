wStreamPool* StreamPool_New(BOOL synchronized, size_t defaultSize)
{
	wStreamPool* pool = NULL;

	pool = (wStreamPool*) malloc(sizeof(wStreamPool));

	if (pool)
	{
		ZeroMemory(pool, sizeof(wStreamPool));

		pool->synchronized = synchronized;
		pool->defaultSize = defaultSize;

		InitializeCriticalSectionAndSpinCount(&pool->lock, 4000);

		pool->aSize = 0;
		pool->aCapacity = 32;
		pool->aArray = (wStream**) malloc(sizeof(wStream*) * pool->aCapacity);
		ZeroMemory(pool->aArray, sizeof(wStream*) * pool->aCapacity);

		pool->uSize = 0;
		pool->uCapacity = 32;
		pool->uArray = (wStream**) malloc(sizeof(wStream*) * pool->uCapacity);
		ZeroMemory(pool->uArray, sizeof(wStream*) * pool->uCapacity);
	}

	return pool;
}