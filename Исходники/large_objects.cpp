LargeMemoryBlock *LargeObjectCacheImpl<Props>::get(uintptr_t currTime, size_t size)
{
    MALLOC_ASSERT( size%Props::CacheStep==0, ASSERT_TEXT );
    int idx = sizeToIdx(size);
    bool setNonEmpty = false;

    LargeMemoryBlock *lmb = bin[idx].get(size, currTime, &setNonEmpty);
    // Setting to true is possible out of lock. As bitmask is used only for cleanup,
    // the lack of consistency is not violating correctness here.
    if (setNonEmpty)
        bitMask.set(idx, true);
    if (lmb) {
        MALLOC_ITT_SYNC_ACQUIRED(bin+idx);
        STAT_increment(getThreadId(), ThreadCommonCounters, allocCachedLargeObj);
    }
    return lmb;
}