VOID
LsapMmFreeLastEntry(
    IN PLSAP_MM_FREE_LIST FreeList
    )

/*++

Routine Description:

    This function frees the last buffer appeended to the Free List.

Arguments:

    FreeList - Pointer to Free List.

--*/

{
    ULONG LastIndex = FreeList->UsedCount - 1;

    if (FreeList->Buffers[LastIndex].Options & LSAP_MM_MIDL) {

        MIDL_user_free( FreeList->Buffers[LastIndex].Buffer );

    } else {

        LsapFreeLsaHeap( FreeList->Buffers[LastIndex].Buffer );
    }

    FreeList->Buffers[LastIndex].Buffer = NULL;
    FreeList->UsedCount--;
}