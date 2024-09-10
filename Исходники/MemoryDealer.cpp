SimpleBestFitAllocator::chunk_t* SimpleBestFitAllocator::dealloc(size_t start)
{
    start = start / kMemoryAlign;
    chunk_t* cur = mList.head();
    while (cur) {
        if (cur->start == start) {
            LOG_FATAL_IF(cur->free,
                "block at offset 0x%08lX of size 0x%08lX already freed",
                cur->start*kMemoryAlign, cur->size*kMemoryAlign);

            // merge freed blocks together
            chunk_t* freed = cur;
            cur->free = 1;
            do {
                chunk_t* const p = cur->prev;
                chunk_t* const n = cur->next;
                if (p && (p->free || !cur->size)) {
                    freed = p;
                    p->size += cur->size;
                    mList.remove(cur);
                    delete cur;
                }
                cur = n;
            } while (cur && cur->free);

            #ifndef NDEBUG
                if (!freed->free) {
                    dump_l("dealloc (!freed->free)");
                }
            #endif
            LOG_FATAL_IF(!freed->free,
                "freed block at offset 0x%08lX of size 0x%08lX is not free!",
                freed->start * kMemoryAlign, freed->size * kMemoryAlign);

            return freed;
        }
        cur = cur->next;
    }
    return 0;
}