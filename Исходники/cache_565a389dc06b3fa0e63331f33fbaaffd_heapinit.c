int __cdecl _heap_init (
        int mtflag
        )
{
#if defined _M_AMD64 || defined _M_IA64
        // HEAP_NO_SERIALIZE is incompatible with the LFH heap
        mtflag = 1;
#endif  /* defined _M_AMD64 || defined _M_IA64 */
        //  Initialize the "big-block" heap first.
        if ( (_crtheap = HeapCreate( mtflag ? 0 : HEAP_NO_SERIALIZE,
                                     BYTES_PER_PAGE, 0 )) == NULL )
            return 0;

#ifndef _WIN64
        // Pick a heap, any heap
        __active_heap = __heap_select();

        if ( __active_heap == __V6_HEAP )
        {
            //  Initialize the small-block heap
            if (__sbh_heap_init(MAX_ALLOC_DATA_SIZE) == 0)
            {
                HeapDestroy(_crtheap);
                _crtheap=NULL;
                return 0;
            }
        }
#ifdef CRTDLL
        else if ( __active_heap == __V5_HEAP )
        {
            if ( __old_sbh_new_region() == NULL )
            {
                HeapDestroy( _crtheap );
                _crtheap=NULL;
                return 0;
            }
        }
#endif  /* CRTDLL */
#elif defined _M_AMD64 || defined _M_IA64
        {
            // Enable the Low Fragmentation Heap for AMD64 and IA64 by default
            // It's the 8 byte overhead heap, and has generally better
            // performance charateristics than the 16 byte overhead heap,
            // particularly for apps that perform lots of small allocations
            ULONG HeapType = 2;
            HeapSetInformation(_crtheap, HeapCompatibilityInformation,
                               &HeapType, sizeof(HeapType));
        }
#endif  /* defined _M_AMD64 || defined _M_IA64 */

        return 1;
}