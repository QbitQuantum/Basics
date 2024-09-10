//! \brief Reallocates \a sz bytes of memory on a 16 byte boundary, optionally tracking the allocation
void* xsAlignedRealloc(void* ptr, size_t sz)
{
#ifdef TRACK_ALLOCS
	lastFreeIdx = (lastAlignedFreeIdx + 1) & (TRACK_ALLOCS-1);
	lastAlignedFrees[lastAlignedFreeIdx] = ptr;

	ptr = _aligned_realloc(ptr, sz, 16);
	lastAlignedAllocIdx = (lastAlignedAllocIdx + 1) & (TRACK_ALLOCS-1);
	lastAlignedAllocs[lastAlignedAllocIdx] = ptr;
	return ptr;
#else
	return _aligned_realloc(ptr, sz, 16);
#endif
}