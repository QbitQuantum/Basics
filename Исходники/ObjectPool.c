wObjectPool* ObjectPool_New(BOOL synchronized)
{
	wObjectPool* pool = NULL;

	pool = (wObjectPool*) calloc(1, sizeof(wObjectPool));

	if (pool)
	{
		pool->capacity = 32;
		pool->size = 0;
		pool->array = (void**) calloc(pool->capacity, sizeof(void*));
		if (!pool->array)
		{
			free(pool);
			return NULL;
		}
		pool->synchronized = synchronized;

		if (pool->synchronized)
			InitializeCriticalSectionAndSpinCount(&pool->lock, 4000);

	}

	return pool;
}