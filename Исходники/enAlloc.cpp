void enAllocKill(void* m)
{
// Check m:

	if(m == 0)
		return;

// Update total:

	Block* b = (Block*) m - 1;

	#ifdef WIN32
	_InterlockedExchangeAdd(&Size, (long) (- b->Size));
	#else
	Size += (long) - b->Size;
	#endif

// Free block:

	free(b);
}