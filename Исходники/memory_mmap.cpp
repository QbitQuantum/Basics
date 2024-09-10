void OpMmapSegment::ReleaseUnused(void)
{
    if ( unused_pages > unused_pages_threshold )
    {
        unsigned int half_unused_pages_threshold = unused_pages_threshold / 2;

        for ( int cls = max_size_class; cls >= 0; cls-- )
        {
            unsigned int anchor = OP_MMAP_UNUSED_SIZECLASS + cls;

            for (;;)
            {
                if ( unused_pages <= half_unused_pages_threshold )
                    return;

                unsigned int idx = page_handle[anchor].prev;

                if ( idx < OP_MMAP_ANCHOR_COUNT )
                    break;

                OP_ASSERT(page_handle[idx].flag == OP_MMAP_FLAG_UNUSED);
                unsigned int pages = page_handle[idx].size;
                void* ptr = (void*)(base + idx * pagesize);
                OpMemory_VirtualFree(mseg, ptr, pages * pagesize,
                                     (OpMemoryClass)unusedtype);

                Unlink(idx);
                Merge(OP_MMAP_FLAG_RESERVED, 0, idx);

                unused_pages -= pages;
            }
        }
    }
}