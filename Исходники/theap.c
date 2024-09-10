int
_cdecl
main(
    int argc,
    char *argv[]
    )
{
    PVOID Heap, AllocatedBlock;
    ULONG i, n;
    PTEST_HEAP_ENTRY p;
    BOOLEAN Result;
    NTSTATUS Status;
    RTL_HEAP_USAGE Usage;
    PRTL_HEAP_USAGE_ENTRY pEntries;
    ULONG TagBaseIndex, Tag;
    ULONG TotalAllocated;

    RtlInitializeHeapManager();
    memset( &Usage, 0, sizeof( Usage ) );

#if 0
    HeapParameters.Length = sizeof( HeapParameters );
    HeapParameters.DeCommitFreeBlockThreshold = 0x1000;
    HeapParameters.DeCommitTotalFreeThreshold = 0x4000;
    Heap = RtlCreateHeap( HEAP_GROWABLE | HEAP_NO_SERIALIZE,
                          NULL,
                          256 * 4096,
                          4096,
                          NULL,
                          &HeapParameters
                        );
#endif
    Heap = RtlCreateHeap( HEAP_GROWABLE | HEAP_NO_SERIALIZE | HEAP_CLASS_3,
                          NULL,
                          0x100000,
                          0x1000,
                          NULL,
                          NULL
                        );
    if (Heap == NULL) {
        fprintf( stderr, "THEAP: Unable to create heap.\n" );
        exit( 1 );
        }
    fprintf( stderr, "THEAP: Created heap at %x\n", Heap );
    DebugBreak();
    TagBaseIndex = RtlCreateTagHeap( Heap, 0, L"THEAP!",
                                     L"!HeapName\0"
                                     L"Tag1\0"
                                     L"Tag2\0"
                                     L"Tag3\0"
                                     L"Tag4\0"
                                     L"Tag5\0"
                                     L"Tag6\0"
                                     L"Tag7\0"
                                     L"Tag8\0"
                                     L"Tag9\0"
                                     L"Tag10\0"
                                     L"Tag11\0"
                                     L"Tag12\0"
                                     L"Tag13\0"
                                     L"Tag14\0"
                                     L"Tag15\0"
                                     L"Tag16\0"
                                     L"Tag17\0"
                                     L"Tag18\0"
                                     L"Tag19\0"
                                     L"Tag20\0"
                                     L"Tag21\0"
                                     L"Tag22\0"
                                     L"Tag23\0"
                                     L"Tag24\0"
                                     L"Tag25\0"
                                     L"Tag26\0"
                                     L"Tag27\0"
                                     L"Tag28\0"
                                     L"Tag29\0"
                                     L"Tag30\0"
                                     L"Tag31\0"
                                     L"Tag32\0"
                                     L"Tag33\0"
                                     L"Tag34\0"
                                     L"Tag35\0"
                                     L"Tag36\0"
                                     L"Tag37\0"
                                     L"Tag38\0"
                                     L"Tag39\0"
                                     L"Tag40\0"
                                     L"Tag41\0"
                                     L"Tag42\0"
                                     L"Tag43\0"
                                     L"Tag44\0"
                                     L"Tag45\0"
                                     L"Tag46\0"
                                     L"Tag47\0"
                                     L"Tag48\0"
                                     L"Tag49\0"
                                     L"Tag50\0"
                                     L"Tag51\0"
                                     L"Tag52\0"
                                     L"Tag53\0"
                                     L"Tag54\0"
                                     L"Tag55\0"
                                     L"Tag56\0"
                                     L"Tag57\0"
                                     L"Tag58\0"
                                     L"Tag59\0"
                                     L"Tag60\0"
                                   );

    NumberOfHeapEntries = 1000;
    HeapEntries = VirtualAlloc( NULL,
                                NumberOfHeapEntries * sizeof( *HeapEntries ),
                                MEM_COMMIT,
                                PAGE_READWRITE
                              );
    if (HeapEntries == NULL) {
        fprintf( stderr, "THEAP: Unable to allocate space.\n" );
        exit( 1 );
        }

    RtlpHeapValidateOnCall=TRUE;
    // RtlpHeapStopOnAllocate=0x350f88;
    // RtlpHeapStopOnReAlloc=0x710040;

    TotalAllocated = 0;
    while (TotalAllocated < (2 * 1024 * 1024)) {
        i = RtlUniform( &Seed ) % NumberOfHeapEntries;
        if (RtlUniform( &Seed ) % 100) {
            n = RtlUniform( &Seed ) % REASONABLE_HEAP_ALLOC;
            }
        else {
            n = RtlUniform( &Seed ) % MAX_HEAP_ALLOC;
            }

#if 0
        Usage.Length = sizeof( Usage );
        Status = RtlUsageHeap( Heap, HEAP_USAGE_ALLOCATED_BLOCKS , &Usage );
        if (NT_SUCCESS( Status )) {
            if (Status == STATUS_MORE_ENTRIES) {
                pEntries = Usage.AddedEntries;
                while (pEntries) {
                    fprintf( stderr,
                             "Added: %08x %06x\n",
                             pEntries->Address,
                             pEntries->Size
                           );
                    pEntries = pEntries->Next;
                    }

                pEntries = Usage.RemovedEntries;
                while (pEntries) {
                    fprintf( stderr,
                             "Freed: %08x %06x\n",
                             pEntries->Address,
                             pEntries->Size
                           );
                    pEntries = pEntries->Next;
                    }
                }

            fprintf( stderr, "%08x  %08x  %08x  %08x  ",
                             Usage.BytesAllocated, Usage.BytesCommitted,
                             Usage.BytesReserved, Usage.BytesReservedMaximum
                   );
            }
        else {
            fprintf( stderr, "RtlUsageHeap failed with status %x\n", Status );
            DebugBreak();
            }

        if (i < 60) {
            Tag = (TagBaseIndex + i + 1) << 16;
            }
        else {
            Tag = 0;
            }
#endif
        Tag = 0;
        p = &HeapEntries[ i ];
        if (p->AllocatedBlock == NULL) {
            TotalAllocated += n;
            p->AllocatedBlock = RtlAllocateHeap( Heap, Tag, n );
            fprintf( stderr, "Allocated %06x bytes at %08x\n", n, p->AllocatedBlock );
            if (p->AllocatedBlock != NULL) {
                p->Size = n;
                }
            else {
                DebugBreak();
                }
            }
        else
        if (RtlUniform( &Seed ) & 1) {
            TotalAllocated -= p->Size;
            TotalAllocated += n;
            AllocatedBlock = RtlReAllocateHeap( Heap, Tag, p->AllocatedBlock, n );
            fprintf( stderr, "ReAlloced %06x bytes at %08x to %06x bytes at %08x\n",
                     p->Size,
                     p->AllocatedBlock,
                     n,
                     AllocatedBlock
                   );
            if (AllocatedBlock != NULL) {
                p->AllocatedBlock = AllocatedBlock;
                p->Size = n;
                }
            else {
                DebugBreak();
                }
            }
        else {
            TotalAllocated -= p->Size;
            Result = RtlFreeHeap( Heap, 0, p->AllocatedBlock );
            fprintf( stderr, "Freed     %06x bytes at %08x\n",
                     p->Size,
                     p->AllocatedBlock
                   );
            if (Result) {
                p->AllocatedBlock = NULL;
                p->Size = 0;
                }
            else {
                DebugBreak();
                }
            }

        }

    RtlResetHeap( Heap, 0 );
    RtlValidateHeap( Heap, 0, NULL );

    return 0;
}