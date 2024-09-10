void FutureMallocAllocator::Free(void * p)
{
	_aligned_free(p);
}