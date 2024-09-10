jlib_decl void PrintMemoryStatusLog()
{
#ifdef _WIN32
    MEMORYSTATUS mS;
    GlobalMemoryStatus(&mS);
    LOG(MCdebugInfo, unknownJob, "Available Physical Memory = %dK", (unsigned)(mS.dwAvailPhys/1024));
#ifdef FRAGMENTATION_CHECK
    // see if fragmented
    size32_t sz = MAX_TRY_SIZE;
    while (sz) {
        if (sz<mS.dwAvailPhys/4) {
            void *p=malloc(sz);
            if (p) {
                free(p);
                break;
            }
        }
        sz /= 2;
    }
    sz *= 2;
    if ((sz<MAX_TRY_SIZE)&&(sz<mS.dwAvailPhys/4)) {
        LOG(MCdebugInfo, unknownJob, "WARNING: Could not allocate block size %d", sz);
       _HEAPINFO hinfo;
       int heapstatus;
       hinfo._pentry = NULL;
       size32_t max=0;
       unsigned fragments=0;
       while( ( heapstatus = _heapwalk( &hinfo ) ) == _HEAPOK ) { 
           if (hinfo._useflag != _USEDENTRY) {
                if (hinfo._size>max)
                    max = hinfo._size;
                fragments++;
           }
       }
       LOG(MCdebugInfo, unknownJob, "Largest unused fragment = %d", max);
       LOG(MCdebugInfo, unknownJob, "Number of fragments = %d", fragments);
    }
#endif
#endif
}