	static inline int64_t
	fenced_compare_exchange_strong(int64_t *ptr, int64_t expected, int64_t desired)
	{
		return _InterlockedCompareExchange64((void*)ptr, desired, expected);
	}