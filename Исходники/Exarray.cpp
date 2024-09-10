void    FCDECL  exaligned_mrealloc (void** p,
                 size_t blocksize, size_t blockalign,
                 size_t memset_start, size_t memset_stop)
{
    void* pp = *p;

    if (blocksize)
    {
        while (blocksize > EXCALCBLOCKSIZE_MAX - blockalign ||
              (pp = _aligned_realloc (*p, blocksize, blockalign))
              == NULL)
        {
            void (*pvf) (void) = set_exalloc_handler (NULL);
            set_exalloc_handler (pvf);
            if (pvf != NULL) { (*pvf)(); continue; }

            (*exalloc_status.size_handler)();
            exalloc_status.nBlocksFailed++;
            return;
        }

        if (((size_t)pp & (blockalign - 1)) != 0) {}

        if (pp != NULL)
        {
            exalloc_status.nBlocksAllocated++;
        }

        if (memset_stop > memset_start)
        {
             memset ((char*)pp + memset_start, 0,
                   memset_stop - memset_start);
        }

        if (exalloc_status.pMinAlloc - 1 >= (char*) pp)
        {
            exalloc_status.pMinAlloc = (char*)pp;
        }
        if (exalloc_status.pMaxAlloc < (char*)pp + blocksize)
        {
            exalloc_status.pMaxAlloc = (char*)pp + blocksize;
        }
    }

    else if (pp)
    {
        _aligned_free (pp); pp = NULL;
        exalloc_status.nBlocksAllocated--;
    }

    *p = pp;
}